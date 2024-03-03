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

bool libj::PrepEngine::set_source(FILE *src)
{
    Lexer l;
    if (!l.set_source(src))
        return false;

    m_stack.push({l, src});
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

libj::Token libj::PrepEngine::read_token()
{
    libj::Token tok;

start:
    tok = m_stack.top().first.next();

    if (tok.type() == TokenType::Keyword && std::get<Keyword>(tok.val()) == Keyword::Import)
    {
        // Get Identifier
        tok = m_stack.top().first.next();
        if (tok.type() != TokenType::Identifier)
        {
            PREPMSG(tok, Err::ERROR, "Expected identifier after import");
            tok = Token(TokenType::Eof, "");
            return tok;
        }

        std::string filename = std::get<std::string>(tok.val());

        PREPMSG(tok, Err::DEBUG, "Requested import of file: %s", filename.c_str());

        // get next token
        tok = m_stack.top().first.next();
        if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
        {
            PREPMSG(tok, Err::ERROR, "Expected semicolon after import");
            return Token(TokenType::Eof, "");
        }

        PREPMSG(tok, Err::DEBUG, "Searching for file: %s in include directories [%s]", filename.c_str(), include_path.c_str());
        FILE *f = nullptr;
        for (auto &dir : m_include_dirs)
        {
            std::string path = dir + "/" + filename + ".j";
            if (!std::filesystem::exists(path))
                continue;

            f = fopen(path.c_str(), "r");
            if (f)
            {
                m_stack.push({Lexer(), f});
                m_stack.top().first.set_source(f);
            }
            else
            {
                PREPMSG(tok, Err::ERROR, "Could not open file: \"%s.j\" in include directories [%s]", filename.c_str(), include_path.c_str());
                tok = Token(TokenType::Eof, "");
                return tok;
            }
        }

        if (!f)
        {
            PREPMSG(tok, Err::ERROR, "Could not find file: \"%s.j\" in include directories [%s]", filename.c_str(), include_path.c_str());
            tok = Token(TokenType::Eof, "");
            return tok;
        }

        goto start;
    }
    else if (tok.type() == TokenType::Eof)
    {
        if (m_stack.size() == 1)
            return tok;

        fclose(m_stack.top().second);
        m_stack.pop();
        goto start;
    }

    return tok;
}
