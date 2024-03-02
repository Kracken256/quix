#ifndef __J_CC_PARSE_NODES_BASIC_H__
#define __J_CC_PARSE_NODES_BASIC_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.hpp>

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
}

#endif // __J_CC_PARSE_NODES_BASIC_H__