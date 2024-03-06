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

#include <parse/nodes/basic.h>
#include <parse/nodes/nodes.h>

size_t libquixcc::ParseNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    return 1;
}

size_t libquixcc::ParseNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    return 1;
}

void libquixcc::ParseNode::replace_child(std::shared_ptr<libquixcc::ParseNode> &find, std::shared_ptr<libquixcc::ParseNode> replace)
{
    find = replace;
}

void callback_nop(std::shared_ptr<libquixcc::ParseNode> parrent, std::shared_ptr<libquixcc::ParseNode> *child)
{
}

size_t libquixcc::ParseNode::count()
{
    return dfs_preorder(callback_nop);
}

bool libquixcc::ParseNode::has_immidiate_child(std::shared_ptr<libquixcc::ParseNode> node)
{
    if (node == shared_from_this())
        return false;

    bool found = false;
    dfs_preorder([&](std::shared_ptr<libquixcc::ParseNode> parrent, std::shared_ptr<libquixcc::ParseNode> *child)
                 {
        if (*child == node)
        {
            found = true;
        } });
    return found;
}

std::string libquixcc::UserTypeNode::to_json() const
{
    return "{\"ntype\":\"UserTypeNode\",\"name\":\"" + m_name + "\"}";
}

llvm::Type *libquixcc::UserTypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return nullptr;
}

std::string libquixcc::BlockNode::to_json() const
{
    std::string json = "{\"ntype\":\"BlockNode\",\"stmts\":[";
    for (auto &stmt : m_stmts)
    {
        json += stmt->to_json() + ",";
    }
    if (m_stmts.size() > 0)
    {
        json.pop_back();
    }
    json += "]}";
    return json;
}

llvm::Value *libquixcc::BlockNode::codegen(libquixcc::LLVMContext &ctx) const
{
    for (auto &stmt : m_stmts)
    {
        llvm::Value *val = stmt->codegen(ctx);
        if (!val)
            return nullptr;
    }
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

size_t libquixcc::BlockNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    size_t count = 1;

    if (ntype != NodeType::BlockNode)
        return count;

    for (auto &stmt : m_stmts)
    {
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&stmt));
        count += stmt->dfs_preorder(callback);
    }
    return count;
}

size_t libquixcc::BlockNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode> *)> callback)
{
    size_t count = 1;
    for (auto &stmt : m_stmts)
    {
        count += stmt->dfs_postorder(callback);
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&stmt));
    }

    return count;
}