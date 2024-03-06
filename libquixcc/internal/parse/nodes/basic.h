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

#include <llvm/llvm-ctx.h>

namespace libquixcc
{
    enum class NodeType
    {
        ParseNode,
        ExprNode,
        ConstExprNode,
        StmtNode,
        TypeNode,
        RootNode,
        DeclNode,
        DefNode,
        BlockNode,
        BasicTypeNode,

        ConstUnaryExprNode,
        ConstBinaryExprNode,

        IdentifierNode,

        U8TypeNode,
        U16TypeNode,
        U32TypeNode,
        U64TypeNode,
        I8TypeNode,
        I16TypeNode,
        I32TypeNode,
        I64TypeNode,
        F32TypeNode,
        F64TypeNode,
        BoolTypeNode,
        CharTypeNode,
        VoidTypeNode,
        StringTypeNode,

        StructTypeNode,
        UnionTypeNode,
        ArrayTypeNode,
        UserTypeNode,

        LiteralNode,
        IntegerLiteralNode,
        FloatLiteralNode,
        StringLiteralNode,
        CharLiteralNode,
        BoolLiteralNode,

        VarDeclNode,
        LetDeclNode,
        ConstDeclNode,

        StructDeclNode,
        UnionDeclNode,
        EnumDeclNode,
        FunctionDeclNode,

        StructDefNode,
        StructFieldNode,
        UnionDefNode,
        EnumDefNode,
        FunctionDefNode,

        SubsystemNode,
        ExportNode,
    };

    class ParseNode : public std::enable_shared_from_this<ParseNode>
    {
    public:
        ParseNode() = default;
        virtual ~ParseNode() = default;
        virtual std::string to_json() const = 0;

        NodeType ntype = NodeType::ParseNode;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);

        void replace_child(std::shared_ptr<ParseNode> &find, std::shared_ptr<libquixcc::ParseNode> replace);
        size_t count();
        bool has_immidiate_child(const std::shared_ptr<ParseNode> node);
    };

    class ExprNode : public ParseNode
    {
    public:
        ExprNode() = default;
        virtual ~ExprNode() = default;

        virtual llvm::Value *codegen(LLVMContext &ctx) const = 0;
    };

    class ConstExprNode : public ExprNode
    {
    public:
        ConstExprNode() { ntype = NodeType::ConstExprNode; }
        virtual ~ConstExprNode() = default;

        virtual llvm::Constant *codegen(LLVMContext &ctx) const = 0;
    };

    class StmtNode : public ParseNode
    {
    public:
        StmtNode() { ntype = NodeType::StmtNode; }
        virtual ~StmtNode() = default;

        virtual llvm::Value *codegen(LLVMContext &ctx) const = 0;
    };

    class TypeNode : public ParseNode
    {
    public:
        TypeNode() { ntype = NodeType::TypeNode; }
        virtual ~TypeNode() = default;

        virtual llvm::Type *codegen(LLVMContext &ctx) const = 0;
    };

    class UserTypeNode : public TypeNode
    {
    public:
        UserTypeNode() { ntype = NodeType::UserTypeNode; }
        UserTypeNode(const std::string &name) : m_name(name) { ntype = NodeType::UserTypeNode; }
        virtual ~UserTypeNode() = default;

        virtual std::string to_json() const override;
        virtual llvm::Type *codegen(LLVMContext &ctx) const override;

        std::string m_name;
    };

    class DeclNode : public StmtNode
    {
    public:
        DeclNode() { ntype = NodeType::DeclNode; }
        virtual ~DeclNode() = default;
    };

    class DefNode : public StmtNode
    {
    public:
        DefNode() { ntype = NodeType::DefNode; }
        virtual ~DefNode() = default;
    };

    class BlockNode : public StmtNode
    {
    public:
        BlockNode() { ntype = NodeType::BlockNode; }
        virtual ~BlockNode() = default;

        virtual std::string to_json() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;

        std::vector<std::shared_ptr<StmtNode>> m_stmts;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);
    };

    ///=========================================================================

    class BasicTypeNode : public TypeNode
    {
    public:
        BasicTypeNode() { ntype = NodeType::BasicTypeNode; }
        virtual ~BasicTypeNode() = default;
    };
}

#endif // __QUIXCC_PARSE_NODES_BASIC_H__