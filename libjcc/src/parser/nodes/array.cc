#define JCC_INTERNAL

#include <parse/nodes/array.h>

std::string libjcc::ArrayTypeNode::to_json() const
{
    std::string json = "{";
    json += "\"type\":\"array\",";
    json += "\"size\":" + m_size->to_json() + ",";
    json += "\"subtype\":" + m_type->to_json();
    json += "}";
    return json;
}

llvm::Type *libjcc::ArrayTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::ArrayType::get(m_type->codegen(ctx), m_size->codegen(ctx)->getUniqueInteger().getLimitedValue());
}

std::shared_ptr<libjcc::ParseNode> libjcc::ArrayTypeNode::clone() const
{
    return std::make_shared<ArrayTypeNode>(*this);
}