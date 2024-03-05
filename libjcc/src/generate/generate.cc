#define JCC_INTERNAL

#include <generate/generate.h>
#include <stdlib.h>
#include "llvm/llvm-ctx.h"
#include <error/message.h>
#include <filesystem>

#include <iostream>

#include <llvm/IR/Verifier.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/Target/TargetOptions.h"
#include "llvm/MC/TargetRegistry.h"
#include <stdlib.h>

bool libjcc::Generator::write_IR(jcc_job_t &ctx, std::shared_ptr<libjcc::BlockNode> ast, const std::string &ir_filename)
{
    // Check if the jcc_job_t is valid
    if (!ctx.m_inner)
    {
        message(ctx, libjcc::Err::FATAL, "Invalid jcc_job_t");
        return false;
    }

    // Create a llvm::raw_fd_ostream
    std::error_code ec;
    llvm::raw_fd_ostream os(ir_filename, ec);
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
    llvm_ctx.m_module->print(os, nullptr, ctx.m_argset->contains("-g"));

    message(ctx, libjcc::Err::DEBUG, "Finished generating LLVM IR");

    return true;
}

bool libjcc::Generator::write_asm(jcc_job_t &ctx, const std::string &ir_filename, const std::string &asm_filename)
{
    // LLVM createTargetMachine is bugging and not working
    // therefore, we will use clang binary to generate the assembly

#if !defined(__linux__) && !defined(__APPLE__) && !defined(__unix__) && !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__NetBSD__)
    message(ctx, libjcc::Err::FATAL, "Unsupported operating system");
    throw std::runtime_error("Unsupported operating system");
#else
    std::string flags;
    for (const auto &e : *ctx.m_argset)
    {
        if (e.first == "-O3" || e.first == "-O2" || e.first == "-O1" || e.first == "-O0")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-g")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-v" || ctx.m_debug)
        {
            flags += "-v ";
        }
    }

    // Its ugly, but it works
    std::string os_cmd = "clang -Wno-override-module -S " + flags + " " + ir_filename + " -o " + asm_filename;

    message(ctx, libjcc::Err::DEBUG, "Running command: " + os_cmd);
    if (system(os_cmd.c_str()) != 0)
    {
        message(ctx, libjcc::Err::ERROR, "Failed to generate assembly");
        return false;
    }

    return true;
#endif
}

bool libjcc::Generator::write_obj(jcc_job_t &ctx, const std::string &asm_filename, const std::string &obj_filename)
{
#if !defined(__linux__) && !defined(__APPLE__) && !defined(__unix__) && !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__NetBSD__)
    message(ctx, libjcc::Err::FATAL, "Unsupported operating system");
    throw std::runtime_error("Unsupported operating system");
#else
    std::string flags;
    for (const auto &e : *ctx.m_argset)
    {
        if (e.first == "-O3" || e.first == "-O2" || e.first == "-O1" || e.first == "-O0")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-flto")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-g")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-v" || ctx.m_debug)
        {
            flags += "-v ";
        }
    }

    // Its ugly, but it works
    std::string os_cmd = "clang -c " + flags + " " + asm_filename + " -o " + obj_filename;

    message(ctx, libjcc::Err::DEBUG, "Running command: " + os_cmd);
    if (system(os_cmd.c_str()) != 0)
    {
        message(ctx, libjcc::Err::ERROR, "Failed to generate object file");
        return false;
    }

    return true;
#endif
}

bool libjcc::Generator::write_bin(jcc_job_t &ctx, const std::string &obj_filename, const std::string &bin_filename)
{
#if !defined(__linux__) && !defined(__APPLE__) && !defined(__unix__) && !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__NetBSD__)
    message(ctx, libjcc::Err::FATAL, "Unsupported operating system");
    throw std::runtime_error("Unsupported operating system");
#else
    std::string flags;
    for (const auto &e : *ctx.m_argset)
    {
        if (e.first == "-O3" || e.first == "-O2" || e.first == "-O1" || e.first == "-O0")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-flto")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-static")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-shared")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-g")
        {
            flags += e.first + " ";
        }
        else if (e.first == "-v" || ctx.m_debug)
        {
            flags += "-v ";
        }
    }

    // Its ugly, but it works
    std::string os_cmd = "clang " + flags + " " + obj_filename + " -o " + bin_filename;

    message(ctx, libjcc::Err::DEBUG, "Running command: " + os_cmd);
    if (system(os_cmd.c_str()) != 0)
    {
        message(ctx, libjcc::Err::ERROR, "Failed to generate executable");
        return false;
    }

    return true;
#endif
}

