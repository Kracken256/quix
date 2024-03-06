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

#include <parse/nodes/integer.h>

/*
 * U8
 * U16
 * U32
 * U64
 * I8
 * I16
 * I32
 * I64
 * F32 = C float
 * F64 = C double
 * Bool = C bool
 * Char = C char
 */

std::string libquixcc::U8TypeNode::to_json() const
{
    return "{\"ntype\":\"u8\"}";
}

llvm::Type *libquixcc::U8TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::string libquixcc::U16TypeNode::to_json() const
{
    return "{\"ntype\":\"u16\"}";
}

llvm::Type *libquixcc::U16TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

std::string libquixcc::U32TypeNode::to_json() const
{
    return "{\"ntype\":\"u32\"}";
}

llvm::Type *libquixcc::U32TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

std::string libquixcc::U64TypeNode::to_json() const
{
    return "{\"ntype\":\"u64\"}";
}

llvm::Type *libquixcc::U64TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

std::string libquixcc::I8TypeNode::to_json() const
{
    return "{\"ntype\":\"i8\"}";
}

llvm::Type *libquixcc::I8TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::string libquixcc::I16TypeNode::to_json() const
{
    return "{\"ntype\":\"i16\"}";
}

llvm::Type *libquixcc::I16TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

std::string libquixcc::I32TypeNode::to_json() const
{
    return "{\"ntype\":\"i32\"}";
}

llvm::Type *libquixcc::I32TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

std::string libquixcc::I64TypeNode::to_json() const
{
    return "{\"ntype\":\"i64\"}";
}

llvm::Type *libquixcc::I64TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

std::string libquixcc::F32TypeNode::to_json() const
{
    return "{\"ntype\":\"f32\"}";
}

llvm::Type *libquixcc::F32TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getFloatTy(*ctx.m_ctx);
}

std::string libquixcc::F64TypeNode::to_json() const
{
    return "{\"ntype\":\"f64\"}";
}

llvm::Type *libquixcc::F64TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getDoubleTy(*ctx.m_ctx);
}

std::string libquixcc::BoolTypeNode::to_json() const
{
    return "{\"ntype\":\"bool\"}";
}

llvm::Type *libquixcc::BoolTypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt1Ty(*ctx.m_ctx);
}

std::string libquixcc::CharTypeNode::to_json() const
{
    return "{\"ntype\":\"char\"}";
}

llvm::Type *libquixcc::CharTypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}
