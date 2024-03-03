#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>

using namespace libj;

static bool parse_struct_field(jcc_job_t &job, libj::Lexer &lexer, StructDefNode::Field &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_MISSING_IDENTIFIER]);
        return false;
    }

    node.name = std::get<std::string>(tok.val());

    tok = lexer.next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Colon)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_MISSING_COLON]);
        return false;
    }

    if (!parse_type(job, lexer, node.type))
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_TYPE_ERR], node.name.c_str());
        return false;
    }

    tok = lexer.next();
    if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Semicolon)
    {
        return true;
    }
    else if (tok.type() == TokenType::Operator && std::get<Operator>(tok.val()) == Operator::Assign)
    {
        if (!parse_const_expr(job, lexer, Token(TokenType::Punctor, Punctor::Semicolon), node.value))
        {
            PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_INIT_ERR], node.name.c_str());
            return false;
        }
    }
    else
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_MISSING_PUNCTOR], node.name.c_str());
        return false;
    }

    tok = lexer.next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_MISSING_PUNCTOR], node.name.c_str());
        return false;
    }

    return true;
}

bool libj::parse_struct(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::StmtNode> &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_MISSING_IDENTIFIER]);
        return false;
    }

    std::string name = std::get<std::string>(tok.val());

    tok = lexer.next();
    if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Semicolon)
    {
        node = std::make_shared<StructDeclNode>();
        std::static_pointer_cast<StructDeclNode>(node)->m_name = name;
        return true;
    }
    else if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::OpenBrace)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_EXPECTED_OPEN_BRACE]);
        return false;
    }

    std::vector<StructDefNode::Field> fields;

    while (true)
    {
        tok = lexer.peek();
        if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::CloseBrace)
        {
            lexer.next();
            break;
        }

        StructDefNode::Field field;
        if (!parse_struct_field(job, lexer, field))
            return false;
        fields.push_back(field);
    }

    tok = lexer.next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
    {
        PARMSG(tok, libj::Err::ERROR, feedback[STRUCT_DECL_EXPECTED_SEMICOLON]);
        return false;
    }

    auto sdef = std::make_shared<StructDefNode>();
    sdef->m_name = name;
    sdef->m_fields = fields;
    node = sdef;
    return true;
}