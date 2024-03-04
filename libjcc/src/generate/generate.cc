#include <generate/generate.h>
#include <stdlib.h>
#include "llvm/llvm-ctx.h"
#include <error/message.h>

#include <llvm/IR/Verifier.h>

bool libjcc::Generator::synthesize_LLVM_IR(jcc_job_t &ctx, std::shared_ptr<libjcc::BlockNode> ast)
{
    int fd;

    // Check if the jcc_job_t is valid
    if (!ctx.m_out || !ctx.m_inner)
    {
        message(ctx, libjcc::Err::FATAL, "Invalid jcc_job_t");
        return false;
    }

    // Get a file descriptor for output stream
    if ((fd = fileno(ctx.m_out)) == -1)
    {
        message(ctx, libjcc::Err::ERROR, "Failed to get file descriptor for output stream");
        return false;
    }

    // Create a llvm::raw_fd_ostream
    llvm::raw_fd_ostream os(fd, false);
    if (os.has_error())
    {
        message(ctx, libjcc::Err::ERROR, "Failed to create llvm::raw_fd_ostream");
        return false;
    }

    // Get the LLVMContext from the jcc_job_t
    LLVMContext &llvm_ctx = *(LLVMContext *)ctx.m_inner;

    // Add root nodes to the LLVMContext
    for (auto &node : ast->m_stmts)
    {
        llvm::Value *val = node->codegen(llvm_ctx);
        if (!val)
        {
            message(ctx, libjcc::Err::ERROR, "Failed to generate code for node");
            return false;
        }
    }

    // Verify the module
    message(ctx, libjcc::Err::DEBUG, "Verifying LLVM module");
    if (llvm::verifyModule(*llvm_ctx.m_module, &os))
    {
        message(ctx, libjcc::Err::ERROR, "Failed to verify LLVM module");
        return false;
    }

    // Generate the IR
    message(ctx, libjcc::Err::DEBUG, "Generating LLVM IR");
    llvm_ctx.m_module->print(os, nullptr);

    message(ctx, libjcc::Err::DEBUG, "Finished generating LLVM IR");

    return true;
}