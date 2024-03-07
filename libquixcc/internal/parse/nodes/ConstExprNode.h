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

#ifndef __QUIXCC_PARSE_NODES_CONST_EXPR_H__
#define __QUIXCC_PARSE_NODES_CONST_EXPR_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/LLVMWrapper.h>
#include <lexer/Token.h>
#include <parse/nodes/BasicNodes.h>
#include <parse/nodes/LiteralNode.h>

namespace libquixcc
{
    class ConstUnaryExprNode : public ConstExprNode
    {
    public:
        ConstUnaryExprNode() { ntype = NodeType::ConstUnaryExprNode; }
        ConstUnaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &expr) : m_op(op), m_expr(expr) { ntype = NodeType::ConstUnaryExprNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ConstUnaryExprNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ConstUnaryExprNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        llvm::Constant *codegen(LLVMContext &ctx) const override;

        Operator m_op;
        std::shared_ptr<ConstExprNode> m_expr;
    };

    class ConstBinaryExprNode : public ConstExprNode
    {
    public:
        ConstBinaryExprNode() { ntype = NodeType::ConstBinaryExprNode; }
        ConstBinaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &lhs, const std::shared_ptr<ConstExprNode> &rhs)
            : m_op(op), m_lhs(lhs), m_rhs(rhs) { ntype = NodeType::ConstBinaryExprNode; }

        virtual size_t dfs_preorder(ParseNodePreorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ConstBinaryExprNode>(shared_from_this())); }
        virtual size_t dfs_postorder(ParseNodePostorderVisitor visitor) override { return visitor.visit(std::static_pointer_cast<ConstBinaryExprNode>(shared_from_this())); }
        virtual std::string to_json(ParseNodeJsonSerializerVisitor visitor) const override { return visitor.visit(this); }

        llvm::Constant *codegen(LLVMContext &ctx) const override;

        Operator m_op;
        std::shared_ptr<ConstExprNode> m_lhs;
        std::shared_ptr<ConstExprNode> m_rhs;
    };
}

#endif // __QUIXCC_PARSE_NODES_CONST_EXPR_H__