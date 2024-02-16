#include <lex.hpp>
#include <cstdio>
#include <cctype>
#include <stdexcept>

///=============================================================================

libj::Token::Token(libj::TokenType type, std::variant<std::string, double> value)
{
    m_type = type;
    m_value = value;
}

libj::TokenType libj::Token::type() const
{
    return m_type;
}

const std::variant<std::string, double> &libj::Token::val() const
{
    return m_value;
}

std::string libj::Token::serialize(bool human_readable) const
{
    if (human_readable)
    {
        switch (m_type)
        {
        case TokenType::Eof:
            return "Eof";
        case TokenType::Define:
            return "Define";
        case TokenType::Extern:
            return "Extern";
        case TokenType::Identifier:
            return "Identifier(" + std::get<std::string>(m_value) + ")";
        case TokenType::Number:
            return "Number(" + std::to_string(std::get<double>(m_value)) + ")";
        case TokenType::Comment:
            return "Comment(" + std::get<std::string>(m_value) + ")";
        case TokenType::Operator:
            return "Operator(" + std::get<std::string>(m_value) + ")";
        case TokenType::Unknown:
            return "Unknown(" + std::get<std::string>(m_value) + ")";
        }
    }
    else
    {
        switch (m_type)
        {
        case TokenType::Eof:
            return "E()";
        case TokenType::Define:
            return "D()";
        case TokenType::Extern:
            return "X()";
        case TokenType::Identifier:
            return "I(" + std::get<std::string>(m_value) + ")";
        case TokenType::Number:
            return "N(" + std::to_string(std::get<double>(m_value)) + ")";
        case TokenType::Comment:
            return "C(" + std::get<std::string>(m_value) + ")";
        case TokenType::Operator:
            return "O(" + std::get<std::string>(m_value) + ")";
        case TokenType::Unknown:
            return "U(" + std::get<std::string>(m_value) + ")";
        }
    }

    return "Unknown";
}

///=============================================================================

libj::Lexer::Lexer()
{
    m_src = nullptr;
    m_buf_pos = 1024;
    m_buffer = std::vector<char>(m_buf_pos);
    m_tok = std::nullopt;
    m_last = 0;
}

char libj::Lexer::getc()
{
    if (m_buf_pos >= m_buffer.size())
    {
        size_t read;
        if ((read = fread(m_buffer.data(), 1, m_buffer.size(), m_src)) == 0)
            return EOF;

        if (m_buffer.size() != read)
            m_buffer.resize(read);

        m_buf_pos = 0;
    }

    return m_buffer[m_buf_pos++];
}

bool libj::Lexer::set_source(FILE *src)
{
    if (src == nullptr)
        return false;

    m_src = src;

    if (fseek(m_src, 0, SEEK_SET) != 0)
        return false;

    return true;
}

libj::Token libj::Lexer::next()
{
    Token tok = peek();

    m_tok = std::nullopt;

    return tok;
}

libj::Token libj::Lexer::peek()
{
    if (m_tok.has_value())
        return m_tok.value();

    enum class LexState
    {
        Start,
        Identifier,
        Number,
        Comment,
    };

    LexState state = LexState::Start;
    std::string buffer;

    char c;

    while (true)
    {
        if (m_last != 0)
        {
            c = m_last;
            m_last = 0;
        }
        else
        {
            if ((c = getc()) == EOF)
                break;
        }

        switch (state)
        {
        case LexState::Start:
        {
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            {
                continue;
            }
            else if (c == '#')
            {
                state = LexState::Comment;
                continue;
            }
            else if (std::isalpha(c) || c == '_')
            {
                buffer += c;
                state = LexState::Identifier;
                continue;
            }
            else if (std::isdigit(c))
            {
                buffer += c;
                state = LexState::Number;
                continue;
            }
            else
            {
                for (const auto &op : operators)
                {
                    if (c == static_cast<char>(op))
                    {
                        m_tok = Token(TokenType::Operator, std::string(1, c));
                        return m_tok.value();
                    }
                }

                m_tok = Token(TokenType::Unknown, std::string(1, c));
                return m_tok.value();
            }
        }
        case LexState::Identifier:
        {
            if (std::isalnum(c) || c == '_')
            {
                buffer += c;
                continue;
            }

            if (buffer == "def")
            {
                m_tok = Token(TokenType::Define, "");
            }
            else if (buffer == "extern")
            {
                m_tok = Token(TokenType::Extern, "");
            }
            else
            {
                m_tok = Token(TokenType::Identifier, buffer);
            }

            m_last = c;
            return m_tok.value();
        }
        case LexState::Number:
        {
            if (std::isdigit(c) || c == '.')
            {
                buffer += c;
                continue;
            }

            try
            {
                m_tok = Token(TokenType::Number, std::stod(buffer));
            }
            catch (std::invalid_argument &)
            {
                m_tok = Token(TokenType::Unknown, buffer);
            }

            m_last = c;
            return m_tok.value();
        }
        case LexState::Comment:
        {
            if (c != '\n')
            {
                buffer += c;
                continue;
            }

            m_tok = Token(TokenType::Comment, buffer);
            m_last = c;
            return m_tok.value();
        }
        }
    }

    m_tok = Token(TokenType::Eof, "");
    return m_tok.value();
}