#include <parse/nodes/identifier.h>

std::string libjcc::IdentifierNode::to_json() const
{
    return "{\"type\":\"identifier\",\"name\":\"" + m_name + "\"}";
}

llvm::Value *libjcc::IdentifierNode::codegen(libjcc::LLVMContext &ctx) const
{
    return ctx.m_named_values.at(m_name);
}

std::shared_ptr<libjcc::ParseNode> libjcc::IdentifierNode::clone() const
{
    return std::make_shared<IdentifierNode>(*this);
}