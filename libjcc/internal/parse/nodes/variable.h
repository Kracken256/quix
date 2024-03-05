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

        virtual bool operator==(const VarDeclNode &other) const
        {
            bool s = m_name == other.m_name && *m_type == *other.m_type &&
                     m_is_mut == other.m_is_mut && m_is_thread_local == other.m_is_thread_local &&
                     m_is_static == other.m_is_static && m_is_deprecated == other.m_is_deprecated;

            if (m_init && other.m_init)
                s = s && *m_init == *other.m_init;
            else if (!(m_init == nullptr && other.m_init == nullptr))
                s = false;

            return s;
        }

        virtual size_t depth_first_traversal(std::function<void(ParseNode *)> callback);
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

        virtual bool operator==(const LetDeclNode &other) const
        {
            bool s = m_name == other.m_name && *m_type == *other.m_type &&
                     m_is_mut == other.m_is_mut && m_is_thread_local == other.m_is_thread_local &&
                     m_is_static == other.m_is_static && m_is_deprecated == other.m_is_deprecated;

            if (m_init && other.m_init)
                s = s && *m_init == *other.m_init;
            else if (!(m_init == nullptr && other.m_init == nullptr))
                s = false;

            return s;
        }

        virtual size_t depth_first_traversal(std::function<void(ParseNode *)> callback);
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

        virtual bool operator==(const ConstDeclNode &other) const
        {
            bool s = m_name == other.m_name && *m_type == *other.m_type && m_is_deprecated == other.m_is_deprecated;

            if (m_init && other.m_init)
                s = s && *m_init == *other.m_init;
            else if (!(m_init == nullptr && other.m_init == nullptr))
                s = false;

            return s;
        }

        virtual size_t depth_first_traversal(std::function<void(ParseNode *)> callback);
    };
}

#endif // __J_CC_PARSE_NODES_VARIABLE_H__