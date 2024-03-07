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

#ifndef __QUIXCC_PARSE_NODES_UNION_H__
#define __QUIXCC_PARSE_NODES_UNION_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/LLVMWrapper.h>
#include <parse/nodes/BasicNodes.h>

namespace libquixcc
{
    class UnionTypeNode : public TypeNode
    {
    public:
        UnionTypeNode() { ntype = NodeType::UnionTypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionTypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionTypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }

        std::vector<std::shared_ptr<TypeNode>> m_fields;
    };

    class UnionDeclNode : public DeclNode
    {
    public:
        UnionDeclNode() { ntype = NodeType::UnionDeclNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionDeclNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionDeclNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }

        std::string m_name;
    };

    class UnionFieldNode : public ParseNode
    {
    public:
        UnionFieldNode() { ntype = NodeType::UnionFieldNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionFieldNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionFieldNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(const CodegenVisitor &visitor) const { return visitor.visit(this); }

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ConstExprNode> m_value;
    };

    class UnionDefNode : public DefNode
    {
    public:
        UnionDefNode() { ntype = NodeType::UnionDefNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionDefNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<UnionDefNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }

        std::string m_name;
        std::vector<std::shared_ptr<UnionFieldNode>> m_fields;
    };
}

#endif // __QUIXCC_PARSE_NODES_UNION_H__