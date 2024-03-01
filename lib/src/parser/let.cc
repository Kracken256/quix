#include <parse.hpp>
#include <macro.h>
#include <message.hpp>

using namespace libj;

bool libj::parse_let(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::StmtNode> &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[LET_DECL_MISSING_IDENTIFIER]);
        return false;
    }

    std::string name = std::get<std::string>(tok.val());

    tok = lexer.next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Colon)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[LET_DECL_MISSING_COLON]);
        return false;
    }

    std::shared_ptr<ParseNode> type;

    if (!parse_type(job, lexer, type))
    {
        PARMSG(tok, libj::Err::ERROR, feedback[LET_DECL_TYPE_ERR], name.c_str());
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
            PARMSG(tok, libj::Err::ERROR, feedback[LET_DECL_INIT_ERR], name.c_str());
            return false;
        }

        tok = lexer.next();
        if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
        {
            PARMSG(tok, libj::Err::ERROR, feedback[LET_DECL_MISSING_PUNCTOR], name.c_str());
            return false;
        }

        node = std::make_shared<LetDeclNode>(name, std::static_pointer_cast<TypeNode>(type), init);
    }
    else
    {
        PARMSG(tok, libj::Err::ERROR, feedback[LET_DECL_MISSING_PUNCTOR], name.c_str());
        return false;
    }

    return true;
}