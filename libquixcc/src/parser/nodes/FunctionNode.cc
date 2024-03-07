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

#include <parse/nodes/FunctionNode.h>

llvm::Function *libquixcc::FunctionDeclNode::codegen(LLVMContext &ctx) const
{
    std::vector<llvm::Type *> params;
    for (const auto &param : m_params)
    {
        params.push_back(param->m_type->codegen(ctx));
    }
    llvm::FunctionType *ftype = llvm::FunctionType::get(m_return_type->codegen(ctx), params, m_variadic);
    llvm::Function *func;

    if (ctx.m_pub)
        func = llvm::Function::Create(ftype, llvm::Function::ExternalLinkage, m_name, *ctx.m_module);
    else
        func = llvm::Function::Create(ftype, llvm::Function::PrivateLinkage, m_name, *ctx.m_module);

    size_t i = 0;
    for (auto &arg : func->args())
    {
        arg.setName(m_params[i]->m_name);
        i++;
    }
    return func;
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