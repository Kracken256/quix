#ifndef __J_CC_LLVM_GEN_H__
#define __J_CC_LLVM_GEN_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include "llvm-ctx.hpp"
#include <bits/types/FILE.h>

namespace libj
{
    bool generate_llvm_ir(LLVMContext &ctx, FILE *out);
};

#endif // __J_CC_LLVM_GEN_H__