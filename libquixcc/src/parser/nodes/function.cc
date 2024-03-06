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

#include <parse/nodes/function.h>

std::string libquixcc::FunctionDeclNode::to_json() const
{
    std::string ret = "{";
    ret += "\"name\": \"" + m_name + "\",";
    ret += "\"params\": [";
    for (size_t i = 0; i < m_params.size(); i++)
    {
        ret += "{";
        ret += "\"name\": \"" + m_params[i].name + "\",";
        ret += "\"type\": " + m_params[i].type->to_json() + ",";
        ret += "\"value\": " + m_params[i].value->to_json();
        ret += "}";
        if (i < m_params.size() - 1)
            ret += ",";
    }
    ret += "],";
    ret += "\"return_type\": " + m_return_type->to_json() + ",";
    ret += "\"variadic\": " + std::to_string(m_variadic) + ",";
    ret += "\"pure\": " + std::to_string(m_pure) + ",";
    ret += "\"thread_safe\": " + std::to_string(m_thread_safe) + ",";
    ret += "\"foreign\": " + std::to_string(m_foreign) + ",";
    ret += "\"nothrow\": " + std::to_string(m_nothrow);
    ret += "}";
    return ret;
}

llvm::Function *libquixcc::FunctionDeclNode::codegen(LLVMContext &ctx) const
{
    std::vector<llvm::Type *> params;
    for (const auto &param : m_params)
    {
        params.push_back(param.type->codegen(ctx));
    }
    llvm::FunctionType *ftype = llvm::FunctionType::get(m_return_type->codegen(ctx), params, m_variadic);
    llvm::Function *func;

    if (ctx.m_pub)
        func = llvm::Function::Create(ftype, llvm::Function::ExternalLinkage, m_name, ctx.m_module.get());
    else
        func = llvm::Function::Create(ftype, llvm::Function::PrivateLinkage, m_name, ctx.m_module.get());

    size_t i = 0;
    for (auto &arg : func->args())
    {
        arg.setName(m_params[i].name);
        i++;
    }
    return func;
}

std::shared_ptr<libquixcc::ParseNode> libquixcc::FunctionDeclNode::clone() const
{
    return std::make_shared<FunctionDeclNode>(*this);
}

size_t libquixcc::FunctionDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

size_t libquixcc::FunctionDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

std::string libquixcc::FunctionDefNode::to_json() const
{
    std::string ret = "{";
    ret += "\"decl\": " + m_decl->to_json() + ",";
    ret += "\"body\": " + m_body->to_json();
    ret += "}";
    return ret;
}

llvm::Value *libquixcc::FunctionDefNode::codegen(LLVMContext &ctx) const
{
    llvm::Function *func = m_decl->codegen(ctx);

    llvm::BasicBlock *EntryBlock = llvm::BasicBlock::Create(*ctx.m_ctx, "entry", func);
    ctx.m_builder->SetInsertPoint(EntryBlock);

    // Create the loop block
    llvm::BasicBlock *LoopBlock = llvm::BasicBlock::Create(*ctx.m_ctx, "loop", func);

    // Branch to the loop block
    ctx.m_builder->CreateBr(LoopBlock);

    // Set insertion point to the loop block
    ctx.m_builder->SetInsertPoint(LoopBlock);

    // Here you would insert code for the loop body

    // Create an unconditional branch back to the loop block
    ctx.m_builder->CreateBr(LoopBlock);

    // If the function returns void, insert a return void instruction at the end of the entry block
    if (func->getReturnType()->isVoidTy())
        ctx.m_builder->SetInsertPoint(EntryBlock);
    // ctx.m_builder->CreateRetVoid();

    return func;
}

std::shared_ptr<libquixcc::ParseNode> libquixcc::FunctionDefNode::clone() const
{
    return std::make_shared<FunctionDefNode>(*this);
}

size_t libquixcc::FunctionDefNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

size_t libquixcc::FunctionDefNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}