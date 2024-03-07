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

#ifndef __QUIXCC_PARSE_NODES_BASIC_H__
#define __QUIXCC_PARSE_NODES_BASIC_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/LLVMWrapper.h>
#include <parse/NodeTraveral.h>
#include <parse/JsonSerialize.h>
#include <parse/NodeType.h>

namespace libquixcc
{
    class ParseNode;

    class ParseNode : public std::enable_shared_from_this<ParseNode>
    {
    public:
        ParseNode() = default;

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) { return visitor.visit(std::static_pointer_cast<ParseNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) { return visitor.visit(std::static_pointer_cast<ParseNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const { return visitor.visit(this); }

        /// @brief Replace a child node with a new node.
        /// @warning Careful, this function depends on wierd reinterpretation of shared_ptr.
        /// @param old_node **Reference** to the old node member in the parent node.
        /// @param new_node The new node to replace with.
        void replace_child(std::shared_ptr<ParseNode> &old_node, std::shared_ptr<libquixcc::ParseNode> new_node);

        /// @brief Count the number of nodes in the tree.
        /// @return The number of nodes in the tree.
        size_t count();

        NodeType ntype = NodeType::ParseNode;
    };

#define PARSE_NODE_SIZE sizeof(ParseNode)

    class ExprNode : public ParseNode
    {
    public:
        ExprNode() = default;

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ExprNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ExprNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(LLVMContext &ctx) const = 0;
    };

    class ConstExprNode : public ExprNode
    {
    public:
        ConstExprNode() { ntype = NodeType::ConstExprNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ConstExprNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ConstExprNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Constant *codegen(LLVMContext &ctx) const = 0;
    };

    class StmtNode : public ParseNode
    {
    public:
        StmtNode() { ntype = NodeType::StmtNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<StmtNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<StmtNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(LLVMContext &ctx) const = 0;
    };

    class TypeNode : public ParseNode
    {
    public:
        TypeNode() { ntype = NodeType::TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(LLVMContext &ctx) const = 0;
    };

    class UserTypeNode : public TypeNode
    {
    public:
        UserTypeNode() { ntype = NodeType::UserTypeNode; }
        UserTypeNode(const std::string &name) : m_name(name) { ntype = NodeType::UserTypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UserTypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UserTypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(LLVMContext &ctx) const override;

        std::string m_name;
    };

    class DeclNode : public StmtNode
    {
    public:
        DeclNode() { ntype = NodeType::DeclNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<DeclNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<DeclNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }
    };

    class DefNode : public StmtNode
    {
    public:
        DefNode() { ntype = NodeType::DefNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<DefNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<DefNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }
    };

    class BlockNode : public StmtNode
    {
    public:
        BlockNode() { ntype = NodeType::BlockNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<BlockNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<BlockNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(LLVMContext &ctx) const override;

        std::vector<std::shared_ptr<StmtNode>> m_stmts;
    };

    ///=========================================================================

    class BasicTypeNode : public TypeNode
    {
    public:
        BasicTypeNode() { ntype = NodeType::BasicTypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<BasicTypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<BasicTypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }
    };
}

#endif // __QUIXCC_PARSE_NODES_BASIC_H__