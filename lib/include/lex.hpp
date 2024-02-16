#ifndef __J_CC_LEX_H__
#define __J_CC_LEX_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <bits/types/FILE.h>
#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <deque>
#include <array>

namespace libj
{
    enum class TokenType
    {
        Eof = -1,

        Define = -2,
        Extern = -3,
        Identifier = -4,
        Number = -5,
        Comment = -6,

        Operator = -7,

        Unknown = -8,
    };

    enum class Operator
    {
        Plus = '+',
        Minus = '-',
        Multiply = '*',
        Divide = '/',
        Modulo = '%',
        Assign = '=',
        LessThan = '<',
        GreaterThan = '>',
        OpenParen = '(',
        CloseParen = ')',
        Comma = ',',
        Semicolon = ';',
    };

    constexpr std::array<Operator, 12> operators = {
        Operator::Plus,
        Operator::Minus,
        Operator::Multiply,
        Operator::Divide,
        Operator::Modulo,
        Operator::Assign,
        Operator::LessThan,
        Operator::GreaterThan,
        Operator::OpenParen,
        Operator::CloseParen,
        Operator::Comma,
        Operator::Semicolon,
    };

    class Token
    {
        TokenType m_type;
        std::variant<std::string, double> m_value;

    public:
        Token(TokenType type, std::variant<std::string, double> value);

        TokenType type() const;
        const std::variant<std::string, double> &val() const;

        std::string serialize(bool human_readable = false) const;
    };

    class Lexer
    {
        /// @brief C FILE* source. Object is owned by the caller.
        /// @note The caller is responsible for closing the file.
        FILE *m_src;
        std::vector<char> m_buffer;
        std::optional<Token> m_tok;
        size_t m_buf_pos;
        char m_last;

        char getc();

    public:
        Lexer();

        /// @brief Set the source file
        /// @param src C FILE pointer
        /// @return true if the source file is set successfully
        bool set_source(FILE *src);

        /// @brief Get the next token
        /// @return The next token
        Token next();

        /// @brief Peek the next token
        /// @return The next token
        Token peek();
    };
};

#endif // __J_CC_LEX_H__