#ifndef __J_CC_LLVM_CTX_H__
#define __J_CC_LLVM_CTX_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <memory>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace libj
{
    class LLVMContext
    {
    private:
        std::string generate_module_name();

    public:
        std::shared_ptr<llvm::LLVMContext> m_ctx;
        std::shared_ptr<llvm::Module> m_module;
        std::shared_ptr<llvm::IRBuilder<>> m_builder;

        LLVMContext()
        {
            m_ctx = std::make_shared<llvm::LLVMContext>();
            m_module = std::make_shared<llvm::Module>(generate_module_name().c_str(), *m_ctx);
            m_builder = std::make_shared<llvm::IRBuilder<>>(*m_ctx);
        }
    };

};

#endif // __J_CC_LLVM_CTX_H__