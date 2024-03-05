#define JCC_INTERNAL

#include <parse/nodes/enum.h>

std::string libjcc::EnumDeclNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"EnumDeclNode\",";
    s += "\"name\":\"" + m_name + "\",";
    s += "\"type\":" + m_type->to_json();
    s += "}";
    return s;
}

llvm::Value *libjcc::EnumDeclNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::EnumDeclNode::clone() const
{
    return std::make_shared<EnumDeclNode>(*this);
}

size_t libjcc::EnumDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback)
{
    return 0;
}

size_t libjcc::EnumDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback)
{
    return 0;
}

std::string libjcc::EnumDefNode::to_json() const
{
    std::string s = "{";
    s += "\"ntype\":\"EnumDefNode\",";
    s += "\"name\":\"" + m_name + "\",";
    s += "\"type\":" + m_type->to_json() + ",";
    s += "\"fields\":[";
    for (size_t i = 0; i < m_fields.size(); i++)
    {
        s += "{";
        s += "\"name\":\"" + m_fields[i].name + "\"";
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

llvm::Constant *libjcc::EnumDefNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::EnumDefNode::clone() const
{
    return std::make_shared<EnumDefNode>(*this);
}

size_t libjcc::EnumDefNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback)
{
    return 0;
}

size_t libjcc::EnumDefNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback)
{
    return 0;
}