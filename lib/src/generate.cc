#include <generate.hpp>
#include <stdlib.h>

bool libj::generate_llvm_ir(libj::LLVMContext &ctx, FILE *out)
{
    int fd;

    fd = fileno(out);

    if (fd == -1)
        return false;

    llvm::raw_fd_ostream os(fd, false);
    if (os.has_error())
        return false;

    ctx.m_module->print(os, nullptr);

    return true;
}