#include <optimize/fold_expr.h>
#include <stack>

#include <iostream>

using namespace libjcc;

static void fold_const_expr(libjcc::ConstExprNode *expr)
{
    std::cout << "Folding expression: " << std::endl;
}

void libjcc::optimize::fold_expr(std::shared_ptr<libjcc::BlockNode> &ast)
{
    ast->depth_first_traversal(
        [&](libjcc::ParseNode *node)
        {
            std::cout << "Node type: " << (int)node->ntype << std::endl;
            if (node->ntype == NodeType::ConstExprNode)
            {
                fold_const_expr(static_cast<libjcc::ConstExprNode *>(node));
            }
        });
}