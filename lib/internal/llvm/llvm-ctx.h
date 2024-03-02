#ifndef __J_CC_LLVM_CTX_H__
#define __J_CC_LLVM_CTX_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <memory>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>
#include <map>

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
        std::map<std::string, llvm::Value *> m_named_values;
        std::string prefix = "j::";

        LLVMContext(const std::string &filename)
        {
            m_ctx = std::make_shared<llvm::LLVMContext>();
            m_module = std::make_shared<llvm::Module>(filename, *m_ctx);
            m_builder = std::make_shared<llvm::IRBuilder<>>(*m_ctx);
        }
    };

};

#endif // __J_CC_LLVM_CTX_H__