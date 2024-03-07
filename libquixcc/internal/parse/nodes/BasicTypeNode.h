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

#ifndef __QUIXCC_PARSE_NODES_INTEGER_H__
#define __QUIXCC_PARSE_NODES_INTEGER_H__

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
    class U8TypeNode : public BasicTypeNode
    {
    public:
        U8TypeNode() { ntype = NodeType::U8TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U8TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U8TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class U16TypeNode : public BasicTypeNode
    {
    public:
        U16TypeNode() { ntype = NodeType::U16TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U16TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U16TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class U32TypeNode : public BasicTypeNode
    {
    public:
        U32TypeNode() { ntype = NodeType::U32TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U32TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U32TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class U64TypeNode : public BasicTypeNode
    {
    public:
        U64TypeNode() { ntype = NodeType::U64TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U64TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<U64TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I8TypeNode : public BasicTypeNode
    {
    public:
        I8TypeNode() { ntype = NodeType::I8TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I8TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I8TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I16TypeNode : public BasicTypeNode
    {
    public:
        I16TypeNode() { ntype = NodeType::I16TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I16TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I16TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I32TypeNode : public BasicTypeNode
    {
    public:
        I32TypeNode() { ntype = NodeType::I32TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I32TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I32TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I64TypeNode : public BasicTypeNode
    {
    public:
        I64TypeNode() { ntype = NodeType::I64TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I64TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<I64TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class F32TypeNode : public BasicTypeNode
    {
    public:
        F32TypeNode() { ntype = NodeType::F32TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<F32TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<F32TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class F64TypeNode : public BasicTypeNode
    {
    public:
        F64TypeNode() { ntype = NodeType::F64TypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<F64TypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<F64TypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class BoolTypeNode : public BasicTypeNode
    {
    public:
        BoolTypeNode() { ntype = NodeType::BoolTypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<BoolTypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<BoolTypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class CharTypeNode : public BasicTypeNode
    {
    public:
        CharTypeNode() { ntype = NodeType::CharTypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<CharTypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<CharTypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class VoidTypeNode : public BasicTypeNode
    {
    public:
        VoidTypeNode() { ntype = NodeType::VoidTypeNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<VoidTypeNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<VoidTypeNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };
}

#endif // __QUIXCC_PARSE_NODES_INTEGER_H__