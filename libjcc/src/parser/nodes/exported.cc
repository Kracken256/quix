#define JCC_INTERNAL

#include <parse/nodes/exported.h>

std::string libjcc::ExportNode::to_json() const
{
    return "{\n"
           "  \"type\": \"ExportNode\",\n"
           "  \"stmt\": " + m_stmt->to_json() + "\n"
           "}";
}

llvm::Value *libjcc::ExportNode::codegen(libjcc::LLVMContext &ctx) const
{
    bool pub = ctx.m_pub;

    ctx.m_pub = true;

    auto stmt = m_stmt->codegen(ctx);

    if (!pub)
        ctx.m_pub = false;
    
    return stmt;
}

std::shared_ptr<libjcc::ParseNode> libjcc::ExportNode::clone() const
{
    return std::make_shared<ExportNode>(*this);
}