#define JCC_INTERNAL

#include <parse/nodes/subsystem.h>

std::string libjcc::SubsystemNode::to_json() const
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

llvm::Value *libjcc::SubsystemNode::codegen(libjcc::LLVMContext &ctx) const
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

std::shared_ptr<libjcc::ParseNode> libjcc::SubsystemNode::clone() const
{
    return std::make_shared<SubsystemNode>(*this);
}

size_t libjcc::SubsystemNode::depth_first_traversal(std::function<void (libjcc::ParseNode *)> callback)
{
    callback(this);
    return m_block->depth_first_traversal(callback) + 1;
}