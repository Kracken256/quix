#include <gtest/gtest.h>

#include <lex.hpp>
#include <map>
#include <string>
#include <cstdio>
#include <iostream>

static std::map<std::string, libj::Token> expected_tokens = {
    
};

static const char *simple_program = R"()";

using namespace libj;

static std::vector<libj::Token> expected = {
   
};

TEST(Lexer, Identifiers)
{
    for (auto &pair : expected_tokens)
    {
        libj::Lexer lex;
        FILE *src = fmemopen((void *)pair.first.c_str(), pair.first.size(), "r");
        if (!lex.set_source(src))
        {
            FAIL() << "Failed to set source";
        }
        auto tok = lex.next();
        ASSERT_EQ(tok.type(), pair.second.type());
        ASSERT_EQ(tok.val(), pair.second.val());
        fclose(src);
    }
}

TEST(Lexer, SimpleProgram)
{
    libj::Lexer lex;
    FILE *src = fmemopen((void *)simple_program, strlen(simple_program), "r");
    if (!lex.set_source(src))
    {
        FAIL() << "Failed to set source";
    }

    std::vector<libj::Token> tokens;

    while (true)
    {
        auto tok = lex.next();
        tokens.push_back(tok);
        if (tok.type() == libj::TokenType::Eof)
        {
            break;
        }

        std::cout << tok.serialize(true) << ", ";
    }

    fclose(src);

    ASSERT_EQ(tokens.size(), expected.size());

    for (size_t i = 0; i < tokens.size(); i++)
    {
        ASSERT_EQ(tokens[i].type(), expected[i].type());
        ASSERT_EQ(tokens[i].val(), expected[i].val());
    }
}
