#include <parse.hpp>

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

std::string libj::U8TypeNode::to_json() const
{
    return "{\"type\":\"u8\"}";
}

llvm::Type *libj::U8TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::U8TypeNode::clone() const
{
    return std::make_shared<U8TypeNode>(*this);
}

std::string libj::U16TypeNode::to_json() const
{
    return "{\"type\":\"u16\"}";
}

llvm::Type *libj::U16TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::U16TypeNode::clone() const
{
    return std::make_shared<U16TypeNode>(*this);
}

std::string libj::U32TypeNode::to_json() const
{
    return "{\"type\":\"u32\"}";
}

llvm::Type *libj::U32TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::U32TypeNode::clone() const
{
    return std::make_shared<U32TypeNode>(*this);
}

std::string libj::U64TypeNode::to_json() const
{
    return "{\"type\":\"u64\"}";
}

llvm::Type *libj::U64TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::U64TypeNode::clone() const
{
    return std::make_shared<U64TypeNode>(*this);
}

std::string libj::I8TypeNode::to_json() const
{
    return "{\"type\":\"i8\"}";
}

llvm::Type *libj::I8TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::I8TypeNode::clone() const
{
    return std::make_shared<I8TypeNode>(*this);
}

std::string libj::I16TypeNode::to_json() const
{
    return "{\"type\":\"i16\"}";
}

llvm::Type *libj::I16TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt16Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::I16TypeNode::clone() const
{
    return std::make_shared<I16TypeNode>(*this);
}

std::string libj::I32TypeNode::to_json() const
{
    return "{\"type\":\"i32\"}";
}

llvm::Type *libj::I32TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt32Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::I32TypeNode::clone() const
{
    return std::make_shared<I32TypeNode>(*this);
}

std::string libj::I64TypeNode::to_json() const
{
    return "{\"type\":\"i64\"}";
}

llvm::Type *libj::I64TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::I64TypeNode::clone() const
{
    return std::make_shared<I64TypeNode>(*this);
}

std::string libj::F32TypeNode::to_json() const
{
    return "{\"type\":\"F32TypeNode\"}";
}

llvm::Type *libj::F32TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getFloatTy(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::F32TypeNode::clone() const
{
    return std::make_shared<F32TypeNode>(*this);
}

std::string libj::F64TypeNode::to_json() const
{
    return "{\"type\":\"F64TypeNode\"}";
}

llvm::Type *libj::F64TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getDoubleTy(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::F64TypeNode::clone() const
{
    return std::make_shared<F64TypeNode>(*this);
}

std::string libj::BoolTypeNode::to_json() const
{
    return "{\"type\":\"BoolTypeNode\"}";
}

llvm::Type *libj::BoolTypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt1Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::BoolTypeNode::clone() const
{
    return std::make_shared<BoolTypeNode>(*this);
}

std::string libj::CharTypeNode::to_json() const
{
    return "{\"type\":\"CharTypeNode\"}";
}

llvm::Type *libj::CharTypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt8Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::CharTypeNode::clone() const
{
    return std::make_shared<CharTypeNode>(*this);
}

std::string libj::VoidTypeNode::to_json() const
{
    return "{\"type\":\"VoidTypeNode\"}";
}

llvm::Type *libj::VoidTypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getVoidTy(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::VoidTypeNode::clone() const
{
    return std::make_shared<VoidTypeNode>(*this);
}