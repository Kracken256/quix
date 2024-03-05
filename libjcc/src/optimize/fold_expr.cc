#include <optimize/fold_expr.h>
#include <stack>
#include <queue>

using namespace libjcc;

static void fold_const_string_expr(std::shared_ptr<libjcc::ParseNode> parent, std::shared_ptr<libjcc::ParseNode> *child)
{
    if ((*child)->ntype != NodeType::ConstBinaryExprNode)
        return;

    auto bin_expr = std::static_pointer_cast<libjcc::ConstBinaryExprNode>(*child);
    std::string concat;

    std::queue<std::shared_ptr<libjcc::ConstExprNode>> stack;
    stack.push(bin_expr->m_lhs);
    stack.push(bin_expr->m_rhs);

    while (!stack.empty())
    {
        auto node = stack.front();
        stack.pop();

        if (node->ntype == NodeType::ConstBinaryExprNode)
        {
            auto bin_node = std::static_pointer_cast<libjcc::ConstBinaryExprNode>(node);
            if (bin_node->m_op != Operator::Plus)
                return;

            stack.push(bin_node->m_lhs);
            stack.push(bin_node->m_rhs);
        }
        else if (node->ntype == NodeType::StringLiteralNode)
        {
            auto str_node = std::static_pointer_cast<libjcc::StringLiteralNode>(node);
            concat += str_node->m_val;
        }
        else
        {
            return; // Not a string literal
        }
    }

    parent->replace_child(*child, std::make_shared<libjcc::StringLiteralNode>(concat));
}

void libjcc::optimize::fold_expr(std::shared_ptr<libjcc::AST> ast)
{
    ast->dfs_preorder(fold_const_string_expr);
}