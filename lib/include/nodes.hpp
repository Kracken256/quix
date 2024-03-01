#ifndef __J_CC_PARSE_TREE_H__
#define __J_CC_PARSE_TREE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm-ctx.hpp>
#include <lex.hpp>

namespace libj
{
    class ParseNode
    {
    public:
        ParseNode() = default;
        virtual ~ParseNode() = default;
        virtual std::string to_json() const = 0;
        virtual std::shared_ptr<ParseNode> clone() const = 0;
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
        ConstExprNode() = default;
        virtual ~ConstExprNode() = default;

        virtual llvm::Constant *codegen(LLVMContext &ctx) const = 0;
    };

    class StmtNode : public ParseNode
    {
    public:
        StmtNode() = default;
        virtual ~StmtNode() = default;

        virtual llvm::Value *codegen(LLVMContext &ctx) const = 0;
    };

    class TypeNode : public ParseNode
    {
    public:
        TypeNode() = default;
        virtual ~TypeNode() = default;

        virtual llvm::Type *codegen(LLVMContext &ctx) const = 0;
    };

    class RootNode : public ParseNode
    {
    public:
        RootNode() = default;
        virtual ~RootNode() = default;

        virtual std::string to_json() const override;
        virtual std::shared_ptr<ParseNode> clone() const override;

        std::vector<std::shared_ptr<StmtNode>> m_children;
    };

    ///=========================================================================

    class DeclNode : public StmtNode
    {
    public:
        DeclNode() = default;
        virtual ~DeclNode() = default;
    };

    class DefNode : public StmtNode
    {
    public:
        DefNode() = default;
        virtual ~DefNode() = default;
    };

    class BlockNode : public StmtNode
    {
    public:
        BlockNode() = default;
        virtual ~BlockNode() = default;

        std::vector<std::shared_ptr<StmtNode>> m_stmts;
    };

    ///=========================================================================

    class BasicTypeNode : public TypeNode
    {
    public:
        BasicTypeNode() = default;
        virtual ~BasicTypeNode() = default;
    };

    ///=========================================================================

    class U8TypeNode : public BasicTypeNode
    {
    public:
        U8TypeNode() = default;
        virtual ~U8TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class U16TypeNode : public BasicTypeNode
    {
    public:
        U16TypeNode() = default;
        virtual ~U16TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class U32TypeNode : public BasicTypeNode
    {
    public:
        U32TypeNode() = default;
        virtual ~U32TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class U64TypeNode : public BasicTypeNode
    {
    public:
        U64TypeNode() = default;
        virtual ~U64TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class I8TypeNode : public BasicTypeNode
    {
    public:
        I8TypeNode() = default;
        virtual ~I8TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class I16TypeNode : public BasicTypeNode
    {
    public:
        I16TypeNode() = default;
        virtual ~I16TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class I32TypeNode : public BasicTypeNode
    {
    public:
        I32TypeNode() = default;
        virtual ~I32TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class I64TypeNode : public BasicTypeNode
    {
    public:
        I64TypeNode() = default;
        virtual ~I64TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class F32TypeNode : public BasicTypeNode
    {
    public:
        F32TypeNode() = default;
        virtual ~F32TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class F64TypeNode : public BasicTypeNode
    {
    public:
        F64TypeNode() = default;
        virtual ~F64TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class BoolTypeNode : public BasicTypeNode
    {
    public:
        BoolTypeNode() = default;
        virtual ~BoolTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class CharTypeNode : public BasicTypeNode
    {
    public:
        CharTypeNode() = default;
        virtual ~CharTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class StringTypeNode : public BasicTypeNode
    {
    public:
        StringTypeNode() = default;
        virtual ~StringTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    class VoidTypeNode : public BasicTypeNode
    {
    public:
        VoidTypeNode() = default;
        virtual ~VoidTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };

    ///=========================================================================

    class VarDeclNode : public DeclNode
    {
    public:
        VarDeclNode() = default;
        VarDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type, const std::shared_ptr<ConstExprNode> &init)
            : m_name(name), m_type(type), m_init(init) {}
        virtual ~VarDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ExprNode> m_init;
    };

    class LetDeclNode : public DeclNode
    {
    public:
        LetDeclNode() = default;
        LetDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type, const std::shared_ptr<ConstExprNode> &init)
            : m_name(name), m_type(type), m_init(init) {}
        virtual ~LetDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ExprNode> m_init;
    };

    /// =========================================================================

    class LiteralNode : public ConstExprNode
    {
    public:
        LiteralNode() = default;
        virtual ~LiteralNode() = default;
    };

    class IntegerLiteralNode : public LiteralNode
    {
    public:
        IntegerLiteralNode() = default;
        IntegerLiteralNode(const std::string &val) : m_val(val) {}
        virtual ~IntegerLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };

    class FloatLiteralNode : public LiteralNode
    {
    public:
        FloatLiteralNode() = default;
        FloatLiteralNode(const std::string &val) : m_val(val) {}
        virtual ~FloatLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };

    class StringLiteralNode : public LiteralNode
    {
    public:
        StringLiteralNode() = default;
        StringLiteralNode(const std::string &val) : m_val(val) {}
        virtual ~StringLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };

    class CharLiteralNode : public LiteralNode
    {
    public:
        CharLiteralNode() = default;
        CharLiteralNode(const std::string &val) : m_val(val) {}
        virtual ~CharLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };

    class IdentifierNode : public ExprNode
    {
    public:
        IdentifierNode() = default;
        IdentifierNode(const std::string &name) : m_name(name) {}
        virtual ~IdentifierNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
    };

    /// =========================================================================

    class ConstUnaryExprNode : public ConstExprNode
    {
    public:
        ConstUnaryExprNode() = default;
        ConstUnaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &expr) : m_op(op), m_expr(expr) {}
        virtual ~ConstUnaryExprNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        Operator m_op;
        std::shared_ptr<ConstExprNode> m_expr;
    };

    class ConstBinaryExprNode : public ConstExprNode
    {
    public:
        ConstBinaryExprNode() = default;
        ConstBinaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &lhs, const std::shared_ptr<ConstExprNode> &rhs)
            : m_op(op), m_lhs(lhs), m_rhs(rhs) {}
        virtual ~ConstBinaryExprNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        Operator m_op;
        std::shared_ptr<ConstExprNode> m_lhs;
        std::shared_ptr<ConstExprNode> m_rhs;
    };

} // namespace libj

#endif // __J_CC_PARSE_TREE_H__