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

#include <parse/NodeTraversal.h>
#include <parse/nodes/AllNodes.h>

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ParseNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ParseNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ExprNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ExprNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ConstExprNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ConstExprNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::StmtNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::StmtNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::DeclNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::DeclNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::DefNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::DefNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::BlockNode> node)
{
    size_t count = 0;
    for (auto &stmt : node->m_stmts)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&stmt));
        count += stmt->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::BlockNode> node)
{
    size_t count = 0;
    for (auto &stmt : node->m_stmts)
    {
        count += stmt->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&stmt));
    }
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::BasicTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::BasicTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ConstUnaryExprNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_expr));
    return node->m_expr->dfs_preorder(*this) + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ConstUnaryExprNode> node)
{
    size_t count = node->m_expr->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_expr));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ConstBinaryExprNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_lhs));
    size_t count = node->m_lhs->dfs_preorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_rhs));
    count += node->m_rhs->dfs_preorder(*this);
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ConstBinaryExprNode> node)
{
    size_t count = 0;
    count += node->m_rhs->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_rhs));
    count += node->m_lhs->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_lhs));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::IdentifierNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::IdentifierNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::U8TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::U8TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::U16TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::U16TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::U32TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::U32TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::U64TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::U64TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::I8TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::I8TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::I16TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::I16TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::I32TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::I32TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::I64TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::I64TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::F32TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::F32TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::F64TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::F64TypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::BoolTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::BoolTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::CharTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::CharTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::VoidTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::VoidTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::StringTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::StringTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::StructTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::StructTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::UnionTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::UnionTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ArrayTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ArrayTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::UserTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::UserTypeNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::LiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::LiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::IntegerLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::IntegerLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::FloatLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::FloatLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::StringLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::StringLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::CharLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::CharLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::BoolLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::BoolLiteralNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::VarDeclNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    size_t count = node->m_type->dfs_preorder(*this);
    if (node->m_init)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_init));
        count += node->m_init->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::VarDeclNode> node)
{
    size_t count = 0;
    if (node->m_init)
    {
        count += node->m_init->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_init));
    }

    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    count += node->m_type->dfs_postorder(*this);
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::LetDeclNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    size_t count = node->m_type->dfs_preorder(*this);
    if (node->m_init)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_init));
        count += node->m_init->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::LetDeclNode> node)
{
    size_t count = 0;
    if (node->m_init)
    {
        count += node->m_init->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_init));
    }

    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    count += node->m_type->dfs_postorder(*this);
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ConstDeclNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    size_t count = node->m_type->dfs_preorder(*this);
    if (node->m_init)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_init));
        count += node->m_init->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ConstDeclNode> node)
{
    size_t count = 0;
    if (node->m_init)
    {
        count += node->m_init->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_init));
    }

    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    count += node->m_type->dfs_postorder(*this);
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::StructDeclNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::StructDeclNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::UnionDeclNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::UnionDeclNode> node)
{
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::EnumDeclNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    return node->m_type->dfs_preorder(*this) + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::EnumDeclNode> node)
{
    size_t count = node->m_type->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::FunctionDeclNode> node)
{
    size_t count = 0;
    for (auto &param : node->m_params)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&param));
        count += param->dfs_preorder(*this);
    }
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_return_type));
    count += node->m_return_type->dfs_preorder(*this);
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::FunctionDeclNode> node)
{
    size_t count = 0;
    for (auto &param : node->m_params)
    {
        count += param->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&param));
    }
    count += node->m_return_type->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_return_type));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::StructDefNode> node)
{
    size_t count = 0;
    for (auto &field : node->m_fields)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&field));
        count += field->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::StructDefNode> node)
{
    size_t count = 0;
    for (auto &field : node->m_fields)
    {
        count += field->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&field));
    }
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::StructFieldNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    size_t count = node->m_type->dfs_preorder(*this);
    if (node->m_value)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
        count += node->m_value->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::StructFieldNode> node)
{
    size_t count = 0;
    if (node->m_value)
    {
        count += node->m_value->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
    }
    count += node->m_type->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::UnionDefNode> node)
{
    size_t count = 0;
    for (auto &field : node->m_fields)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&field));
        count += field->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::UnionDefNode> node)
{
    size_t count = 0;
    for (auto &field : node->m_fields)
    {
        count += field->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&field));
    }
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::UnionFieldNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    size_t count = node->m_type->dfs_preorder(*this);
    if (node->m_value)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
        count += node->m_value->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::UnionFieldNode> node)
{
    size_t count = 0;
    if (node->m_value)
    {
        count += node->m_value->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
    }
    count += node->m_type->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::EnumDefNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    size_t count = node->m_type->dfs_preorder(*this);
    for (auto &field : node->m_fields)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&field));
        count += field->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::EnumDefNode> node)
{
    size_t count = 0;
    for (auto &field : node->m_fields)
    {
        count += field->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&field));
    }
    count += node->m_type->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::EnumFieldNode> node)
{
    if (node->m_value)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
        return node->m_value->dfs_preorder(*this) + 1;
    }
    return 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::EnumFieldNode> node)
{
    if (node->m_value)
    {
        size_t count = node->m_value->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
        return count + 1;
    }
    return 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::FunctionDefNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_decl));
    size_t count = node->m_decl->dfs_preorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_body));
    count += node->m_body->dfs_preorder(*this);
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::FunctionDefNode> node)
{
    size_t count = node->m_body->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_body));
    count += node->m_decl->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_decl));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::FunctionParamNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    size_t count = node->m_type->dfs_preorder(*this);
    if (node->m_value)
    {
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
        count += node->m_value->dfs_preorder(*this);
    }
    return count + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::FunctionParamNode> node)
{
    size_t count = 0;
    if (node->m_value)
    {
        count += node->m_value->dfs_postorder(*this);
        m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_value));
    }
    count += node->m_type->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_type));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::SubsystemNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_block));
    return node->m_block->dfs_preorder(*this) + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::SubsystemNode> node)
{
    size_t count = node->m_block->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_block));
    return count + 1;
}

size_t libquixcc::ParseNodePreorderVisitor::visit(std::shared_ptr<libquixcc::ExportNode> node)
{
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_stmt));
    return node->m_stmt->dfs_preorder(*this) + 1;
}

size_t libquixcc::ParseNodePostorderVisitor::visit(std::shared_ptr<libquixcc::ExportNode> node)
{
    size_t count = node->m_stmt->dfs_postorder(*this);
    m_callback(node, reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&node->m_stmt));
    return count + 1;
}