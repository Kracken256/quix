////////////////////////////////////////////////////////////////////////////////
///                                                                          ///
///  ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
///  ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
///    ░▒▓█▓▒░                                                               ///
///     ░▒▓██▓▒░                                                             ///
///                                                                          ///
///   * QUIX LANG COMPILER - The official compiler for the Quix language.    ///
///   * Copyright (C) 2024 Wesley C. Jones                                   ///
///                                                                          ///
///   The QUIX Compiler Suite is free software; you can redistribute it or   ///
///   modify it under the terms of the GNU Lesser General Public             ///
///   License as published by the Free Software Foundation; either           ///
///   version 2.1 of the License, or (at your option) any later version.     ///
///                                                                          ///
///   The QUIX Compiler Suite is distributed in the hope that it will be     ///
///   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of ///
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      ///
///   Lesser General Public License for more details.                        ///
///                                                                          ///
///   You should have received a copy of the GNU Lesser General Public       ///
///   License along with the QUIX Compiler Suite; if not, see                ///
///   <https://www.gnu.org/licenses/>.                                       ///
///                                                                          ///
////////////////////////////////////////////////////////////////////////////////

#ifndef __QUIXCC_PARSE_NODES_NODETYPES_H__
#define __QUIXCC_PARSE_NODES_NODETYPES_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <cstdint>
#include <string>
#include <unordered_map>

namespace libquixcc {
enum class NodeType : uint8_t {
  ParseNode,
  ExprNode,
  ConstExprNode,
  StmtNode,
  ExprStmtNode,
  NopStmtNode,
  TypeNode,
  DeclNode,
  DefNode,
  BlockNode,
  StmtGroupNode,

  ConstUnaryExprNode,
  ConstPostUnaryExprNode,
  ConstBinaryExprNode,

  CastExprNode,
  StaticCastExprNode,
  BitCastExprNode,
  SignedUpcastExprNode,
  UnsignedUpcastExprNode,
  DowncastExprNode,
  PtrToIntCastExprNode,
  IntToPtrCastExprNode,

  UnaryExprNode,
  PostUnaryExprNode,
  BinaryExprNode,
  CallExprNode,
  ListExprNode,
  MemberAccessNode,
  IndexNode,

  IdentifierNode,

  MutTypeNode,
  U8TypeNode,
  U16TypeNode,
  U32TypeNode,
  U64TypeNode,
  U128TypeNode,
  I8TypeNode,
  I16TypeNode,
  I32TypeNode,
  I64TypeNode,
  I128TypeNode,
  F32TypeNode,
  F64TypeNode,
  BoolTypeNode,
  VoidTypeNode,
  NullTypeNode,
  PointerTypeNode,
  OpaqueTypeNode,
  StringTypeNode,

  EnumTypeNode,
  StructTypeNode,
  GroupTypeNode,
  RegionTypeNode,
  UnionTypeNode,
  ArrayTypeNode,
  VectorTypeNode,
  ResultTypeNode,
  GeneratorTypeNode,
  FunctionTypeNode,
  UserTypeNode,

  LiteralNode,
  IntegerNode,
  FloatLiteralNode,
  StringNode,
  CharNode,
  BoolLiteralNode,
  NullLiteralNode,
  UndefLiteralNode,

  TypedefNode,

  VarDeclNode,
  LetDeclNode,
  ConstDeclNode,

  FunctionDeclNode,

  StructDefNode,
  StructFieldNode,
  RegionDefNode,
  RegionFieldNode,
  GroupDefNode,
  GroupFieldNode,
  UnionDefNode,
  UnionFieldNode,
  EnumDefNode,
  EnumFieldNode,
  FunctionDefNode,
  FunctionParamNode,

  SubsystemNode,
  ExportNode,
  InlineAsmNode,

  ReturnStmtNode,
  RetifStmtNode,
  RetzStmtNode,
  RetvStmtNode,
  IfStmtNode,
  WhileStmtNode,
  ForStmtNode,
};

class ParseNode;
class ExprNode;
class ConstExprNode;
class StmtNode;
class ExprStmtNode;
class NopStmtNode;
class TypeNode;
class DeclNode;
class DefNode;
class BlockNode;
class StmtGroupNode;
class CastExprNode;
class StaticCastExprNode;
class BitCastExprNode;
class SignedUpcastExprNode;
class UnsignedUpcastExprNode;
class DowncastExprNode;
class PtrToIntCastExprNode;
class IntToPtrCastExprNode;
class UnaryExprNode;
class PostUnaryExprNode;
class BinaryExprNode;
class CallExprNode;
class ListExprNode;
class MemberAccessNode;
class IndexNode;
class ConstUnaryExprNode;
class ConstPostUnaryExprNode;
class ConstBinaryExprNode;
class IdentifierNode;
class MutTypeNode;
class U8TypeNode;
class U16TypeNode;
class U32TypeNode;
class U64TypeNode;
class U128TypeNode;
class I8TypeNode;
class I16TypeNode;
class I32TypeNode;
class I64TypeNode;
class I128TypeNode;
class F32TypeNode;
class F64TypeNode;
class BoolTypeNode;
class VoidTypeNode;
class NullTypeNode;
class PointerTypeNode;
class OpaqueTypeNode;
class StringTypeNode;
class EnumTypeNode;
class StructTypeNode;
class GroupTypeNode;
class RegionTypeNode;
class UnionTypeNode;
class ArrayTypeNode;
class VectorTypeNode;
class ResultTypeNode;
class GeneratorTypeNode;
class FunctionTypeNode;
class UserTypeNode;
class LiteralNode;
class IntegerNode;
class FloatLiteralNode;
class StringNode;
class CharNode;
class BoolLiteralNode;
class NullLiteralNode;
class UndefLiteralNode;
class TypedefNode;
class VarDeclNode;
class LetDeclNode;
class ConstDeclNode;
class FunctionDeclNode;
class StructDefNode;
class StructFieldNode;
class RegionDefNode;
class RegionFieldNode;
class GroupDefNode;
class GroupFieldNode;
class UnionDefNode;
class UnionFieldNode;
class EnumDefNode;
class EnumFieldNode;
class FunctionDefNode;
class FunctionParamNode;
class SubsystemNode;
class ExportNode;
class InlineAsmNode;
class ReturnStmtNode;
class RetifStmtNode;
class RetzStmtNode;
class RetvStmtNode;
class IfStmtNode;
class WhileStmtNode;
class ForStmtNode;

extern std::unordered_map<NodeType, std::string_view> NodeTypeNames;
}  // namespace libquixcc

#endif  // __QUIXCC_PARSE_NODES_NODETYPES_H__