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

#ifndef __QUIXCC_PARSE_NODES_TRAVERSAL_H__
#define __QUIXCC_PARSE_NODES_TRAVERSAL_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <memory>
#include <parse/NodeType.h>

namespace libquixcc
{
    typedef void (*ParseNodePreorderVisitorCallback)(std::shared_ptr<libquixcc::ParseNode> parent, std::shared_ptr<libquixcc::ParseNode> *node);
    typedef void (*ParseNodePostorderVisitorCallback)(std::shared_ptr<libquixcc::ParseNode> parent, std::shared_ptr<libquixcc::ParseNode> *node);

    class ParseNodePreorderVisitor
    {
        ParseNodePreorderVisitorCallback m_callback;

    public:
        ParseNodePreorderVisitor(ParseNodePreorderVisitorCallback callback) : m_callback(callback) {}

        size_t visit(std::shared_ptr<ParseNode> node);
        size_t visit(std::shared_ptr<ExprNode> node);
        size_t visit(std::shared_ptr<ConstExprNode> node);
        size_t visit(std::shared_ptr<StmtNode> node);
        size_t visit(std::shared_ptr<TypeNode> node);
        size_t visit(std::shared_ptr<DeclNode> node);
        size_t visit(std::shared_ptr<DefNode> node);
        size_t visit(std::shared_ptr<BlockNode> node);
        size_t visit(std::shared_ptr<BasicTypeNode> node);
        size_t visit(std::shared_ptr<ConstUnaryExprNode> node);
        size_t visit(std::shared_ptr<ConstBinaryExprNode> node);
        size_t visit(std::shared_ptr<IdentifierNode> node);
        size_t visit(std::shared_ptr<U8TypeNode> node);
        size_t visit(std::shared_ptr<U16TypeNode> node);
        size_t visit(std::shared_ptr<U32TypeNode> node);
        size_t visit(std::shared_ptr<U64TypeNode> node);
        size_t visit(std::shared_ptr<I8TypeNode> node);
        size_t visit(std::shared_ptr<I16TypeNode> node);
        size_t visit(std::shared_ptr<I32TypeNode> node);
        size_t visit(std::shared_ptr<I64TypeNode> node);
        size_t visit(std::shared_ptr<F32TypeNode> node);
        size_t visit(std::shared_ptr<F64TypeNode> node);
        size_t visit(std::shared_ptr<BoolTypeNode> node);
        size_t visit(std::shared_ptr<CharTypeNode> node);
        size_t visit(std::shared_ptr<VoidTypeNode> node);
        size_t visit(std::shared_ptr<StringTypeNode> node);
        size_t visit(std::shared_ptr<StructTypeNode> node);
        size_t visit(std::shared_ptr<UnionTypeNode> node);
        size_t visit(std::shared_ptr<ArrayTypeNode> node);
        size_t visit(std::shared_ptr<UserTypeNode> node);
        size_t visit(std::shared_ptr<LiteralNode> node);
        size_t visit(std::shared_ptr<IntegerLiteralNode> node);
        size_t visit(std::shared_ptr<FloatLiteralNode> node);
        size_t visit(std::shared_ptr<StringLiteralNode> node);
        size_t visit(std::shared_ptr<CharLiteralNode> node);
        size_t visit(std::shared_ptr<BoolLiteralNode> node);
        size_t visit(std::shared_ptr<VarDeclNode> node);
        size_t visit(std::shared_ptr<LetDeclNode> node);
        size_t visit(std::shared_ptr<ConstDeclNode> node);
        size_t visit(std::shared_ptr<StructDeclNode> node);
        size_t visit(std::shared_ptr<UnionDeclNode> node);
        size_t visit(std::shared_ptr<EnumDeclNode> node);
        size_t visit(std::shared_ptr<FunctionDeclNode> node);
        size_t visit(std::shared_ptr<StructDefNode> node);
        size_t visit(std::shared_ptr<StructFieldNode> node);
        size_t visit(std::shared_ptr<UnionDefNode> node);
        size_t visit(std::shared_ptr<UnionFieldNode> node);
        size_t visit(std::shared_ptr<EnumDefNode> node);
        size_t visit(std::shared_ptr<EnumFieldNode> node);
        size_t visit(std::shared_ptr<FunctionDefNode> node);
        size_t visit(std::shared_ptr<FunctionParamNode> node);
        size_t visit(std::shared_ptr<SubsystemNode> node);
        size_t visit(std::shared_ptr<ExportNode> node);
    };

