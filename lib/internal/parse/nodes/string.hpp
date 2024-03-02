#ifndef __J_CC_PARSE_NODES_STRING_H__
#define __J_CC_PARSE_NODES_STRING_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.hpp>
#include <parse/nodes/basic.hpp>

namespace libj
{
    class StringTypeNode : public BasicTypeNode
    {
    public:
        StringTypeNode() = default;
        virtual ~StringTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };
}

#endif // __J_CC_PARSE_NODES_STRING_H__