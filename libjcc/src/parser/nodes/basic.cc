#define JCC_INTERNAL

#include <parse/nodes/basic.h>

size_t libjcc::ParseNode::depth_first_traversal(std::function<void(libjcc::ParseNode *)> callback)
{
    callback(this);
    return 1;
}

std::string libjcc::UserTypeNode::to_json() const
{
    return "{\"type\":\"UserTypeNode\",\"name\":\"" + m_name + "\"}";
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
    std::string json = "{\"type\":\"BlockNode\",\"stmts\":[";
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

size_t libjcc::BlockNode::depth_first_traversal(std::function<void (libjcc::ParseNode *)> callback)
{
    size_t count = 1;
    callback(this);
    for (auto &stmt : m_stmts)
    {
        count += stmt->depth_first_traversal(callback);
    }
    return count;
}