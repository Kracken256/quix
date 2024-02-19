#include <parse.hpp>
#include <macro.h>
#include <message.hpp>

using namespace libj;

bool libj::parse_const_expr(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::ConstExprNode> &node)
{
    (void)job;
    (void)lexer;
    (void)node;
    message(job, libj::Err::ERROR, "Not implemented");
    return false;
}