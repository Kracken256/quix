#ifndef __J_CC_PREP_MACRO_DEFINE_H__
#define __J_CC_PREP_MACRO_DEFINE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <prep/macro/parser.h>

namespace libj::macro
{
    bool ParseDefine(jcc_job_t *job, const std::string &directive, const std::string &parameter, std::vector<libj::Token> &exp);
}

#endif // __J_CC_PREP_MACRO_DEFINE_H__