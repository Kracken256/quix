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

#include <parse/nodes/BasicTypeNode.h>

llvm::Type *libquixcc::U8TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::U16TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::U32TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::U64TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::I8TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::I16TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::I32TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::I64TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::F32TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getFloatTy(*ctx.m_ctx);
}

llvm::Type *libquixcc::F64TypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getDoubleTy(*ctx.m_ctx);
}

llvm::Type *libquixcc::BoolTypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt1Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::CharTypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

llvm::Type *libquixcc::VoidTypeNode::codegen(libquixcc::LLVMContext &ctx) const
{
    return llvm::Type::getVoidTy(*ctx.m_ctx);
}