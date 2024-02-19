#include <parse.hpp>

std::string libj::U8TypeNode::to_json() const
{
    return "{\"type\": \"u8\"}";
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
    return "{\"type\": \"u16\"}";
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
    return "{\"type\": \"u32\"}";
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
    return "{\"type\": \"u64\"}";
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
    return "{\"type\": \"i8\"}";
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
    return "{\"type\": \"i16\"}";
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
    return "{\"type\": \"i32\"}";
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
    return "{\"type\": \"i64\"}";
}

llvm::Type *libj::I64TypeNode::codegen(libj::LLVMContext &ctx) const
{
    return llvm::Type::getInt64Ty(*ctx.m_ctx);
}

std::shared_ptr<libj::ParseNode> libj::I64TypeNode::clone() const
{
    return std::make_shared<I64TypeNode>(*this);
}