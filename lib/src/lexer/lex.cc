#include <lexer/lex.h>
#include <cstdio>
#include <cctype>
#include <stdexcept>
#include <cstring>
#include <iomanip>
#include <regex>
#include <cmath>

///=============================================================================

#define FLOATING_POINT_LITERAL_ROUND_DIGITS 32

namespace libj
{
    std::map<std::string, libj::Keyword> keyword_map = {
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

    std::map<libj::Keyword, std::string> keyword_map_inverse = {
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

    std::map<std::string, libj::Punctor> punctor_map = {
        {"(", libj::Punctor::OpenParen},
        {")", libj::Punctor::CloseParen},
        {"{", libj::Punctor::OpenBrace},
        {"}", libj::Punctor::CloseBrace},
        {"[", libj::Punctor::OpenBracket},
        {"]", libj::Punctor::CloseBracket},
        {".", libj::Punctor::Dot},
        {",", libj::Punctor::Comma},
        {":", libj::Punctor::Colon},
        {";", libj::Punctor::Semicolon}};

    std::map<libj::Punctor, std::string> punctor_map_inverse = {
        {libj::Punctor::OpenParen, "("},
        {libj::Punctor::CloseParen, ")"},
        {libj::Punctor::OpenBrace, "{"},
        {libj::Punctor::CloseBrace, "}"},
        {libj::Punctor::OpenBracket, "["},
        {libj::Punctor::CloseBracket, "]"},
        {libj::Punctor::Dot, "."},
        {libj::Punctor::Comma, ","},
        {libj::Punctor::Colon, ":"},
        {libj::Punctor::Semicolon, ";"}};

    std::map<std::string, libj::Operator> operator_map = {
        {"<", libj::Operator::LessThan},
        {">", libj::Operator::GreaterThan},
        {"=", libj::Operator::Assign},
        {"@", libj::Operator::At},
        {"-", libj::Operator::Minus},
        {"+", libj::Operator::Plus},
        {"*", libj::Operator::Multiply},
        {"/", libj::Operator::Divide},
        {"%", libj::Operator::Modulo},
        {"&", libj::Operator::BitAnd},
        {"|", libj::Operator::BitOr},
        {"^", libj::Operator::BitXor},
        {"~", libj::Operator::BitNot},
        {"!", libj::Operator::Not},
        {"?", libj::Operator::Question},
        {"+=", libj::Operator::PlusAssign},
        {"-=", libj::Operator::MinusAssign},
        {"*=", libj::Operator::MultiplyAssign},
        {"/=", libj::Operator::DivideAssign},
        {"%=", libj::Operator::ModuloAssign},
        {"|=", libj::Operator::BitOrAssign},
        {"&=", libj::Operator::BitAndAssign},
        {"^=", libj::Operator::BitXorAssign},
        {"<<", libj::Operator::LeftShift},
        {">>", libj::Operator::RightShift},
        {"==", libj::Operator::Equal},
        {"!=", libj::Operator::NotEqual},
        {"&&", libj::Operator::And},
        {"||", libj::Operator::Or},
        {"^^", libj::Operator::Xor},
        {"<=", libj::Operator::LessThanEqual},
        {">=", libj::Operator::GreaterThanEqual},
        {"++", libj::Operator::Increment},
        {"--", libj::Operator::Decrement},
        {"^^=", libj::Operator::XorAssign},
        {"||=", libj::Operator::OrAssign},
        {"&&=", libj::Operator::AndAssign},
        {"<<=", libj::Operator::LeftShiftAssign},
        {">>=", libj::Operator::RightShiftAssign}};

    std::map<libj::Operator, std::string> operator_map_inverse = {
        {libj::Operator::LessThan, "<"},
        {libj::Operator::GreaterThan, ">"},
        {libj::Operator::Assign, "="},
        {libj::Operator::At, "@"},
        {libj::Operator::Minus, "-"},
        {libj::Operator::Plus, "+"},
        {libj::Operator::Multiply, "*"},
        {libj::Operator::Divide, "/"},
        {libj::Operator::Modulo, "%"},
        {libj::Operator::BitAnd, "&"},
        {libj::Operator::BitOr, "|"},
        {libj::Operator::BitXor, "^"},
        {libj::Operator::BitNot, "~"},
        {libj::Operator::Not, "!"},
        {libj::Operator::Question, "?"},
        {libj::Operator::PlusAssign, "+="},
        {libj::Operator::MinusAssign, "-="},
        {libj::Operator::MultiplyAssign, "*="},
        {libj::Operator::DivideAssign, "/="},
        {libj::Operator::ModuloAssign, "%="},
        {libj::Operator::BitOrAssign, "|="},
        {libj::Operator::BitAndAssign, "&="},
        {libj::Operator::BitXorAssign, "^="},
        {libj::Operator::LeftShift, "<<"},
        {libj::Operator::RightShift, ">>"},
        {libj::Operator::Equal, "=="},
        {libj::Operator::NotEqual, "!="},
        {libj::Operator::And, "&&"},
        {libj::Operator::Or, "||"},
        {libj::Operator::Xor, "^^"},
        {libj::Operator::LessThanEqual, "<="},
        {libj::Operator::GreaterThanEqual, ">="},
        {libj::Operator::Increment, "++"},
        {libj::Operator::Decrement, "--"},
        {libj::Operator::XorAssign, "^^="},
        {libj::Operator::OrAssign, "||="},
        {libj::Operator::AndAssign, "&&="},
        {libj::Operator::LeftShiftAssign, "<<="},
        {libj::Operator::RightShiftAssign, ">>="}};
}
///=============================================================================

libj::Lexer::Lexer()
{
    m_src = nullptr;
    m_buf_pos = 1024;
    m_buffer = std::vector<char>(m_buf_pos);
    m_tok = std::nullopt;
    m_last = 0;
    added_newline = false;
}

#include <iostream>

char libj::Lexer::getc()
{
    char c = EOF;

    if (m_buf_pos >= m_buffer.size())
    {
        size_t read;
        if ((read = fread(m_buffer.data(), 1, m_buffer.size(), m_src)) == 0)
        {
            if (added_newline)
                goto end;

            m_buffer[0] = '\n';
            read = 1;
            added_newline = true;
        }

        if (m_buffer.size() != read)
            m_buffer.resize(read);

        m_buf_pos = 0;
    }

    c = m_buffer[m_buf_pos++];

    m_loc = m_loc_curr;

    if (c == '\n')
    {
        m_loc_curr.line++;
        m_loc_curr.col = 1;
    }
    else
    {
        m_loc_curr.col++;
    }

end:
    return c;
}

bool libj::Lexer::set_source(FILE *src, const std::string &filename)
{
    if (src == nullptr)
        return false;

    m_src = src;

    if (fseek(m_src, 0, SEEK_SET) != 0)
        return false;

    m_filename = filename;
    m_loc_curr = Loc(1, 1, filename);

    return true;
}

libj::Token libj::Lexer::next()
{
    Token tok = peek();
    m_tok = std::nullopt;
    return tok;
}

// static bool validate_identifier_type_1(const std::string &id)
// {
//     int state = 0;

//     for (const auto &c : id)
//     {
//         switch (state)
//         {
//         case 0:
//             if (std::isalnum(c) || c == '_')
//                 continue;
//             if (c == ':')
//             {
//                 state = 1;
//                 continue;
//             }
//             return false;
//         case 1:
//             if (c != ':')
//                 return false;
//             state = 2;
//             continue;
//         case 2:
//             if (std::isalnum(c) || c == '_')
//             {
//                 state = 0;
//                 continue;
//             }
//             return false;
//         }
//     }

//     return state == 0;
// }

static bool validate_identifier_type_2(const std::string &id)
{
    int state = 0;

    for (const auto &c : id)
    {
        switch (state)
        {
        case 0:
            if (std::isalnum(c) || c == '_')
                continue;
            if (c == '.')
            {
                state = 1;
                continue;
            }
            return false;
        case 1:
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

static bool reduce_identifier(std::string &str)
{
    // if (validate_identifier_type_1(str))
    //     return true;

    if (validate_identifier_type_2(str))
    {
        size_t index = 0;
        while (true)
        {
            /* Locate the substring to replace. */
            index = str.find(".", index);
            if (index == std::string::npos)
                break;

            /* Make the replacement. */
            str.replace(index, 1, "::");

            /* Advance index forward so the next iteration doesn't pick it up as well. */
            index++;
        }

        return true;
    }

    return false;
}

enum class NumberLiteralType
{
    Invalid,
    Decimal,
    DecimalExplicit,
    Hexadecimal,
    Binary,
    Octal,
    Floating,
};

static NumberLiteralType check_number_literal_type(std::string input)
{
    if (input[0] == '-')
    {
        input = input.substr(1);
    }

    if (input.length() < 3)
    {
        if (std::isdigit(input[0]))
            return NumberLiteralType::Decimal;
        else
            return NumberLiteralType::Invalid;
    }

    std::string prefix = input.substr(0, 2);

    if (prefix == "0x")
    {
        for (size_t i = 2; i < input.length(); i++)
        {
            if (!((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'a' && input[i] <= 'f')))
            {
                return NumberLiteralType::Invalid;
            }
        }
        return NumberLiteralType::Hexadecimal;
    }
    else if (prefix == "0b")
    {
        for (size_t i = 2; i < input.length(); i++)
        {
            if (!(input[i] == '0' || input[i] == '1'))
            {
                return NumberLiteralType::Invalid;
            }
        }
        return NumberLiteralType::Binary;
    }
    else if (prefix == "0o")
    {
        for (size_t i = 2; i < input.length(); i++)
        {
            if (!(input[i] >= '0' && input[i] <= '7'))
            {
                return NumberLiteralType::Invalid;
            }
        }
        return NumberLiteralType::Octal;
    }
    else if (prefix == "0d")
    {
        for (size_t i = 2; i < input.length(); i++)
        {
            if (!(input[i] >= '0' && input[i] <= '9'))
            {
                return NumberLiteralType::Invalid;
            }
        }
        return NumberLiteralType::DecimalExplicit;
    }
    else
    {
        for (size_t i = 0; i < input.length(); i++)
        {
            if (!(input[i] >= '0' && input[i] <= '9'))
            {
                goto test_float;
            }
        }
        return NumberLiteralType::Decimal;
    }

test_float:
    auto regexpFloat = std::regex("^([0-9]+(\\.[0-9]+)?)?(e[+-]?([0-9]+(\\.?[0-9]+)?)+)*$");

    // slow operation
    if (std::regex_match(input, regexpFloat))
    {
        return NumberLiteralType::Floating;
    }

    return NumberLiteralType::Invalid;
}

static std::string normalize_float(const std::string &input)
{
    double mantissa = 0;
    double exponent = 0;
    double x = 0;

    size_t e_pos = input.find('e');

    if (e_pos == std::string::npos)
        return input;

    mantissa = std::stod(input.substr(0, e_pos));
    exponent = std::stod(input.substr(e_pos + 1));

    x = mantissa * std::pow(10.0, exponent);
    std::stringstream ss;
    ss << std::setprecision(FLOATING_POINT_LITERAL_ROUND_DIGITS) << x;
    return ss.str();
}

bool normalize_number_literal(std::string &number, std::string &norm, NumberLiteralType type)
{
    uint64_t x = 0;

    for (size_t i = 0; i < number.length(); i++)
    {
        number[i] = std::tolower(number[i]);
    }

    switch (type)
    {
    case NumberLiteralType::Hexadecimal:
        for (size_t i = 2; i < number.length(); ++i)
        {
            // check for overflow
            if (x & 0xF000000000000000)
                return false;

            if (number[i] >= '0' && number[i] <= '9')
                x = (x << 4) + (number[i] - '0');
            else if (number[i] >= 'a' && number[i] <= 'f')
                x = (x << 4) + (number[i] - 'a' + 10);
            else
                return false;
        }
        break;
    case NumberLiteralType::Binary:
        for (size_t i = 2; i < number.length(); ++i)
        {
            // check for overflow
            if (x & 0x8000000000000000)
                return false;

            x = (x << 1) + (number[i] - '0');
        }
        break;
    case NumberLiteralType::Octal:
        for (size_t i = 2; i < number.length(); ++i)
        {
            // check for overflow
            if (x & 0xE000000000000000)
                return false;

            x = (x << 3) + (number[i] - '0');
        }
        break;
    case NumberLiteralType::DecimalExplicit:
        x = std::stoull(number.substr(2));
        break;
    case NumberLiteralType::Decimal:
        x = std::stoull(number);
        break;
    default:
        break;
    }

    norm = std::to_string(x);
    return true;
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
        IntegerLiteral,
        CommentStart,
        CommentSingleLine,
        CommentMultiLine,
        MacroStart,
        SingleLineMacro,
        BlockMacro,
        Other,
    };

    LexState state = LexState::Start;
    std::string buffer;
    size_t state_parens = 0;

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
                state = LexState::IntegerLiteral;
                continue;
            }
            else if (c == '"' || c == '\'')
            {
                // String literal
                buffer += c;
                state = LexState::StringLiteral;
                continue;
            }
            else if (c == '@')
            {
                // Macro
                state = LexState::MacroStart;
                continue;
            }
            else
            {
                // Operator or punctor or comment or invalid
                buffer += c;
                state = LexState::Other;
                continue;
            }
        }
        case LexState::Identifier:
        {
            // match [a-zA-Z0-9_]
            if (std::isalnum(c) || c == '_' || c == '.')
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
                    m_tok = Token(TokenType::Keyword, keyword_map.at(buffer), m_loc - buffer.size());
                    return m_tok.value();
                }
            }

            if (!reduce_identifier(buffer))
            {
                m_tok = Token(TokenType::Unknown, buffer, m_loc - buffer.size());
                return m_tok.value();
            }

            // it's an identifier
            m_tok = Token(TokenType::Identifier, buffer, m_loc - buffer.size());
            return m_tok.value();
        }
        case LexState::IntegerLiteral:
        {
            // match [0-9.]
            if (std::isxdigit(c) || c == '.' || c == 'x' || c == 'b' || c == 'd' || c == 'o' || c == 'e')
            {
                buffer += c;
                continue;
            }

            auto type = check_number_literal_type(buffer);

            if (type == NumberLiteralType::Floating)
            {
                m_tok = Token(TokenType::FloatingLiteral, normalize_float(buffer), m_loc - buffer.size());
            }
            else if (type != NumberLiteralType::Invalid)
            {
                std::string norm;
                if (!normalize_number_literal(buffer, norm, type))
                {
                    m_tok = Token(TokenType::Unknown, buffer, m_loc - buffer.size());
                }

                m_tok = Token(TokenType::IntegerLiteral, norm, m_loc - buffer.size());
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
                m_tok = Token(TokenType::Operator, Operator::Divide, m_loc);
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

            m_tok = Token(TokenType::Comment, buffer, m_loc - buffer.size());
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
                m_tok = Token(TokenType::Comment, buffer, m_loc - buffer.size());
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
                // buffer += c;
                // continue;
                if (c == '\\')
                {
                    // escape sequence
                    c = getc();
                    switch (c)
                    {
                    case 'n':
                        buffer += '\n';
                        break;
                    case 't':
                        buffer += '\t';
                        break;
                    case 'r':
                        buffer += '\r';
                        break;
                    case '0':
                        buffer += '\0';
                        break;
                    case '\\':
                        buffer += '\\';
                        break;
                    case '\'':
                        buffer += '\'';
                        break;
                    case '\"':
                        buffer += '\"';
                        break;
                    default:
                        buffer += c;
                        break;
                    }
                }
                else
                {
                    buffer += c;
                }
                continue;
            }

            if (buffer.front() == '\'' && buffer.size() == 2)
            {
                m_tok = Token(TokenType::CharLiteral, std::string(1, buffer[1]), m_loc - 2);
            }
            else
            {
                m_tok = Token(TokenType::StringLiteral, buffer.substr(1, buffer.size() - 1), m_loc - buffer.size());
            }

            return m_tok.value();
        }
        case LexState::MacroStart:
            // macros begin with '@'
            // There are two types. One is a single line macro, the other is a block macro.
            // single line macros end with a semicolon and a newline
            // block macros begin with a '@(' and end with a ');'
            if (c == '(')
            {
                state = LexState::BlockMacro;
                state_parens = 1;
                continue;
            }
            else
            {
                state = LexState::SingleLineMacro;
                buffer += c;
                continue;
            }
            break;
        case LexState::SingleLineMacro:
        {
            if (c != '\n')
            {
                buffer += c;
                continue;
            }

            m_tok = Token(TokenType::MacroSingleLine, buffer, m_loc - buffer.size());
            return m_tok.value();
        }
        case LexState::BlockMacro:
        {
            // block macros can contain anything
            // therefore, we must keep track of how many open and close parens we have
            // and stop when we have a matching pair
            if (c == '(')
            {
                state_parens++;
            }
            else if (c == ')')
            {
                state_parens--;
            }

            if (state_parens == 0)
            {
                m_tok = Token(TokenType::MacroBlock, buffer, m_loc - buffer.size());
                return m_tok.value();
            }

            buffer += c;
            continue;
        }
            
