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
