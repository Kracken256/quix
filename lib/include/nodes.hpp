#ifndef __J_CC_PARSE_TREE_H__
#define __J_CC_PARSE_TREE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/IR/Value.h>
#include <llvm-ctx.hpp>

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
        std::shared_ptr<ConstExprNode> m_init;
    };

};

#endif // __J_CC_PARSE_TREE_H__