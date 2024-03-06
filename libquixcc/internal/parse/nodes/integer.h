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

#ifndef __QUIXCC_PARSE_NODES_INTEGER_H__
#define __QUIXCC_PARSE_NODES_INTEGER_H__

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
    class U8TypeNode : public BasicTypeNode
    {
    public:
        U8TypeNode() { ntype = NodeType::U8TypeNode; }
        virtual ~U8TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class U16TypeNode : public BasicTypeNode
    {
    public:
        U16TypeNode() { ntype = NodeType::U16TypeNode; }
        virtual ~U16TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class U32TypeNode : public BasicTypeNode
    {
    public:
        U32TypeNode() { ntype = NodeType::U32TypeNode; }
        virtual ~U32TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class U64TypeNode : public BasicTypeNode
    {
    public:
        U64TypeNode() { ntype = NodeType::U64TypeNode; }
        virtual ~U64TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class I8TypeNode : public BasicTypeNode
    {
    public:
        I8TypeNode() { ntype = NodeType::I8TypeNode; }
        virtual ~I8TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class I16TypeNode : public BasicTypeNode
    {
    public:
        I16TypeNode() { ntype = NodeType::I16TypeNode; }
        virtual ~I16TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class I32TypeNode : public BasicTypeNode
    {
    public:
        I32TypeNode() { ntype = NodeType::I32TypeNode; }
        virtual ~I32TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class I64TypeNode : public BasicTypeNode
    {
    public:
        I64TypeNode() { ntype = NodeType::I64TypeNode; }
        virtual ~I64TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class F32TypeNode : public BasicTypeNode
    {
    public:
        F32TypeNode() { ntype = NodeType::F32TypeNode; }
        virtual ~F32TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class F64TypeNode : public BasicTypeNode
    {
    public:
        F64TypeNode() { ntype = NodeType::F64TypeNode; }
        virtual ~F64TypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class BoolTypeNode : public BasicTypeNode
    {
    public:
        BoolTypeNode() { ntype = NodeType::BoolTypeNode; }
        virtual ~BoolTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };

    class CharTypeNode : public BasicTypeNode
    {
    public:
        CharTypeNode() { ntype = NodeType::CharTypeNode; }
        virtual ~CharTypeNode() = default;

        std::string to_json() const override;
        llvm::Type *codegen(LLVMContext &ctx) const override;
    };
}

#endif // __QUIXCC_PARSE_NODES_INTEGER_H__