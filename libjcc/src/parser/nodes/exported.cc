#define JCC_INTERNAL

#include <parse/nodes/exported.h>

std::string libjcc::ExportNode::to_json() const
{
    return "{\"ntype\":\"ExportNode\",\"stmt\":" + m_stmt->to_json() + "}";
}

llvm::Value *libjcc::ExportNode::codegen(libjcc::LLVMContext &ctx) const
{
    bool pub = ctx.m_pub;

    ctx.m_pub = true;

    auto stmt = m_stmt->codegen(ctx);

    if (!pub)
        ctx.m_pub = false;

    return stmt;
}

std::shared_ptr<libjcc::ParseNode> libjcc::ExportNode::clone() const
{
    return std::make_shared<ExportNode>(*this);
}

size_t libjcc::ExportNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback)
{

    if (ntype != NodeType::ExportNode)
        return 1;

    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&m_stmt));
    return m_stmt->dfs_preorder(callback) + 1;
}

size_t libjcc::ExportNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback)
{
    size_t ret = m_stmt->dfs_postorder(callback) + 1;
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&m_stmt));
    return ret;
}