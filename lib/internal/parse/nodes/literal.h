#ifndef __J_CC_PARSE_NODES_LITERAL_H__
#define __J_CC_PARSE_NODES_LITERAL_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.h>
#include <parse/nodes/basic.h>

namespace libj
{
    class LiteralNode : public ConstExprNode
    {
    public:
        LiteralNode() { ntype = NodeType::LiteralNode; }
        virtual ~LiteralNode() = default;
    };

    class IntegerLiteralNode : public LiteralNode
    {
    public:
        IntegerLiteralNode() { ntype = NodeType::IntegerLiteralNode; }
        IntegerLiteralNode(const std::string &val) : m_val(val) { ntype = NodeType::IntegerLiteralNode; }
        virtual ~IntegerLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };

    class FloatLiteralNode : public LiteralNode
    {
    public:
        FloatLiteralNode() { ntype = NodeType::FloatLiteralNode; }
        FloatLiteralNode(const std::string &val) : m_val(val) { ntype = NodeType::FloatLiteralNode; }
        virtual ~FloatLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };

    class StringLiteralNode : public LiteralNode
    {
    public:
        StringLiteralNode() { ntype = NodeType::StringLiteralNode; }
        StringLiteralNode(const std::string &val) : m_val(val) { ntype = NodeType::StringLiteralNode; }
        virtual ~StringLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };

    class CharLiteralNode : public LiteralNode
    {
    public:
        CharLiteralNode() { ntype = NodeType::CharLiteralNode; }
        CharLiteralNode(const std::string &val) : m_val(val) { ntype = NodeType::CharLiteralNode; }
        virtual ~CharLiteralNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_val;
    };
}

#endif // __J_CC_PARSE_NODES_LITERAL_H__