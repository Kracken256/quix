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

#include <parse/nodes/variable.h>
#include <mangle/symbol.h>

std::string libquixcc::VarDeclNode::to_json() const
{
    std::string json = "{\"ntype\":\"VarDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ",\"init\":" + m_init->to_json();
    }

    json += "}";

    return json;
}

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

size_t libquixcc::VarDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    return 0;
}

size_t libquixcc::VarDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    return 0;
}

std::string libquixcc::LetDeclNode::to_json() const
{
    std::string json = "{\"ntype\":\"LetDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ",\"init\":" + m_init->to_json();
    }

    json += "}";

    return json;
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

size_t libquixcc::LetDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    return 0;
}

size_t libquixcc::LetDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    return 0;
}

std::string libquixcc::ConstDeclNode::to_json() const
{
    std::string json = "{\"ntype\":\"ConstDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ",\"init\":" + m_init->to_json();
    }

    json += "}";

    return json;
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

size_t libquixcc::ConstDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    if (ntype != NodeType::ConstDeclNode)
        return 1;

    size_t ret = 1;
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_type));
    ret += m_type->dfs_preorder(callback);
    if (m_init)
    {
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_init));
        ret += m_init->dfs_preorder(callback);
    }

    return ret;
}

size_t libquixcc::ConstDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    size_t ret = 1;
    if (m_init)
    {
        ret += m_init->dfs_postorder(callback);
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_init));
    }

    ret += m_type->dfs_postorder(callback);
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_type));

    return ret;
}