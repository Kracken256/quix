#ifndef __J_CC_PREP_MACRO_PARSER_H__
#define __J_CC_PREP_MACRO_PARSER_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <lexer/token.h>
#include <jcc.h>
#include <map>

namespace libjcc
{
    typedef bool (*MacroParserRoutine)(jcc_job_t *job, const Token &tok, const std::string &directive, const std::string &parameter, std::vector<libjcc::Token> &exp);

    class MacroParser
    {
    protected:
        std::map<std::string, MacroParserRoutine> m_routines;
        jcc_job_t *m_job;

    public:
        MacroParser(jcc_job_t &job) : m_job(&job) {}
        void add_routine(const std::string &name, MacroParserRoutine routine) { m_routines[name] = routine; }
        bool parse(const libjcc::Token &macro, std::vector<libjcc::Token> &exp) const;
    };
}

#endif // __J_CC_PREP_MACRO_PARSER_H__