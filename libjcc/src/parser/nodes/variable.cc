#define JCC_INTERNAL

#include <parse/nodes/variable.h>
#include <mangle/symbol.h>

std::string libjcc::VarDeclNode::to_json() const
{
    std::string json = "{\"ntype\":\"VarDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ",\"init\":" + m_init->to_json();
    }

    json += "}";

    return json;
}

llvm::Value *libjcc::VarDeclNode::codegen(libjcc::LLVMContext &ctx) const
{
    llvm::Type *type = m_type->codegen(ctx);
    if (!type)
    {
        return nullptr;
    }

    llvm::Constant *init = nullptr;
    if (m_init)
    {
        init = static_cast<llvm::Constant *>(m_init->codegen(ctx));
        if (!init)
        {
            return nullptr;
        }
    }

    if (ctx.m_pub)
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::ExternalLinkage, init, Symbol::mangle(this, ctx.prefix));
    else
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::PrivateLinkage, init, Symbol::mangle(this, ctx.prefix));
}

std::shared_ptr<libjcc::ParseNode> libjcc::VarDeclNode::clone() const
{
    return std::make_shared<VarDeclNode>(*this);
}

size_t libjcc::VarDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    return 0;
}

size_t libjcc::VarDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    return 0;
}

std::string libjcc::LetDeclNode::to_json() const
{
    std::string json = "{\"ntype\":\"LetDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ",\"init\":" + m_init->to_json();
    }

    json += "}";

    return json;
}

llvm::Value *libjcc::LetDeclNode::codegen(libjcc::LLVMContext &ctx) const
{
    llvm::Type *type = m_type->codegen(ctx);
    if (!type)
    {
        return nullptr;
    }

    llvm::Constant *init = nullptr;
    if (m_init)
    {
        init = static_cast<llvm::Constant *>(m_init->codegen(ctx));
        if (!init)
        {
            return nullptr;
        }
    }

    if (ctx.m_pub)
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::ExternalLinkage, init, Symbol::mangle(this, ctx.prefix));
    else
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::PrivateLinkage, init, Symbol::mangle(this, ctx.prefix));
}

std::shared_ptr<libjcc::ParseNode> libjcc::LetDeclNode::clone() const
{
    return std::make_shared<LetDeclNode>(*this);
}

size_t libjcc::LetDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    return 0;
}

size_t libjcc::LetDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    return 0;
}

std::string libjcc::ConstDeclNode::to_json() const
{
    std::string json = "{\"ntype\":\"ConstDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ",\"init\":" + m_init->to_json();
    }

    json += "}";

    return json;
}

llvm::Value *libjcc::ConstDeclNode::codegen(libjcc::LLVMContext &ctx) const
{
    llvm::Type *type = m_type->codegen(ctx);
    if (!type)
    {
        return nullptr;
    }

    llvm::Constant *init = nullptr;
    if (m_init)
    {
        init = static_cast<llvm::Constant *>(m_init->codegen(ctx));
        if (!init)
        {
            return nullptr;
        }
    }

    if (ctx.m_pub)
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::ExternalLinkage, init, Symbol::mangle(this, ctx.prefix));
    else
        return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::PrivateLinkage, init, Symbol::mangle(this, ctx.prefix));
}

std::shared_ptr<libjcc::ParseNode> libjcc::ConstDeclNode::clone() const
{
    return std::make_shared<ConstDeclNode>(*this);
}

size_t libjcc::ConstDeclNode::dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    if (ntype != NodeType::ConstDeclNode)
        return 1;

    size_t ret = 1;
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&m_type));
    ret += m_type->dfs_preorder(callback);
    if (m_init)
    {
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&m_init));
        ret += m_init->dfs_preorder(callback);
    }

    return ret;
}

size_t libjcc::ConstDeclNode::dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode> *)> callback)
{
    size_t ret = 1;
    if (m_init)
    {
        ret += m_init->dfs_postorder(callback);
        callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&m_init));
    }

    ret += m_type->dfs_postorder(callback);
    callback(shared_from_this(), reinterpret_cast<std::shared_ptr<libjcc::ParseNode> *>(&m_type));

    return ret;
}