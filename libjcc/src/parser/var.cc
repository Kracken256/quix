#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>

using namespace libjcc;

bool libjcc::parse_var(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node)
{
    Token tok = scanner->next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[VAR_DECL_MISSING_IDENTIFIER]);
        return false;
    }

    std::string name = std::get<std::string>(tok.val());

    tok = scanner->next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Colon)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[VAR_DECL_MISSING_COLON]);
        return false;
    }

    std::shared_ptr<TypeNode> type;

    if (!parse_type(job, scanner, type))
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[VAR_DECL_TYPE_ERR], name.c_str());
        return false;
    }

    tok = scanner->next();
    if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Semicolon)
    {
        // No initializer
        node = std::make_shared<VarDeclNode>(name, std::static_pointer_cast<TypeNode>(type), nullptr);
    }
    else if (tok.type() == TokenType::Operator && std::get<Operator>(tok.val()) == Operator::Assign)
    {
        // Parse initializer
        std::shared_ptr<ConstExprNode> init;
        if (!parse_const_expr(job, scanner, Token(TokenType::Punctor, Punctor::Semicolon), init))
        {
            PARMSG(tok, libjcc::Err::ERROR, feedback[VAR_DECL_INIT_ERR], name.c_str());
            return false;
        }

        tok = scanner->next();
        if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
        {
            PARMSG(tok, libjcc::Err::ERROR, feedback[VAR_DECL_MISSING_PUNCTOR], name.c_str());
            return false;
        }

        node = std::make_shared<VarDeclNode>(name, std::static_pointer_cast<TypeNode>(type), init);
    }
    else
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[VAR_DECL_MISSING_PUNCTOR], name.c_str());
        return false;
    }

    return true;
}