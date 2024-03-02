#include <parse/nodes/struct.h>

std::string libj::StructTypeNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructTypeNode\",";
    s += "\"fields\":[";
    for (size_t i = 0; i < m_fields.size(); i++)
    {
        s += m_fields[i]->to_json();
        if (i != m_fields.size() - 1)
        {
            s += ",";
        }
    }
    s += "]}";
    return s;
}

llvm::Type *libj::StructTypeNode::codegen(libj::LLVMContext &ctx) const
{
    std::vector<llvm::Type *> fields;
    for (auto &field : m_fields)
    {
        fields.push_back(field->codegen(ctx));
    }
    return llvm::StructType::create(fields);
}

std::shared_ptr<libj::ParseNode> libj::StructTypeNode::clone() const
{
    return std::make_shared<StructTypeNode>(*this);
}