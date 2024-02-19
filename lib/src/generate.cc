#include <generate.hpp>
#include <stdlib.h>
#include "llvm-ctx.hpp"
#include <error.hpp>

#include <llvm/IR/Verifier.h>

bool libj::Generator::synthesize_LLVM_IR(jcc_job_t &ctx, const AST &ast)
{
    int fd;

    // Check if the jcc_job_t is valid
    if (!ctx.m_out || !ctx.m_inner)
    {
        message(ctx, libj::Err::FATAL, "Invalid jcc_job_t");
        return false;
    }

    // Get a file descriptor for output stream
    if ((fd = fileno(ctx.m_out)) == -1)
    {
        message(ctx, libj::Err::ERROR, "Failed to get file descriptor for output stream");
        return false;
    }

    // Create a llvm::raw_fd_ostream
    llvm::raw_fd_ostream os(fd, false);
    if (os.has_error())
    {
        message(ctx, libj::Err::ERROR, "Failed to create llvm::raw_fd_ostream");
        return false;
    }

    // Get the LLVMContext from the jcc_job_t
    LLVMContext &llvm_ctx = *(LLVMContext *)ctx.m_inner;

    // Add root nodes to the LLVMContext
    for (auto &node : ast.m_children)
    {
        llvm::Value *val = node->codegen(llvm_ctx);
        if (!val)
        {
            message(ctx, libj::Err::ERROR, "Failed to generate code for node");
            return false;
        }

        message(ctx, libj::Err::DEBUG, "Generated code for node");
    }

    // Verify the module
    message(ctx, libj::Err::DEBUG, "Verifying LLVM module");
    if (llvm::verifyModule(*llvm_ctx.m_module, &os))
    {
        message(ctx, libj::Err::ERROR, "Failed to verify LLVM module");
        return false;
    }

    // Generate the IR
    message(ctx, libj::Err::DEBUG, "Generating LLVM IR");
    llvm_ctx.m_module->print(os, nullptr);
    message(ctx, libj::Err::DEBUG, "Generated LLVM IR");

    return true;
}