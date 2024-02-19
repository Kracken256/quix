#include <parse.hpp>
#include <macro.h>
#include <message.hpp>

using namespace libj;

bool libj::parse_let(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::StmtNode> &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libj::Err::ERROR, "Missing identifier in variable declaration. To fix the issue, name your variable. Syntax: let name: type [= const_expr];");
        return false;
    }

    std::string name = std::get<std::string>(tok.val());

    tok = lexer.next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Colon)
    {
        PARMSG(tok, libj::Err::ERROR, "Missing colon separator in variable declaration. To fix the issue, insert a colon between the variable name and the typename. Syntax: let name: type [= const_expr];");
        return false;
    }

    std::shared_ptr<ParseNode> type;

    // Parse type
    if (!parse_type(job, lexer, type))
    {
        PARMSG(tok, libj::Err::ERROR, "An error occurred while parsing the type of variable '%s'. Syntax: let name: type [= const_expr];", name.c_str());
        return false;
    }

    tok = lexer.next();
    if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Semicolon)
    {
        // No initializer
        node = std::make_shared<LetDeclNode>(name, std::static_pointer_cast<TypeNode>(type), nullptr);
    }
    else if (tok.type() == TokenType::Operator && std::get<Operator>(tok.val()) == Operator::Assign)
    {
        // Parse initializer
        std::shared_ptr<ConstExprNode> init;
        if (!parse_const_expr(job, lexer, init))
        {
            PARMSG(tok, libj::Err::ERROR, "Declaration of variable '%s' requires an initializer, but an error occurred while parsing the initializer. Syntax: let name: type [= const_expr];", name.c_str());
        }

        node = std::make_shared<LetDeclNode>(name, std::static_pointer_cast<TypeNode>(type), init);
    }
    else
    {
        PARMSG(tok, libj::Err::ERROR, "Declaration of variable '%s' requires an initializer OR a semicolon punctuator, but neither was found. Make sure to terminate all statements with a semicolon. Syntax: let name: type [= const_expr];", name.c_str());
        return false;
    }

    return true;
}