#ifndef __J_CC_PARSE_NODES_BASIC_H__
#define __J_CC_PARSE_NODES_BASIC_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.h>

namespace libjcc
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
        EnumDeclNode,


        StructDefNode,
        EnumDefNode,
        ArrayTypeNode,
        UserTypeNode,

        SubsystemNode,
    };

    class ParseNode
    {
    public:
        ParseNode() = default;
        virtual ~ParseNode() = default;
        virtual std::string to_json() const = 0;
        virtual std::shared_ptr<ParseNode> clone() const = 0;

        virtual bool operator==(const ParseNode &other) const = default;

        NodeType ntype = NodeType::ParseNode;
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
        virtual std::shared_ptr<ParseNode> clone() const override;
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
        virtual std::shared_ptr<ParseNode> clone() const override;

        std::vector<std::shared_ptr<StmtNode>> m_stmts;
    };

    ///=========================================================================

    class BasicTypeNode : public TypeNode
    {
    public:
        BasicTypeNode() { ntype = NodeType::BasicTypeNode; }
        virtual ~BasicTypeNode() = default;
    };
}

#endif // __J_CC_PARSE_NODES_BASIC_H__