#define JCC_INTERNAL

#include <parse/nodes/basic.h>
#include <parse/nodes/nodes.h>

size_t libjcc::ParseNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    return 1;
}

size_t libjcc::ParseNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    return 1;
}

void libjcc::ParseNode::replace_child(std::shared_ptr<libjcc::ParseNode> &find, std::shared_ptr<libjcc::ParseNode> replace)
{
    find = replace;
}

void callback_nop(std::shared_ptr<libjcc::ParseNode> parrent, std::shared_ptr<libjcc::ParseNode> *child)
{
}

size_t libjcc::ParseNode::count()
{
    return dfs_preorder(callback_nop);
}

bool libjcc::ParseNode::has_immidiate_child(std::shared_ptr<libjcc::ParseNode> node)
{
    if (node == shared_from_this())
        return false;

    bool found = false;
    dfs_preorder([&](std::shared_ptr<libjcc::ParseNode> parrent, std::shared_ptr<libjcc::ParseNode> *child)
                 {
        if (*child == node)
        {
            found = true;
        } });
    return found;
}

std::string libjcc::UserTypeNode::to_json() const
{
    return "{\"ntype\":\"UserTypeNode\",\"name\":\"" + m_name + "\"}";
}

llvm::Type *libjcc::UserTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return nullptr;
}

std::shared_ptr<libjcc::ParseNode> libjcc::UserTypeNode::clone() const
{
    return std::make_shared<UserTypeNode>(m_name);
}

std::string libjcc::BlockNode::to_json() const
{
    std::string json = "{\"ntype\":\"BlockNode\",\"stmts\":[";
    for (auto &stmt : m_stmts)
    {
        json += stmt->to_json() + ",";
    }
    if (m_stmts.size() > 0)
    {
        json.pop_back();
    }
    json += "]}";
    return json;
}

llvm::Value *libjcc::BlockNode::codegen(libjcc::LLVMContext &ctx) const
{
    for (auto &stmt : m_stmts)
    {
        llvm::Value *val = stmt->codegen(ctx);
        if (!val)
            return nullptr;
    }
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libjcc::ParseNode> libjcc::BlockNode::clone() const
{
    auto node = std::make_shared<BlockNode>();
    for (auto &stmt : m_stmts)
    {
        node->m_stmts.push_back(std::static_pointer_cast<StmtNode>(stmt->clone()));
    }
    return node;
}

size_t libjcc::BlockNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    size_t count = 1;

    if (ntype != NodeType::BlockNode)
        return count;

    for (auto &stmt : m_stmts)
    {
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&stmt));
        count += stmt->dfs_preorder(callback);
    }
    return count;
}

size_t libjcc::BlockNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    size_t count = 1;
    for (auto &stmt : m_stmts)
    {
        count += stmt->dfs_postorder(callback);
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&stmt));
    }

    return count;
}