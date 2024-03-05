#ifndef __J_CC_PARSE_NODES_VARIABLE_H__
#define __J_CC_PARSE_NODES_VARIABLE_H__

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
    class VarDeclNode : public DeclNode
    {
    public:
        VarDeclNode() { ntype = NodeType::VarDeclNode; }
        VarDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type, const std::shared_ptr<ConstExprNode> &init)
            : m_name(name), m_type(type), m_init(init) { ntype = NodeType::VarDeclNode; }
        virtual ~VarDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ExprNode> m_init;

        bool m_is_mut = false;
        bool m_is_thread_local = false;
        bool m_is_static = false;
        bool m_is_deprecated = false;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
    };

    class LetDeclNode : public DeclNode
    {
    public:
        LetDeclNode() { ntype = NodeType::LetDeclNode; }
        LetDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type, const std::shared_ptr<ConstExprNode> &init)
            : m_name(name), m_type(type), m_init(init) { ntype = NodeType::LetDeclNode; }
        virtual ~LetDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ExprNode> m_init;

        bool m_is_mut = false;
        bool m_is_thread_local = false;
        bool m_is_static = false;
        bool m_is_deprecated = false;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
    };

    class ConstDeclNode : public DeclNode
    {
    public:
        ConstDeclNode() { ntype = NodeType::ConstDeclNode; }
        ConstDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type, const std::shared_ptr<ConstExprNode> &init)
            : m_name(name), m_type(type), m_init(init) { ntype = NodeType::ConstDeclNode; }
        virtual ~ConstDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ExprNode> m_init;

        bool m_is_deprecated = false;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
    };
}

#endif // __J_CC_PARSE_NODES_VARIABLE_H__