#ifndef __J_CC_PARSE_NODES_UNION_H__
#define __J_CC_PARSE_NODES_UNION_H__

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
    class UnionTypeNode : public TypeNode
    {
    public:
        UnionTypeNode() { ntype = NodeType::UnionTypeNode; }
        virtual ~UnionTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::vector<std::shared_ptr<TypeNode>> m_fields;
    };

    class UnionDeclNode : public DeclNode
    {
    public:
        UnionDeclNode() { ntype = NodeType::UnionDeclNode; }
        virtual ~UnionDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
    };

    class UnionDefNode : public DefNode
    {
    public:
        UnionDefNode() { ntype = NodeType::UnionDefNode; }
        virtual ~UnionDefNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        struct Field
        {
            std::string name;
            std::shared_ptr<TypeNode> type;
            std::shared_ptr<ConstExprNode> value;
        };

        std::string m_name;
        std::vector<Field> m_fields;
    };
}

#endif // __J_CC_PARSE_NODES_UNION_H__