#include <parse/nodes/basic.h>

std::string libj::RootNode::to_json() const
{
    std::string json = "{\"type\":\"RootNode\",\"children\":[";
    for (auto &child : m_children)
    {
        json += child->to_json() + ",";
    }
    json.pop_back();
    json += "]}";
    return json;
}

std::shared_ptr<libj::ParseNode> libj::RootNode::clone() const
{
    auto node = std::make_shared<RootNode>();
    for (auto &child : m_children)
    {
        node->m_children.push_back(std::static_pointer_cast<StmtNode>(child->clone()));
    }
    return node;
}

std::string libj::UserTypeNode::to_json() const
{
    return "{\"type\":\"UserTypeNode\",\"name\":\"" + m_name + "\"}";
}

llvm::Type *libj::UserTypeNode::codegen(libj::LLVMContext &ctx) const
{
    return nullptr;
}

std::shared_ptr<libj::ParseNode> libj::UserTypeNode::clone() const
{
    return std::make_shared<UserTypeNode>(m_name);
}
