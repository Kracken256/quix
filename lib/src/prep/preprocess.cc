#include <prep/preprocess.h>
#include <cstdio>
#include <cctype>
#include <stdexcept>
#include <cstring>
#include <iomanip>
#include <regex>
#include <cmath>
#include <iostream>
#include <error/message.h>
#include <macro.h>
#include <filesystem>

#define JLANG_HEADER_EXTENSION ".jh"

void libj::PrepEngine::addpath(const std::string &path)
{
    m_include_dirs.insert(path);

    include_path = "";
    for (auto &dir : m_include_dirs)
    {
        include_path += std::filesystem::absolute(dir).string();

        if (dir != *m_include_dirs.rbegin())
            include_path += ":";
    }
}

bool libj::PrepEngine::set_source(FILE *src, const std::string &filename)
{
    Lexer l;
    if (!l.set_source(src, filename))
        return false;

    m_stack.push({l, filename, src, {}});
    return true;
}

libj::Token libj::PrepEngine::next()
{
    Token tok = peek();
    m_tok = std::nullopt;
    return tok;
}

libj::Token libj::PrepEngine::peek()
{
    if (m_tok)
        return m_tok.value();

    m_tok = read_token();

    return m_tok.value();
}

bool libj::PrepEngine::handle_import()
{
    // Get Identifier
    Token tok = m_stack.top().lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        PREPMSG(tok, Err::ERROR, "Expected identifier after import");
        return false;
    }

    std::string filename = std::get<std::string>(tok.val());
    filename = std::regex_replace(filename, std::regex("::"), "/") + JLANG_HEADER_EXTENSION;

    PREPMSG(tok, Err::DEBUG, "Requested import of file: %s", filename.c_str());

    tok = m_stack.top().lexer.next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
    {
        PREPMSG(tok, Err::ERROR, "Expected semicolon after import");
        return false;
    }

    PREPMSG(tok, Err::DEBUG, "Searching for file: %s in include directories [%s]", filename.c_str(), include_path.c_str());
    std::string filepath;
    for (auto &dir : m_include_dirs)
    {
        std::string path = dir + "/" + filename;
        if (!std::filesystem::exists(path))
            continue;

        filepath = path;
        break;
    }

    if (filepath.empty())
    {
        PREPMSG(tok, Err::ERROR, "Could not find file: \"%s.j\" in include directories [%s]", filename.c_str(), include_path.c_str());
        return false;
    }

    filepath = std::filesystem::absolute(filepath).string();

    // circular include detection
    if (std::find(m_include_files.begin(), m_include_files.end(), filepath) != m_include_files.end())
    {
        std::string msg;
        for (auto &file : m_include_files)
            msg += "  -> " + file + "\n";
        msg += "  -> " + filepath + "\n";
        PREPMSG(tok, Err::ERROR, "Circular include detected: \n%s", msg.c_str());
        PREPMSG(tok, Err::ERROR, "Refusing to enter infinite loop. Try to split your dependencies into smaller files.");
        return false;
    }

    // don't double include in the same file
    if (!m_stack.top().already_included.contains(filepath))
    {
        FILE *f;

        if (!(f = fopen(filepath.c_str(), "r")))
        {
            PREPMSG(tok, Err::ERROR, "Could not open file: \"%s.j\" in include directories [%s]", filepath.c_str(), include_path.c_str());
            return false;
        }

        m_stack.top().already_included.insert(filepath);
        m_include_files.push_back(filepath);
        m_stack.push({Lexer(), filepath, f, {}});
        m_stack.top().lexer.set_source(f, filepath);
        return true;
    }
    else
    {
        PREPMSG(tok, Err::ERROR, feedback[PREP_DUPLICATE_IMPORT], m_stack.top().path.c_str(), filepath.c_str());
        return false;
    }

    return true;
}

libj::Token libj::PrepEngine::read_token()
{
    libj::Token tok;

start:
    tok = m_stack.top().lexer.next();

    if (tok.type() == TokenType::Keyword && std::get<Keyword>(tok.val()) == Keyword::Import)
    {
        if (handle_import())
            goto start;

        PREPMSG(tok, Err::ERROR, "Failed to handle import");
        tok = Token(TokenType::Eof, "");
    }
    else if (tok.type() == TokenType::MacroSingleLine || tok.type() == TokenType::MacroBlock)
    {
        goto start;
    }
    else if (tok.type() == TokenType::Eof)
    {
        if (m_stack.size() == 1)
            return tok;

        fclose(m_stack.top().file);
        m_include_files.pop_back();
        m_stack.pop();
        goto start;
    }

    return tok;
}
