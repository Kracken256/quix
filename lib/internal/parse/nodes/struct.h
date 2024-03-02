#ifndef __J_CC_PARSE_NODES_STRUCT_H__
#define __J_CC_PARSE_NODES_STRUCT_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.h>
#include <parse/nodes/basic.h>

namespace libj
{
    class StructTypeNode : public TypeNode
    {
    public:
        StructTypeNode() { ntype = NodeType::StructTypeNode; }
        virtual ~StructTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::vector<std::shared_ptr<TypeNode>> m_fields;
    };
}

#endif // __J_CC_PARSE_NODES_STRUCT_H__