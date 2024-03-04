#include <parse/nodes/union.h>

std::string libjcc::UnionTypeNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"UnionTypeNode\",";
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

llvm::Type *libjcc::UnionTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    std::vector<llvm::Type *> fields;

    fields.push_back(llvm::Type::getInt32Ty(*ctx.m_ctx)); // selector

    size_t largest = 0;
    for (auto &field : m_fields)
    {
        auto type = field->codegen(ctx);
        if (type->getPrimitiveSizeInBits() > largest)
            largest = type->getPrimitiveSizeInBits();
    }

    fields.push_back(llvm::ArrayType::get(llvm::Type::getInt8Ty(*ctx.m_ctx), largest / 8));

    return llvm::StructType::create(*ctx.m_ctx, fields);
}

std::shared_ptr<libjcc::ParseNode> libjcc::UnionTypeNode::clone() const
{
    return std::make_shared<UnionTypeNode>(*this);
}

std::string libjcc::UnionDeclNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"UnionDeclNode\",";
    s += "\"name\":\"" + m_name + "\"";
    s += "}";
    return s;
}

llvm::Value *libjcc::UnionDeclNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::UnionDeclNode::clone() const
{
    return std::make_shared<UnionDeclNode>(*this);
}

std::string libjcc::UnionDefNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"UnionDefNode\",";
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

llvm::Constant *libjcc::UnionDefNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::UnionDefNode::clone() const
{
    return std::make_shared<UnionDefNode>(*this);
}