#define JCC_INTERNAL

#include <parse/nodes/struct.h>

std::string libjcc::StructTypeNode::to_json() const
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

llvm::Type *libjcc::StructTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    std::vector<llvm::Type *> fields;

    for (auto &field : m_fields)
        fields.push_back(field->codegen(ctx));

    return llvm::StructType::create(*ctx.m_ctx, fields);
}

std::shared_ptr<libjcc::ParseNode> libjcc::StructTypeNode::clone() const
{
    return std::make_shared<StructTypeNode>(*this);
}

size_t libjcc::StructTypeNode::depth_first_traversal(std::function<void(libjcc::ParseNode *)> callback)
{
    callback(this);
    size_t ret = 1;
    for (auto &field : m_fields)
    {
        ret += field->depth_first_traversal(callback);
    }

    return ret;
}

std::string libjcc::StructDeclNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructDeclNode\",";
    s += "\"name\":\"" + m_name + "\"";
    s += "}";
    return s;
}

llvm::Value *libjcc::StructDeclNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::StructDeclNode::clone() const
{
    return std::make_shared<StructDeclNode>(*this);
}

std::string libjcc::StructFieldNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructFieldNode\",";
    s += "\"name\":\"" + m_name + "\",";
    s += "\"type\":" + m_type->to_json();
    if (m_value)
        s += ",\"value\":" + m_value->to_json();
    s += "}";
    return s;
}

llvm::Constant *libjcc::StructFieldNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::StructFieldNode::clone() const
{
    return std::make_shared<StructFieldNode>(*this);
}

size_t libjcc::StructFieldNode::depth_first_traversal(std::function<void (libjcc::ParseNode *)> callback)
{
    callback(this);
    size_t ret = 1;
    ret += m_type->depth_first_traversal(callback);
    if (m_value)
        ret += m_value->depth_first_traversal(callback);
    return ret;
}

std::string libjcc::StructDefNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"StructDefNode\",";
    s += "\"name\":\"" + m_name + "\",";
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

llvm::Constant *libjcc::StructDefNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::StructDefNode::clone() const
{
    return std::make_shared<StructDefNode>(*this);
}

size_t libjcc::StructDefNode::depth_first_traversal(std::function<void(libjcc::ParseNode *)> callback)
{
    callback(this);
    size_t ret = 1;
    for (auto &field : m_fields)
    {
        ret += field->depth_first_traversal(callback);
    }

    return ret;
}