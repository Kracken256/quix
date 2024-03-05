#define JCC_INTERNAL

#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>

using namespace libjcc;

bool libjcc::parse_pub(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::StmtNode> &node)
{
    Token tok = scanner->next();

    if (tok.type() != TokenType::Keyword)
    {
        PARMSG(tok, libjcc::Err::ERROR, feedback[PARSER_EXPECTED_KEYWORD], tok.serialize().c_str());
        return false;
    }

    std::shared_ptr<libjcc::StmtNode> stmt;

    switch (std::get<Keyword>(tok.val()))
    {
    case Keyword::Var:
        if (!parse_var(job, scanner, stmt))
            return false;
        break;
    case Keyword::Let:
        if (!parse_let(job, scanner, stmt))
            return false;
        break;
    case Keyword::Const:
        if (!parse_const(job, scanner, stmt))
            return false;
        break;
    case Keyword::Enum:
        if (!parse_enum(job, scanner, stmt))
            return false;
        break;

    case Keyword::Subsystem:
        if (!parse_subsystem(job, scanner, stmt))
            return false;
        break;
    case Keyword::Fn:
        if (!parse_function(job, scanner, stmt))
            return false;
        break;
    case Keyword::Pub:
        if (!parse_pub(job, scanner, stmt))
            return false;
        break;
    default:
        PARMSG(tok, libjcc::Err::ERROR, feedback[PARSER_EXPECTED_KEYWORD], tok.serialize().c_str());
        return false;
    }

    node = std::make_shared<libjcc::ExportNode>(stmt);

    return true;
}