#include <optimize/fold_expr.h>
#include <stack>

using namespace libjcc;

static void fold_const_expr(std::shared_ptr<libjcc::ParseNode> parrent, std::shared_ptr<libjcc::ParseNode> *child)
{
    if ((*child)->ntype != NodeType::ConstBinaryExprNode)
        return;

    auto bin_expr = std::static_pointer_cast<ConstBinaryExprNode>(*child);

    if (bin_expr->m_lhs->ntype != NodeType::StringLiteralNode || bin_expr->m_rhs->ntype != NodeType::StringLiteralNode)
        return;

    auto lhs = std::static_pointer_cast<StringLiteralNode>(bin_expr->m_lhs);
    auto rhs = std::static_pointer_cast<StringLiteralNode>(bin_expr->m_rhs);

    parrent->replace_child(*child, std::make_shared<StringLiteralNode>(lhs->m_val + rhs->m_val));
}

void libjcc::optimize::fold_expr(std::shared_ptr<libjcc::AST> ast)
{
    ast->dfs_preorder(fold_const_expr);
}