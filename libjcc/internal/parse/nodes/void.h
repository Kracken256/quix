#ifndef __J_CC_PARSE_NODES_VOID_H__
#define __J_CC_PARSE_NODES_VOID_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.h>
#include <parse/nodes/basic.h>

namespace libjcc
{
    class VoidTypeNode : public BasicTypeNode
    {
    public:
        VoidTypeNode() { ntype = NodeType::VoidTypeNode; }
        virtual ~VoidTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;
    };
}

#endif // __J_CC_PARSE_NODES_VOID_H__