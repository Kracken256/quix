#define JCC_INTERNAL

#include <prep/macro/readstdin.h>
#include <lexer/lex.h>
#include <error/message.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

static void enable_noecho()
{
#if !defined(__linux__)
#error "Unsupported platform"
#endif

    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

static void disable_noecho()
{
#if !defined(__linux__)
#error "Unsupported platform"
#endif

    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

bool libjcc::macro::ParseReadStdin(jcc_job_t *job, const Token &tok, const std::string &directive, const std::string &parameter, std::vector<libjcc::Token> &exp)
{
    // readstdin [noecho] [binary] <maxlen>

    (void)directive;

    std::vector<libjcc::Token> tokens;
    if (!libjcc::StringLexer::QuickLex(parameter, tokens))
    {
        libjcc::message(*job, libjcc::Err::ERROR, "Failed to lex readstdin parameter");
        return false;
    }

    if (tokens.empty())
    {
        libjcc::message(*job, libjcc::Err::ERROR, "Empty parameter for readstdin");
        return false;
    }

    bool noecho = false;
    bool binary = false;
    bool expand = false;
    size_t maxlen = 0;

    Token t = tokens[0];
    if (t.type() == TokenType::Identifier && tokens.size() > 1)
    {
        // check for noecho and/or binary
        // if present, noecho is first
        if (std::get<std::string>(t.val()) == "noecho")
        {
            noecho = true;
            t = tokens[1];
        }
        if (std::get<std::string>(t.val()) == "binary")
        {
            binary = true;
            if ((uint)(noecho + 1) >= tokens.size())
            {
                libjcc::message(*job, libjcc::Err::ERROR, "Invalid readstdin argument count");
                return false;
            }
            t = tokens[noecho + 1];
        }
        if (std::get<std::string>(t.val()) == "expand")
        {
            expand = true;
            if ((uint)(noecho + binary + 1) >= tokens.size())
            {
                libjcc::message(*job, libjcc::Err::ERROR, "Invalid readstdin argument count");
                return false;
            }
            t = tokens[noecho + binary + 1];
        }
    }

    if (t.type() != TokenType::IntegerLiteral)
    {
        libjcc::message(*job, libjcc::Err::ERROR, "Invalid readstdin maxlen");
        return false;
    }

    maxlen = std::stoull(std::get<std::string>(t.val()));

    (void)binary;

    if (maxlen == 0)
        return true;

    if (noecho)
        enable_noecho();

    std::string input;
    if (binary)
    {
        input.resize(maxlen);
        size_t len = fread(&input[0], 1, maxlen, stdin);
        input.resize(len);
    }
    else
    {
        std::getline(std::cin, input);
    }

    if (expand)
    {
        if (!StringLexer::QuickLex(input, exp))
        {
            libjcc::message(*job, libjcc::Err::ERROR, "Failed to lex readstdin input");
            disable_noecho();
            return false;
        }
    }
    else
    {
        exp.push_back(Token(TokenType::StringLiteral, input));
    }

    if (noecho)
        disable_noecho();

    return true;
}