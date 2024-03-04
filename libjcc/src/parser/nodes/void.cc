#include <parse/nodes/void.h>

std::string libjcc::VoidTypeNode::to_json() const
{
    return "{\"type\":\"VoidTypeNode\"}";
}

llvm::Type *libjcc::VoidTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getVoidTy(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::VoidTypeNode::clone() const
{
    return std::make_shared<VoidTypeNode>(*this);
}