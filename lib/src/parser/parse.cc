#include <parse.hpp>
#include <nodes.hpp>
#include <error.hpp>
#include <iostream>

using namespace libj;

static bool parse_type(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::ParseNode> &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        message(job, libj::Err::ERROR, "Expected identifier");
        return false;
    }

    static std::set<std::string> primitive_types = {
        "u8",
        "u16",
        "u32",
        "u64",
        "i8",
        "i16",
        "i32",
        "i64",
    };

    if (primitive_types.find(std::get<std::string>(tok.val())) == primitive_types.end())
    {
        message(job, libj::Err::ERROR, "Unknown type");
        return false;
    }

    if (std::get<std::string>(tok.val()) == "u8")
    {
        node = std::make_shared<U8TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "u16")
    {
        node = std::make_shared<U16TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "u32")
    {
        node = std::make_shared<U32TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "u64")
    {
        node = std::make_shared<U64TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i8")
    {
        node = std::make_shared<I8TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i16")
    {
        node = std::make_shared<I16TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i32")
    {
        node = std::make_shared<I32TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i64")
    {
        node = std::make_shared<I64TypeNode>();
    }



    return true;
}

static bool parse_var(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::StmtNode> &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        message(job, libj::Err::ERROR, "Expected identifier");
        return false;
    }

    std::string name = std::get<std::string>(tok.val());

    tok = lexer.next();
    if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Colon)
    {
        message(job, libj::Err::ERROR, "Expected colon");
        return false;
    }

    std::shared_ptr<ParseNode> type;

    // Parse type
    if (!parse_type(job, lexer, type))
        return false;

    tok = lexer.next();
    if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::Semicolon)
    {
        // No initializer
        node = std::make_shared<VarDeclNode>(name, std::static_pointer_cast<TypeNode>(type), nullptr);
    };

    return true;
}

bool libj::Parser::parse(jcc_job_t &job, libj::Lexer &lexer, AST &ast)
{
    Token tok;

    while ((tok = lexer.next()).type() != TokenType::Eof)
    {
        std::cout << tok.serialize() << std::endl;
        if (tok.type() != TokenType::Keyword)
        {
            message(job, libj::Err::ERROR, "Expected keyword");
            return false;
        }

        std::shared_ptr<StmtNode> node;

        switch (std::get<Keyword>(tok.val()))
        {
        case Keyword::Var:
            if (!parse_var(job, lexer, node))
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

    // Create global variable
    // auto i32Initializer = llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm_ctx), 42);
    // llvm::GlobalVariable *gvar = new llvm::GlobalVariable(module, llvm::Type::getInt32Ty(llvm_ctx), false, llvm::GlobalValue::ExternalLinkage, i32Initializer, "gvar");

    // (void)gvar;

    return true;
}