bool libjcc::Generator::generate(jcc_job_t &job, std::shared_ptr<libjcc::BlockNode> ast)
{
    std::string ir_filename = std::tmpnam(nullptr) + std::string(".ll");
    std::string asm_filename = std::tmpnam(nullptr) + std::string(".s");
    std::string obj_filename = std::tmpnam(nullptr) + std::string(".o");
    std::string bin_filename = std::tmpnam(nullptr) + std::string(".out");
    char buf[4096];
    size_t n = 0;
    FILE *ir_out, *asm_out, *obj_out, *bin_out;
    ir_out = asm_out = obj_out = bin_out = nullptr;

    if (!libjcc::Generator::write_IR(job, ast, ir_filename))
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to generate output");
        goto remove_irfile_false;
    }

    if (job.m_argset->contains("-IR"))
    {
        libjcc::message(job, libjcc::Err::DEBUG, "IR output requested");

        if ((ir_out = fopen(ir_filename.c_str(), "r")) == nullptr)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to open temporary file to write IR");
            goto remove_irfile_false;
        }

        while ((n = fread(buf, 1, sizeof(buf), ir_out)) > 0)
        {
            if (fwrite(buf, 1, n, job.m_out) != n)
            {
                libjcc::message(job, libjcc::Err::ERROR, "failed to write IR to output");
                fclose(ir_out);
                goto remove_irfile_false;
            }
        }

        if (ferror(ir_out) != 0)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to read IR from temporary file");
            fclose(ir_out);
            goto remove_irfile_false;
        }

        fclose(ir_out);
        return true;
    }

    if (!libjcc::Generator::write_asm(job, ir_filename, asm_filename))
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to generate assembly");
        goto remove_irfile_asm_false;
    }

    message(job, libjcc::Err::DEBUG, "Generated assembly");

    if (job.m_argset->contains("-S"))
    {
        libjcc::message(job, libjcc::Err::DEBUG, "Assembly output requested");

        if ((asm_out = fopen(asm_filename.c_str(), "r")) == nullptr)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to open temporary file to write assembly");
            goto remove_irfile_asm_false;
        }

        while ((n = fread(buf, 1, sizeof(buf), asm_out)) > 0)
        {
            if (fwrite(buf, 1, n, job.m_out) != n)
            {
                libjcc::message(job, libjcc::Err::ERROR, "failed to write assembly to output");
                fclose(asm_out);
                goto remove_irfile_asm_false;
            }
        }

        if (ferror(asm_out) != 0)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to read assembly from temporary file");
            fclose(asm_out);
            goto remove_irfile_asm_false;
        }

        fclose(asm_out);
        return true;
    }

    if (!libjcc::Generator::write_obj(job, asm_filename, obj_filename))
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to generate object file");
        goto remove_irfile_asm_obj_false;
    }

    message(job, libjcc::Err::DEBUG, "Generated object file");

    if (job.m_argset->contains("-c"))
    {
        libjcc::message(job, libjcc::Err::DEBUG, "Object file output requested");

        if ((obj_out = fopen(obj_filename.c_str(), "r")) == nullptr)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to open temporary file to write object file");
            goto remove_irfile_asm_obj_false;
        }

        while ((n = fread(buf, 1, sizeof(buf), obj_out)) > 0)
        {
            if (fwrite(buf, 1, n, job.m_out) != n)
            {
                libjcc::message(job, libjcc::Err::ERROR, "failed to write object file to output");
                fclose(obj_out);
                goto remove_irfile_asm_obj_false;
            }
        }

        if (ferror(obj_out) != 0)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to read object file from temporary file");
            fclose(obj_out);
            goto remove_irfile_asm_obj_false;
        }

        fclose(obj_out);
        return true;
    }

    if (!libjcc::Generator::write_bin(job, obj_filename, bin_filename))
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to generate executable");
        goto remove_irfile_asm_obj_false;
    }

    message(job, libjcc::Err::DEBUG, "Generated executable");

    if ((bin_out = fopen(bin_filename.c_str(), "r")) == nullptr)
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to open temporary file to write executable");
        fclose(bin_out);
        goto remove_irfile_asm_obj_false;
    }

    while ((n = fread(buf, 1, sizeof(buf), bin_out)) > 0)
    {
        if (fwrite(buf, 1, n, job.m_out) != n)
        {
            libjcc::message(job, libjcc::Err::ERROR, "failed to write object file to output");
            fclose(bin_out);
            goto remove_irfile_asm_obj_false;
        }
    }

    if (ferror(bin_out) != 0)
    {
        libjcc::message(job, libjcc::Err::ERROR, "failed to read object file from temporary file");
        fclose(bin_out);
        goto remove_irfile_asm_obj_false;
    }

    fflush(job.m_out);
    fclose(bin_out);

    std::filesystem::remove(ir_filename);
    std::filesystem::remove(asm_filename);
    std::filesystem::remove(obj_filename);
    std::filesystem::remove(bin_filename);
    return true; // TODO: fixme

remove_irfile_false:
    std::filesystem::remove(ir_filename);
    return false;

remove_irfile_asm_false:
    std::filesystem::remove(ir_filename);
    std::filesystem::remove(asm_filename);
    return false;

remove_irfile_asm_obj_false:
    std::filesystem::remove(ir_filename);
    std::filesystem::remove(asm_filename);
    std::filesystem::remove(obj_filename);
    return false;
}