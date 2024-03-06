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

#include <parse/nodes/struct.h>

std::string libquixcc::StructTypeNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructTypeNode\",";
    s += "\"fields\":[";
    for (size_t i = 0; i < m_fields.size(); i++)
    {
        s += m_fields[i]->to_json();
        if (i != m_fields.size() - 1)
        {
            s += ",";
        }
    }
    s += "]}";
    return s;
}

llvm::Type *libquixcc::StructTypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    std::vector<llvm::Type *> fields;

    for (auto &field : m_fields)
        fields.push_back(field->codegen(ctx));

    return llvm::StructType::create(*ctx.m_ctx, fields);
}

size_t libquixcc::StructTypeNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

size_t libquixcc::StructTypeNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

std::string libquixcc::StructDeclNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructDeclNode\",";
    s += "\"name\":\"" + m_name + "\"";
    s += "}";
    return s;
}

llvm::Value *libquixcc::StructDeclNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::string libquixcc::StructFieldNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructFieldNode\",";
    s += "\"name\":\"" + m_name + "\",";
    s += "\"type\":" + m_type->to_json();
    if (m_value)
        s += ",\"value\":" + m_value->to_json();
    s += "}";
    return s;
}

llvm::Constant *libquixcc::StructFieldNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

size_t libquixcc::StructFieldNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

size_t libquixcc::StructFieldNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

std::string libquixcc::StructDefNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructDefNode\",";
    s += "\"name\":\"" + m_name + "\",";
    s += "\"fields\":[";
    for (size_t i = 0; i < m_fields.size(); i++)
    {
        s += m_fields[i]->to_json();
        if (i != m_fields.size() - 1)
        {
            s += ",";
        }
    }
    s += "]}";
    return s;
}

llvm::Constant *libquixcc::StructDefNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

size_t libquixcc::StructDefNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}

size_t libquixcc::StructDefNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    return 0;
}