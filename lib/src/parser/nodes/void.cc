#include <parse/nodes/void.hpp>

std::string libj::VoidTypeNode::to_json() const
{
    return "{\"type\":\"VoidTypeNode\"}";
}

llvm::Type *libj::VoidTypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getVoidTy(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::VoidTypeNode::clone() const
{
    return std::make_shared<VoidTypeNode>(*this);
}