////////////////////////////////////////////////////////////////////////////////////
///                                                                              ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///      ░▒▓█▓▒░                                                                 ///
///       ░▒▓██▓▒░                                                               ///
///                                                                              ///
///     * QUIX LANG COMPILER - The official compiler for the Quix language.      ///
///     * Copyright (c) 2024, Wesley C. Jones. All rights reserved.              ///
///     * License terms may be found in the LICENSE file.                        ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#define QUIXCC_INTERNAL

#include <prep/macro/print.h>
#include <lexer/lex.h>
#include <error/message.h>
#include <iostream>

bool libquixcc::macro::ParsePrint(quixcc_job_t *job, const Token &tok, const std::string &directive, const std::string &parameter, std::vector<libquixcc::Token> &exp)
{
    // print [mode] <message>
    (void)directive;
    (void)exp;

    std::vector<libquixcc::Token> tokens;
    if (!libquixcc::StringLexer::QuixkLex(parameter, tokens))
    {
        libquixcc::message(*job, libquixcc::Err::ERROR, "Failed to lex print message");
        return false;
    }

    if (tokens.empty())
    {
        libquixcc::message(*job, libquixcc::Err::ERROR, "Empty print message");
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
            libquixcc::message(*job, libquixcc::Err::ERROR, "Invalid print level");
            return false;
        }

        switch (level)
        {
        case DEBUG:
            prepmsg(*job, tok, libquixcc::Err::DEBUG, std::get<std::string>(tokens[1].val()));
            break;
        case INFO:
            prepmsg(*job, tok, libquixcc::Err::INFO, std::get<std::string>(tokens[1].val()));
            break;
        case WARNING:
            prepmsg(*job, tok, libquixcc::Err::WARN, std::get<std::string>(tokens[1].val()));
            break;
        case ERROR:
            prepmsg(*job, tok, libquixcc::Err::ERROR, std::get<std::string>(tokens[1].val()));
            break;
        case RAW:
            std::cout << std::get<std::string>(tokens[1].val());
            break;
        }
    }
    else
    {
        prepmsg(*job, tok, libquixcc::Err::INFO, std::get<std::string>(t.val()));
    }

    return true;
}