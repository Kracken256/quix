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
        virtual std::string to_string() const = 0;

        virtual llvm::Value *codegen(LLVMContext &ctx) const = 0;
        virtual std::unique_ptr<ParseNode> clone() const = 0;
    };

    class ExprNode : public ParseNode
    {
    public:
        ExprNode() = default;
        virtual ~ExprNode() = default;
    };

    class StmtNode : public ParseNode
    {
    public:
        StmtNode() = default;
        virtual ~StmtNode() = default;
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

        std::vector<std::unique_ptr<StmtNode>> m_stmts;
    };

    ///=========================================================================

    class TypeNode : public DeclNode
    {
    public:
        TypeNode() = default;
        virtual ~TypeNode() = default;
    };

    class PrimTypeNode : public TypeNode
    {
    public:
        PrimTypeNode() = default;
        virtual ~PrimTypeNode() = default;
    };

    class CompTypeNode : public TypeNode
    {
    public:
        CompTypeNode() = default;
        virtual ~CompTypeNode() = default;
    };

    class FnTypeNode : public TypeNode
    {
    public:
        FnTypeNode() = default;
        virtual ~FnTypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::vector<std::unique_ptr<TypeNode>> m_params;
        std::unique_ptr<TypeNode> m_ret_type;
    };

    ///=========================================================================

    class I8TypeNode : public PrimTypeNode
    {
    public:
        I8TypeNode() = default;
        virtual ~I8TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        int8_t m_value;
    };

    class I16TypeNode : public PrimTypeNode
    {
    public:
        I16TypeNode() = default;
        virtual ~I16TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        int16_t m_value;
    };

    class I32TypeNode : public PrimTypeNode
    {
    public:
        I32TypeNode() = default;
        virtual ~I32TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        int32_t m_value;
    };

    class I64TypeNode : public PrimTypeNode
    {
    public:
        I64TypeNode() = default;
        virtual ~I64TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        int64_t m_value;
    };

    class U8TypeNode : public PrimTypeNode
    {
    public:
        U8TypeNode() = default;
        virtual ~U8TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        uint8_t m_value;
    };

    class U16TypeNode : public PrimTypeNode
    {
    public:
        U16TypeNode() = default;
        virtual ~U16TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        uint16_t m_value;
    };

    class U32TypeNode : public PrimTypeNode
    {
    public:
        U32TypeNode() = default;
        virtual ~U32TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        uint32_t m_value;
    };

    class U64TypeNode : public PrimTypeNode
    {
    public:
        U64TypeNode() = default;
        virtual ~U64TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        uint64_t m_value;
    };

    class F32TypeNode : public PrimTypeNode
    {
    public:
        F32TypeNode() = default;
        virtual ~F32TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        float m_value;
    };

    class F64TypeNode : public PrimTypeNode
    {
    public:
        F64TypeNode() = default;
        virtual ~F64TypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        double m_value;
    };

    class BoolTypeNode : public PrimTypeNode
    {
    public:
        BoolTypeNode() = default;
        virtual ~BoolTypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        bool m_value;
    };

    class CharTypeNode : public PrimTypeNode
    {
    public:
        CharTypeNode() = default;
        virtual ~CharTypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        char m_value;
    };

    class StringTypeNode : public PrimTypeNode
    {
    public:
        StringTypeNode() = default;
        virtual ~StringTypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::string m_value;
    };

    class ArrayTypeNode : public PrimTypeNode
    {
    public:
        ArrayTypeNode() = default;
        virtual ~ArrayTypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::vector<std::unique_ptr<PrimTypeNode>> m_value;
    };

    ///=========================================================================

    class StructTypeNode : public CompTypeNode
    {
    public:
        StructTypeNode() = default;
        virtual ~StructTypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::string m_name;
    };

    class UnionTypeNode : public CompTypeNode
    {
    public:
        UnionTypeNode() = default;
        virtual ~UnionTypeNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::string m_name;
    };

    ///=========================================================================

    class StructDeclNode : public DeclNode
    {
    public:
        StructDeclNode() = default;
        virtual ~StructDeclNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::unique_ptr<StructTypeNode> m_type;
    };

    class UnionDeclNode : public DeclNode
    {
    public:
        UnionDeclNode() = default;
        virtual ~UnionDeclNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::unique_ptr<UnionTypeNode> m_type;        
    };

    class VarDeclNode : public DeclNode
    {
    public:
        VarDeclNode() = default;
        virtual ~VarDeclNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::unique_ptr<TypeNode> m_type;
        std::unique_ptr<ExprNode> m_value;
    };

    class FnDeclNode : public DeclNode
    {
    public:
        FnDeclNode() = default;
        virtual ~FnDeclNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::unique_ptr<FnTypeNode> m_type;
    };

    ///=========================================================================

    class FnDefNode : public DefNode
    {
    public:
        FnDefNode() = default;
        virtual ~FnDefNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::unique_ptr<FnDeclNode> m_decl;
        std::unique_ptr<BlockNode> m_body;
    };

    class StructDefNode : public DefNode
    {
    public:
        StructDefNode() = default;
        virtual ~StructDefNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::unique_ptr<StructDeclNode> m_decl;
        std::vector<std::pair<std::string, std::unique_ptr<TypeNode>>> m_fields;
    };

    class UnionDefNode : public DefNode
    {
    public:
        UnionDefNode() = default;
        virtual ~UnionDefNode() = default;

        virtual std::string to_string() const override;
        virtual llvm::Value *codegen(LLVMContext &ctx) const override;
        virtual std::unique_ptr<ParseNode> clone() const override;

        std::unique_ptr<UnionDeclNode> m_decl;
        std::vector<std::pair<std::string, std::unique_ptr<TypeNode>>> m_fields;
    };
};

#endif // __J_CC_PARSE_TREE_H__