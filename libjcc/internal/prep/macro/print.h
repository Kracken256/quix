#ifndef __J_CC_PREP_MACRO_PRINT_H__
#define __J_CC_PREP_MACRO_PRINT_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <prep/macro/parser.h>

namespace libjcc::macro
{
    bool ParsePrint(jcc_job_t *job, const Token &tok, const std::string &directive, const std::string &parameter, std::vector<libjcc::Token> &exp);
}

#endif // __J_CC_PREP_MACRO_PRAGMA_H__