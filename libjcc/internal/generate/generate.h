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
    public:
        Generator() = default;
        ~Generator() = default;

        bool synthesize_LLVM_IR(jcc_job_t &ctx, const std::shared_ptr<libjcc::AST> ast);
    };
};

#endif // __J_CC_LLVM_GEN_H__