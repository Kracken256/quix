#include <parse/nodes/subsystem.h>

std::string libj::SubsystemNode::to_json() const
{
    std::string s = "{\"ntype\":\"SubsystemNode\",\"name\":\"" + m_name + "\",\"deps\":[";
    for (auto &dep : m_deps)
    {
        s += "\"" + dep + "\",";
    }
    if (m_deps.size() > 0)
    {
        s.pop_back();
    }
    s += "],\"block\":" + m_block->to_json() + "}";
    return s;
}

llvm::Value *libj::SubsystemNode::codegen(libj::LLVMContext &ctx) const
{
    size_t len = ctx.prefix.size();
    if (len == 0)
        ctx.prefix = m_name;
    else
        ctx.prefix += "::" + m_name;

    auto block = m_block->codegen(ctx);
    ctx.prefix = ctx.prefix.substr(0, len);
    return block;
}

std::shared_ptr<libj::ParseNode> libj::SubsystemNode::clone() const
{
    return std::make_shared<SubsystemNode>(*this);
}