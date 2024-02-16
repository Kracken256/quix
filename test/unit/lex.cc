#include <gtest/gtest.h>

#include <lex.hpp>
#include <map>
#include <string>
#include <cstdio>
#include <iostream>

static std::map<std::string, libj::Token> expected_tokens = {
    {"# hello\n", libj::Token(libj::TokenType::Comment, " hello")},
    {"100\n", libj::Token(libj::TokenType::Number, 100.0)},
    {"def\n", libj::Token(libj::TokenType::Define, "")},
    {"extern\n", libj::Token(libj::TokenType::Extern, "")},
    {"foo\n", libj::Token(libj::TokenType::Identifier, "foo")},
    {"_bar\n", libj::Token(libj::TokenType::Identifier, "_bar")},
    {"*\n", libj::Token(libj::TokenType::Operator, "*")},
    {"+\n", libj::Token(libj::TokenType::Operator, "+")},
    {"-\n", libj::Token(libj::TokenType::Operator, "-")},
    {"/\n", libj::Token(libj::TokenType::Operator, "/")},
    {"%\n", libj::Token(libj::TokenType::Operator, "%")},
    {"=\n", libj::Token(libj::TokenType::Operator, "=")},
    {"<\n", libj::Token(libj::TokenType::Operator, "<")},
    {">\n", libj::Token(libj::TokenType::Operator, ">")},
    {"(\n", libj::Token(libj::TokenType::Operator, "(")},
    {")\n", libj::Token(libj::TokenType::Operator, ")")},
    {",\n", libj::Token(libj::TokenType::Operator, ",")},
    {";\n", libj::Token(libj::TokenType::Operator, ";")},
    {"\n", libj::Token(libj::TokenType::Eof, "")},
};

static const char *simple_program = R"(# Compute the x'th fibonacci number.
def fib(x)
  if x < 3 then
    1
  else
    fib(x-1)+fib(x-2)

# This expression will compute the 40th number.
fib(40)
)";

using namespace libj;

static std::vector<libj::Token> expected = {
    Token(TokenType::Comment, " Compute the x'th fibonacci number."),
    Token(TokenType::Define, ""),
    Token(TokenType::Identifier, "fib"),
    Token(TokenType::Operator, "("),
    Token(TokenType::Identifier, "x"),
    Token(TokenType::Operator, ")"),
    Token(TokenType::Identifier, "if"),
    Token(TokenType::Identifier, "x"),
    Token(TokenType::Operator, "<"),
    Token(TokenType::Number, 3.0),
    Token(TokenType::Identifier, "then"),
    Token(TokenType::Number, 1.0),
    Token(TokenType::Identifier, "else"),
    Token(TokenType::Identifier, "fib"),
    Token(TokenType::Operator, "("),
    Token(TokenType::Identifier, "x"),
    Token(TokenType::Operator, "-"),
    Token(TokenType::Number, 1.0),
    Token(TokenType::Operator, ")"),
    Token(TokenType::Operator, "+"),
    Token(TokenType::Identifier, "fib"),
    Token(TokenType::Operator, "("),
    Token(TokenType::Identifier, "x"),
    Token(TokenType::Operator, "-"),
    Token(TokenType::Number, 2.0),
    Token(TokenType::Operator, ")"),
    Token(TokenType::Comment, " This expression will compute the 40th number."),
    Token(TokenType::Identifier, "fib"),
    Token(TokenType::Operator, "("),
    Token(TokenType::Number, 40.0),
    Token(TokenType::Operator, ")"),
    Token(TokenType::Eof, ""),
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
