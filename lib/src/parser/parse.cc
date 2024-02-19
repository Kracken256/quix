#include <parse.hpp>
#include <nodes.hpp>
#include <message.hpp>
#include <iostream>
#include <macro.h>

using namespace libj;

static bool parse_struct(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::StmtNode> &node)
{
    /*
        struct name {
            a: typeA [= const_exprA];
            b: typeB [= const_exprB];
        };
    */
    (void)job;
    (void)lexer;
    (void)node;
    return false;
}

bool libj::Parser::parse(jcc_job_t &job, libj::Lexer &lexer, AST &ast)
{
    Token tok;

    while ((tok = lexer.next()).type() != TokenType::Eof)
    {
        if (tok.type() != TokenType::Keyword)
        {
            PARMSG(tok, libj::Err::ERROR, "Parser failed because a keyword was expected, but the token %s was found", tok.serialize().c_str());
            return false;
        }

        std::shared_ptr<StmtNode> node;

        switch (std::get<Keyword>(tok.val()))
        {
        case Keyword::Var:
            if (!parse_var(job, lexer, node))
                return false;
            break;
        case Keyword::Let:
            if (!parse_let(job, lexer, node))
                return false;
            break;
        case Keyword::Struct:
            if (!parse_struct(job, lexer, node))
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