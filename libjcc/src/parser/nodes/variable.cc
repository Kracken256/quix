#include <parse/nodes/variable.h>
#include <mangle/symbol.h>

std::string libjcc::VarDeclNode::to_json() const
{
    std::string json = "{\"type\":\"VarDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ", \"init\": " + m_init->to_json();
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

std::string libjcc::LetDeclNode::to_json() const
{
    std::string json = "{\"type\":\"LetDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ", \"init\": " + m_init->to_json();
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

std::string libjcc::ConstDeclNode::to_json() const
{
    std::string json = "{\"type\":\"ConstDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ", \"init\": " + m_init->to_json();
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