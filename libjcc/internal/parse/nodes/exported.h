#ifndef __J_CC_PARSE_NODES_EXPORTED_H__
#define __J_CC_PARSE_NODES_EXPORTED_H__

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
    class ExportNode : public StmtNode
    {
    public:
        ExportNode() { ntype = NodeType::ExportNode; }
        ExportNode(std::shared_ptr<StmtNode> stmt) : m_stmt(stmt) { ntype = NodeType::ExportNode; }
        virtual ~ExportNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;
        std::shared_ptr<ParseNode> clone() const override;

        std::shared_ptr<libjcc::StmtNode> m_stmt;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libjcc::ParseNode>, std::shared_ptr<libjcc::ParseNode>*)> callback);
    };
}

#endif // __J_CC_PARSE_NODES_EXPORTED_H__