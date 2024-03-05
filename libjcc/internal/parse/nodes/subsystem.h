#ifndef __J_CC_PARSE_NODES_SUBSYSTEM_H__
#define __J_CC_PARSE_NODES_SUBSYSTEM_H__

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
    class SubsystemNode : public StmtNode
    {
    public:
        SubsystemNode() { ntype = NodeType::SubsystemNode; }
        SubsystemNode(const std::string &name, const std::set<std::string> &deps, const std::shared_ptr<BlockNode> &block) : m_name(name), m_deps(deps), m_block(block) { ntype = NodeType::SubsystemNode; }
        virtual ~SubsystemNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::string m_name;
        std::set<std::string> m_deps;
        std::shared_ptr<libjcc::BlockNode> m_block;

        virtual size_t depth_first_traversal(std::function<void(ParseNode *)> callback);
    };
}

#endif // __J_CC_PARSE_NODES_SUBSYSTEM_H__