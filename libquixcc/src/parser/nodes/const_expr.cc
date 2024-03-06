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

#define QUIXCC_INTERNAL

#include <parse/nodes/const_expr.h>
#include <lexer/lex.h>

std::string libquixcc::ConstUnaryExprNode::to_json() const
{
    std::string json = "{";
    json += "\"type\":\"ConstUnaryExprNode\",";
    json += "\"operator\":\"" + operator_map_inverse.at(m_op) + "\",";
    json += "\"expr\":" + m_expr->to_json();
    json += "}";
    return json;
}

llvm::Constant *libquixcc::ConstUnaryExprNode::codegen(libquixcc::LLVMContext &ctx) const
{
    llvm::Constant *expr = m_expr->codegen(ctx);
    if (!expr)
        return nullptr;

    switch (m_op)
    {
    case Operator::Minus:
        return llvm::ConstantExpr::getNeg(expr);
    case Operator::Plus:
        return expr;
    case Operator::BitNot:
        return llvm::ConstantExpr::getNot(expr);
    case Operator::Not:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_EQ, expr, llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, 0, false)));
    case Operator::Increment:
        return llvm::ConstantExpr::getAdd(expr, llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, 1, false)));
    case Operator::Decrement:
        return llvm::ConstantExpr::getSub(expr, llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, 1, false)));
    default:
        return nullptr;
    }
}

std::shared_ptr<libquixcc::ParseNode> libquixcc::ConstUnaryExprNode::clone() const
{
    return std::make_shared<ConstUnaryExprNode>(*this);
}

size_t libquixcc::ConstUnaryExprNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{

    if (ntype != NodeType::ConstUnaryExprNode)
        return 1;
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_expr));
    return m_expr->dfs_preorder(callback) + 1;
}

size_t libquixcc::ConstUnaryExprNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    size_t ret = 1 + m_expr->dfs_postorder(callback);
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_expr));
    return ret + 1;
}

std::string libquixcc::ConstBinaryExprNode::to_json() const
{
    std::string json = "{";
    json += "\"type\":\"ConstBinaryExprNode\",";
    json += "\"operator\":\"" + operator_map_inverse.at(m_op) + "\",";
    json += "\"lhs\":" + m_lhs->to_json() + ",";
    json += "\"rhs\":" + m_rhs->to_json();
    json += "}";
    return json;
}

llvm::Constant *libquixcc::ConstBinaryExprNode::codegen(libquixcc::LLVMContext &ctx) const
{
    llvm::Constant *lhs = m_lhs->codegen(ctx);
    if (!lhs)
        return nullptr;

    llvm::Constant *rhs = m_rhs->codegen(ctx);
    if (!rhs)
        return nullptr;

    switch (m_op)
    {
    case Operator::LessThan:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_SLT, lhs, rhs);
    case Operator::GreaterThan:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_SGT, lhs, rhs);
    case Operator::LessThanEqual:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_SLE, lhs, rhs);
    case Operator::GreaterThanEqual:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_SGE, lhs, rhs);
    case Operator::Equal:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_EQ, lhs, rhs);
    case Operator::NotEqual:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_NE, lhs, rhs);

    case Operator::Plus:
        return llvm::ConstantExpr::getAdd(lhs, rhs);
    case Operator::Minus:
        return llvm::ConstantExpr::getSub(lhs, rhs);
    case Operator::Multiply:
        return llvm::ConstantExpr::getMul(lhs, rhs);

    case Operator::BitAnd:
        return llvm::ConstantExpr::getAnd(lhs, rhs);
    case Operator::BitOr:
        return llvm::ConstantExpr::getOr(lhs, rhs);
    case Operator::BitXor:
        return llvm::ConstantExpr::getXor(lhs, rhs);
    case Operator::LeftShift:
        return llvm::ConstantExpr::getShl(lhs, rhs);
    case Operator::RightShift:
        return llvm::ConstantExpr::getLShr(lhs, rhs);

    case Operator::And:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_NE, llvm::ConstantExpr::getAnd(lhs, rhs), llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, 0, false)));
    case Operator::Or:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_NE, llvm::ConstantExpr::getOr(lhs, rhs), llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, 0, false)));
    case Operator::Xor:
        return llvm::ConstantExpr::getICmp(llvm::CmpInst::Predicate::ICMP_NE, llvm::ConstantExpr::getXor(lhs, rhs), llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, 0, false)));

    default:
        return nullptr;
    }
}

std::shared_ptr<libquixcc::ParseNode> libquixcc::ConstBinaryExprNode::clone() const
{
    return std::make_shared<ConstBinaryExprNode>(*this);
}

size_t libquixcc::ConstBinaryExprNode::dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    if (ntype != NodeType::ConstBinaryExprNode)
        return 1;

    size_t ret = 1;

    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_lhs));
    ret += m_lhs->dfs_preorder(callback);
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_rhs));
    ret += m_rhs->dfs_preorder(callback);

    return ret;
}

size_t libquixcc::ConstBinaryExprNode::dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback)
{
    size_t ret = 1 + m_lhs->dfs_postorder(callback);
    ret += m_rhs->dfs_postorder(callback);
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libquixcc::ParseNode> *>(&m_lhs));
    return ret + 1;
}