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

#ifndef __QUIXCC_PARSE_NODES_NODETYPES_H__
#define __QUIXCC_PARSE_NODES_NODETYPES_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

namespace libquixcc
{
    enum class NodeType : uint8_t
    {
        ParseNode,
        ExprNode,
        ConstExprNode,
        StmtNode,
        TypeNode,
        RootNode,
        DeclNode,
        DefNode,
        BlockNode,
        BasicTypeNode,

        ConstUnaryExprNode,
        ConstBinaryExprNode,

        IdentifierNode,

        U8TypeNode,
        U16TypeNode,
        U32TypeNode,
        U64TypeNode,
        I8TypeNode,
        I16TypeNode,
        I32TypeNode,
        I64TypeNode,
        F32TypeNode,
        F64TypeNode,
        BoolTypeNode,
        CharTypeNode,
        VoidTypeNode,
        StringTypeNode,

        StructTypeNode,
        UnionTypeNode,
        ArrayTypeNode,
        UserTypeNode,

        LiteralNode,
        IntegerLiteralNode,
        FloatLiteralNode,
        StringLiteralNode,
        CharLiteralNode,
        BoolLiteralNode,

        VarDeclNode,
        LetDeclNode,
        ConstDeclNode,

        StructDeclNode,
        UnionDeclNode,
        EnumDeclNode,
        FunctionDeclNode,

        StructDefNode,
        StructFieldNode,
        UnionDefNode,
        UnionFieldNode,
        EnumDefNode,
        EnumFieldNode,
        FunctionDefNode,
        FunctionParamNode,

        SubsystemNode,
        ExportNode,
    };
}

#endif // __QUIXCC_PARSE_NODES_NODETYPES_H__