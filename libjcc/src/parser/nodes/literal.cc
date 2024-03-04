#include <parse/nodes/literal.h>

static uint8_t get_numbits(const std::string &s)
{
    if (s.find('.') != std::string::npos)
    {
        float f0 = std::stof(s);
        double f1 = std::stod(s);
        const double delta = 0.0000001;

        return std::abs(f0 - f1) < delta ? 64 : 32;
    }

    uint64_t val = std::stoull(s);
    uint8_t bits = 0;
    while (val)
    {
        val >>= 1;
        bits++;
    }

    if (bits > 32)
        return 64;
    else if (bits > 16)
        return 32;
    else if (bits > 8)
        return 16;
    return 8;
}

std::string libjcc::IntegerLiteralNode::to_json() const
{
    return "{\"type\":\"number\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libjcc::IntegerLiteralNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(get_numbits(m_val), m_val, 10));
}

std::shared_ptr<libjcc::ParseNode> libjcc::IntegerLiteralNode::clone() const
{
    return std::make_shared<IntegerLiteralNode>(*this);
}

std::string libjcc::FloatLiteralNode::to_json() const
{
    return "{\"type\":\"float\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libjcc::FloatLiteralNode::codegen(libjcc::LLVMContext &ctx) const
{
    if (get_numbits(m_val) > 32)
    {
        return llvm::ConstantFP::get(*ctx.m_ctx, llvm::APFloat(llvm::APFloat::IEEEdouble(), m_val));
    }

    return llvm::ConstantFP::get(*ctx.m_ctx, llvm::APFloat(llvm::APFloat::IEEEsingle(), m_val));
}

std::shared_ptr<libjcc::ParseNode> libjcc::FloatLiteralNode::clone() const
{
    return std::make_shared<FloatLiteralNode>(*this);
}

std::string libjcc::StringLiteralNode::to_json() const
{
    return "{\"type\":\"string\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libjcc::StringLiteralNode::codegen(libjcc::LLVMContext &ctx) const
{
    auto str = llvm::ConstantDataArray::getString(*ctx.m_ctx, m_val);

    llvm::GlobalVariable *global;
    if (ctx.m_pub)
    {
        global = new llvm::GlobalVariable(*ctx.m_module, str->getType(), true, llvm::GlobalValue::ExternalLinkage, str);
    }
    else
    {
        global = new llvm::GlobalVariable(*ctx.m_module, str->getType(), true, llvm::GlobalValue::PrivateLinkage, str);
    }

    llvm::Constant *zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*ctx.m_ctx));
    llvm::Constant *indices[] = {zero, zero};
    return llvm::ConstantExpr::getGetElementPtr(str->getType(), global, indices, true);
}

std::shared_ptr<libjcc::ParseNode> libjcc::StringLiteralNode::clone() const
{
    return std::make_shared<StringLiteralNode>(*this);
}

std::string libjcc::CharLiteralNode::to_json() const
{
    return "{\"type\":\"char\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libjcc::CharLiteralNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(8, m_val[0]));
}

std::shared_ptr<libjcc::ParseNode> libjcc::CharLiteralNode::clone() const
{
    return std::make_shared<CharLiteralNode>(*this);
}

std::string libjcc::BoolLiteralNode::to_json() const
{
    return std::string("{\"type\":\"bool\",\"value\":") + (m_val ? "true" : "false") + "}";
}

llvm::Constant *libjcc::BoolLiteralNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, m_val));
}

std::shared_ptr<libjcc::ParseNode> libjcc::BoolLiteralNode::clone() const
{
    return std::make_shared<BoolLiteralNode>(*this);
}