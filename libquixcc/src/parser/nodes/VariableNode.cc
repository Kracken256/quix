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

#include <parse/nodes/VariableNode.h>
#include <mangle/Symbol.h>

llvm::Value *libquixcc::VarDeclNode::codegen(libquixcc::LLVMContext &ctx) const
{
    llvm::Type *type = m_type->codegen(ctx);
    if (!type)
    {
        return nullptr;
    }

    llvm::Constant *init = nullptr;
    if (m_init)
    {
        init = static_cast<llvm::Constant *>(m_init->codegen(ctx));
        if (!init)
        {
            return nullptr;
        }
    }

    if (ctx.m_pub)
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::ExternalLinkage, init, Symbol::mangle(this, ctx.prefix));
    else
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::PrivateLinkage, init, Symbol::mangle(this, ctx.prefix));
}

llvm::Value *libquixcc::LetDeclNode::codegen(libquixcc::LLVMContext &ctx) const
{
    llvm::Type *type = m_type->codegen(ctx);
    if (!type)
    {
        return nullptr;
    }

    llvm::Constant *init = nullptr;
    if (m_init)
    {
        init = static_cast<llvm::Constant *>(m_init->codegen(ctx));
        if (!init)
        {
            return nullptr;
        }
    }

    if (ctx.m_pub)
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::ExternalLinkage, init, Symbol::mangle(this, ctx.prefix));
    else
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::PrivateLinkage, init, Symbol::mangle(this, ctx.prefix));
}

llvm::Value *libquixcc::ConstDeclNode::codegen(libquixcc::LLVMContext &ctx) const
{
    llvm::Type *type = m_type->codegen(ctx);
    if (!type)
    {
        return nullptr;
    }

    llvm::Constant *init = nullptr;
    if (m_init)
    {
        init = static_cast<llvm::Constant *>(m_init->codegen(ctx));
        if (!init)
        {
            return nullptr;
        }
    }

    if (ctx.m_pub)
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::ExternalLinkage, init, Symbol::mangle(this, ctx.prefix));
    else
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::PrivateLinkage, init, Symbol::mangle(this, ctx.prefix));
}
