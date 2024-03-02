#ifndef __J_CC_MESSAGES_HPP__
#define __J_CC_MESSAGES_HPP__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <map>

namespace libj
{
    enum Msg
    {
        PARSER_EXPECTED_KEYWORD,
        LET_DECL_MISSING_IDENTIFIER,
        LET_DECL_MISSING_COLON,
        LET_DECL_TYPE_ERR,
        LET_DECL_INIT_ERR,
        LET_DECL_MISSING_PUNCTOR,

        VAR_DECL_MISSING_IDENTIFIER,
        VAR_DECL_MISSING_COLON,
        VAR_DECL_TYPE_ERR,
        VAR_DECL_INIT_ERR,
        VAR_DECL_MISSING_PUNCTOR,

        CONST_DECL_MISSING_IDENTIFIER,
        CONST_DECL_MISSING_COLON,
        CONST_DECL_TYPE_ERR,
        CONST_DECL_INIT_ERR,
        CONST_DECL_MISSING_PUNCTOR
    };

    extern std::map<Msg, const char *> feedback;
};

#endif