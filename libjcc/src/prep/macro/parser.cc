#include <prep/macro/parser.h>
#include <stdexcept>
#include <map>
#include <macro.h>
#include <error/message.h>

static void trim(std::string &str)
{
    str = str.substr(str.find_first_not_of(" \t\n\r\f\v"), str.find_last_not_of(" \t\n\r\f\v") + 1);
}

bool libjcc::MacroParser::parse(const libjcc::Token &macro, std::vector<libjcc::Token> &exp) const
{
    std::string content = std::get<std::string>(macro.val());
    trim(content);

    if (macro.type() == TokenType::MacroSingleLine)
    {
        std::string directive;
        std::string parameter;
        size_t pos = content.find(' ');
        if (pos == std::string::npos)
        {
            directive = content;
        }
        else
        {
            directive = content.substr(0, pos);
            if (pos + 1 < content.size())
                parameter = content.substr(pos + 1);
        }

        if (!m_routines.contains(directive))
            PREPMSG(macro, Err::ERROR, "Unknown macro directive: %s", directive.c_str());

        if (!m_routines.at(directive)(m_job, directive, parameter, exp))
            PREPMSG(macro, Err::ERROR, "Failed to process macro directive: %s", directive.c_str());

        return true;
    }
    else if (macro.type() == TokenType::MacroBlock)
    {
        // content = content.substr(1, content.size() - 2);
        PREPMSG(macro, Err::ERROR, "Macro block expansion not implemented");
    }
    else
    {
        throw std::runtime_error("Invalid macro type");
    }

    return false;
}