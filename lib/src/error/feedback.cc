#include <error/messages.h>

using namespace libj;

std::map<libj::Msg, const char *> libj::feedback = {
    {PARSER_EXPECTED_KEYWORD, "Parser failed because a keyword was expected, but the token %s was found"},
    {LET_DECL_MISSING_IDENTIFIER, "Missing identifier in variable declaration. To fix the issue, name your variable. Syntax: let name: type [= expr];"},
    {LET_DECL_MISSING_COLON, "Missing colon separator in variable declaration. To fix the issue, insert a colon between the variable name and the typename. Syntax: let name: type [= expr];"},
    {LET_DECL_TYPE_ERR, "An error occurred while parsing the type of variable '%s'. Syntax: let name: type [= expr];"},
    {LET_DECL_INIT_ERR, "Declaration of variable '%s' requires an initializer, but an error occurred while parsing the initializer. Syntax: let name: type [= expr];"},
    {LET_DECL_MISSING_PUNCTOR, "Declaration of variable '%s' requires an initializer OR a semicolon punctuator, but neither was found. Make sure to terminate all statements with a semicolon. Syntax: let name: type [= expr];"},
    {VAR_DECL_MISSING_IDENTIFIER, "Missing identifier in variable declaration. To fix the issue, name your variable. Syntax: var name: type [= expr];"},
    {VAR_DECL_MISSING_COLON, "Missing colon separator in variable declaration. To fix the issue, insert a colon between the variable name and the typename. Syntax: var name: type [= expr];"},
    {VAR_DECL_TYPE_ERR, "An error occurred while parsing the type of variable '%s'. Syntax: var name: type [= expr];"},
    {VAR_DECL_INIT_ERR, "Declaration of variable '%s' requires an initializer, but an error occurred while parsing the initializer. Syntax: var name: type [= expr];"},
    {VAR_DECL_MISSING_PUNCTOR, "Declaration of variable '%s' requires an initializer OR a semicolon punctuator, but neither was found. Make sure to terminate all statements with a semicolon. Syntax: var name: type [= expr];"}
};