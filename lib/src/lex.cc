#include <lex.hpp>
#include <cstdio>
#include <cctype>
#include <stdexcept>
#include <cstring>

///=============================================================================

std::map<int, std::vector<const char *>> libj::operators = {
    {1, {"<", ">", "=", "@", "-", "+", "*", "/", "%", "&", "|", "^", "~", "!", "?"}},
    {2, {"+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=", "<<", ">>", "==", "!=", "&&", "||", "^^", "<=", ">=", "++", "--"}},
    {3, {"^^=", "||=", "&&=", "<<=", ">>="}}};

static std::map<std::string, libj::Keyword> keyword_map = {
    {"subsystem", libj::Keyword::Subsystem},
    {"import", libj::Keyword::Import},
    {"export", libj::Keyword::Export},
    {"let", libj::Keyword::Let},
    {"var", libj::Keyword::Var},
    {"struct", libj::Keyword::Struct},
    {"region", libj::Keyword::Region},
    {"union", libj::Keyword::Union},
    {"packet", libj::Keyword::Packet},
    {"fn", libj::Keyword::Fn},
    {"typedef", libj::Keyword::Typedef},
    {"const", libj::Keyword::Const},
    {"static", libj::Keyword::Static},
    {"volatile", libj::Keyword::Volatile},
    {"enum", libj::Keyword::Enum},
    {"class", libj::Keyword::Class},
    {"bundle", libj::Keyword::Bundle},
    {"public", libj::Keyword::Public},
    {"private", libj::Keyword::Private},
    {"protected", libj::Keyword::Protected},
    {"override", libj::Keyword::Override},
    {"virtual", libj::Keyword::Virtual},
    {"abstract", libj::Keyword::Abstract},
    {"friend", libj::Keyword::Friend},
    {"interface", libj::Keyword::Interface},
    {"delete", libj::Keyword::Delete},
    {"if", libj::Keyword::If},
    {"else", libj::Keyword::Else},
    {"for", libj::Keyword::For},
    {"while", libj::Keyword::While},
    {"do", libj::Keyword::Do},
    {"switch", libj::Keyword::Switch},
    {"case", libj::Keyword::Case},
    {"default", libj::Keyword::Default},
    {"break", libj::Keyword::Break},
    {"continue", libj::Keyword::Continue},
    {"return", libj::Keyword::Return},
    {"retif", libj::Keyword::Retif},
    {"abortif", libj::Keyword::Abortif},
    {"retz", libj::Keyword::Retz},
    {"void", libj::Keyword::Void},
    {"null", libj::Keyword::Null},
    {"true", libj::Keyword::True},
    {"false", libj::Keyword::False}};

static std::map<libj::Keyword, std::string> keyword_map_inverse = {
    {libj::Keyword::Subsystem, "subsystem"},
    {libj::Keyword::Import, "import"},
    {libj::Keyword::Export, "export"},
    {libj::Keyword::Let, "let"},
    {libj::Keyword::Var, "var"},
    {libj::Keyword::Struct, "struct"},
    {libj::Keyword::Region, "region"},
    {libj::Keyword::Union, "union"},
    {libj::Keyword::Packet, "packet"},
    {libj::Keyword::Fn, "fn"},
    {libj::Keyword::Typedef, "typedef"},
    {libj::Keyword::Const, "const"},
    {libj::Keyword::Static, "static"},
    {libj::Keyword::Volatile, "volatile"},
    {libj::Keyword::Enum, "enum"},
    {libj::Keyword::Class, "class"},
    {libj::Keyword::Bundle, "bundle"},
    {libj::Keyword::Public, "public"},
    {libj::Keyword::Private, "private"},
    {libj::Keyword::Protected, "protected"},
    {libj::Keyword::Override, "override"},
    {libj::Keyword::Virtual, "virtual"},
    {libj::Keyword::Abstract, "abstract"},
    {libj::Keyword::Friend, "friend"},
    {libj::Keyword::Interface, "interface"},
    {libj::Keyword::Delete, "delete"},
    {libj::Keyword::If, "if"},
    {libj::Keyword::Else, "else"},
    {libj::Keyword::For, "for"},
    {libj::Keyword::While, "while"},
    {libj::Keyword::Do, "do"},
    {libj::Keyword::Switch, "switch"},
    {libj::Keyword::Case, "case"},
    {libj::Keyword::Default, "default"},
    {libj::Keyword::Break, "break"},
    {libj::Keyword::Continue, "continue"},
    {libj::Keyword::Return, "return"},
    {libj::Keyword::Retif, "retif"},
    {libj::Keyword::Abortif, "abortif"},
    {libj::Keyword::Retz, "retz"},
    {libj::Keyword::Void, "void"},
    {libj::Keyword::Null, "null"},
    {libj::Keyword::True, "true"},
    {libj::Keyword::False, "false"}};

