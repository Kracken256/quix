#include <parse/parser.h>
#include <error/message.h>
#include <macro.h>

using namespace libj;

bool libj::Parser::parse(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, AST &ast)
{
    Token tok;

    while ((tok = scanner->next()).type() != TokenType::Eof)
    {
        if (tok.type() != TokenType::Keyword)
        {
            PARMSG(tok, libj::Err::ERROR, feedback[PARSER_EXPECTED_KEYWORD], tok.serialize().c_str());
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
        case Keyword::Struct:
            if (!parse_struct(job, scanner, node))
                return false;
            break;
        default:
            break;
        }

        if (node)
            ast.m_children.push_back(node);
    }

    // llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_ctx), false);
    // llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", &module);

    // llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvm_ctx, "entry", mainFunc);
    // builder.SetInsertPoint(entry);
    // builder.CreateRetVoid();

    return true;
}