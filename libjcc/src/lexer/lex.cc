#define JCC_INTERNAL

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

namespace libjcc
{
    std::map<std::string, libjcc::Keyword> keyword_map = {
        {"subsystem", libjcc::Keyword::Subsystem},
        {"import", libjcc::Keyword::Import},
        {"export", libjcc::Keyword::Export},
        {"let", libjcc::Keyword::Let},
        {"var", libjcc::Keyword::Var},
        {"struct", libjcc::Keyword::Struct},
        {"region", libjcc::Keyword::Region},
        {"union", libjcc::Keyword::Union},
        {"packet", libjcc::Keyword::Packet},
        {"fn", libjcc::Keyword::Fn},
        {"nothrow", libjcc::Keyword::Nothrow},
        {"foreign", libjcc::Keyword::Foreign},
        {"pure", libjcc::Keyword::Pure},
        {"impure", libjcc::Keyword::Impure},
        {"tsafe", libjcc::Keyword::Tsafe},
        {"typedef", libjcc::Keyword::Typedef},
        {"const", libjcc::Keyword::Const},
        {"static", libjcc::Keyword::Static},
        {"volatile", libjcc::Keyword::Volatile},
        {"enum", libjcc::Keyword::Enum},
        {"class", libjcc::Keyword::Class},
        {"bundle", libjcc::Keyword::Bundle},
        {"pub", libjcc::Keyword::Pub},
        {"private", libjcc::Keyword::Private},
        {"protected", libjcc::Keyword::Protected},
        {"override", libjcc::Keyword::Override},
        {"virtual", libjcc::Keyword::Virtual},
        {"abstract", libjcc::Keyword::Abstract},
        {"friend", libjcc::Keyword::Friend},
        {"interface", libjcc::Keyword::Interface},
        {"delete", libjcc::Keyword::Delete},
        {"if", libjcc::Keyword::If},
        {"else", libjcc::Keyword::Else},
        {"for", libjcc::Keyword::For},
        {"while", libjcc::Keyword::While},
        {"do", libjcc::Keyword::Do},
        {"switch", libjcc::Keyword::Switch},
        {"case", libjcc::Keyword::Case},
        {"default", libjcc::Keyword::Default},
        {"break", libjcc::Keyword::Break},
        {"continue", libjcc::Keyword::Continue},
        {"return", libjcc::Keyword::Return},
        {"retif", libjcc::Keyword::Retif},
        {"abortif", libjcc::Keyword::Abortif},
        {"retz", libjcc::Keyword::Retz},
        {"void", libjcc::Keyword::Void},
        {"null", libjcc::Keyword::Null},
        {"true", libjcc::Keyword::True},
        {"false", libjcc::Keyword::False}};

    std::map<libjcc::Keyword, std::string> keyword_map_inverse = {
        {libjcc::Keyword::Subsystem, "subsystem"},
        {libjcc::Keyword::Import, "import"},
        {libjcc::Keyword::Export, "export"},
        {libjcc::Keyword::Let, "let"},
        {libjcc::Keyword::Var, "var"},
        {libjcc::Keyword::Struct, "struct"},
        {libjcc::Keyword::Region, "region"},
        {libjcc::Keyword::Union, "union"},
        {libjcc::Keyword::Packet, "packet"},
        {libjcc::Keyword::Fn, "fn"},
        {libjcc::Keyword::Nothrow, "nothrow"},
        {libjcc::Keyword::Foreign, "foreign"},
        {libjcc::Keyword::Pure, "pure"},
        {libjcc::Keyword::Impure, "impure"},
        {libjcc::Keyword::Tsafe, "tsafe"},
        {libjcc::Keyword::Typedef, "typedef"},
        {libjcc::Keyword::Const, "const"},
        {libjcc::Keyword::Static, "static"},
        {libjcc::Keyword::Volatile, "volatile"},
        {libjcc::Keyword::Enum, "enum"},
        {libjcc::Keyword::Class, "class"},
        {libjcc::Keyword::Bundle, "bundle"},
        {libjcc::Keyword::Pub, "pub"},
        {libjcc::Keyword::Private, "private"},
        {libjcc::Keyword::Protected, "protected"},
        {libjcc::Keyword::Override, "override"},
        {libjcc::Keyword::Virtual, "virtual"},
        {libjcc::Keyword::Abstract, "abstract"},
        {libjcc::Keyword::Friend, "friend"},
        {libjcc::Keyword::Interface, "interface"},
        {libjcc::Keyword::Delete, "delete"},
        {libjcc::Keyword::If, "if"},
        {libjcc::Keyword::Else, "else"},
        {libjcc::Keyword::For, "for"},
        {libjcc::Keyword::While, "while"},
        {libjcc::Keyword::Do, "do"},
        {libjcc::Keyword::Switch, "switch"},
        {libjcc::Keyword::Case, "case"},
        {libjcc::Keyword::Default, "default"},
        {libjcc::Keyword::Break, "break"},
        {libjcc::Keyword::Continue, "continue"},
        {libjcc::Keyword::Return, "return"},
        {libjcc::Keyword::Retif, "retif"},
        {libjcc::Keyword::Abortif, "abortif"},
        {libjcc::Keyword::Retz, "retz"},
        {libjcc::Keyword::Void, "void"},
        {libjcc::Keyword::Null, "null"},
        {libjcc::Keyword::True, "true"},
        {libjcc::Keyword::False, "false"}};

