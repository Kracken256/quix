#include <llvm-ctx.hpp>
#include <openssl/rand.h>
#include <iostream>

std::string libj::LLVMContext::generate_module_name()
{
    std::string name = "j_llvm_";

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    uint8_t bytes[16];
    if (RAND_bytes(bytes, sizeof(bytes)) != 1)
    {
        std::cerr << "error: failed to generate random bytes" << std::endl;
        exit(1);
    }

    for (int i = 0; i < 16; ++i)
    {
        name += alphanum[bytes[i] % (sizeof(alphanum) - 1)];
    }

    return name;
}