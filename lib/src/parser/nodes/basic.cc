#include <parse/nodes/basic.h>

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

std::string libj::BlockNode::to_json() const
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

llvm::Value *libj::BlockNode::codegen(libj::LLVMContext &ctx) const
{
    for (auto &stmt : m_stmts)
    {
        llvm::Value *val = stmt->codegen(ctx);
        if (!val)
            return nullptr;
    }
    return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*ctx.m_ctx));
}

std::shared_ptr<libj::ParseNode> libj::BlockNode::clone() const
{
    auto node = std::make_shared<BlockNode>();
    for (auto &stmt : m_stmts)
    {
        node->m_stmts.push_back(std::static_pointer_cast<StmtNode>(stmt->clone()));
    }
    return node;
}