    std::map<std::string, libjcc::Punctor> punctor_map = {
        {"(", libjcc::Punctor::OpenParen},
        {")", libjcc::Punctor::CloseParen},
        {"{", libjcc::Punctor::OpenBrace},
        {"}", libjcc::Punctor::CloseBrace},
        {"[", libjcc::Punctor::OpenBracket},
        {"]", libjcc::Punctor::CloseBracket},
        {".", libjcc::Punctor::Dot},
        {",", libjcc::Punctor::Comma},
        {":", libjcc::Punctor::Colon},
        {";", libjcc::Punctor::Semicolon}};

    std::map<libjcc::Punctor, std::string> punctor_map_inverse = {
        {libjcc::Punctor::OpenParen, "("},
        {libjcc::Punctor::CloseParen, ")"},
        {libjcc::Punctor::OpenBrace, "{"},
        {libjcc::Punctor::CloseBrace, "}"},
        {libjcc::Punctor::OpenBracket, "["},
        {libjcc::Punctor::CloseBracket, "]"},
        {libjcc::Punctor::Dot, "."},
        {libjcc::Punctor::Comma, ","},
        {libjcc::Punctor::Colon, ":"},
        {libjcc::Punctor::Semicolon, ";"}};

    std::map<std::string, libjcc::Operator> operator_map = {
        {"<", libjcc::Operator::LessThan},
        {">", libjcc::Operator::GreaterThan},
        {"=", libjcc::Operator::Assign},
        {"@", libjcc::Operator::At},
        {"-", libjcc::Operator::Minus},
        {"+", libjcc::Operator::Plus},
        {"*", libjcc::Operator::Multiply},
        {"/", libjcc::Operator::Divide},
        {"%", libjcc::Operator::Modulo},
        {"&", libjcc::Operator::BitAnd},
        {"|", libjcc::Operator::BitOr},
        {"^", libjcc::Operator::BitXor},
        {"~", libjcc::Operator::BitNot},
        {"!", libjcc::Operator::Not},
        {"?", libjcc::Operator::Question},
        {"+=", libjcc::Operator::PlusAssign},
        {"-=", libjcc::Operator::MinusAssign},
        {"*=", libjcc::Operator::MultiplyAssign},
        {"/=", libjcc::Operator::DivideAssign},
        {"%=", libjcc::Operator::ModuloAssign},
        {"|=", libjcc::Operator::BitOrAssign},
        {"&=", libjcc::Operator::BitAndAssign},
        {"^=", libjcc::Operator::BitXorAssign},
        {"<<", libjcc::Operator::LeftShift},
        {">>", libjcc::Operator::RightShift},
        {"==", libjcc::Operator::Equal},
        {"!=", libjcc::Operator::NotEqual},
        {"&&", libjcc::Operator::And},
        {"||", libjcc::Operator::Or},
        {"^^", libjcc::Operator::Xor},
        {"<=", libjcc::Operator::LessThanEqual},
        {">=", libjcc::Operator::GreaterThanEqual},
        {"++", libjcc::Operator::Increment},
        {"--", libjcc::Operator::Decrement},
        {"^^=", libjcc::Operator::XorAssign},
        {"||=", libjcc::Operator::OrAssign},
        {"&&=", libjcc::Operator::AndAssign},
        {"<<=", libjcc::Operator::LeftShiftAssign},
        {">>=", libjcc::Operator::RightShiftAssign}};

