#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>

using namespace libjcc;

static bool parse_union_field(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, UnionDefNode::Field &node)
{
    Token tok = scanner->next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[UNION_FIELD_MISSING_IDENTIFIER]);
        return false;
    }

    node.name = std::get<std::string>(tok.val());

    tok = scanner->next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Colon)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[UNION_FIELD_MISSING_COLON]);
        return false;
    }

    if (!parse_type(job, scanner, node.type))
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[UNION_FIELD_TYPE_ERR], node.name.c_str());
        return false;
    }

    tok = scanner->next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[UNION_FIELD_MISSING_PUNCTOR]);
        return false;
    }

    return true;
}

bool libjcc::parse_union(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node)
{
    Token tok = scanner->next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[UNION_DECL_MISSING_IDENTIFIER]);
        return false;
    }

    std::string name = std::get<std::string>(tok.val());

    tok = scanner->next();
    if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Semicolon)
    {
        node = std::make_shared<UnionDeclNode>();
        std::static_pointer_cast<UnionDeclNode>(node)->m_name = name;
        return true;
    }
    else if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::OpenBrace)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[UNION_DEF_EXPECTED_OPEN_BRACE]);
        return false;
    }

    std::vector<UnionDefNode::Field> fields;

    while (true)
    {
        tok = scanner->peek();
        if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::CloseBrace)
        {
            scanner->next();
            break;
        }

        UnionDefNode::Field field;
        if (!parse_union_field(job, scanner, field))
            return false;
        fields.push_back(field);
    }

    tok = scanner->next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[UNION_DEF_EXPECTED_SEMICOLON]);
        return false;
    }

    auto sdef = std::make_shared<UnionDefNode>();
    sdef->m_name = name;
    sdef->m_fields = fields;
    node = sdef;
    return true;
}