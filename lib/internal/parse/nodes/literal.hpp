#ifndef __J_CC_PARSE_NODES_LITERAL_H__
#define __J_CC_PARSE_NODES_LITERAL_H__

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
}

#endif // __J_CC_PARSE_NODES_LITERAL_H__