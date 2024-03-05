#ifndef __J_CC_PARSE_NODES_ENUM_H__
#define __J_CC_PARSE_NODES_ENUM_H__

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
    class EnumDeclNode : public DeclNode
    {
    public:
        EnumDeclNode() { ntype = NodeType::EnumDeclNode; }
        EnumDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type) : m_name(name), m_type(type) { ntype = NodeType::EnumDeclNode; }
        virtual ~EnumDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
    };

    class EnumDefNode : public DefNode
    {
    public:
        EnumDefNode() { ntype = NodeType::EnumDefNode; }
        EnumDefNode(const std::string &name, const std::shared_ptr<TypeNode> &type) : m_name(name), m_type(type) { ntype = NodeType::EnumDefNode; }
        virtual ~EnumDefNode() = default;

        std::string to_json() const override;
        llvm::Constant *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        struct Field
        {
            std::string name;
            std::shared_ptr<ConstExprNode> value;
        };

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::vector<Field> m_fields;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
    };
}

#endif // __J_CC_PARSE_NODES_ENUM_H__