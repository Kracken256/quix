#ifndef __J_CC_PARSE_NODES_IDENTIFIER_H__
#define __J_CC_PARSE_NODES_IDENTIFIER_H__

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
    class IdentifierNode : public ExprNode
    {
    public:
        IdentifierNode() = default;
        IdentifierNode(const std::string &name) : m_name(name) {}
        virtual ~IdentifierNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
    };
}

#endif // __J_CC_PARSE_NODES_IDENTIFIER_H__