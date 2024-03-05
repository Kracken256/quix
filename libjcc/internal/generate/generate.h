#ifndef __J_CC_LLVM_GEN_H__
#define __J_CC_LLVM_GEN_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <bits/types/FILE.h>
#include <jcc.h>
#include <parse/parser.h>

namespace libjcc
{
    class Generator
    {
        Generator() = delete;
        static bool write_IR(jcc_job_t &ctx, const std::shared_ptr<libjcc::AST> ast, const std::string &ir_filename);
        static bool write_asm(jcc_job_t &ctx, const std::string &ir_filename, const std::string &asm_filename);
        static bool write_obj(jcc_job_t &ctx, const std::string &asm_filename, const std::string &obj_filename);
        static bool write_bin(jcc_job_t &ctx, const std::string &obj_filename, const std::string &bin_filename);
    public:
        static bool generate(jcc_job_t &ctx, const std::shared_ptr<libjcc::AST> ast);
    };
};

#endif // __J_CC_LLVM_GEN_H__