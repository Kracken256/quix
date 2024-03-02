#ifndef __J_CC_PARSE_NODES_INTEGER_H__
#define __J_CC_PARSE_NODES_INTEGER_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.hpp>
#include <parse/nodes/basic.hpp>

namespace libj
{
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
}

#endif // __J_CC_PARSE_NODES_INTEGER_H__