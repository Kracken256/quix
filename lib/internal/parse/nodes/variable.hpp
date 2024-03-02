#ifndef __J_CC_PARSE_NODES_VARIABLE_H__
#define __J_CC_PARSE_NODES_VARIABLE_H__

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
    class VarDeclNode : public DeclNode
    {
    public:
        VarDeclNode() = default;
        VarDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type, const std::shared_ptr<ConstExprNode> &init)
            : m_name(name), m_type(type), m_init(init) {}
        virtual ~VarDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ExprNode> m_init;
    };

    class LetDeclNode : public DeclNode
    {
    public:
        LetDeclNode() = default;
        LetDeclNode(const std::string &name, const std::shared_ptr<TypeNode> &type, const std::shared_ptr<ConstExprNode> &init)
            : m_name(name), m_type(type), m_init(init) {}
        virtual ~LetDeclNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::shared_ptr<TypeNode> m_type;
        std::shared_ptr<ExprNode> m_init;
    };
}

#endif // __J_CC_PARSE_NODES_VARIABLE_H__