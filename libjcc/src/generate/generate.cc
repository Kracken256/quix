#define JCC_INTERNAL

#include <generate/generate.h>
#include <stdlib.h>
#include "llvm/llvm-ctx.h"
#include <error/message.h>
#include <filesystem>

#include <llvm/IR/Verifier.h>

bool libjcc::Generator::synthesize_LLVM_IR(jcc_job_t &ctx, FILE *out, std::shared_ptr<libjcc::BlockNode> ast)
{
    int fd;

    // Check if the jcc_job_t is valid
    if (!out || !ctx.m_inner)
    {
        message(ctx, libjcc::Err::FATAL, "Invalid jcc_job_t");
        return false;
    }

    // Get a file descriptor for output stream
    if ((fd = fileno(out)) == -1)
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
        throw std::runtime_error("LLVM IR generation failed. The AST must have been semantically incorrect");

    // Generate the IR
    message(ctx, libjcc::Err::DEBUG, "Generating LLVM IR");
    llvm_ctx.m_module->print(os, nullptr);

    message(ctx, libjcc::Err::DEBUG, "Finished generating LLVM IR");

    return true;
}

bool libjcc::Generator::generate(jcc_job_t &job, std::shared_ptr<libjcc::BlockNode> ast)
{
    FILE *ir_out;
    if ((ir_out = tmpfile()) == nullptr)
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to open temporary file to write IR");
        return false;
    }

    if (!libjcc::Generator::synthesize_LLVM_IR(job, ir_out, ast))
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to generate output");
        return false;
    }

    if (job.m_argset->contains("-IR"))
    {
        libjcc::message(job, libjcc::Err::DEBUG, "IR output requested");
        if (fseek(ir_out, 0, SEEK_SET) != 0)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to seek to beginning of temporary file");
            return false;
        }

        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), ir_out)) > 0)
        {
            if (fwrite(buf, 1, n, job.m_out) != n)
            {
                libjcc::message(job, libjcc::Err::ERROR, "failed to write IR to output");
                return false;
            }
        }

        if (ferror(ir_out) != 0)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to read IR from temporary file");
            return false;
        }

        fclose(ir_out);
        return true;
    }

    fclose(ir_out);

    /// TODO: Generate assembly
    /// TODO: Generate object file
    /// TODO: Generate executable

    return false; // TODO: fixme
}