#ifndef __J_CC_ERROR_H__
#define __J_CC_ERROR_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <jcc.h>
#include <lexer/token.h>
#include <error/messages.h>

namespace libjcc
{
    enum class Err
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    void message(jcc_job_t &job, Err type, const std::string &format, ...);
    [[noreturn]] void parmsg(jcc_job_t &job, const Token &tok, Err type, const std::string &format, ...);
    [[noreturn]] void prepmsg(jcc_job_t &job, const Token &tok, Err type, const std::string &format, ...);
};

#endif // __J_CC_ERROR_H__