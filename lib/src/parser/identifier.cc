#include <parse/nodes/identifier.hpp>

std::string libj::IdentifierNode::to_json() const
{
    return "{\"type\":\"identifier\",\"name\":\"" + m_name + "\"}";
}

llvm::Value *libj::IdentifierNode::codegen(libj::LLVMContext &ctx) const
{
    return ctx.m_named_values.at(m_name);
}

std::shared_ptr<libj::ParseNode> libj::IdentifierNode::clone() const
{
    return std::make_shared<IdentifierNode>(*this);
}