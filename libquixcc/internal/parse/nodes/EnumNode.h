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

#ifndef __QUIXCC_PARSE_NODES_ENUM_H__
#define __QUIXCC_PARSE_NODES_ENUM_H__

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
    class EnumDeclNode : public DeclNode
    {
    public:
        EnumDeclNode() { ntype = NodeType::EnumDeclNode; }
        EnumDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type) : m_name(name), m_type(type) { ntype = NodeType::EnumDeclNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<EnumDeclNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<EnumDeclNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
    };

    class EnumFieldNode : public ParseNode
    {
    public:
        EnumFieldNode() { ntype = NodeType::EnumFieldNode; }
        EnumFieldNode(const std::string &name, const std::shared_ptr<ConstExprNode> &value) : m_name(name), m_value(value) { ntype = NodeType::EnumFieldNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<EnumFieldNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<EnumFieldNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }
       
       virtual llvm::Value *codegen(const CodegenVisitor &visitor) const { return visitor.visit(this); }

        std::string m_name;
        std::shared_ptr<ConstExprNode> m_value;
    };

    class EnumDefNode : public DefNode
    {
    public:
        EnumDefNode() { ntype = NodeType::EnumDefNode; }
        EnumDefNode(const std::string &name, const std::shared_ptr<TypeNode> &type) : m_name(name), m_type(type) { ntype = NodeType::EnumDefNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<EnumDefNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<EnumDefNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Value *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::vector<std::shared_ptr<EnumFieldNode>> m_fields;
    };
}

#endif // __QUIXCC_PARSE_NODES_ENUM_H__