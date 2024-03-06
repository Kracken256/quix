////////////////////////////////////////////////////////////////////////////////////
///                                                                              ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///      ░▒▓█▓▒░                                                                 ///
///       ░▒▓██▓▒░                                                               ///
///                                                                              ///
///     * QUIX LANG COMPILER - The official compiler for the Quix language.      ///
///     * Copyright (c) 2024, Wesley C. Jones. All rights reserved.              ///
///     * License terms may be found in the LICENSE file.                        ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#define QUIXCC_INTERNAL

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

std::string libquixcc::IntegerLiteralNode::to_json() const
{
    return "{\"ntype\":\"number\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libquixcc::IntegerLiteralNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(get_numbits(m_val), m_val, 10));
}

std::string libquixcc::FloatLiteralNode::to_json() const
{
    return "{\"ntype\":\"float\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libquixcc::FloatLiteralNode::codegen(libquixcc::LLVMContext &ctx) const
{
    if (get_numbits(m_val) > 32)
    {
        return llvm::ConstantFP::get(*ctx.m_ctx, llvm::APFloat(llvm::APFloat::IEEEdouble(), m_val));
    }

    return llvm::ConstantFP::get(*ctx.m_ctx, llvm::APFloat(llvm::APFloat::IEEEsingle(), m_val));
}

std::string libquixcc::StringLiteralNode::to_json() const
{
    return "{\"ntype\":\"string\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libquixcc::StringLiteralNode::codegen(libquixcc::LLVMContext &ctx) const
{
    auto str = llvm::ConstantDataArray::getString(*ctx.m_ctx, m_val);

    llvm::GlobalVariable *global = new llvm::GlobalVariable(*ctx.m_module, str->getType(), true, llvm::GlobalValue::PrivateLinkage, str);

    llvm::Constant *zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(*ctx.m_ctx));
    llvm::Constant *indices[] = {zero, zero};
    return llvm::ConstantExpr::getGetElementPtr(str->getType(), global, indices, true);
}

std::string libquixcc::CharLiteralNode::to_json() const
{
    return "{\"ntype\":\"char\",\"value\":\"" + m_val + "\"}";
}

llvm::Constant *libquixcc::CharLiteralNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(8, m_val[0]));
}

std::string libquixcc::BoolLiteralNode::to_json() const
{
    return std::string("{\"ntype\":\"bool\",\"value\":") + (m_val ? "true" : "false") + "}";
}

llvm::Constant *libquixcc::BoolLiteralNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::ConstantInt::get(*ctx.m_ctx, llvm::APInt(1, m_val));
}