static std::map<std::string, libj::Punctor> punctor_map = {
    {"(", libj::Punctor::OpenParen},
    {")", libj::Punctor::CloseBrace},
    {"{", libj::Punctor::OpenBrace},
    {"}", libj::Punctor::CloseBrace},
    {"[", libj::Punctor::OpenBracket},
    {"]", libj::Punctor::CloseBracket},
    {".", libj::Punctor::Dot},
    {",", libj::Punctor::Comma},
    {":", libj::Punctor::Colon},
    {";", libj::Punctor::Semicolon}};

static std::map<libj::Punctor, std::string> punctor_map_inverse = {
    {libj::Punctor::OpenParen, "("},
    {libj::Punctor::CloseBrace, ")"},
    {libj::Punctor::OpenBrace, "{"},
    {libj::Punctor::CloseBrace, "}"},
    {libj::Punctor::OpenBracket, "["},
    {libj::Punctor::CloseBracket, "]"},
    {libj::Punctor::Dot, "."},
    {libj::Punctor::Comma, ","},
    {libj::Punctor::Colon, ":"},
    {libj::Punctor::Semicolon, ";"}};


libj::Token::Token(libj::TokenType type, libj::TokVal value)
{
    m_type = type;
    m_value = value;
}

libj::TokenType libj::Token::type() const
{
    return m_type;
}

const libj::TokVal &libj::Token::val() const
{
    return m_value;
}

