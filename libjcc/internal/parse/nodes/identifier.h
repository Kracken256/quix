#ifndef __J_CC_PARSE_NODES_IDENTIFIER_H__
#define __J_CC_PARSE_NODES_IDENTIFIER_H__

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
    class IdentifierNode : public ExprNode
    {
    public:
        IdentifierNode() { ntype = NodeType::IdentifierNode; }
        IdentifierNode(const std::string &name) : m_name(name) { ntype = NodeType::IdentifierNode; }
        virtual ~IdentifierNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
    };
}

#endif // __J_CC_PARSE_NODES_IDENTIFIER_H__