    std::map<libjcc::Operator, std::string> operator_map_inverse = {
        {libjcc::Operator::LessThan, "<"},
        {libjcc::Operator::GreaterThan, ">"},
        {libjcc::Operator::Assign, "="},
        {libjcc::Operator::At, "@"},
        {libjcc::Operator::Minus, "-"},
        {libjcc::Operator::Plus, "+"},
        {libjcc::Operator::Multiply, "*"},
        {libjcc::Operator::Divide, "/"},
        {libjcc::Operator::Modulo, "%"},
        {libjcc::Operator::BitAnd, "&"},
        {libjcc::Operator::BitOr, "|"},
        {libjcc::Operator::BitXor, "^"},
        {libjcc::Operator::BitNot, "~"},
        {libjcc::Operator::Not, "!"},
        {libjcc::Operator::Question, "?"},
        {libjcc::Operator::PlusAssign, "+="},
        {libjcc::Operator::MinusAssign, "-="},
        {libjcc::Operator::MultiplyAssign, "*="},
        {libjcc::Operator::DivideAssign, "/="},
        {libjcc::Operator::ModuloAssign, "%="},
        {libjcc::Operator::BitOrAssign, "|="},
        {libjcc::Operator::BitAndAssign, "&="},
        {libjcc::Operator::BitXorAssign, "^="},
        {libjcc::Operator::LeftShift, "<<"},
        {libjcc::Operator::RightShift, ">>"},
        {libjcc::Operator::Equal, "=="},
        {libjcc::Operator::NotEqual, "!="},
        {libjcc::Operator::And, "&&"},
        {libjcc::Operator::Or, "||"},
        {libjcc::Operator::Xor, "^^"},
        {libjcc::Operator::LessThanEqual, "<="},
        {libjcc::Operator::GreaterThanEqual, ">="},
        {libjcc::Operator::Increment, "++"},
        {libjcc::Operator::Decrement, "--"},
        {libjcc::Operator::XorAssign, "^^="},
        {libjcc::Operator::OrAssign, "||="},
        {libjcc::Operator::AndAssign, "&&="},
        {libjcc::Operator::LeftShiftAssign, "<<="},
        {libjcc::Operator::RightShiftAssign, ">>="}};
}
///=============================================================================

libjcc::StreamLexer::StreamLexer()
{
    m_src = nullptr;
    m_buf_pos = 1024;
    m_buffer = std::vector<char>(m_buf_pos);
    m_tok = std::nullopt;
    m_last = 0;
    added_newline = false;
}

char libjcc::StreamLexer::getc()
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

bool libjcc::StreamLexer::set_source(FILE *src, const std::string &filename)
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

libjcc::Token libjcc::StreamLexer::next()
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
    static const auto regexpFloat = std::regex("^([0-9]+(\\.[0-9]+)?)?(e[+-]?([0-9]+(\\.?[0-9]+)?)+)*$");

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

libjcc::Token libjcc::StreamLexer::read_token()
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

libjcc::Token libjcc::StreamLexer::peek()
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

bool libjcc::StringLexer::set_source(const std::string &source_code, const std::string &filename)
{
    m_src = source_code;
    m_filename = filename;
    m_loc_curr = Loc(1, 1, filename);
    m_buf_pos = 0;
    return true;
}

char libjcc::StringLexer::getc()
{
    if (m_buf_pos >= m_src.size())
        return EOF;

    char c = m_src[m_buf_pos++];

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

    return c;
}

bool libjcc::StringLexer::QuickLex(const std::string &source_code, std::vector<libjcc::Token> &tokens)
{
    try
    {
        StringLexer lex;
        lex.set_source(source_code, "quicklex");
        Token tok;
        tokens.clear();
        while ((tok = lex.next()).type() != TokenType::Eof)
        {
            tokens.push_back(tok);
        }
    }
    catch (std::exception &e)
    {
        return false;
    }

    return true;
}