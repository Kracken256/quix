#define JCC_INTERNAL

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

std::string libjcc::U8TypeNode::to_json() const
{
    return "{\"ntype\":\"u8\"}";
}

llvm::Type *libjcc::U8TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::U8TypeNode::clone() const
{
    return std::make_shared<U8TypeNode>(*this);
}

std::string libjcc::U16TypeNode::to_json() const
{
    return "{\"ntype\":\"u16\"}";
}

llvm::Type *libjcc::U16TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::U16TypeNode::clone() const
{
    return std::make_shared<U16TypeNode>(*this);
}

std::string libjcc::U32TypeNode::to_json() const
{
    return "{\"ntype\":\"u32\"}";
}

llvm::Type *libjcc::U32TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::U32TypeNode::clone() const
{
    return std::make_shared<U32TypeNode>(*this);
}

std::string libjcc::U64TypeNode::to_json() const
{
    return "{\"ntype\":\"u64\"}";
}

llvm::Type *libjcc::U64TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::U64TypeNode::clone() const
{
    return std::make_shared<U64TypeNode>(*this);
}

std::string libjcc::I8TypeNode::to_json() const
{
    return "{\"ntype\":\"i8\"}";
}

llvm::Type *libjcc::I8TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::I8TypeNode::clone() const
{
    return std::make_shared<I8TypeNode>(*this);
}

std::string libjcc::I16TypeNode::to_json() const
{
    return "{\"ntype\":\"i16\"}";
}

llvm::Type *libjcc::I16TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::I16TypeNode::clone() const
{
    return std::make_shared<I16TypeNode>(*this);
}

std::string libjcc::I32TypeNode::to_json() const
{
    return "{\"ntype\":\"i32\"}";
}

llvm::Type *libjcc::I32TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::I32TypeNode::clone() const
{
    return std::make_shared<I32TypeNode>(*this);
}

std::string libjcc::I64TypeNode::to_json() const
{
    return "{\"ntype\":\"i64\"}";
}

llvm::Type *libjcc::I64TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::I64TypeNode::clone() const
{
    return std::make_shared<I64TypeNode>(*this);
}

std::string libjcc::F32TypeNode::to_json() const
{
    return "{\"ntype\":\"f32\"}";
}

llvm::Type *libjcc::F32TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getFloatTy(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::F32TypeNode::clone() const
{
    return std::make_shared<F32TypeNode>(*this);
}

std::string libjcc::F64TypeNode::to_json() const
{
    return "{\"ntype\":\"f64\"}";
}

llvm::Type *libjcc::F64TypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getDoubleTy(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::F64TypeNode::clone() const
{
    return std::make_shared<F64TypeNode>(*this);
}

std::string libjcc::BoolTypeNode::to_json() const
{
    return "{\"ntype\":\"bool\"}";
}

llvm::Type *libjcc::BoolTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt1Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::BoolTypeNode::clone() const
{
    return std::make_shared<BoolTypeNode>(*this);
}

std::string libjcc::CharTypeNode::to_json() const
{
    return "{\"ntype\":\"char\"}";
}

llvm::Type *libjcc::CharTypeNode::codegen(libjcc::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::shared_ptr<libjcc::ParseNode> libjcc::CharTypeNode::clone() const
{
    return std::make_shared<CharTypeNode>(*this);
}
