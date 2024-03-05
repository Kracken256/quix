#define JCC_INTERNAL

#include <parse/parser.h>
#include <error/message.h>
#include <macro.h>

using namespace libjcc;

bool libjcc::parse(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, std::shared_ptr<libjcc::BlockNode> &group, bool expect_braces)
{
    Token tok;

    if (expect_braces)
    {
        tok = scanner->next();
        if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::OpenBrace)
        {
            PARMSG(tok, libjcc::Err::ERROR, feedback[PARSER_EXPECTED_LEFT_BRACE], tok.serialize().c_str());
            return false;
        }
    }

    group = std::make_shared<BlockNode>();

    while ((tok = scanner->next()).type() != TokenType::Eof)
    {

        if (expect_braces)
        {
            if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::CloseBrace)
                break;
        }

        if (tok.type() != TokenType::Keyword)
        {
            PARMSG(tok, libjcc::Err::ERROR, feedback[PARSER_EXPECTED_KEYWORD], tok.serialize().c_str());
            return false;
        }

        std::shared_ptr<StmtNode> node;

        switch (std::get<Keyword>(tok.val()))
        {
        case Keyword::Var:
            if (!parse_var(job, scanner, node))
                return false;
            break;
        case Keyword::Let:
            if (!parse_let(job, scanner, node))
                return false;
            break;
        case Keyword::Const:
            if (!parse_const(job, scanner, node))
                return false;
            break;
        case Keyword::Enum:
            if (!parse_enum(job, scanner, node))
                return false;
            break;
        case Keyword::Struct:
            if (!parse_struct(job, scanner, node))
                return false;
            break;
        case Keyword::Union:
            if (!parse_union(job, scanner, node))
                return false;
            break;
        case Keyword::Subsystem:
            if (!parse_subsystem(job, scanner, node))
                return false;
            break;
        case Keyword::Fn:
            if (!parse_function(job, scanner, node))
                return false;
            break;
        case Keyword::Pub:
            if (!parse_pub(job, scanner, node))
                return false;
            break;
        default:
            break;
        }

        if (node)
            group->m_stmts.push_back(node);
    }

    // llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_ctx), false);
    // llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", &module);

    // llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvm_ctx, "entry", mainFunc);
    // builder.SetInsertPoint(entry);
    // builder.CreateRetVoid();

    return true;
}