#include <parse/nodes/variable.hpp>

std::string libj::VarDeclNode::to_json() const
{
    std::string json= "{\"type\":\"VarDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ", \"init\": " + m_init->to_json();
    }

    json += "}";

    return json;
}

llvm::Value *libj::VarDeclNode::codegen(libj::LLVMContext &ctx) const
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

    return new llvm::GlobalVariable(*ctx.m_module, type, false, llvm::GlobalValue::ExternalLinkage, init, m_name);
}

std::shared_ptr<libj::ParseNode> libj::VarDeclNode::clone() const
{
    return std::make_shared<VarDeclNode>(*this);
}

std::string libj::LetDeclNode::to_json() const
{
    std::string json = "{\"type\":\"LetDeclNode\",\"name\":\"" + m_name + "\",\"dtype\":" + m_type->to_json();

    if (m_init)
    {
        json += ", \"init\": " + m_init->to_json();
    }

    json += "}";

    return json;
}

llvm::Value *libj::LetDeclNode::codegen(libj::LLVMContext &ctx) const
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

    return new llvm::GlobalVariable(*ctx.m_module, type, true, llvm::GlobalValue::ExternalLinkage, init, m_name);
}

std::shared_ptr<libj::ParseNode> libj::LetDeclNode::clone() const
{
    return std::make_shared<LetDeclNode>(*this);
}