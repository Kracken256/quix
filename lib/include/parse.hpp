#ifndef __J_CC_PARSE_H__
#define __J_CC_PARSE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <lex.hpp>
#include <nodes.hpp>
#include <jcc.h>

namespace libj
{
    typedef RootNode AST;

    class Parser
    {
    public:
        Parser() = default;
        ~Parser() = default;

        bool parse(jcc_job_t &job, Lexer &lexer, AST &ast);
    };
};

#endif // __J_CC_PARSE_H__