#include <parse/nodes/array.h>

std::string libj::ArrayTypeNode::to_json() const
{
    std::string json = "{";
    json += "\"type\":\"array\",";
    json += "\"size\":" + m_size->to_json() + ",";
    json += "\"subtype\":" + m_type->to_json();
    json += "}";
    return json;
}

llvm::Type *libj::ArrayTypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::ArrayType::get(m_type->codegen(ctx), m_size->codegen(ctx)->getUniqueInteger().getLimitedValue());
}

std::shared_ptr<libj::ParseNode> libj::ArrayTypeNode::clone() const
{
    return std::make_shared<ArrayTypeNode>(*this);
}