    class ParseNodePostorderVisitor
    {
        ParseNodePostorderVisitorCallback m_callback;

    public:
        ParseNodePostorderVisitor(ParseNodePostorderVisitorCallback callback) : m_callback(callback) {}

        size_t visit(std::shared_ptr<ParseNode> node);
        size_t visit(std::shared_ptr<ExprNode> node);
        size_t visit(std::shared_ptr<ConstExprNode> node);
        size_t visit(std::shared_ptr<StmtNode> node);
        size_t visit(std::shared_ptr<TypeNode> node);
        size_t visit(std::shared_ptr<DeclNode> node);
        size_t visit(std::shared_ptr<DefNode> node);
        size_t visit(std::shared_ptr<BlockNode> node);
        size_t visit(std::shared_ptr<BasicTypeNode> node);
        size_t visit(std::shared_ptr<ConstUnaryExprNode> node);
        size_t visit(std::shared_ptr<ConstBinaryExprNode> node);
        size_t visit(std::shared_ptr<IdentifierNode> node);
        size_t visit(std::shared_ptr<U8TypeNode> node);
        size_t visit(std::shared_ptr<U16TypeNode> node);
        size_t visit(std::shared_ptr<U32TypeNode> node);
        size_t visit(std::shared_ptr<U64TypeNode> node);
        size_t visit(std::shared_ptr<I8TypeNode> node);
        size_t visit(std::shared_ptr<I16TypeNode> node);
        size_t visit(std::shared_ptr<I32TypeNode> node);
        size_t visit(std::shared_ptr<I64TypeNode> node);
        size_t visit(std::shared_ptr<F32TypeNode> node);
        size_t visit(std::shared_ptr<F64TypeNode> node);
        size_t visit(std::shared_ptr<BoolTypeNode> node);
        size_t visit(std::shared_ptr<CharTypeNode> node);
        size_t visit(std::shared_ptr<VoidTypeNode> node);
        size_t visit(std::shared_ptr<StringTypeNode> node);
        size_t visit(std::shared_ptr<StructTypeNode> node);
        size_t visit(std::shared_ptr<UnionTypeNode> node);
        size_t visit(std::shared_ptr<ArrayTypeNode> node);
        size_t visit(std::shared_ptr<UserTypeNode> node);
        size_t visit(std::shared_ptr<LiteralNode> node);
        size_t visit(std::shared_ptr<IntegerLiteralNode> node);
        size_t visit(std::shared_ptr<FloatLiteralNode> node);
        size_t visit(std::shared_ptr<StringLiteralNode> node);
        size_t visit(std::shared_ptr<CharLiteralNode> node);
        size_t visit(std::shared_ptr<BoolLiteralNode> node);
        size_t visit(std::shared_ptr<VarDeclNode> node);
        size_t visit(std::shared_ptr<LetDeclNode> node);
        size_t visit(std::shared_ptr<ConstDeclNode> node);
        size_t visit(std::shared_ptr<StructDeclNode> node);
        size_t visit(std::shared_ptr<UnionDeclNode> node);
        size_t visit(std::shared_ptr<EnumDeclNode> node);
        size_t visit(std::shared_ptr<FunctionDeclNode> node);
        size_t visit(std::shared_ptr<StructDefNode> node);
        size_t visit(std::shared_ptr<StructFieldNode> node);
        size_t visit(std::shared_ptr<UnionDefNode> node);
        size_t visit(std::shared_ptr<UnionFieldNode> node);
        size_t visit(std::shared_ptr<EnumDefNode> node);
        size_t visit(std::shared_ptr<EnumFieldNode> node);
        size_t visit(std::shared_ptr<FunctionDefNode> node);
        size_t visit(std::shared_ptr<FunctionParamNode> node);
        size_t visit(std::shared_ptr<SubsystemNode> node);
        size_t visit(std::shared_ptr<ExportNode> node);
    };

}

#endif // __QUIXCC_PARSE_NODES_TRAVERSAL_H__