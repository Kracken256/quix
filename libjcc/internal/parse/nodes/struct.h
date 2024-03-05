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

namespace libjcc
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

        virtual size_t depth_first_traversal(std::function<void(ParseNode *)> callback);
    };

    class StructDeclNode : public DeclNode
    {
    public:
        StructDeclNode() { ntype = NodeType::StructDeclNode; }
        virtual ~StructDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
    };

    class StructFieldNode : public DefNode
    {
    public:
        StructFieldNode() { ntype = NodeType::StructFieldNode; }
        StructFieldNode(const std::string &name, std::shared_ptr<TypeNode> type, std::shared_ptr<ConstExprNode> value = nullptr) : m_name(name), m_type(type), m_value(value) { ntype = NodeType::StructFieldNode; }
        virtual ~StructFieldNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ConstExprNode> m_value;

        virtual size_t depth_first_traversal(std::function<void(ParseNode *)> callback);
    };

    class StructDefNode : public DefNode
    {
    public:
        StructDefNode() { ntype = NodeType::StructDefNode; }
        virtual ~StructDefNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::vector<std::shared_ptr<StructFieldNode>> m_fields;

        virtual size_t depth_first_traversal(std::function<void(ParseNode *)> callback);
    };
}

#endif // __J_CC_PARSE_NODES_STRUCT_H__