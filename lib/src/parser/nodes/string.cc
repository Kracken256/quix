#include <parse/parser.hpp>

std::string libj::StringTypeNode::to_json() const
{
    return "{\"type\":\"StringTypeNode\"}";
}

llvm::Type *libj::StringTypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt8PtrTy(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::StringTypeNode::clone() const
{
    return std::make_shared<StringTypeNode>(*this);
}