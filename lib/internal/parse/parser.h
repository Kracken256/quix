#ifndef __J_CC_PARSE_H__
#define __J_CC_PARSE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <lexer/lex.h>
#include <parse/nodes/nodes.h>
#include <jcc.h>

namespace libj
{
    typedef RootNode AST;

    class Parser
    {
    public:
        Parser() = default;
        ~Parser() = default;

        bool parse(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, AST &ast);
    };

    bool parse_let(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, std::shared_ptr<libj::StmtNode> &node);
    bool parse_var(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, std::shared_ptr<libj::StmtNode> &node);
    bool parse_const(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, std::shared_ptr<libj::StmtNode> &node);
    bool parse_struct(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, std::shared_ptr<libj::StmtNode> &node);
    bool parse_const_expr(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, Token terminator, std::shared_ptr<libj::ConstExprNode> &node);
    bool parse_type(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, std::shared_ptr<libj::TypeNode> &node);
};

#endif // __J_CC_PARSE_H__