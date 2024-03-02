#ifndef __J_CC_PARSE_H__
#define __J_CC_PARSE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <lexer/lex.hpp>
#include <parse/nodes/nodes.hpp>
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

    bool parse_let(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::StmtNode> &node);
    bool parse_var(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::StmtNode> &node);
    bool parse_const_expr(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::ConstExprNode> &node);
    bool parse_type(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::ParseNode> &node);
};

#endif // __J_CC_PARSE_H__