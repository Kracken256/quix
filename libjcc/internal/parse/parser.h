#ifndef __J_CC_PARSE_H__
#define __J_CC_PARSE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <lexer/lex.h>
#include <parse/nodes/nodes.h>
#include <jcc.h>

namespace libjcc
{
    typedef BlockNode AST;

    bool parse(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<BlockNode> &node, bool expect_braces = true);

    bool parse_let(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node);
    bool parse_var(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node);
    bool parse_const(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node);
    bool parse_struct(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node);
    bool parse_subsystem(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node);
    bool parse_const_expr(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, Token terminator, std::shared_ptr<libjcc::ConstExprNode> &node);
    bool parse_type(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::TypeNode> &node);
};

#endif // __J_CC_PARSE_H__