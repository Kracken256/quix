#ifndef __J_CC_PARSE_NODES_ARRAY_H__
#define __J_CC_PARSE_NODES_ARRAY_H__

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
    class ArrayTypeNode : public TypeNode
    {
    public:
        ArrayTypeNode() { ntype = NodeType::ArrayTypeNode; }
        ArrayTypeNode(std::shared_ptr<TypeNode> type, std::shared_ptr<ConstExprNode> size) : m_type(type), m_size(size) { ntype = NodeType::ArrayTypeNode; }
        virtual ~ArrayTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ConstExprNode> m_size;
    };
}

#endif // __J_CC_PARSE_NODES_ARRAY_H__