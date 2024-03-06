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

#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>

using namespace libquixcc;

static bool parse_union_field(quixcc_job_t &job, std::shared_ptr<libquixcc::Scanner> scanner, UnionDefNode::Field &node)
{
    Token tok = scanner->next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libquixcc::Err::ERROR, feedback[UNION_FIELD_MISSING_IDENTIFIER]);
        return false;
    }

    node.name = std::get<std::string>(tok.val());

    tok = scanner->next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Colon)
    {
        PARMSG(tok, libquixcc::Err::ERROR, feedback[UNION_FIELD_MISSING_COLON]);
        return false;
    }

    if (!parse_type(job, scanner, node.type))
    {
        PARMSG(tok, libquixcc::Err::ERROR, feedback[UNION_FIELD_TYPE_ERR], node.name.c_str());
        return false;
    }

    tok = scanner->next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
    {
        PARMSG(tok, libquixcc::Err::ERROR, feedback[UNION_FIELD_MISSING_PUNCTOR]);
        return false;
    }

    return true;
}

bool libquixcc::parse_union(quixcc_job_t &job, std::shared_ptr<libquixcc::Scanner> scanner, std::shared_ptr<libquixcc::StmtNode> &node)
{
    Token tok = scanner->next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libquixcc::Err::ERROR, feedback[UNION_DECL_MISSING_IDENTIFIER]);
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
        PARMSG(tok, libquixcc::Err::ERROR, feedback[UNION_DEF_EXPECTED_OPEN_BRACE]);
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
        PARMSG(tok, libquixcc::Err::ERROR, feedback[UNION_DEF_EXPECTED_SEMICOLON]);
        return false;
    }

    auto sdef = std::make_shared<UnionDefNode>();
    sdef->m_name = name;
    sdef->m_fields = fields;
    node = sdef;
    return true;
}