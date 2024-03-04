#ifndef __J_CC_ERROR_EXCEPTIONS_H__
#define __J_CC_ERROR_EXCEPTIONS_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>

namespace libjcc
{
    class PreprocessorException : public std::exception
    {
    public:
        const char *what() const noexcept override { return "Preprocessor error"; }
    };

    class ParseException : public std::exception
    {
    public:
        const char *what() const noexcept override { return "Parse error"; }
    };
}

#endif // __J_CC_ERROR_EXCEPTIONS_H__