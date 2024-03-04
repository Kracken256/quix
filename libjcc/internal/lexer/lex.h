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
#include <map>
#include <lexer/token.h>

namespace libjcc
{
    constexpr std::array<const char *, 10> punctors = {
        "(", ")", "{", "}", "[", "]", ".", ",", ":", ";"};

    typedef std::pair<const char *, int> KWPair;

    constexpr std::array<KWPair, 44> keywords = {
        KWPair("subsystem", 9),
        KWPair("import", 6),
        KWPair("export", 6),
        KWPair("let", 3),
        KWPair("var", 3),
        KWPair("struct", 6),
        KWPair("region", 6),
        KWPair("union", 5),
        KWPair("packet", 6),
        KWPair("fn", 2),
        KWPair("typedef", 7),
        KWPair("const", 5),
        KWPair("static", 6),
        KWPair("volatile", 8),
        KWPair("enum", 4),
        KWPair("class", 5),
        KWPair("bundle", 6),
        KWPair("public", 6),
        KWPair("private", 7),
        KWPair("protected", 9),
        KWPair("override", 8),
        KWPair("virtual", 7),
        KWPair("abstract", 8),
        KWPair("friend", 6),
        KWPair("interface", 9),
        KWPair("delete", 6),
        KWPair("if", 2),
        KWPair("else", 4),
        KWPair("for", 3),
        KWPair("while", 5),
        KWPair("do", 2),
        KWPair("switch", 6),
        KWPair("case", 4),
        KWPair("default", 7),
        KWPair("break", 5),
        KWPair("continue", 8),
        KWPair("return", 6),
        KWPair("retif", 5),
        KWPair("abortif", 7),
        KWPair("retz", 4),
        KWPair("void", 4),
        KWPair("null", 4),
        KWPair("true", 4),
        KWPair("false", 5),
    };

    extern std::map<std::string, libjcc::Keyword> keyword_map;
    extern std::map<libjcc::Keyword, std::string> keyword_map_inverse;
    extern std::map<std::string, libjcc::Punctor> punctor_map;
    extern std::map<libjcc::Punctor, std::string> punctor_map_inverse;
    extern std::map<std::string, libjcc::Operator> operator_map;
    extern std::map<libjcc::Operator, std::string> operator_map_inverse;

    class Scanner
    {
    public:
        Scanner() = default;
        ~Scanner() = default;

        /// @brief Set the source file
        /// @param src C FILE pointer
        /// @return true if the source file is set successfully
        virtual bool set_source(FILE *src, const std::string &filename) = 0;

        /// @brief Get the next token
        /// @return The next token
        virtual Token next() = 0;

        /// @brief Peek the next token
        /// @return The next token
        virtual Token peek() = 0;
    };

    class Lexer : public Scanner
    {
    protected:
        /// @brief C FILE* source. Object is owned by the caller.
        /// @note The caller is responsible for closing the file.
        FILE *m_src = nullptr;
        std::string m_filename;
        std::vector<char> m_buffer;
        std::optional<Token> m_tok;
        size_t m_buf_pos = 0;
        char m_last = 0;
        Loc m_loc_curr;
        Loc m_loc;
        bool added_newline = false;

        char getc();
        virtual libjcc::Token read_token();

    public:
        Lexer();

        /// @brief Set the source file
        /// @param src C FILE pointer
        /// @return true if the source file is set successfully
        virtual bool set_source(FILE *src, const std::string &filename) override;

        /// @brief Get the next token
        /// @return The next token
        Token next() override;

        /// @brief Peek the next token
        /// @return The next token
        Token peek() override;
    };
};

#endif // __J_CC_LEX_H__