////////////////////////////////////////////////////////////////////////////////////
///                                                                              ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///      ░▒▓█▓▒░                                                                 ///
///       ░▒▓██▓▒░                                                               ///
///                                                                              ///
///     * QUIX LANG COMPILER - The official compiler for the Quix language.      ///
///     * Copyright (c) 2024, Wesley C. Jones. All rights reserved.              ///
///     * License terms may be found in the LICENSE file.                        ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#ifndef __QUIXCC_PARSE_NODES_FUNCTION_H__
#define __QUIXCC_PARSE_NODES_FUNCTION_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <vector>
#include <memory>

#include <llvm/llvm-ctx.h>
#include <parse/nodes/basic.h>

namespace libquixcc
{
    class FunctionDeclNode : public DeclNode
    {
    public:
        FunctionDeclNode() { ntype = NodeType::FunctionDeclNode; }
        virtual ~FunctionDeclNode() = default;

        std::string to_json() const override;
        llvm::Function *codegen(LLVMContext &ctx) const override;

        struct Param
        {
            std::string name;
            std::shared_ptr<TypeNode> type;
            std::shared_ptr<ConstExprNode> value;
        };

        std::string m_name;
        std::vector<Param> m_params;
        std::shared_ptr<TypeNode> m_return_type;
        bool m_variadic = false;
        bool m_pure = false;
        bool m_thread_safe = false;
        bool m_foreign = false;
        bool m_nothrow = false;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);
    };

    class FunctionDefNode : public DefNode
    {
    public:
        FunctionDefNode() { ntype = NodeType::FunctionDefNode; }
        virtual ~FunctionDefNode() = default;

        std::string to_json() const override;
        llvm::Value *codegen(LLVMContext &ctx) const override;

        std::shared_ptr<FunctionDeclNode> m_decl;
        std::shared_ptr<BlockNode> m_body;

        virtual size_t dfs_preorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);
        virtual size_t dfs_postorder(std::function<void(std::shared_ptr<libquixcc::ParseNode>, std::shared_ptr<libquixcc::ParseNode>*)> callback);
    };
}

#endif // __QUIXCC_PARSE_NODES_FUNCTION_H__