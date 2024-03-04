#include <parse/parser.h>
#include <error/message.h>
#include <macro.h>

#include <iostream>

bool libjcc::parse_subsystem(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node)
{
    Token tok = scanner->next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[SUBSYSTEM_MISSING_IDENTIFIER]);
        return false;
    }

    std::string name = std::get<std::string>(tok.val());
    std::set<std::string> deps;

    tok = scanner->peek();

    // check if : item1, item2, item3
    if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Colon)
    {
        scanner->next(); // consume colon
        tok = scanner->next();
        if (tok.type() != TokenType::Identifier)
        {
            PARMSG(tok, libjcc::Err::ERROR, feedback[SUBSYSTEM_EXPECTED_IDENTIFIER]);
            return false;
        }
        deps.insert(std::get<std::string>(tok.val()));

        tok = scanner->peek();
        while (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Comma)
        {
            scanner->next(); // consume comma
            tok = scanner->next();
            if (tok.type() != TokenType::Identifier)
            {
                PARMSG(tok, libjcc::Err::ERROR, feedback[SUBSYSTEM_EXPECTED_IDENTIFIER]);
                return false;
            }
            deps.insert(std::get<std::string>(tok.val()));
            tok = scanner->peek();
        }
    }

    std::shared_ptr<BlockNode> block;
    if (!parse(job, scanner, block))
        return false;

    tok = scanner->next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[SUBSYSTEM_EXPECTED_SEMICOLON], tok.serialize().c_str());
        return false;
    }

    node = std::make_shared<SubsystemNode>(name, deps, block);

    return true;
}