        case LexState::Other:
        {
            if (buffer.size() == 1)
            {
                for (const auto &punc : punctors)
                {
                    if (punc[0] == buffer[0])
                    {
                        m_last = c;
                        m_tok = Token(TokenType::Punctor, punctor_map.at(buffer), m_loc - buffer.size());
                        return m_tok.value();
                    }
                }

                if ((buffer[0] == '~' && c == '>'))
                {
                    state = LexState::CommentSingleLine;
                    continue;
                }

                if (buffer[0] == '#' && std::isspace(c))
                {
                    state = LexState::CommentSingleLine;
                    continue;
                }
            }
            try
            {
                if (operator_map.find(buffer) != operator_map.end())
                {
                    m_last = c;
                    m_tok = Token(TokenType::Operator, operator_map.at(buffer), m_loc - buffer.size());
                    return m_tok.value();
                }

                buffer += c;
                continue;
            }
            catch (std::out_of_range &)
            {
                m_tok = Token(TokenType::Unknown, buffer, m_loc - buffer.size());
                return m_tok.value();
            }
        }
        }
    }

    m_tok = Token(TokenType::Eof, "", m_loc);
    return m_tok.value();
}

libj::Token libj::Lexer::peek()
{
    try
    {
        Token tok;
        while (true)
        {
            tok = read_token();
            if (tok.type() == TokenType::Comment)
                m_tok = std::nullopt;
            else
                return tok;
        }
    }
    catch (...)
    {
        throw std::runtime_error("INTERNAL COMPILER ERROR: The Lexer throw an unexpected exception");
    }
}