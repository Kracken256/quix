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
        fields.push_back(field->codegen(ctx));

    return llvm::StructType::create(*ctx.m_ctx, fields);
}

std::shared_ptr<libj::ParseNode> libj::StructTypeNode::clone() const
{
    return std::make_shared<StructTypeNode>(*this);
}

std::string libj::StructDeclNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructDeclNode\",";
    s += "\"name\":\"" + m_name + "\"";
    s += "}";
    return s;
}

llvm::Value *libj::StructDeclNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libj::ParseNode> libj::StructDeclNode::clone() const
{
    return std::make_shared<StructDeclNode>(*this);
}

std::string libj::StructDefNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructDefNode\",";
    s += "\"name\":\"" + m_name + "\",";
    s += "\"fields\":[";
    for (size_t i = 0; i < m_fields.size(); i++)
    {
        s += "{";
        s += "\"name\":\"" + m_fields[i].name + "\",";
        s += "\"type\":" + m_fields[i].type->to_json();
        if (m_fields[i].value)
            s += ",\"value\":" + m_fields[i].value->to_json();

        s += "}";
        if (i != m_fields.size() - 1)
        {
            s += ",";
        }
    }
    s += "]}";
    return s;
}

llvm::Constant *libj::StructDefNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libj::ParseNode> libj::StructDefNode::clone() const
{
    return std::make_shared<StructDefNode>(*this);
}