std::string libj::Token::serialize(bool human_readable) const
{
    (void)human_readable;

    switch (m_type)
    {
    case TokenType::Eof:
        return "Eof";
    case TokenType::Unknown:
        return "Unknown";
    case TokenType::Identifier:
        return "Identifier(" + std::get<std::string>(m_value) + ")";
    case TokenType::Keyword:
        return "Keyword(" + keyword_map_inverse.at(std::get<Keyword>(m_value)) + ")";
    case TokenType::Operator:
        return "Operator(" + std::string(std::get<const char *>(m_value)) + ")";
    case TokenType::Punctor:
        return "Punctor(" + punctor_map_inverse.at(std::get<Punctor>(m_value)) + ")";
    case TokenType::StringLiteral:
        return "\"" + std::get<std::string>(m_value) + "\"";
    case TokenType::CharLiteral:
        return "'" + std::get<std::string>(m_value) + "'";
    case TokenType::NumberLiteral:
        return "Number(" + std::to_string(std::get<uint64_t>(m_value)) + ")";
    case TokenType::Comment:
        return "/* " + std::get<std::string>(m_value) + " */";
    default:
        return "Unknown";
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

static bool validate_identifier(const std::string &id)
{
    int state = 0;

    for (const auto &c : id)
    {
        switch (state)
        {
        case 0:
            if (std::isalnum(c) || c == '_')
                continue;
            if (c == ':')
            {
                state = 1;
                continue;
            }
            return false;
        case 1:
            if (c != ':')
                return false;
            state = 2;
            continue;
        case 2:
            if (std::isalnum(c) || c == '_')
            {
                state = 0;
                continue;
            }
            return false;
        }
    }

    return state == 0;
}

libj::Token libj::Lexer::read_token()
{
    if (m_tok.has_value())
        return m_tok.value();

    enum class LexState
    {
        Start,
        Identifier,
        StringLiteral,
        NumberLiteral,
        CommentStart,
        CommentSingleLine,
        CommentMultiLine,
        Operator,
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
            // Skip whitespace
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            {
                continue;
            }
            else if (c == '/')
            {
                state = LexState::CommentStart;

                // it could also be an operator
                continue;
            }
            else if (std::isalpha(c) || c == '_')
            {
                buffer += c;
                state = LexState::Identifier;

                // it can also be a keyword
                continue;
            }
            else if (std::isdigit(c))
            {
                // Number literal
                buffer += c;
                state = LexState::NumberLiteral;
                continue;
            }
            else if (c == '"' || c == '\'')
            {
                // String literal
                buffer += c;
                state = LexState::StringLiteral;
                continue;
            }
            else
            {
                // Operator or punctor or invalid
                buffer += c;
                state = LexState::Operator;
                continue;
            }
        }
        case LexState::Identifier:
        {
            // match [a-zA-Z0-9_]
            if (std::isalnum(c) || c == '_')
            {
                buffer += c;
                continue;
            }

            m_last = c;

            // check if it's a keyword
            for (const auto &kw : keywords)
            {
                if (buffer == kw.first)
                {
                    m_tok = Token(TokenType::Keyword, keyword_map.at(buffer));
                    return m_tok.value();
                }
            }

            if (!validate_identifier(buffer))
            {
                m_tok = Token(TokenType::Unknown, buffer);
                return m_tok.value();
            }

            // it's an identifier
            m_tok = Token(TokenType::Identifier, buffer);
            return m_tok.value();
        }
        case LexState::NumberLiteral:
        {
            // match [0-9.]
            if (std::isdigit(c) || c == '.')
            {
                buffer += c;
                continue;
            }

            try
            {
                // Parse the number
                m_tok = Token(TokenType::NumberLiteral, std::stoull(buffer));
            }
            catch (std::invalid_argument &)
            {
                // Invalid number
                m_tok = Token(TokenType::Unknown, buffer);
            }

            m_last = c;
            return m_tok.value();
        }
        case LexState::CommentStart:
        {
            if (c == '/')
            {
                state = LexState::CommentSingleLine;
                continue;
            }
            else if (c == '*')
            {
                state = LexState::CommentMultiLine;
                continue;
            }
            else
            {
                // it's an operator
                m_last = c;
                m_tok = Token(TokenType::Operator, "/");
                return m_tok.value();
            }
        }
        case LexState::CommentSingleLine:
        {
            if (c != '\n')
            {
                buffer += c;
                continue;
            }

            m_tok = Token(TokenType::Comment, buffer);
            return m_tok.value();
        }
        case LexState::CommentMultiLine:
        {
            if (c != '*')
            {
                buffer += c;
                continue;
            }

            if ((c = getc()) == '/')
            {
                m_tok = Token(TokenType::Comment, buffer);
                return m_tok.value();
            }

            buffer += '*';
            buffer += c;
            continue;
        }
        case LexState::StringLiteral:
        {
            if (c != buffer[0])
            {
                buffer += c;
                continue;
            }

            if (buffer.front() == '\'' && buffer.size() == 2)
            {
                m_tok = Token(TokenType::CharLiteral, std::string(1, buffer[1]));
            }
            else
            {
                m_tok = Token(TokenType::StringLiteral, buffer.substr(1, buffer.size() - 1));
            }

            return m_tok.value();
        }
        case LexState::Operator:
        {
            if (buffer.size() == 1)
            {
                for (const auto &punc : punctors)
                {
                    if (punc[0] == buffer[0])
                    {
                        m_last = c;
                        m_tok = Token(TokenType::Punctor, punctor_map.at(buffer));
                        return m_tok.value();
                    }
                }
            }
            try
            {
                for (const auto &op : operators.at(buffer.size()))
                {
                    if (strcmp(op, buffer.c_str()) == 0)
                    {
                        m_last = c;
                        m_tok = Token(TokenType::Operator, op);
                        return m_tok.value();
                    }
                }

                buffer += c;
                continue;
            }
            catch (std::out_of_range &)
            {
                m_tok = Token(TokenType::Unknown, buffer);
                return m_tok.value();
            }
        }
        }
    }

    m_tok = Token(TokenType::Eof, "");
    return m_tok.value();
}

libj::Token libj::Lexer::peek()
{
    try
    {
        return read_token();
    }
    catch (...)
    {
        throw std::runtime_error("INTERNAL COMPILER ERROR: The Lexer throw an unexpected exception");
    }
}