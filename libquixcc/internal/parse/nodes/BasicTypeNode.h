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
        U8TypeNode() { ntype = NodeType::U8TypeNode; }
        static std::shared_ptr<U8TypeNode> m_instance;

    public:
        static std::shared_ptr<U8TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<U8TypeNode>(new U8TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class U16TypeNode : public BasicTypeNode
    {
        U16TypeNode() { ntype = NodeType::U16TypeNode; }
        static std::shared_ptr<U16TypeNode> m_instance;

    public:
        static std::shared_ptr<U16TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<U16TypeNode>(new U16TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class U32TypeNode : public BasicTypeNode
    {
        U32TypeNode() { ntype = NodeType::U32TypeNode; }
        static std::shared_ptr<U32TypeNode> m_instance;

    public:
        static std::shared_ptr<U32TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<U32TypeNode>(new U32TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class U64TypeNode : public BasicTypeNode
    {
        U64TypeNode() { ntype = NodeType::U64TypeNode; }
        static std::shared_ptr<U64TypeNode> m_instance;

    public:
        static std::shared_ptr<U64TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<U64TypeNode>(new U64TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I8TypeNode : public BasicTypeNode
    {
        I8TypeNode() { ntype = NodeType::I8TypeNode; }
        static std::shared_ptr<I8TypeNode> m_instance;

    public:
        static std::shared_ptr<I8TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<I8TypeNode>(new I8TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I16TypeNode : public BasicTypeNode
    {
        I16TypeNode() { ntype = NodeType::I16TypeNode; }
        static std::shared_ptr<I16TypeNode> m_instance;

    public:
        static std::shared_ptr<I16TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<I16TypeNode>(new I16TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I32TypeNode : public BasicTypeNode
    {
        I32TypeNode() { ntype = NodeType::I32TypeNode; }
        static std::shared_ptr<I32TypeNode> m_instance;

    public:
        static std::shared_ptr<I32TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<I32TypeNode>(new I32TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class I64TypeNode : public BasicTypeNode
    {
        I64TypeNode() { ntype = NodeType::I64TypeNode; }
        static std::shared_ptr<I64TypeNode> m_instance;

    public:
        static std::shared_ptr<I64TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<I64TypeNode>(new I64TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class F32TypeNode : public BasicTypeNode
    {
        F32TypeNode() { ntype = NodeType::F32TypeNode; }
        static std::shared_ptr<F32TypeNode> m_instance;

    public:
        static std::shared_ptr<F32TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<F32TypeNode>(new F32TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class F64TypeNode : public BasicTypeNode
    {
        F64TypeNode() { ntype = NodeType::F64TypeNode; }
        static std::shared_ptr<F64TypeNode> m_instance;

    public:
        static std::shared_ptr<F64TypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<F64TypeNode>(new F64TypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class BoolTypeNode : public BasicTypeNode
    {
        BoolTypeNode() { ntype = NodeType::BoolTypeNode; }
        static std::shared_ptr<BoolTypeNode> m_instance;

    public:
        static std::shared_ptr<BoolTypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<BoolTypeNode>(new BoolTypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class CharTypeNode : public BasicTypeNode
    {
        CharTypeNode() { ntype = NodeType::CharTypeNode; }
        static std::shared_ptr<CharTypeNode> m_instance;

    public:
        static std::shared_ptr<CharTypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<CharTypeNode>(new CharTypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };

    class VoidTypeNode : public BasicTypeNode
    {
        VoidTypeNode() { ntype = NodeType::VoidTypeNode; }
        static std::shared_ptr<VoidTypeNode> m_instance;

    public:
        static std::shared_ptr<VoidTypeNode> create()
        {
            if (m_instance == nullptr)
                m_instance = std::shared_ptr<VoidTypeNode>(new VoidTypeNode());
            return m_instance;
        }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(this); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(this); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        virtual llvm::Type *codegen(const CodegenVisitor &visitor) const override { return visitor.visit(this); }
    };
}

#endif // __QUIXCC_PARSE_NODES_INTEGER_H__