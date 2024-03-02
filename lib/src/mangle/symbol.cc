#include <mangle/symbol.h>

#include <parse/nodes/nodes.h>

std::string libj::Symbol::mangle(std::shared_ptr<libj::DeclNode> node)
{
    auto raw = node.get();

    switch (node->ntype)
    {
    case libj::NodeType::VarDeclNode:
        return static_cast<const libj::VarDeclNode *>(raw)->m_name;
    case libj::NodeType::LetDeclNode:
        return static_cast<const libj::LetDeclNode *>(raw)->m_name;
    default:
        break;
    }

    return "";
}

std::shared_ptr<libj::DeclNode> libj::Symbol::demangle(const std::string &mangled)
{
    return nullptr;
}
