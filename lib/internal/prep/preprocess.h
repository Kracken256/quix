#ifndef __J_CC_PREP_PREPROCESS_H__
#define __J_CC_PREP_PREPROCESS_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <bits/types/FILE.h>
#include <vector>
#include <string>
#include <optional>
#include <lexer/lex.h>
#include <jcc.h>
#include <set>
#include <stack>

namespace libj
{
    class PrepEngine : public libj::Scanner
    {
    protected:
        struct Entry
        {
            Lexer lexer;
            std::string path;
            FILE *file;
        };
        std::set<std::string> m_include_dirs;
        std::vector<std::string> m_include_files; // for circular include detection
        std::stack<Entry> m_stack;
        jcc_job_t *m_job;
        std::string include_path;
        std::optional<Token> m_tok;

        Token read_token();

        bool handle_import(Token &tok);

    public:
        PrepEngine(jcc_job_t &job) : m_job(&job) {}

        void addpath(const std::string &path);

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
}

#endif // __J_CC_PREP_PREPROCESS_H__