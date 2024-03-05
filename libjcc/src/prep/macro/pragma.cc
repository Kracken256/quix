#define JCC_INTERNAL

#include <prep/macro/pragma.h>
#include <iostream>

bool libjcc::macro::ParsePragma(jcc_job_t *job, const Token &tok, const std::string &directive, const std::string &parameter, std::vector<libjcc::Token> &exp)
{
    // pragma <directive>
    
    std::cout << "Pragma: " << directive << " " << parameter << std::endl;

    return true;
}