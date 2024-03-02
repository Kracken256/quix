#ifndef __J_CC_PARSE_NODES_CONST_EXPR_H__
#define __J_CC_PARSE_NODES_CONST_EXPR_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.h>
#include <lexer/token.h>
#include <parse/nodes/basic.h>
#include <parse/nodes/literal.h>

namespace libj
{
    class ConstUnaryExprNode : public ConstExprNode
    {
    public:
        ConstUnaryExprNode() { ntype = NodeType::ConstUnaryExprNode; }
        ConstUnaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &expr) : m_op(op), m_expr(expr) { ntype = NodeType::ConstUnaryExprNode; }
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
        ConstBinaryExprNode() { ntype = NodeType::ConstBinaryExprNode; }
        ConstBinaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &lhs, const std::shared_ptr<ConstExprNode> &rhs)
            : m_op(op), m_lhs(lhs), m_rhs(rhs) { ntype = NodeType::ConstBinaryExprNode; }
        virtual ~ConstBinaryExprNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        Operator m_op;
        std::shared_ptr<ConstExprNode> m_lhs;
        std::shared_ptr<ConstExprNode> m_rhs;
    };
}

#endif // __J_CC_PARSE_NODES_CONST_EXPR_H__