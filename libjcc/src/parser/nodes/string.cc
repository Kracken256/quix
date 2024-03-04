#include <parse/nodes/string.h>

std::string libjcc::StringTypeNode::to_json() const
{
    return "{\"type\":\"StringTypeNode\"}";
}

llvm::Type *libjcc::StringTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8PtrTy(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::StringTypeNode::clone() const
{
    return std::make_shared<StringTypeNode>(*this);
}