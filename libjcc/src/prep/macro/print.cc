#define JCC_INTERNAL

#include <prep/macro/print.h>
#include <lexer/lex.h>
#include <error/message.h>
#include <iostream>

bool libjcc::macro::ParsePrint(jcc_job_t *job, const Token &tok, const std::string &directive, const std::string &parameter, std::vector<libjcc::Token> &exp)
{
    // print [mode] <message>

    std::vector<libjcc::Token> tokens;
    if (!libjcc::StringLexer::QuickLex(parameter, tokens))
    {
        libjcc::message(*job, libjcc::Err::ERROR, "Failed to lex print message");
        return false;
    }

    if (tokens.empty())
    {
        libjcc::message(*job, libjcc::Err::ERROR, "Empty print message");
        return false;
    }

    enum Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        RAW,
    } level = INFO;

    Token t = tokens[0];
    if (t.type() == TokenType::Identifier && tokens.size() == 2)
    {
        std::string id = std::get<std::string>(t.val());
        if (id == "debug")
            level = DEBUG;
        else if (id == "info")
            level = INFO;
        else if (id == "warning" || id == "warn")
            level = WARNING;
        else if (id == "error")
            level = ERROR;
        else if (id == "raw")
            level = RAW;
        else
        {
            libjcc::message(*job, libjcc::Err::ERROR, "Invalid print level");
            return false;
        }

        switch (level)
        {
        case DEBUG:
            prepmsg(*job, tok, libjcc::Err::DEBUG, std::get<std::string>(tokens[1].val()));
            break;
        case INFO:
            prepmsg(*job, tok, libjcc::Err::INFO, std::get<std::string>(tokens[1].val()));
            break;
        case WARNING:
            prepmsg(*job, tok, libjcc::Err::WARN, std::get<std::string>(tokens[1].val()));
            break;
        case ERROR:
            prepmsg(*job, tok, libjcc::Err::ERROR, std::get<std::string>(tokens[1].val()));
            break;
        case RAW:
            std::cout << std::get<std::string>(tokens[1].val());
            break;
        }
    }
    else
    {
        prepmsg(*job, tok, libjcc::Err::INFO, std::get<std::string>(t.val()));
    }

    return true;
}