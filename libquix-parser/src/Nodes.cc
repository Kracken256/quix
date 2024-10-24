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

#define __QPARSE_IMPL__

#include <quix-core/Error.h>
#include <quix-parser/Node.h>
#include <quix-parser/Parser.h>

#include <cstring>
#include <unordered_map>

#include "LibMacro.h"

using namespace qparse;

///=============================================================================
namespace qparse {
  void ArenaAllocatorImpl::swap(qcore_arena_t &arena) { std::swap(*m_arena.get(), arena); }

  thread_local ArenaAllocatorImpl qparse_arena;
}  // namespace qparse

LIB_EXPORT void *ArenaAllocatorImpl::allocate(std::size_t size) {
  const std::size_t alignment = 16;
  return qcore_arena_alloc_ex(m_arena.get(), size, alignment);
}

LIB_EXPORT void ArenaAllocatorImpl::deallocate(void *ptr) noexcept { (void)ptr; }

///=============================================================================

LIB_EXPORT const char *Node::type_name(qparse_ty_t type) {
#define NAMEOF_ROW(__name) \
  { QAST_NODE_##__name, "QAST_NODE_" #__name }

  static const std::unordered_map<qparse_ty_t, const char *> names = {
      NAMEOF_ROW(STMT),
      NAMEOF_ROW(TYPE),
      NAMEOF_ROW(DECL),
      NAMEOF_ROW(EXPR),
      NAMEOF_ROW(CEXPR),
      NAMEOF_ROW(UNRES_TY),
      NAMEOF_ROW(U1_TY),
      NAMEOF_ROW(U8_TY),
      NAMEOF_ROW(U16_TY),
      NAMEOF_ROW(U32_TY),
      NAMEOF_ROW(U64_TY),
      NAMEOF_ROW(U128_TY),
      NAMEOF_ROW(I8_TY),
      NAMEOF_ROW(I16_TY),
      NAMEOF_ROW(I32_TY),
      NAMEOF_ROW(I64_TY),
      NAMEOF_ROW(I128_TY),
      NAMEOF_ROW(F16_TY),
      NAMEOF_ROW(F32_TY),
      NAMEOF_ROW(F64_TY),
      NAMEOF_ROW(F128_TY),
      NAMEOF_ROW(VOID_TY),
      NAMEOF_ROW(PTR_TY),
      NAMEOF_ROW(OPAQUE_TY),
      NAMEOF_ROW(TUPLE_TY),
      NAMEOF_ROW(ARRAY_TY),
      NAMEOF_ROW(ENUM_TY),
      NAMEOF_ROW(REF_TY),
      NAMEOF_ROW(STRUCT_TY),
      NAMEOF_ROW(GROUP_TY),
      NAMEOF_ROW(REGION_TY),
      NAMEOF_ROW(UNION_TY),
      NAMEOF_ROW(FN_TY),
      NAMEOF_ROW(UNEXPR),
      NAMEOF_ROW(BINEXPR),
      NAMEOF_ROW(POST_UNEXPR),
      NAMEOF_ROW(TEREXPR),
      NAMEOF_ROW(INT),
      NAMEOF_ROW(FLOAT),
      NAMEOF_ROW(BOOL),
      NAMEOF_ROW(STRING),
      NAMEOF_ROW(CHAR),
      NAMEOF_ROW(NULL),
      NAMEOF_ROW(UNDEF),
      NAMEOF_ROW(CALL),
      NAMEOF_ROW(TEMPL_CALL),
      NAMEOF_ROW(LIST),
      NAMEOF_ROW(ASSOC),
      NAMEOF_ROW(FIELD),
      NAMEOF_ROW(INDEX),
      NAMEOF_ROW(SLICE),
      NAMEOF_ROW(FSTRING),
      NAMEOF_ROW(IDENT),
      NAMEOF_ROW(SEQ_POINT),
      NAMEOF_ROW(STMT_EXPR),
      NAMEOF_ROW(TYPE_EXPR),
      NAMEOF_ROW(BLOCK),
      NAMEOF_ROW(VOLSTMT),
      NAMEOF_ROW(CONST),
      NAMEOF_ROW(VAR),
      NAMEOF_ROW(LET),
      NAMEOF_ROW(INLINE_ASM),
      NAMEOF_ROW(IF),
      NAMEOF_ROW(WHILE),
      NAMEOF_ROW(FOR),
      NAMEOF_ROW(FORM),
      NAMEOF_ROW(FOREACH),
      NAMEOF_ROW(BREAK),
      NAMEOF_ROW(CONTINUE),
      NAMEOF_ROW(RETURN),
      NAMEOF_ROW(RETIF),
      NAMEOF_ROW(RETZ),
      NAMEOF_ROW(RETV),
      NAMEOF_ROW(CASE),
      NAMEOF_ROW(SWITCH),
      NAMEOF_ROW(TYPEDEF),
      NAMEOF_ROW(FNDECL),
      NAMEOF_ROW(FN),
      NAMEOF_ROW(COMPOSITE_FIELD),
      NAMEOF_ROW(STRUCT),
      NAMEOF_ROW(GROUP),
      NAMEOF_ROW(REGION),
      NAMEOF_ROW(UNION),
      NAMEOF_ROW(ENUM),
      NAMEOF_ROW(SUBSYSTEM),
      NAMEOF_ROW(EXPORT),
      NAMEOF_ROW(EXPR_STMT),
  };

  qcore_assert(names.size() == QAST_NODE_COUNT, "Polymorphic type size lookup table is incomplete");
  qcore_assert(names.contains(type));

  return names.at(type);
}

LIB_EXPORT uint32_t Node::this_sizeof() const {
#define SIZEOF_ROW(__type) \
  { typeid(__type).hash_code(), sizeof(__type) }

  static const std::unordered_map<size_t, uint32_t> sizes = {
      SIZEOF_ROW(Stmt),         SIZEOF_ROW(Type),          SIZEOF_ROW(Decl),
      SIZEOF_ROW(Expr),         SIZEOF_ROW(ConstExpr),     SIZEOF_ROW(UnresolvedType),
      SIZEOF_ROW(InferType),    SIZEOF_ROW(TemplType),     SIZEOF_ROW(U1),
      SIZEOF_ROW(U8),           SIZEOF_ROW(U16),           SIZEOF_ROW(U32),
      SIZEOF_ROW(U64),          SIZEOF_ROW(U128),          SIZEOF_ROW(I8),
      SIZEOF_ROW(I16),          SIZEOF_ROW(I32),           SIZEOF_ROW(I64),
      SIZEOF_ROW(I128),         SIZEOF_ROW(F16),           SIZEOF_ROW(F32),
      SIZEOF_ROW(F64),          SIZEOF_ROW(F128),          SIZEOF_ROW(VoidTy),
      SIZEOF_ROW(PtrTy),        SIZEOF_ROW(OpaqueTy),      SIZEOF_ROW(TupleTy),
      SIZEOF_ROW(ArrayTy),      SIZEOF_ROW(EnumTy),        SIZEOF_ROW(RefTy),
      SIZEOF_ROW(StructTy),     SIZEOF_ROW(GroupTy),       SIZEOF_ROW(RegionTy),
      SIZEOF_ROW(UnionTy),      SIZEOF_ROW(FuncTy),        SIZEOF_ROW(UnaryExpr),
      SIZEOF_ROW(BinExpr),      SIZEOF_ROW(PostUnaryExpr), SIZEOF_ROW(TernaryExpr),
      SIZEOF_ROW(ConstInt),     SIZEOF_ROW(ConstFloat),    SIZEOF_ROW(ConstBool),
      SIZEOF_ROW(ConstString),  SIZEOF_ROW(ConstChar),     SIZEOF_ROW(ConstNull),
      SIZEOF_ROW(ConstUndef),   SIZEOF_ROW(Call),          SIZEOF_ROW(TemplCall),
      SIZEOF_ROW(List),         SIZEOF_ROW(Assoc),         SIZEOF_ROW(Field),
      SIZEOF_ROW(Index),        SIZEOF_ROW(Slice),         SIZEOF_ROW(FString),
      SIZEOF_ROW(Ident),        SIZEOF_ROW(SeqPoint),      SIZEOF_ROW(StmtExpr),
      SIZEOF_ROW(TypeExpr),     SIZEOF_ROW(Block),         SIZEOF_ROW(VolStmt),
      SIZEOF_ROW(ConstDecl),    SIZEOF_ROW(VarDecl),       SIZEOF_ROW(LetDecl),
      SIZEOF_ROW(InlineAsm),    SIZEOF_ROW(IfStmt),        SIZEOF_ROW(WhileStmt),
      SIZEOF_ROW(ForStmt),      SIZEOF_ROW(FormStmt),      SIZEOF_ROW(ForeachStmt),
      SIZEOF_ROW(BreakStmt),    SIZEOF_ROW(ContinueStmt),  SIZEOF_ROW(ReturnStmt),
      SIZEOF_ROW(ReturnIfStmt), SIZEOF_ROW(RetZStmt),      SIZEOF_ROW(RetVStmt),
      SIZEOF_ROW(CaseStmt),     SIZEOF_ROW(SwitchStmt),    SIZEOF_ROW(TypedefDecl),
      SIZEOF_ROW(FnDecl),       SIZEOF_ROW(FnDef),         SIZEOF_ROW(CompositeField),
      SIZEOF_ROW(StructDef),    SIZEOF_ROW(GroupDef),      SIZEOF_ROW(RegionDef),
      SIZEOF_ROW(UnionDef),     SIZEOF_ROW(EnumDef),       SIZEOF_ROW(SubsystemDecl),
      SIZEOF_ROW(ExportDecl),   SIZEOF_ROW(ExprStmt),
  };

  qcore_assert(sizes.size() == QAST_NODE_COUNT, "Polymorphic type size lookup table is incomplete");

  size_t id = typeid(*this).hash_code();
  qcore_assert(sizes.contains(id));

  return sizes.at(id);
}

LIB_EXPORT qparse_ty_t Node::this_typeid() const {
#define TYPEID_ROW(__type, __name) \
  { typeid(__type).hash_code(), QAST_NODE_##__name }

  static const std::unordered_map<size_t, qparse_ty_t> typeid_map = {
      TYPEID_ROW(Stmt, STMT),
      TYPEID_ROW(Type, TYPE),
      TYPEID_ROW(Decl, DECL),
      TYPEID_ROW(Expr, EXPR),
      TYPEID_ROW(ConstExpr, CEXPR),
      TYPEID_ROW(UnresolvedType, UNRES_TY),
      TYPEID_ROW(InferType, INFER_TY),
      TYPEID_ROW(TemplType, TEMPL_TY),
      TYPEID_ROW(U1, U1_TY),
      TYPEID_ROW(U8, U8_TY),
      TYPEID_ROW(U16, U16_TY),
      TYPEID_ROW(U32, U32_TY),
      TYPEID_ROW(U64, U64_TY),
      TYPEID_ROW(U128, U128_TY),
      TYPEID_ROW(I8, I8_TY),
      TYPEID_ROW(I16, I16_TY),
      TYPEID_ROW(I32, I32_TY),
      TYPEID_ROW(I64, I64_TY),
      TYPEID_ROW(I128, I128_TY),
      TYPEID_ROW(F16, F16_TY),
      TYPEID_ROW(F32, F32_TY),
      TYPEID_ROW(F64, F64_TY),
      TYPEID_ROW(F128, F128_TY),
      TYPEID_ROW(VoidTy, VOID_TY),
      TYPEID_ROW(PtrTy, PTR_TY),
      TYPEID_ROW(OpaqueTy, OPAQUE_TY),
      TYPEID_ROW(TupleTy, TUPLE_TY),
      TYPEID_ROW(ArrayTy, ARRAY_TY),
      TYPEID_ROW(EnumTy, ENUM_TY),
      TYPEID_ROW(RefTy, REF_TY),
      TYPEID_ROW(StructTy, STRUCT_TY),
      TYPEID_ROW(GroupTy, GROUP_TY),
      TYPEID_ROW(RegionTy, REGION_TY),
      TYPEID_ROW(UnionTy, UNION_TY),
      TYPEID_ROW(FuncTy, FN_TY),
      TYPEID_ROW(UnaryExpr, UNEXPR),
      TYPEID_ROW(BinExpr, BINEXPR),
      TYPEID_ROW(PostUnaryExpr, POST_UNEXPR),
      TYPEID_ROW(TernaryExpr, TEREXPR),
      TYPEID_ROW(ConstInt, INT),
      TYPEID_ROW(ConstFloat, FLOAT),
      TYPEID_ROW(ConstBool, BOOL),
      TYPEID_ROW(ConstString, STRING),
      TYPEID_ROW(ConstChar, CHAR),
      TYPEID_ROW(ConstNull, NULL),
      TYPEID_ROW(ConstUndef, UNDEF),
      TYPEID_ROW(Call, CALL),
      TYPEID_ROW(TemplCall, TEMPL_CALL),
      TYPEID_ROW(List, LIST),
      TYPEID_ROW(Assoc, ASSOC),
      TYPEID_ROW(Field, FIELD),
      TYPEID_ROW(Index, INDEX),
      TYPEID_ROW(Slice, SLICE),
      TYPEID_ROW(FString, FSTRING),
      TYPEID_ROW(Ident, IDENT),
      TYPEID_ROW(SeqPoint, SEQ_POINT),
      TYPEID_ROW(StmtExpr, STMT_EXPR),
      TYPEID_ROW(TypeExpr, TYPE_EXPR),
      TYPEID_ROW(Block, BLOCK),
      TYPEID_ROW(VolStmt, VOLSTMT),
      TYPEID_ROW(ConstDecl, CONST),
      TYPEID_ROW(VarDecl, VAR),
      TYPEID_ROW(LetDecl, LET),
      TYPEID_ROW(InlineAsm, INLINE_ASM),
      TYPEID_ROW(IfStmt, IF),
      TYPEID_ROW(WhileStmt, WHILE),
      TYPEID_ROW(ForStmt, FOR),
      TYPEID_ROW(FormStmt, FORM),
      TYPEID_ROW(ForeachStmt, FOREACH),
      TYPEID_ROW(BreakStmt, BREAK),
      TYPEID_ROW(ContinueStmt, CONTINUE),
      TYPEID_ROW(ReturnStmt, RETURN),
      TYPEID_ROW(ReturnIfStmt, RETIF),
      TYPEID_ROW(RetZStmt, RETZ),
      TYPEID_ROW(RetVStmt, RETV),
      TYPEID_ROW(CaseStmt, CASE),
      TYPEID_ROW(SwitchStmt, SWITCH),
      TYPEID_ROW(TypedefDecl, TYPEDEF),
      TYPEID_ROW(FnDecl, FNDECL),
      TYPEID_ROW(FnDef, FN),
      TYPEID_ROW(CompositeField, COMPOSITE_FIELD),
      TYPEID_ROW(StructDef, STRUCT),
      TYPEID_ROW(GroupDef, GROUP),
      TYPEID_ROW(RegionDef, REGION),
      TYPEID_ROW(UnionDef, UNION),
      TYPEID_ROW(EnumDef, ENUM),
      TYPEID_ROW(SubsystemDecl, SUBSYSTEM),
      TYPEID_ROW(ExportDecl, EXPORT),
      TYPEID_ROW(ExprStmt, EXPR_STMT),
  };

  qcore_assert(typeid_map.size() == QAST_NODE_COUNT);

  return typeid_map.at(typeid(*this).hash_code());
}

LIB_EXPORT const char *Node::this_nameof() const { return type_name(this_typeid()); }

LIB_EXPORT bool Node::is_type() const {
  switch (this_typeid()) {
    case QAST_NODE_TYPE:
    case QAST_NODE_REF_TY:
    case QAST_NODE_U1_TY:
    case QAST_NODE_U8_TY:
    case QAST_NODE_U16_TY:
    case QAST_NODE_U32_TY:
    case QAST_NODE_U64_TY:
    case QAST_NODE_U128_TY:
    case QAST_NODE_I8_TY:
    case QAST_NODE_I16_TY:
    case QAST_NODE_I32_TY:
    case QAST_NODE_I64_TY:
    case QAST_NODE_I128_TY:
    case QAST_NODE_F16_TY:
    case QAST_NODE_F32_TY:
    case QAST_NODE_F64_TY:
    case QAST_NODE_F128_TY:
    case QAST_NODE_VOID_TY:
    case QAST_NODE_PTR_TY:
    case QAST_NODE_OPAQUE_TY:
    case QAST_NODE_ENUM_TY:
    case QAST_NODE_STRUCT_TY:
    case QAST_NODE_GROUP_TY:
    case QAST_NODE_REGION_TY:
    case QAST_NODE_UNION_TY:
    case QAST_NODE_ARRAY_TY:
    case QAST_NODE_TUPLE_TY:
    case QAST_NODE_FN_TY:
    case QAST_NODE_UNRES_TY:
    case QAST_NODE_INFER_TY:
    case QAST_NODE_TEMPL_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Node::is_stmt() const {
  switch (this_typeid()) {
    case QAST_NODE_STMT:
    case QAST_NODE_TYPEDEF:
    case QAST_NODE_FNDECL:
    case QAST_NODE_STRUCT:
    case QAST_NODE_REGION:
    case QAST_NODE_GROUP:
    case QAST_NODE_UNION:
    case QAST_NODE_ENUM:
    case QAST_NODE_FN:
    case QAST_NODE_SUBSYSTEM:
    case QAST_NODE_EXPORT:
    case QAST_NODE_COMPOSITE_FIELD:
    case QAST_NODE_BLOCK:
    case QAST_NODE_VOLSTMT:
    case QAST_NODE_CONST:
    case QAST_NODE_VAR:
    case QAST_NODE_LET:
    case QAST_NODE_INLINE_ASM:
    case QAST_NODE_RETURN:
    case QAST_NODE_RETIF:
    case QAST_NODE_RETZ:
    case QAST_NODE_RETV:
    case QAST_NODE_BREAK:
    case QAST_NODE_CONTINUE:
    case QAST_NODE_IF:
    case QAST_NODE_WHILE:
    case QAST_NODE_FOR:
    case QAST_NODE_FORM:
    case QAST_NODE_FOREACH:
    case QAST_NODE_CASE:
    case QAST_NODE_SWITCH:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Node::is_decl() const {
  switch (this_typeid()) {
    case QAST_NODE_CONST:
    case QAST_NODE_VAR:
    case QAST_NODE_LET:
    case QAST_NODE_TYPEDEF:
    case QAST_NODE_FNDECL:
    case QAST_NODE_FN:
    case QAST_NODE_COMPOSITE_FIELD:
    case QAST_NODE_STRUCT:
    case QAST_NODE_GROUP:
    case QAST_NODE_REGION:
    case QAST_NODE_UNION:
    case QAST_NODE_ENUM:
    case QAST_NODE_SUBSYSTEM:
    case QAST_NODE_EXPORT:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Node::is_expr() const {
  switch (this_typeid()) {
    case QAST_NODE_EXPR:
    case QAST_NODE_CEXPR:
    case QAST_NODE_BINEXPR:
    case QAST_NODE_UNEXPR:
    case QAST_NODE_TEREXPR:
    case QAST_NODE_INT:
    case QAST_NODE_FLOAT:
    case QAST_NODE_STRING:
    case QAST_NODE_CHAR:
    case QAST_NODE_BOOL:
    case QAST_NODE_NULL:
    case QAST_NODE_UNDEF:
    case QAST_NODE_CALL:
    case QAST_NODE_TEMPL_CALL:
    case QAST_NODE_LIST:
    case QAST_NODE_ASSOC:
    case QAST_NODE_FIELD:
    case QAST_NODE_INDEX:
    case QAST_NODE_SLICE:
    case QAST_NODE_FSTRING:
    case QAST_NODE_IDENT:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Node::is(qparse_ty_t type) const { return type == this_typeid(); }
LIB_EXPORT bool Node::verify(std::ostream &os) const { return verify_impl(os); }
LIB_EXPORT void Node::canonicalize() { canonicalize_impl(); }

LIB_EXPORT std::string Node::to_string(bool minify, bool binary_repr) const {
#define INDENT_STEP 1
  size_t len = 0;
  uint8_t *outbuf = nullptr;

  if (binary_repr) {
    qparse_brepr(this, minify, &outbuf, &len);
  } else {
    outbuf = (uint8_t *)qparse_repr(this, minify, INDENT_STEP, &len);
  }

  std::string result((char *)outbuf, len);

  free(outbuf);

  return result;
}

///=============================================================================

LIB_EXPORT bool Type::is_primitive() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_primitive();
  }

  switch (this_typeid()) {
    case QAST_NODE_U1_TY:
    case QAST_NODE_U8_TY:
    case QAST_NODE_U16_TY:
    case QAST_NODE_U32_TY:
    case QAST_NODE_U64_TY:
    case QAST_NODE_U128_TY:
    case QAST_NODE_I8_TY:
    case QAST_NODE_I16_TY:
    case QAST_NODE_I32_TY:
    case QAST_NODE_I64_TY:
    case QAST_NODE_I128_TY:
    case QAST_NODE_F16_TY:
    case QAST_NODE_F32_TY:
    case QAST_NODE_F64_TY:
    case QAST_NODE_F128_TY:
    case QAST_NODE_VOID_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Type::is_array() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_array();
  }

  return this_typeid() == QAST_NODE_ARRAY_TY;
}

LIB_EXPORT bool Type::is_tuple() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_tuple();
  }

  return this_typeid() == QAST_NODE_TUPLE_TY;
}

LIB_EXPORT bool Type::is_pointer() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_pointer();
  }

  return this_typeid() == QAST_NODE_PTR_TY;
}

LIB_EXPORT bool Type::is_function() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_function();
  }

  return this_typeid() == QAST_NODE_FN_TY;
}

LIB_EXPORT bool Type::is_composite() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_composite();
  }

  switch (this_typeid()) {
    case QAST_NODE_ARRAY_TY:
    case QAST_NODE_TUPLE_TY:
    case QAST_NODE_STRUCT_TY:
    case QAST_NODE_GROUP_TY:
    case QAST_NODE_REGION_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Type::is_union() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_union();
  }

  return this_typeid() == QAST_NODE_UNION_TY;
}

LIB_EXPORT bool Type::is_numeric() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_numeric();
  }

  switch (this_typeid()) {
    case QAST_NODE_U1_TY:
    case QAST_NODE_U8_TY:
    case QAST_NODE_U16_TY:
    case QAST_NODE_U32_TY:
    case QAST_NODE_U64_TY:
    case QAST_NODE_U128_TY:
    case QAST_NODE_I8_TY:
    case QAST_NODE_I16_TY:
    case QAST_NODE_I32_TY:
    case QAST_NODE_I64_TY:
    case QAST_NODE_I128_TY:
    case QAST_NODE_F16_TY:
    case QAST_NODE_F32_TY:
    case QAST_NODE_F64_TY:
    case QAST_NODE_F128_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Type::is_integral() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_integral();
  }

  switch (this_typeid()) {
    case QAST_NODE_U1_TY:
    case QAST_NODE_U8_TY:
    case QAST_NODE_U16_TY:
    case QAST_NODE_U32_TY:
    case QAST_NODE_U64_TY:
    case QAST_NODE_U128_TY:
    case QAST_NODE_I8_TY:
    case QAST_NODE_I16_TY:
    case QAST_NODE_I32_TY:
    case QAST_NODE_I64_TY:
    case QAST_NODE_I128_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Type::is_floating_point() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_floating_point();
  }

  switch (this_typeid()) {
    case QAST_NODE_F16_TY:
    case QAST_NODE_F32_TY:
    case QAST_NODE_F64_TY:
    case QAST_NODE_F128_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Type::is_signed() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_signed();
  }

  switch (this_typeid()) {
    case QAST_NODE_I8_TY:
    case QAST_NODE_I16_TY:
    case QAST_NODE_I32_TY:
    case QAST_NODE_I64_TY:
    case QAST_NODE_I128_TY:
    case QAST_NODE_F16_TY:
    case QAST_NODE_F32_TY:
    case QAST_NODE_F64_TY:
    case QAST_NODE_F128_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Type::is_unsigned() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_unsigned();
  }

  switch (this_typeid()) {
    case QAST_NODE_U1_TY:
    case QAST_NODE_U8_TY:
    case QAST_NODE_U16_TY:
    case QAST_NODE_U32_TY:
    case QAST_NODE_U64_TY:
    case QAST_NODE_U128_TY:
      return true;
    default:
      return false;
  }
}

LIB_EXPORT bool Type::is_void() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_void();
  }

  return this_typeid() == QAST_NODE_VOID_TY;
}

LIB_EXPORT bool Type::is_bool() const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_bool();
  }

  return this_typeid() == QAST_NODE_U1_TY;
}

LIB_EXPORT bool Type::is_ref() const { return this_typeid() == QAST_NODE_REF_TY; }

LIB_EXPORT bool Type::is_volatile() const { return m_volatile; }

LIB_EXPORT bool Type::is_ptr_to(const Type *type) const {
  if (is<RefTy>()) {
    return as<RefTy>()->get_item()->is_ptr_to(type);
  }

  if (!is_pointer()) {
    return false;
  }

  Type *item = as<PtrTy>()->get_item();
  while (item->is<RefTy>()) {
    item = item->as<RefTy>()->get_item();
  }

  return item->is(type->this_typeid());
}

///=============================================================================

LIB_EXPORT bool Expr::is_binexpr() const {
  if (is<BinExpr>()) {
    return true;
  }

  if (!is<ConstExpr>()) {
    return false;
  }

  return as<ConstExpr>()->get_value()->is_binexpr();
}

LIB_EXPORT bool Expr::is_unaryexpr() const {
  if (is<UnaryExpr>()) {
    return true;
  }

  if (!is<ConstExpr>()) {
    return false;
  }

  return as<ConstExpr>()->get_value()->is_unaryexpr();
}

LIB_EXPORT bool Expr::is_ternaryexpr() const {
  if (is<TernaryExpr>()) {
    return true;
  }

  if (!is<ConstExpr>()) {
    return false;
  }

  return as<ConstExpr>()->get_value()->is_ternaryexpr();
}

bool ExprStmt::verify_impl(std::ostream &os) const {
  if (!m_expr) {
    os << "ExprStmt: expression is NULL\n";
    return false;
  }

  if (!m_expr->verify(os)) {
    os << "ExprStmt: expression is invalid\n";
    return false;
  }

  return true;
}

void ExprStmt::canonicalize_impl() {
  if (m_expr) {
    m_expr->canonicalize();
  }
}

void ExprStmt::print_impl(std::ostream &os, bool debug) const {
  if (m_expr) {
    m_expr->print(os, debug);
  } else {
    os << "?";
  }
  os << ";";
}

ExprStmt *ExprStmt::clone_impl() const {
  Expr *expr = m_expr ? m_expr->clone() : nullptr;
  return ExprStmt::get(expr);
}

bool StmtExpr::verify_impl(std::ostream &os) const {
  if (!m_stmt) {
    os << "StmtExpr: statement is NULL\n";
    return false;
  }

  if (!m_stmt->verify(os)) {
    os << "StmtExpr: statement is invalid\n";
    return false;
  }

  return true;
}

void StmtExpr::canonicalize_impl() {
  if (m_stmt) {
    m_stmt->canonicalize();
  }
}

void StmtExpr::print_impl(std::ostream &os, bool debug) const {
  if (m_stmt) {
    m_stmt->print(os, debug);
  } else {
    os << "?";
  }
}

StmtExpr *StmtExpr::clone_impl() const {
  Stmt *stmt = m_stmt ? m_stmt->clone() : nullptr;
  return StmtExpr::get(stmt);
}

bool TypeExpr::verify_impl(std::ostream &os) const {
  if (!m_type) {
    os << "TypeExpr: type is NULL\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "TypeExpr: type is invalid\n";
    return false;
  }

  return true;
}

void TypeExpr::canonicalize_impl() {
  if (m_type) {
    m_type->canonicalize();
  }
}

void TypeExpr::print_impl(std::ostream &os, bool debug) const {
  if (m_type) {
    m_type->print(os, debug);
  } else {
    os << "?";
  }
}

TypeExpr *TypeExpr::clone_impl() const {
  Type *type = m_type ? m_type->clone() : nullptr;
  return TypeExpr::get(type);
}

///=============================================================================

bool ConstExpr::verify_impl(std::ostream &os) const {
  if (!m_value) {
    os << "ConstExpr: value is NULL\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "ConstExpr: value is invalid\n";
    return false;
  }

  return true;
}

void ConstExpr::canonicalize_impl() {
  if (m_value) {
    m_value->canonicalize();
  }
}

void ConstExpr::print_impl(std::ostream &os, bool debug) const {
  os << "const ";
  if (m_value) {
    m_value->print(os, debug);
  } else {
    os << "?";
  }
}

ConstExpr *ConstExpr::clone_impl() const {
  Expr *value = m_value ? m_value->clone() : nullptr;
  return ConstExpr::get(value);
}

///=============================================================================

bool UnresolvedType::verify_impl(std::ostream &os) const {
  if (m_name.empty()) {
    os << "UnresolvedType: name is empty\n";
    return false;
  }

  return true;
}

void UnresolvedType::canonicalize_impl() {}

void UnresolvedType::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << m_name;
}

UnresolvedType *UnresolvedType::clone_impl() const { return UnresolvedType::get(m_name); }

bool InferType::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}

void InferType::canonicalize_impl() {}

void InferType::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "?";
}

InferType *InferType::clone_impl() const { return InferType::get(); }

bool TemplType::verify_impl(std::ostream &os) const {
  if (!m_template) {
    os << "TemplType: template type is NULL\n";
    return false;
  }

  if (!m_template->verify(os)) {
    os << "TemplType: template type is invalid\n";
    return false;
  }

  for (auto &arg : m_args) {
    if (!arg) {
      os << "TemplType: template argument is NULL\n";
      return false;
    }

    if (!arg->verify(os)) {
      os << "TemplType: template argument is invalid\n";
      return false;
    }
  }

  return true;
}

void TemplType::canonicalize_impl() {
  if (m_template) {
    m_template->canonicalize();
  }

  for (auto &arg : m_args) {
    if (arg) {
      arg->canonicalize();
    }
  }
}

void TemplType::print_impl(std::ostream &os, bool debug) const {
  if (m_template) {
    m_template->print(os, debug);
  } else {
    os << "?";
  }

  os << "<";

  for (size_t i = 0; i < m_args.size(); i++) {
    if (i > 0) {
      os << ", ";
    }

    if (m_args[i]) {
      m_args[i]->print(os, debug);
    } else {
      os << "?";
    }
  }

  os << ">";
}

TemplType *TemplType::clone_impl() const {
  Type *templ = m_template ? m_template->clone() : nullptr;
  TemplTypeArgs args;
  for (auto &arg : m_args) {
    args.push_back(arg ? arg->clone() : nullptr);
  }

  return TemplType::get(templ, args);
}

#define TRIVIAL_TYPE_IMPL(__typename, __dumpstr, __bits)            \
  bool __typename::verify_impl(std::ostream &os) const {            \
    (void)os;                                                       \
    return true;                                                    \
  }                                                                 \
  void __typename::canonicalize_impl() {}                           \
  void __typename::print_impl(std::ostream &os, bool debug) const { \
    (void)debug;                                                    \
    os << __dumpstr;                                                \
  }                                                                 \
  __typename *__typename::clone_impl() const { return __typename::get(); }

LIB_EXPORT TRIVIAL_TYPE_IMPL(U1, "u1", 1);
LIB_EXPORT TRIVIAL_TYPE_IMPL(U8, "u8", 8);
LIB_EXPORT TRIVIAL_TYPE_IMPL(U16, "u16", 16);
LIB_EXPORT TRIVIAL_TYPE_IMPL(U32, "u32", 32);
LIB_EXPORT TRIVIAL_TYPE_IMPL(U64, "u64", 64);
LIB_EXPORT TRIVIAL_TYPE_IMPL(U128, "u128", 128);
LIB_EXPORT TRIVIAL_TYPE_IMPL(I8, "i8", 8);
LIB_EXPORT TRIVIAL_TYPE_IMPL(I16, "i16", 16);
LIB_EXPORT TRIVIAL_TYPE_IMPL(I32, "i32", 32);
LIB_EXPORT TRIVIAL_TYPE_IMPL(I64, "i64", 64);
LIB_EXPORT TRIVIAL_TYPE_IMPL(I128, "i128", 128);
LIB_EXPORT TRIVIAL_TYPE_IMPL(F16, "f16", 16);
LIB_EXPORT TRIVIAL_TYPE_IMPL(F32, "f32", 32);
LIB_EXPORT TRIVIAL_TYPE_IMPL(F64, "f64", 64);
LIB_EXPORT TRIVIAL_TYPE_IMPL(F128, "f128", 128);
LIB_EXPORT TRIVIAL_TYPE_IMPL(VoidTy, "void", 0);

bool PtrTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "PtrTy: item type is NULL\n";
    return false;
  }

  if (!m_item->verify(os)) {
    os << "PtrTy: item type is invalid\n";
    return false;
  }

  return true;
}

void PtrTy::canonicalize_impl() {
  if (m_item) {
    m_item->canonicalize();
  }
}

void PtrTy::print_impl(std::ostream &os, bool debug) const {
  if (m_is_volatile) {
    os << "volatile<ptr<";

    if (m_item) {
      m_item->print(os, debug);
    } else {
      os << "?";
    }

    os << ">>";
  } else {
    os << "ptr<";

    if (m_item) {
      m_item->print(os, debug);
    } else {
      os << "?";
    }

    os << ">";
  }
}

PtrTy *PtrTy::clone_impl() const {
  Type *item = m_item ? m_item->clone() : nullptr;
  return PtrTy::get(item, m_is_volatile);
}

bool OpaqueTy::verify_impl(std::ostream &os) const {
  if (m_name.empty()) {
    os << "OpaqueTy: name is empty\n";
    return false;
  }

  return true;
}

void OpaqueTy::canonicalize_impl() {}
void OpaqueTy::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "opaque<" << m_name << ">";
}
OpaqueTy *OpaqueTy::clone_impl() const { return OpaqueTy::get(m_name); }

bool TupleTy::verify_impl(std::ostream &os) const {
  for (size_t i = 0; i < m_items.size(); i++) {
    if (!m_items[i]) {
      os << "TupleTy: item " << i << " is NULL\n";
      return false;
    }

    if (!m_items[i]->verify(os)) {
      os << "TupleTy: item " << i << " is invalid\n";
      return false;
    }
  }

  return true;
}

void TupleTy::canonicalize_impl() {
  for (auto item : m_items) {
    item->canonicalize();
  }
}

void TupleTy::print_impl(std::ostream &os, bool debug) const {
  os << "tuple<";

  for (size_t i = 0; i < m_items.size(); i++) {
    if (m_items[i]) {
      m_items[i]->print(os, debug);
    } else {
      os << "?";
    }

    if (i + 1 < m_items.size()) {
      os << ", ";
    }
  }

  os << ">";
}

TupleTy *TupleTy::clone_impl() const {
  std::vector<Type *, Arena<Type *>> items;
  for (auto item : m_items) {
    if (item) {
      items.push_back(item->clone());
    } else {
      items.push_back(nullptr);
    }
  }

  return TupleTy::get(items);
}

bool ArrayTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "ArrayTy: item type is NULL\n";
    return false;
  }

  if (!m_size) {
    os << "ArrayTy: size is NULL\n";
    return false;
  }

  if (!m_item->verify(os)) {
    os << "ArrayTy: item type is invalid\n";
    return false;
  }

  if (!m_size->verify(os)) {
    os << "ArrayTy: size is invalid\n";
    return false;
  }

  return true;
}

void ArrayTy::canonicalize_impl() {
  if (m_item) {
    m_item->canonicalize();
  }

  if (m_size) {
    m_size->canonicalize();
  }
}

void ArrayTy::print_impl(std::ostream &os, bool debug) const {
  os << "array<";

  if (m_item) {
    m_item->print(os, debug);
  } else {
    os << "?";
  }

  os << ", ";

  if (m_size) {
    m_size->print(os, debug);
  } else {
    os << "?";
  }

  os << ">";
}

ArrayTy *ArrayTy::clone_impl() const {
  Type *item = m_item ? m_item->clone() : nullptr;
  ConstExpr *size = m_size ? m_size->clone() : nullptr;

  return ArrayTy::get(item, size);
}

bool EnumTy::verify_impl(std::ostream &os) const {
  if (!m_memtype) {
    os << "EnumTy: member item type is NULL\n";
    return false;
  }

  if (!m_memtype->verify(os)) {
    os << "EnumTy: member item type is invalid\n";
    return false;
  }

  return true;
}

void EnumTy::canonicalize_impl() {
  if (m_memtype) {
    m_memtype->canonicalize();
  }
}

void EnumTy::print_impl(std::ostream &os, bool debug) const {
  os << "enum<" << m_name << ", ";

  if (m_memtype) {
    m_memtype->print(os, debug);
  } else {
    os << "?";
  }

  os << ">";
}

EnumTy *EnumTy::clone_impl() const {
  Type *memtype = m_memtype ? m_memtype->clone() : nullptr;
  return EnumTy::get(m_name, memtype);
}

bool RefTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "RefTy: item type is NULL\n";
    return false;
  }

  if (!m_item->verify(os)) {
    os << "RefTy: item type is invalid\n";
    return false;
  }

  return true;
}

void RefTy::canonicalize_impl() {
  if (m_item) {
    m_item->canonicalize();
  }
}

void RefTy::print_impl(std::ostream &os, bool debug) const {
  if (!m_item) {
    os << "mut<?>";
    return;
  }

  os << "mut<";
  m_item->print(os, debug);
  os << ">";
}

RefTy *RefTy::clone_impl() const {
  Type *item = m_item ? m_item->clone() : nullptr;
  return RefTy::get(item);
}

bool StructTy::verify_impl(std::ostream &os) const {
  std::set<String> names({});

  for (size_t i = 0; i < m_items.size(); i++) {
    if (names.contains(m_items[i].first)) {
      os << "StructTy: duplicate field name '" << m_items[i].first << "'\n";
      return false;
    }

    if (!m_items[i].second) {
      os << "StructTy: item " << i << " is NULL\n";
      return false;
    }

    if (!m_items[i].second->verify(os)) {
      os << "StructTy: item " << i << " is invalid\n";
      return false;
    }

    names.insert(m_items[i].first);
  }

  return true;
}

void StructTy::canonicalize_impl() {
  for (auto &[name, item] : m_items) {
    if (item) {
      item->canonicalize();
    }
  }
}

void StructTy::print_impl(std::ostream &os, bool debug) const {
  os << "struct<";

  for (size_t i = 0; i < m_items.size(); i++) {
    os << m_items[i].first << ": ";

    if (m_items[i].second) {
      m_items[i].second->print(os, debug);
    } else {
      os << "?";
    }

    if (i + 1 < m_items.size()) {
      os << ", ";
    }
  }

  os << ">";
}

StructTy *StructTy::clone_impl() const {
  std::vector<StructItem, Arena<StructItem>> fields;
  for (auto &[name, item] : m_items) {
    if (item) {
      fields.push_back({name, item->clone()});
    } else {
      fields.push_back({name, nullptr});
    }
  }

  return StructTy::get(fields);
}

LIB_EXPORT void StructTy::add_item(String name, Type *item) { m_items.push_back({name, item}); }

LIB_EXPORT void StructTy::add_items(std::initializer_list<StructItem> fields) {
  for (auto [name, item] : fields) {
    add_item(name, item);
  }
}

LIB_EXPORT void StructTy::clear_items() { m_items.clear(); }

LIB_EXPORT void StructTy::remove_item(String name) {
  std::erase_if(m_items, [name](auto &field) { return field.first == name; });
}

bool GroupTy::verify_impl(std::ostream &os) const {
  for (size_t i = 0; i < m_items.size(); i++) {
    if (!m_items[i]) {
      os << "GroupTy: item " << i << " is NULL\n";
      return false;
    }

    if (!m_items[i]->verify(os)) {
      os << "GroupTy: item " << i << " is invalid\n";
      return false;
    }
  }

  return true;
}

void GroupTy::canonicalize_impl() {
  for (auto item : m_items) {
    if (item) {
      item->canonicalize();
    }
  }
}

void GroupTy::print_impl(std::ostream &os, bool debug) const {
  os << "group<";

  for (size_t i = 0; i < m_items.size(); i++) {
    if (m_items[i]) {
      m_items[i]->print(os, debug);
    } else {
      os << "?";
    }

    if (i + 1 < m_items.size()) {
      os << ", ";
    }
  }

  os << ">";
}

GroupTy *GroupTy::clone_impl() const {
  std::vector<Type *, Arena<Type *>> fields;
  for (auto item : m_items) {
    if (item) {
      fields.push_back(item->clone());
    } else {
      fields.push_back(nullptr);
    }
  }

  return GroupTy::get(fields);
}

LIB_EXPORT void GroupTy::add_item(Type *item) { m_items.push_back(item); }

LIB_EXPORT void GroupTy::add_items(std::initializer_list<Type *> fields) {
  for (auto field : fields) {
    add_item(field);
  }
}

LIB_EXPORT void GroupTy::clear_items() { m_items.clear(); }

LIB_EXPORT void GroupTy::remove_item(Type *item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

bool RegionTy::verify_impl(std::ostream &os) const {
  for (size_t i = 0; i < m_items.size(); i++) {
    if (!m_items[i]) {
      os << "RegionTy: item " << i << " is NULL\n";
      return false;
    }

    if (!m_items[i]->verify(os)) {
      os << "RegionTy: item " << i << " is invalid\n";
      return false;
    }
  }

  return true;
}

void RegionTy::canonicalize_impl() {
  for (auto item : m_items) {
    if (item) {
      item->canonicalize();
    }
  }
}

void RegionTy::print_impl(std::ostream &os, bool debug) const {
  os << "region<";

  for (size_t i = 0; i < m_items.size(); i++) {
    if (m_items[i]) {
      m_items[i]->print(os, debug);
    } else {
      os << "?";
    }

    if (i + 1 < m_items.size()) {
      os << ", ";
    }
  }

  os << ">";
}

RegionTy *RegionTy::clone_impl() const {
  std::vector<Type *, Arena<Type *>> fields;
  for (auto item : m_items) {
    if (item) {
      fields.push_back(item->clone());
    } else {
      fields.push_back(nullptr);
    }
  }

  return RegionTy::get(fields);
}

LIB_EXPORT void RegionTy::add_item(Type *item) { m_items.push_back(item); }

LIB_EXPORT void RegionTy::add_items(std::initializer_list<Type *> fields) {
  for (auto field : fields) {
    add_item(field);
  }
}

LIB_EXPORT void RegionTy::clear_items() { m_items.clear(); }

LIB_EXPORT void RegionTy::remove_item(Type *item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

bool UnionTy::verify_impl(std::ostream &os) const {
  for (size_t i = 0; i < m_items.size(); i++) {
    if (!m_items[i]) {
      os << "UnionTy: item " << i << " is NULL\n";
      return false;
    }

    if (!m_items[i]->verify(os)) {
      os << "UnionTy: item " << i << " is invalid\n";
      return false;
    }
  }

  return true;
}

void UnionTy::canonicalize_impl() {
  for (auto item : m_items) {
    if (item) {
      item->canonicalize();
    }
  }
}

void UnionTy::print_impl(std::ostream &os, bool debug) const {
  os << "union<";

  for (size_t i = 0; i < m_items.size(); i++) {
    if (m_items[i]) {
      m_items[i]->print(os, debug);
    } else {
      os << "?";
    }

    if (i + 1 < m_items.size()) {
      os << ", ";
    }
  }

  os << ">";
}

UnionTy *UnionTy::clone_impl() const {
  std::vector<Type *, Arena<Type *>> fields;
  for (auto item : m_items) {
    if (item) {
      fields.push_back(item->clone());
    } else {
      fields.push_back(nullptr);
    }
  }

  return UnionTy::get(fields);
}

LIB_EXPORT void UnionTy::add_item(Type *item) { m_items.push_back(item); }

LIB_EXPORT void UnionTy::add_items(std::initializer_list<Type *> fields) {
  for (auto field : fields) {
    add_item(field);
  }
}

LIB_EXPORT void UnionTy::clear_items() { m_items.clear(); }

LIB_EXPORT void UnionTy::remove_item(Type *item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

bool FuncTy::verify_impl(std::ostream &os) const {
  if (!m_return) {
    os << "FuncTy: return type is NULL\n";
    return false;
  }

  std::set<String> names({});
  for (size_t i = 0; i < m_params.size(); i++) {
    if (names.contains(std::get<0>(m_params[i]))) {
      os << "FuncTy: duplicate param name '" << std::get<0>(m_params[i]) << "'\n";
      return false;
    }

    if (!std::get<1>(m_params[i])) {
      os << "FuncTy: param " << i << " is NULL\n";
      return false;
    }

    if (!std::get<1>(m_params[i])->verify(os)) {
      os << "FuncTy: param " << i << " is invalid\n";
      return false;
    }

    if (std::get<2>(m_params[i])) {
      if (!std::get<2>(m_params[i])->verify(os)) {
        os << "FuncTy: param default " << i << " is invalid\n";
        return false;
      }
    }

    names.insert(std::get<0>(m_params[i]));
  }

  if (!m_return->verify(os)) {
    os << "FuncTy: return type is invalid\n";
    return false;
  }

  if (m_noreturn) {
    if (!m_return->is_void()) {
      os << "FuncTy: noreturn function does not return void\n";
      return false;
    }
  }

  return true;
}

void FuncTy::canonicalize_impl() {
  for (auto &[name, param, default_val] : m_params) {
    if (param) {
      param->canonicalize();
    }

    if (default_val) {
      default_val->canonicalize();
    }
  }

  if (m_return) {
    m_return->canonicalize();
  }
}

void FuncTy::print_impl(std::ostream &os, bool debug) const {
  os << "func<(";

  for (size_t i = 0; i < m_params.size(); i++) {
    os << std::get<0>(m_params[i]) << ": ";

    if (std::get<1>(m_params[i])) {
      std::get<1>(m_params[i])->print(os, debug);
    } else {
      os << "?";
    }

    if (std::get<2>(m_params[i])) {
      os << " = ";
      std::get<2>(m_params[i])->print(os, debug);
    }

    if (i + 1 < m_params.size()) {
      os << ", ";
    }
  }

  if (m_variadic) {
    os << ", ...";
  }

  os << ") ";

  if (m_is_foreign) {
    os << "foreign ";
  }

  if (m_crashpoint) {
    os << "crashpoint ";
  }

  if (m_noexcept) {
    os << "noexcept ";
  }

  if (m_noreturn) {
    os << "noreturn ";
  }

  switch (m_purity) {
    case FuncPurity::IMPURE_THREAD_UNSAFE:
      os << "impure ";
      break;
    case FuncPurity::IMPURE_THREAD_SAFE:
      os << "impure tsafe ";
      break;
    case FuncPurity::PURE:
      os << "pure tsafe ";
      break;
    case FuncPurity::QUASIPURE:
      os << "quasipure tsafe ";
      break;
    case FuncPurity::RETROPURE:
      os << "retropure tsafe ";
      break;
  }

  os << "-> ";

  if (m_return) {
    m_return->print(os, debug);
  } else {
    os << "?";
  }

  os << ">";
}

FuncTy *FuncTy::clone_impl() const {
  std::vector<FuncParam, Arena<FuncParam>> params;
  for (auto [name, param, default_val] : m_params) {
    Type *p = param ? param->clone() : nullptr;
    Expr *d = default_val ? default_val->clone() : nullptr;

    params.push_back({name, p, d});
  }

  Type *ret = m_return ? m_return->clone() : nullptr;

  return FuncTy::get(ret, params, m_variadic, m_purity, m_is_foreign, m_crashpoint, m_noexcept,
                     m_noreturn);
}

LIB_EXPORT bool FuncTy::is_noreturn() const { return m_noreturn; }

LIB_EXPORT void FuncTy::add_param(String name, Type *ty, Expr *default_val) {
  m_params.push_back({name, ty, default_val});
}
LIB_EXPORT void FuncTy::add_params(std::initializer_list<FuncParam> params) {
  for (auto [name, ty, expr] : params) {
    add_param(name, ty, expr);
  }
}
LIB_EXPORT void FuncTy::clear_params() { m_params.clear(); }
LIB_EXPORT void FuncTy::remove_param(String name) {
  std::erase_if(m_params, [name](auto &param) { return std::get<0>(param) == name; });
}

///=============================================================================

bool UnaryExpr::verify_impl(std::ostream &os) const {
  if (!m_rhs) {
    os << "UnaryExpr: rhs is NULL\n";
    return false;
  }

  if (m_op == 0) {
    os << "UnaryExpr: unknown operator\n";
    return false;
  }

  if (!m_rhs->verify(os)) {
    os << "UnaryExpr: rhs is invalid\n";
    return false;
  }

  return true;
}

void UnaryExpr::canonicalize_impl() {
  if (m_rhs) {
    m_rhs->canonicalize();
  }
}

void UnaryExpr::print_impl(std::ostream &os, bool debug) const {
  os << "(";

  os << m_op;

  if (m_rhs) {
    m_rhs->print(os, debug);
  } else {
    os << "?";
  }
}

UnaryExpr *UnaryExpr::clone_impl() const {
  Expr *rhs = m_rhs ? m_rhs->clone() : nullptr;
  return UnaryExpr::get(m_op, rhs);
}

bool BinExpr::verify_impl(std::ostream &os) const {
  if (!m_lhs) {
    os << "BinExpr: lhs is NULL\n";
    return false;
  }

  if (!m_rhs) {
    os << "BinExpr: rhs is NULL\n";
    return false;
  }

  if (m_op == 0) {
    os << "BinExpr: unknown operator\n";
    return false;
  }

  if (!m_lhs->verify(os)) {
    os << "BinExpr: lhs is invalid\n";
    return false;
  }

  if (!m_rhs->verify(os)) {
    os << "BinExpr: rhs is invalid\n";
    return false;
  }

  return true;
}

void BinExpr::canonicalize_impl() {
  if (m_lhs) {
    m_lhs->canonicalize();
  }

  if (m_rhs) {
    m_rhs->canonicalize();
  }
}

void BinExpr::print_impl(std::ostream &os, bool debug) const {
  os << "(";

  if (m_lhs) {
    m_lhs->print(os, debug);
  } else {
    os << "?";
  }

  os << " " << m_op << " ";

  if (m_rhs) {
    m_rhs->print(os, debug);
  } else {
    os << "?";
  }

  os << ")";
}

BinExpr *BinExpr::clone_impl() const {
  Expr *lhs = m_lhs ? m_lhs->clone() : nullptr;
  Expr *rhs = m_rhs ? m_rhs->clone() : nullptr;

  return BinExpr::get(lhs, m_op, rhs);
}

bool PostUnaryExpr::verify_impl(std::ostream &os) const {
  if (!m_lhs) {
    os << "PostUnaryExpr: lhs is NULL\n";
    return false;
  }

  if (m_op == 0) {
    os << "PostUnaryExpr: unknown operator\n";
    return false;
  }

  if (!m_lhs->verify(os)) {
    os << "PostUnaryExpr: lhs is invalid\n";
    return false;
  }

  return true;
}

void PostUnaryExpr::canonicalize_impl() {
  if (m_lhs) {
    m_lhs->canonicalize();
  }
}

void PostUnaryExpr::print_impl(std::ostream &os, bool debug) const {
  os << "(";

  if (m_lhs) {
    m_lhs->print(os, debug);
  } else {
    os << "?";
  }

  os << m_op;

  os << ")";
}

PostUnaryExpr *PostUnaryExpr::clone_impl() const {
  Expr *lhs = m_lhs ? m_lhs->clone() : nullptr;
  return PostUnaryExpr::get(lhs, m_op);
}

bool TernaryExpr::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "TernaryExpr: cond is NULL\n";
    return false;
  }

  if (!m_lhs) {
    os << "TernaryExpr: lhs is NULL\n";
    return false;
  }

  if (!m_rhs) {
    os << "TernaryExpr: rhs is NULL\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "TernaryExpr: cond is invalid\n";
    return false;
  }

  if (!m_lhs->verify(os)) {
    os << "TernaryExpr: lhs is invalid\n";
    return false;
  }

  if (!m_rhs->verify(os)) {
    os << "TernaryExpr: rhs is invalid\n";
    return false;
  }

  return true;
}

void TernaryExpr::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }

  if (m_lhs) {
    m_lhs->canonicalize();
  }

  if (m_rhs) {
    m_rhs->canonicalize();
  }
}

void TernaryExpr::print_impl(std::ostream &os, bool debug) const {
  os << "(";

  if (m_cond) {
    m_cond->print(os, debug);
  } else {
    os << "?";
  }

  os << " ? (";

  if (m_lhs) {
    m_lhs->print(os, debug);
  } else {
    os << "?";
  }

  os << ") : (";

  if (m_rhs) {
    m_rhs->print(os, debug);
  } else {
    os << "?";
  }

  os << "))";
}

TernaryExpr *TernaryExpr::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Expr *lhs = m_lhs ? m_lhs->clone() : nullptr;
  Expr *rhs = m_rhs ? m_rhs->clone() : nullptr;

  return TernaryExpr::get(cond, lhs, rhs);
}

///=============================================================================

bool ConstInt::verify_impl(std::ostream &os) const {
  if (m_value.empty()) {
    os << "ConstInt: value is empty\n";
    return false;
  }

  for (char c : m_value) {
    if (!std::isdigit(c)) {
      os << "ConstInt: value is not a number\n";
      return false;
    }
  }

  return true;
}

void ConstInt::canonicalize_impl() {}

void ConstInt::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << m_value;
}

ConstInt *ConstInt::clone_impl() const { return ConstInt::get(m_value); }

bool ConstFloat::verify_impl(std::ostream &os) const {
  if (m_value.empty()) {
    os << "ConstFloat: value is empty\n";
    return false;
  }

  bool found_dot = false;

  for (char c : m_value) {
    if (!std::isdigit(c) && c != '.') {
      os << "ConstFloat: value is not a number\n";
      return false;
    }

    if (c == '.') {
      if (found_dot) {
        os << "ConstFloat: value has multiple dots\n";
        return false;
      }

      found_dot = true;
    }
  }

  return true;
}

void ConstFloat::canonicalize_impl() {}

void ConstFloat::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << m_value;
}

ConstFloat *ConstFloat::clone_impl() const { return ConstFloat::get(m_value); }

bool ConstBool::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}

void ConstBool::canonicalize_impl() {}

void ConstBool::print_impl(std::ostream &os, bool debug) const {
  (void)debug;

  os << (m_value ? "true" : "false");
}

ConstBool *ConstBool::clone_impl() const { return ConstBool::get(m_value); }

bool ConstChar::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}

void ConstChar::canonicalize_impl() {}

void ConstChar::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "'\\u{" << std::hex << (int32_t)m_value << "}'" << std::dec;
}

ConstChar *ConstChar::clone_impl() const { return ConstChar::get(m_value); }

bool ConstString::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}

void ConstString::canonicalize_impl() {}

void ConstString::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "\"" << m_value << "\"";
}

ConstString *ConstString::clone_impl() const { return ConstString::get(m_value); }

bool ConstNull::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}
void ConstNull::canonicalize_impl() {}
void ConstNull::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "null";
}
ConstNull *ConstNull::clone_impl() const { return ConstNull::get(); }

bool ConstUndef::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}
void ConstUndef::canonicalize_impl() {}
void ConstUndef::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "undef";
}
ConstUndef *ConstUndef::clone_impl() const { return ConstUndef::get(); }

///=============================================================================

bool Call::verify_impl(std::ostream &os) const {
  if (!m_func) {
    os << "CallExpr: function is NULL\n";
    return false;
  }

  for (const auto &[name, expr] : m_args) {
    if (!expr) {
      os << "CallExpr: arg '" << name << "' is NULL\n";
      return false;
    }

    if (!expr->verify(os)) {
      os << "CallExpr: arg '" << name << "' is invalid\n";
      return false;
    }
  }

  if (!m_func->verify(os)) {
    os << "CallExpr: function is invalid\n";
    return false;
  }

  return true;
}

void Call::canonicalize_impl() {
  if (m_func) {
    m_func->canonicalize();
  }

  for (auto &[name, expr] : m_args) {
    if (expr) {
      expr->canonicalize();
    }
  }
}

void Call::print_impl(std::ostream &os, bool debug) const {
  if (m_func) {
    m_func->print(os, debug);
  } else {
    os << "?";
  }

  os << "(";

  for (auto it = m_args.begin(); it != m_args.end(); ++it) {
    os << it->first << ": ";
    if (it->second) {
      it->second->print(os, debug);
    } else {
      os << "?";
    }
    if (std::next(it) != m_args.end()) {
      os << ", ";
    }
  }

  os << ")";
}

Call *Call::clone_impl() const {
  Expr *func = m_func ? m_func->clone() : nullptr;
  CallArgs args;

  for (const auto &[name, expr] : m_args) {
    Expr *e = expr ? expr->clone() : nullptr;
    args.push_back({name, e});
  }

  return Call::get(func, args);
}

LIB_EXPORT void Call::add_arg(CallArg arg) { m_args.push_back(arg); }
LIB_EXPORT void Call::add_args(std::initializer_list<CallArg> args) {
  for (auto arg : args) {
    add_arg(arg);
  }
}
LIB_EXPORT void Call::clear_args() { m_args.clear(); }
LIB_EXPORT void Call::remove_arg(String name) {
  std::erase_if(m_args, [name](auto &arg) { return arg.first == name; });
}

bool TemplCall::verify_impl(std::ostream &os) const {
  if (!m_func) {
    os << "TemplCall: function is NULL\n";
    return false;
  }

  for (const auto &[name, expr] : m_args) {
    if (!expr) {
      os << "TemplCall: arg '" << name << "' is NULL\n";
      return false;
    }

    if (!expr->verify(os)) {
      os << "TemplCall: arg '" << name << "' is invalid\n";
      return false;
    }
  }

  for (const auto &[key, value] : m_template_args) {
    if (!value) {
      os << "TemplCall: param is NULL\n";
      return false;
    }

    if (!value->verify(os)) {
      os << "TemplCall: param is invalid\n";
      return false;
    }
  }

  if (!m_func->verify(os)) {
    os << "TemplCall: function is invalid\n";
    return false;
  }

  return true;
}

void TemplCall::canonicalize_impl() {
  if (m_func) {
    m_func->canonicalize();
  }

  for (auto &[name, expr] : m_args) {
    if (expr) {
      expr->canonicalize();
    }
  }

  for (auto &[key, value] : m_template_args) {
    if (value) {
      value->canonicalize();
    }
  }
}

void TemplCall::print_impl(std::ostream &os, bool debug) const {
  (void)os;
  (void)debug;

  qcore_implement(__func__);
}

TemplCall *TemplCall::clone_impl() const {
  Expr *func = m_func ? m_func->clone() : nullptr;
  CallArgs args;

  for (const auto &[name, expr] : m_args) {
    Expr *e = expr ? expr->clone() : nullptr;
    args.push_back({name, e});
  }

  TemplateArgs template_args;

  for (const auto &[key, value] : m_template_args) {
    ConstExpr *v = value ? value->clone() : nullptr;
    template_args[key] = v;
  }

  return TemplCall::get(func, args, template_args);
}

LIB_EXPORT void TemplCall::add_template_arg(String name, ConstExpr *arg) {
  m_template_args[name] = arg;
}
LIB_EXPORT void TemplCall::clear_template_args() { m_template_args.clear(); }
LIB_EXPORT void TemplCall::remove_template_arg(String name) { m_template_args.erase(name); }

bool List::verify_impl(std::ostream &os) const {
  for (size_t i = 0; i < m_items.size(); i++) {
    if (!m_items[i]) {
      os << "List: item " << i << " is NULL\n";
      return false;
    }

    if (!m_items[i]->verify(os)) {
      os << "List: item " << i << " is invalid\n";
      return false;
    }
  }

  return true;
}

void List::canonicalize_impl() {
  for (auto item : m_items) {
    if (item) {
      item->canonicalize();
    }
  }
}

void List::print_impl(std::ostream &os, bool debug) const {
  os << "[";

  for (size_t i = 0; i < m_items.size(); i++) {
    if (m_items[i]) {
      m_items[i]->print(os, debug);
    } else {
      os << "?";
    }

    if (i + 1 < m_items.size()) {
      os << ", ";
    }
  }

  os << "]";
}

List *List::clone_impl() const {
  ListData items;
  for (auto item : m_items) {
    if (item) {
      items.push_back(item->clone());
    } else {
      items.push_back(nullptr);
    }
  }

  return List::get(items);
}

LIB_EXPORT void List::add_item(Expr *item) { m_items.push_back(item); }
LIB_EXPORT void List::clear_items() { m_items.clear(); }
LIB_EXPORT void List::remove_item(Expr *item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

bool Assoc::verify_impl(std::ostream &os) const {
  if (!m_key) {
    os << "Assoc: key is NULL\n";
    return false;
  }

  if (!m_value) {
    os << "Assoc: value is NULL\n";
    return false;
  }

  if (!m_key->verify(os)) {
    os << "Assoc: key is invalid\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "Assoc: value is invalid\n";
    return false;
  }

  return true;
}

void Assoc::canonicalize_impl() {
  if (m_key) {
    m_key->canonicalize();
  }

  if (m_value) {
    m_value->canonicalize();
  }
}

void Assoc::print_impl(std::ostream &os, bool debug) const {
  if (m_key) {
    m_key->print(os, debug);
  } else {
    os << "?";
  }

  os << ": ";

  if (m_value) {
    m_value->print(os, debug);
  } else {
    os << "?";
  }
}

Assoc *Assoc::clone_impl() const {
  Expr *key = m_key ? m_key->clone() : nullptr;
  Expr *value = m_value ? m_value->clone() : nullptr;

  return Assoc::get(key, value);
}

bool Field::verify_impl(std::ostream &os) const {
  if (!m_base) {
    os << "Field: base is NULL\n";
    return false;
  }

  if (m_field.empty()) {
    os << "Field: field is empty\n";
    return false;
  }

  if (!m_base->verify(os)) {
    os << "Field: base is invalid\n";
    return false;
  }

  return true;
}

void Field::canonicalize_impl() {
  if (m_base) {
    m_base->canonicalize();
  }
}

void Field::print_impl(std::ostream &os, bool debug) const {
  if (m_base) {
    m_base->print(os, debug);
  } else {
    os << "?";
  }

  os << "." << m_field;
}

Field *Field::clone_impl() const {
  Expr *base = m_base ? m_base->clone() : nullptr;
  return Field::get(base, m_field);
}

bool Index::verify_impl(std::ostream &os) const {
  if (!m_base) {
    os << "Index: base is NULL\n";
    return false;
  }

  if (!m_index) {
    os << "Index: index is NULL\n";
    return false;
  }

  if (!m_base->verify(os)) {
    os << "Index: base is invalid\n";
    return false;
  }

  if (!m_index->verify(os)) {
    os << "Index: index is invalid\n";
    return false;
  }

  return true;
}

void Index::canonicalize_impl() {
  if (m_base) {
    m_base->canonicalize();
  }

  if (m_index) {
    m_index->canonicalize();
  }
}

void Index::print_impl(std::ostream &os, bool debug) const {
  if (m_base) {
    m_base->print(os, debug);
  } else {
    os << "?";
  }

  os << "[";

  if (m_index) {
    m_index->print(os, debug);
  } else {
    os << "?";
  }

  os << "]";
}

Index *Index::clone_impl() const {
  Expr *base = m_base ? m_base->clone() : nullptr;
  Expr *index = m_index ? m_index->clone() : nullptr;

  return Index::get(base, index);
}

bool Slice::verify_impl(std::ostream &os) const {
  if (!m_base) {
    os << "Slice: base is NULL\n";
    return false;
  }

  if (!m_start) {
    os << "Slice: start is NULL\n";
    return false;
  }

  if (!m_end) {
    os << "Slice: end is NULL\n";
    return false;
  }

  if (!m_base->verify(os)) {
    os << "Slice: base is invalid\n";
    return false;
  }

  if (!m_start->verify(os)) {
    os << "Slice: start is invalid\n";
    return false;
  }

  if (!m_end->verify(os)) {
    os << "Slice: end is invalid\n";
    return false;
  }

  return true;
}

void Slice::canonicalize_impl() {
  if (m_base) {
    m_base->canonicalize();
  }

  if (m_start) {
    m_start->canonicalize();
  }

  if (m_end) {
    m_end->canonicalize();
  }
}

void Slice::print_impl(std::ostream &os, bool debug) const {
  if (m_base) {
    m_base->print(os, debug);
  } else {
    os << "?";
  }

  os << "[";

  if (m_start) {
    m_start->print(os, debug);
  } else {
    os << "?";
  }

  os << ":";

  if (m_end) {
    m_end->print(os, debug);
  } else {
    os << "?";
  }

  os << "]";
}

Slice *Slice::clone_impl() const {
  Expr *base = m_base ? m_base->clone() : nullptr;
  Expr *start = m_start ? m_start->clone() : nullptr;
  Expr *end = m_end ? m_end->clone() : nullptr;

  return Slice::get(base, start, end);
}

bool FString::verify_impl(std::ostream &os) const {
  for (auto item : m_items) {
    if (std::holds_alternative<String>(item)) {
      continue;
    }

    auto x = std::get<Expr *>(item);

    if (!x) {
      os << "FString: item is NULL\n";
      return false;
    }

    if (!x->verify(os)) {
      os << "FString: item is invalid\n";
      return false;
    }
  }

  return true;
}

void FString::canonicalize_impl() {
  for (auto item : m_items) {
    if (std::holds_alternative<Expr *>(item)) {
      auto x = std::get<Expr *>(item);
      if (x) {
        x->canonicalize();
      }
    }
  }
}

void FString::print_impl(std::ostream &os, bool debug) const {
  os << "f\"";

  for (auto item : m_items) {
    if (std::holds_alternative<String>(item)) {
      os << std::get<String>(item);
    } else {
      os << "{";
      std::get<Expr *>(item)->print(os, debug);
      os << "}";
    }
  }

  os << "\"";
}

FString *FString::clone_impl() const {
  FStringItems items;
  for (auto item : m_items) {
    if (std::holds_alternative<String>(item)) {
      items.push_back(std::get<String>(item));
    } else {
      items.push_back(std::get<Expr *>(item)->clone());
    }
  }

  return FString::get(items);
}

LIB_EXPORT void qparse::FString::add_item(qparse::String item) { m_items.push_back(item); }
LIB_EXPORT void qparse::FString::add_item(qparse::Expr *item) { m_items.push_back(item); }

bool Ident::verify_impl(std::ostream &os) const {
  if (m_name.empty()) {
    os << "Ident: name is empty\n";
    return false;
  }

  return true;
}

void Ident::canonicalize_impl() {}

void Ident::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << m_name;
}

Ident *Ident::clone_impl() const { return Ident::get(m_name); }

bool SeqPoint::verify_impl(std::ostream &os) const {
  for (auto item : m_items) {
    if (!item) {
      os << "SeqPoint: item is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "SeqPoint: item is invalid\n";
      return false;
    }
  }

  return true;
}

void SeqPoint::canonicalize_impl() {
  for (auto item : m_items) {
    if (item) {
      item->canonicalize();
    }
  }
}

void SeqPoint::print_impl(std::ostream &os, bool debug) const {
  for (auto item : m_items) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << ",";
  }
}

SeqPoint *SeqPoint::clone_impl() const {
  SeqPointItems items;
  for (auto item : m_items) {
    if (item) {
      items.push_back(item->clone());
    } else {
      items.push_back(nullptr);
    }
  }

  return SeqPoint::get(items);
}

LIB_EXPORT void SeqPoint::add_item(Expr *item) { m_items.push_back(item); }
LIB_EXPORT void SeqPoint::clear_items() { m_items.clear(); }
LIB_EXPORT void SeqPoint::remove_item(Expr *item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

///=============================================================================

bool Block::verify_impl(std::ostream &os) const {
  for (auto item : m_items) {
    if (!item) {
      os << "Block: item is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "Block: item is invalid\n";
      return false;
    }
  }

  return true;
}

void Block::canonicalize_impl() {
  for (auto item : m_items) {
    if (item) {
      item->canonicalize();
    }
  }
}

void Block::print_impl(std::ostream &os, bool debug) const {
  os << "{\n";

  for (auto item : m_items) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "}";
}

Block *Block::clone_impl() const {
  BlockItems items;
  for (auto item : m_items) {
    if (item) {
      items.push_back(item->clone());
    } else {
      items.push_back(nullptr);
    }
  }

  return Block::get(items);
}

LIB_EXPORT void Block::add_item(Stmt *item) { m_items.push_back(item); }
LIB_EXPORT void Block::clear_items() { m_items.clear(); }
LIB_EXPORT void Block::remove_item(Stmt *item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

bool VolStmt::verify_impl(std::ostream &os) const {
  if (!m_stmt) {
    os << "VolStmt: stmt is NULL\n";
    return false;
  }

  if (!m_stmt->verify(os)) {
    os << "VolStmt: stmt is invalid\n";
    return false;
  }

  return true;
}

void VolStmt::canonicalize_impl() {
  if (m_stmt) {
    m_stmt->canonicalize();
  }
}

void VolStmt::print_impl(std::ostream &os, bool debug) const {
  os << "volatile ";
  if (m_stmt) {
    m_stmt->print(os, debug);
  } else {
    os << "?";
  }
}

VolStmt *VolStmt::clone_impl() const {
  Stmt *stmt = m_stmt ? m_stmt->clone() : nullptr;
  return VolStmt::get(stmt);
}

bool ConstDecl::verify_impl(std::ostream &os) const {
  if (!m_value) {
    os << "ConstDecl: value is NULL\n";
    return false;
  }

  if (!m_type) {
    os << "ConstDecl: type is NULL\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "ConstDecl: value is invalid\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "ConstDecl: type is invalid\n";
    return false;
  }

  return true;
}

void ConstDecl::canonicalize_impl() {
  if (m_value) {
    m_value->canonicalize();
  }
}

void ConstDecl::print_impl(std::ostream &os, bool debug) const {
  os << "const " << m_name;

  if (m_type) {
    os << ": ";
    m_type->print(os, debug);
  }

  if (m_value) {
    os << " = ";
    m_value->print(os, debug);
  }

  os << ";";
}

ConstDecl *ConstDecl::clone_impl() const {
  Expr *value = m_value ? m_value->clone() : nullptr;
  Type *type = m_type ? m_type->clone() : nullptr;
  return ConstDecl::get(m_name, type, value);
}

bool VarDecl::verify_impl(std::ostream &os) const {
  if (!m_value) {
    os << "VarDecl: value is NULL\n";
    return false;
  }

  if (!m_type) {
    os << "VarDecl: type is NULL\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "VarDecl: value is invalid\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "VarDecl: type is invalid\n";
    return false;
  }

  return true;
}

void VarDecl::canonicalize_impl() {
  if (m_value) {
    m_value->canonicalize();
  }
}

void VarDecl::print_impl(std::ostream &os, bool debug) const {
  os << "var " << m_name;

  if (m_type) {
    os << ": ";
    m_type->print(os, debug);
  }

  if (m_value) {
    os << " = ";
    m_value->print(os, debug);
  }

  os << ";";
}

VarDecl *VarDecl::clone_impl() const {
  Expr *value = m_value ? m_value->clone() : nullptr;
  Type *type = m_type ? m_type->clone() : nullptr;
  return VarDecl::get(m_name, type, value);
}

bool LetDecl::verify_impl(std::ostream &os) const {
  if (!m_value) {
    os << "LetDecl: value is NULL\n";
    return false;
  }

  if (!m_type) {
    os << "LetDecl: type is NULL\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "LetDecl: value is invalid\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "LetDecl: type is invalid\n";
    return false;
  }

  return true;
}

void LetDecl::canonicalize_impl() {
  if (m_value) {
    m_value->canonicalize();
  }
}

void LetDecl::print_impl(std::ostream &os, bool debug) const {
  os << "let " << m_name;

  if (m_type) {
    os << ": ";
    m_type->print(os, debug);
  }

  if (m_value) {
    os << " = ";
    m_value->print(os, debug);
  }

  os << ";";
}

LetDecl *LetDecl::clone_impl() const {
  Expr *value = m_value ? m_value->clone() : nullptr;
  Type *type = m_type ? m_type->clone() : nullptr;
  return LetDecl::get(m_name, type, value);
}

bool InlineAsm::verify_impl(std::ostream &os) const {
  for (auto item : m_args) {
    if (!item) {
      os << "InlineAsm: item is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "InlineAsm: item is invalid\n";
      return false;
    }
  }

  return true;
}

void InlineAsm::canonicalize_impl() {
  for (auto item : m_args) {
    if (item) {
      item->canonicalize();
    }
  }
}

void InlineAsm::print_impl(std::ostream &os, bool debug) const {
  os << "asm(\"" << m_code << "\"";

  for (auto item : m_args) {
    os << ", ";
    item->print(os, debug);
  }

  os << ");";
}

InlineAsm *InlineAsm::clone_impl() const {
  InlineAsmArgs args;
  for (auto item : m_args) {
    if (item) {
      args.push_back(item->clone());
    } else {
      args.push_back(nullptr);
    }
  }

  return InlineAsm::get(m_code, args);
}

LIB_EXPORT void InlineAsm::add_arg(Expr *arg) { m_args.push_back(arg); }
LIB_EXPORT void InlineAsm::clear_args() { m_args.clear(); }
LIB_EXPORT void InlineAsm::remove_arg(Expr *arg) {
  std::erase_if(m_args, [arg](auto &field) { return field == arg; });
}

bool IfStmt::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "IfStmt: cond is NULL\n";
    return false;
  }

  if (!m_then) {
    os << "IfStmt: then is NULL\n";
    return false;
  }

  if (!m_else) {
    os << "IfStmt: else is NULL\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "IfStmt: cond is invalid\n";
    return false;
  }

  if (!m_then->verify(os)) {
    os << "IfStmt: then is invalid\n";
    return false;
  }

  if (!m_else->verify(os)) {
    os << "IfStmt: else is invalid\n";
    return false;
  }

  return true;
}

void IfStmt::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }

  if (m_then) {
    m_then->canonicalize();
  }

  if (m_else) {
    m_else->canonicalize();
  }
}

void IfStmt::print_impl(std::ostream &os, bool debug) const {
  os << "if (";
  m_cond->print(os, debug);
  os << ") ";

  if (m_then) {
    m_then->print(os, debug);
  } else {
    os << "?";
  }

  os << " else ";

  if (m_else) {
    m_else->print(os, debug);
  } else {
    os << "?";
  }
}

IfStmt *IfStmt::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Stmt *then = m_then ? m_then->clone() : nullptr;
  Stmt *els = m_else ? m_else->clone() : nullptr;

  return IfStmt::get(cond, then, els);
}

bool WhileStmt::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "WhileStmt: cond is NULL\n";
    return false;
  }

  if (!m_body) {
    os << "WhileStmt: body is NULL\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "WhileStmt: cond is invalid\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "WhileStmt: body is invalid\n";
    return false;
  }

  return true;
}

void WhileStmt::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }

  if (m_body) {
    m_body->canonicalize();
  }
}

void WhileStmt::print_impl(std::ostream &os, bool debug) const {
  os << "while (";
  m_cond->print(os, debug);
  os << ") ";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }
}

WhileStmt *WhileStmt::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Stmt *body = m_body ? m_body->clone() : nullptr;

  return WhileStmt::get(cond, body);
}

bool ForStmt::verify_impl(std::ostream &os) const {
  if (!m_init) {
    os << "ForStmt: init is NULL\n";
    return false;
  }

  if (!m_cond) {
    os << "ForStmt: cond is NULL\n";
    return false;
  }

  if (!m_step) {
    os << "ForStmt: incr is NULL\n";
    return false;
  }

  if (!m_body) {
    os << "ForStmt: body is NULL\n";
    return false;
  }

  if (!m_init->verify(os)) {
    os << "ForStmt: init is invalid\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "ForStmt: cond is invalid\n";
    return false;
  }

  if (!m_step->verify(os)) {
    os << "ForStmt: incr is invalid\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "ForStmt: body is invalid\n";
    return false;
  }

  return true;
}

void ForStmt::canonicalize_impl() {
  if (m_init) {
    m_init->canonicalize();
  }

  if (m_cond) {
    m_cond->canonicalize();
  }

  if (m_step) {
    m_step->canonicalize();
  }

  if (m_body) {
    m_body->canonicalize();
  }
}

void ForStmt::print_impl(std::ostream &os, bool debug) const {
  os << "for (";

  if (m_init) {
    m_init->print(os, debug);
  } else {
    os << "?";
  }

  os << "; ";

  if (m_cond) {
    m_cond->print(os, debug);
  } else {
    os << "?";
  }

  os << "; ";

  if (m_step) {
    m_step->print(os, debug);
  } else {
    os << "?";
  }

  os << ") ";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }
}

ForStmt *ForStmt::clone_impl() const {
  Expr *init = m_init ? m_init->clone() : nullptr;
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Expr *step = m_step ? m_step->clone() : nullptr;
  Block *body = m_body ? m_body->clone() : nullptr;

  return ForStmt::get(init, cond, step, body);
}

bool FormStmt::verify_impl(std::ostream &os) const {
  if (!m_expr) {
    os << "FormStmt: expr is NULL\n";
    return false;
  }

  if (!m_maxjobs) {
    os << "FormStmt: maxjobs is NULL\n";
    return false;
  }

  if (!m_body) {
    os << "FormStmt: body is NULL\n";
    return false;
  }

  if (!m_expr->verify(os)) {
    os << "FormStmt: expr is invalid\n";
    return false;
  }

  if (!m_maxjobs->verify(os)) {
    os << "FormStmt: maxjobs is invalid\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "FormStmt: body is invalid\n";
    return false;
  }

  return true;
}

void FormStmt::canonicalize_impl() {
  if (m_expr) {
    m_expr->canonicalize();
  }

  if (m_maxjobs) {
    m_maxjobs->canonicalize();
  }

  if (m_body) {
    m_body->canonicalize();
  }
}

void FormStmt::print_impl(std::ostream &os, bool debug) const {
  os << "form (";
  if (m_maxjobs) {
    m_maxjobs->print(os, debug);
  } else {
    os << "?";
  }
  os << ") (" << m_idx_ident << ", " << m_val_ident << " in ";

  if (m_expr) {
    m_expr->print(os, debug);
  } else {
    os << "?";
  }

  os << ")";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }
}

FormStmt *FormStmt::clone_impl() const {
  Expr *expr = m_expr ? m_expr->clone() : nullptr;
  Expr *maxjobs = m_maxjobs ? m_maxjobs->clone() : nullptr;
  Stmt *body = m_body ? m_body->clone() : nullptr;

  return FormStmt::get(m_idx_ident, m_val_ident, expr, maxjobs, body);
}

bool ForeachStmt::verify_impl(std::ostream &os) const {
  if (!m_expr) {
    os << "ForeachStmt: expr is NULL\n";
    return false;
  }

  if (!m_body) {
    os << "ForeachStmt: body is NULL\n";
    return false;
  }

  if (!m_expr->verify(os)) {
    os << "ForeachStmt: expr is invalid\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "ForeachStmt: body is invalid\n";
    return false;
  }

  return true;
}

void ForeachStmt::canonicalize_impl() {
  if (m_expr) {
    m_expr->canonicalize();
  }

  if (m_body) {
    m_body->canonicalize();
  }
}

void ForeachStmt::print_impl(std::ostream &os, bool debug) const {
  os << "foreach (" << m_idx_ident << ", " << m_val_ident << " in ";

  if (m_expr) {
    m_expr->print(os, debug);
  } else {
    os << "?";
  }

  os << ")";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }
}

ForeachStmt *ForeachStmt::clone_impl() const {
  Expr *expr = m_expr ? m_expr->clone() : nullptr;
  Stmt *body = m_body ? m_body->clone() : nullptr;

  return ForeachStmt::get(m_idx_ident, m_val_ident, expr, body);
}

bool BreakStmt::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}
void BreakStmt::canonicalize_impl() {}
void BreakStmt::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "break;";
}
BreakStmt *BreakStmt::clone_impl() const { return BreakStmt::get(); }

bool ContinueStmt::verify_impl(std::ostream &os) const {
  (void)os;
  return true;
}
void ContinueStmt::canonicalize_impl() {}
void ContinueStmt::print_impl(std::ostream &os, bool debug) const {
  (void)debug;
  os << "continue;";
}
ContinueStmt *ContinueStmt::clone_impl() const { return ContinueStmt::get(); }

bool ReturnStmt::verify_impl(std::ostream &os) const {
  if (!m_value) {
    os << "ReturnStmt: value is NULL\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "ReturnStmt: value is invalid\n";
    return false;
  }

  return true;
}

void ReturnStmt::canonicalize_impl() {
  if (m_value) {
    m_value->canonicalize();
  }
}

void ReturnStmt::print_impl(std::ostream &os, bool debug) const {
  os << "return ";

  if (m_value) {
    m_value->print(os, debug);
  } else {
    os << "?";
  }

  os << ";";
}

ReturnStmt *ReturnStmt::clone_impl() const {
  Expr *value = m_value ? m_value->clone() : nullptr;
  return ReturnStmt::get(value);
}

bool ReturnIfStmt::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "ReturnIfStmt: cond is NULL\n";
    return false;
  }

  if (!m_value) {
    os << "ReturnIfStmt: value is NULL\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "ReturnIfStmt: cond is invalid\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "ReturnIfStmt: value is invalid\n";
    return false;
  }

  return true;
}

void ReturnIfStmt::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }

  if (m_value) {
    m_value->canonicalize();
  }
}

void ReturnIfStmt::print_impl(std::ostream &os, bool debug) const {
  os << "retif (";

  if (m_cond) {
    m_cond->print(os, debug);
  } else {
    os << "?";
  }

  os << ") ";

  if (m_value) {
    m_value->print(os, debug);
  } else {
    os << "?";
  }

  os << ";";
}

ReturnIfStmt *ReturnIfStmt::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Expr *value = m_value ? m_value->clone() : nullptr;

  return ReturnIfStmt::get(cond, value);
}

bool RetZStmt::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "RetZStmt: cond is NULL\n";
    return false;
  }

  if (!m_value) {
    os << "RetZStmt: value is NULL\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "RetZStmt: cond is invalid\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "RetZStmt: value is invalid\n";
    return false;
  }

  return true;
}

void RetZStmt::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }

  if (m_value) {
    m_value->canonicalize();
  }
}

void RetZStmt::print_impl(std::ostream &os, bool debug) const {
  os << "retz (";

  if (m_cond) {
    m_cond->print(os, debug);
  } else {
    os << "?";
  }

  os << ") ";

  if (m_value) {
    m_value->print(os, debug);
  } else {
    os << "?";
  }

  os << ";";
}

RetZStmt *RetZStmt::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Expr *value = m_value ? m_value->clone() : nullptr;

  return RetZStmt::get(cond, value);
}

bool RetVStmt::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "RetVStmt: cond is NULL\n";
    return false;
  }

  return true;
}

void RetVStmt::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }
}

void RetVStmt::print_impl(std::ostream &os, bool debug) const {
  os << "retv (";

  if (m_cond) {
    m_cond->print(os, debug);
  } else {
    os << "?";
  }

  os << ")";
}

RetVStmt *RetVStmt::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;

  return RetVStmt::get(cond);
}

bool CaseStmt::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "CaseStmt: cond is NULL\n";
    return false;
  }

  if (!m_body) {
    os << "CaseStmt: body is NULL\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "CaseStmt: cond is invalid\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "CaseStmt: body is invalid\n";
    return false;
  }

  return true;
}

void CaseStmt::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }

  if (m_body) {
    m_body->canonicalize();
  }
}

void CaseStmt::print_impl(std::ostream &os, bool debug) const {
  os << "case ";

  if (m_cond) {
    m_cond->print(os, debug);
  } else {
    os << "?";
  }

  os << ":\n";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }
}

CaseStmt *CaseStmt::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Stmt *body = m_body ? m_body->clone() : nullptr;

  return CaseStmt::get(cond, body);
}

bool SwitchStmt::verify_impl(std::ostream &os) const {
  if (!m_cond) {
    os << "SwitchStmt: cond is NULL\n";
    return false;
  }

  if (!m_cond->verify(os)) {
    os << "SwitchStmt: cond is invalid\n";
    return false;
  }

  for (auto item : m_cases) {
    if (!item) {
      os << "SwitchStmt: case is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "SwitchStmt: case is invalid\n";
      return false;
    }
  }

  return true;
}

void SwitchStmt::canonicalize_impl() {
  if (m_cond) {
    m_cond->canonicalize();
  }

  for (auto item : m_cases) {
    if (item) {
      item->canonicalize();
    }
  }
}

void SwitchStmt::print_impl(std::ostream &os, bool debug) const {
  os << "switch (";

  if (m_cond) {
    m_cond->print(os, debug);
  } else {
    os << "?";
  }

  os << ") {\n";

  for (auto item : m_cases) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "}";
}

SwitchStmt *SwitchStmt::clone_impl() const {
  Expr *cond = m_cond ? m_cond->clone() : nullptr;
  Stmt *_default = m_default ? m_default->clone() : nullptr;

  SwitchCases cases;
  for (auto item : m_cases) {
    if (item) {
      cases.push_back(item->clone());
    } else {
      cases.push_back(nullptr);
    }
  }

  return SwitchStmt::get(cond, m_cases, _default);
}

LIB_EXPORT void SwitchStmt::add_case(CaseStmt *item) { m_cases.push_back(item); }
LIB_EXPORT void SwitchStmt::clear_cases() { m_cases.clear(); }
LIB_EXPORT void SwitchStmt::remove_case(CaseStmt *item) {
  std::erase_if(m_cases, [item](auto &field) { return field == item; });
}

bool TypedefDecl::verify_impl(std::ostream &os) const {
  if (!m_type) {
    os << "TypedefDecl: type is NULL\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "TypedefDecl: type is invalid\n";
    return false;
  }

  return true;
}

void TypedefDecl::canonicalize_impl() {
  if (m_type) {
    m_type->canonicalize();
  }
}

void TypedefDecl::print_impl(std::ostream &os, bool debug) const {
  os << "typedef ";

  if (m_type) {
    m_type->print(os, debug);
  } else {
    os << "?";
  }

  os << " " << m_name << ";";
}

TypedefDecl *TypedefDecl::clone_impl() const {
  Type *type = m_type ? m_type->clone() : nullptr;
  return TypedefDecl::get(m_name, type);
}

bool FnDecl::verify_impl(std::ostream &os) const {
  if (!m_type) {
    os << "FnDecl: type is NULL\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "FnDecl: type is invalid\n";
    return false;
  }

  return true;
}

void FnDecl::canonicalize_impl() {
  if (m_type) {
    m_type->canonicalize();
  }
}

void FnDecl::print_impl(std::ostream &os, bool debug) const {
  os << "fn " << m_name << "(";

  if (m_type) {
    m_type->print(os, debug);
  } else {
    os << "?";
  }

  os << ")";
}

FnDecl *FnDecl::clone_impl() const {
  if (m_type) {
    return FnDecl::get(m_name, m_type->clone()->as<FuncTy>());
  } else {
    return FnDecl::get(m_name, nullptr);
  }
}

bool FnDef::verify_impl(std::ostream &os) const {
  if (!m_type) {
    os << "FnDef: type is NULL\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "FnDef: type is invalid\n";
    return false;
  }

  if (!m_body) {
    os << "FnDef: body is NULL\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "FnDef: body is invalid\n";
    return false;
  }

  return true;
}

void FnDef::canonicalize_impl() {
  if (m_type) {
    m_type->canonicalize();
  }

  if (m_body) {
    m_body->canonicalize();
  }

  if (m_precond) {
    m_precond->canonicalize();
  }

  if (m_postcond) {
    m_postcond->canonicalize();
  }
}

void FnDef::print_impl(std::ostream &os, bool debug) const {
  os << "fn ";

  if (!m_captures.empty()) {
    os << "[";
    for (auto it = m_captures.begin(); it != m_captures.end(); ++it) {
      if (it->second) {
        os << "&";
      }
      os << it->first;

      if (std::next(it) != m_captures.end()) {
        os << ", ";
      }
    }
    os << "] ";
  }

  os << m_name << "(";

  if (m_type) {
    m_type->print(os, debug);
  } else {
    os << "?";
  }

  os << ") ";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }
}

FnDef *FnDef::clone_impl() const {
  Stmt *body = m_body ? m_body->clone() : nullptr;
  FnDecl *decl = FnDecl::clone_impl();
  Expr *precond = m_precond ? m_precond->clone() : nullptr;
  Expr *postcond = m_postcond ? m_postcond->clone() : nullptr;

  return FnDef::get(decl, body, precond, postcond, m_captures);
}

bool CompositeField::verify_impl(std::ostream &os) const {
  if (!m_type) {
    os << "CompositeField: type is NULL\n";
    return false;
  }

  if (!m_type->verify(os)) {
    os << "CompositeField: type is invalid\n";
    return false;
  }

  if (!m_value) {
    os << "CompositeField: value is NULL\n";
    return false;
  }

  if (!m_value->verify(os)) {
    os << "CompositeField: value is invalid\n";
    return false;
  }

  return true;
}

void CompositeField::canonicalize_impl() {
  if (m_type) {
    m_type->canonicalize();
  }

  if (m_value) {
    m_value->canonicalize();
  }
}

void CompositeField::print_impl(std::ostream &os, bool debug) const {
  os << m_name;

  if (m_type) {
    os << ": ";
    m_type->print(os, debug);
  }

  if (m_value) {
    os << " = ";
    m_value->print(os, debug);
  }
}

CompositeField *CompositeField::clone_impl() const {
  Type *type = m_type ? m_type->clone() : nullptr;
  Expr *value = m_value ? m_value->clone() : nullptr;

  return CompositeField::get(m_name, type, value);
}

bool StructDef::verify_impl(std::ostream &os) const {
  for (auto item : m_methods) {
    if (!item) {
      os << "StructDef: method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "StructDef: method is invalid\n";
      return false;
    }
  }

  for (auto item : m_static_methods) {
    if (!item) {
      os << "StructDef: static method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "StructDef: static method is invalid\n";
      return false;
    }
  }

  for (auto item : m_fields) {
    if (!item) {
      os << "StructDef: field is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "StructDef: field is invalid\n";
      return false;
    }
  }

  return true;
}

void StructDef::canonicalize_impl() {
  for (auto item : m_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_static_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_fields) {
    if (item) {
      item->canonicalize();
    }
  }
}

void StructDef::print_impl(std::ostream &os, bool debug) const {
  os << "struct " << m_name << " {\n";

  for (auto item : m_fields) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_static_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "}";
}

StructDef *StructDef::clone_impl() const {
  auto type = m_type ? m_type->clone() : nullptr;

  StructDefFields fields;
  for (auto item : m_fields) {
    if (item) {
      fields.push_back(item->clone());
    } else {
      fields.push_back(nullptr);
    }
  }

  StructDefMethods methods;
  for (auto item : m_methods) {
    if (item) {
      methods.push_back(item->clone());
    } else {
      methods.push_back(nullptr);
    }
  }

  StructDefStaticMethods static_methods;
  for (auto item : m_static_methods) {
    if (item) {
      static_methods.push_back(item->clone());
    } else {
      static_methods.push_back(nullptr);
    }
  }

  return StructDef::get(m_name, static_cast<StructTy *>(type), fields, methods, static_methods);
}

LIB_EXPORT void StructDef::add_method(FnDecl *item) { m_methods.push_back(item); }
LIB_EXPORT void StructDef::add_methods(std::initializer_list<FnDecl *> items) {
  m_methods.insert(m_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void StructDef::clear_methods() { m_methods.clear(); }
LIB_EXPORT void StructDef::remove_method(FnDecl *item) {
  std::erase_if(m_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void StructDef::add_static_method(FnDecl *item) { m_static_methods.push_back(item); }
LIB_EXPORT void StructDef::add_static_methods(std::initializer_list<FnDecl *> items) {
  m_static_methods.insert(m_static_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void StructDef::clear_static_methods() { m_static_methods.clear(); }
LIB_EXPORT void StructDef::remove_static_method(FnDecl *item) {
  std::erase_if(m_static_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void StructDef::add_field(CompositeField *item) { m_fields.push_back(item); }
LIB_EXPORT void StructDef::add_fields(std::initializer_list<CompositeField *> items) {
  m_fields.insert(m_fields.end(), items.begin(), items.end());
}
LIB_EXPORT void StructDef::clear_fields() { m_fields.clear(); }
LIB_EXPORT void StructDef::remove_field(CompositeField *item) {
  std::erase_if(m_fields, [item](auto &field) { return field == item; });
}

bool GroupDef::verify_impl(std::ostream &os) const {
  for (auto item : m_methods) {
    if (!item) {
      os << "GroupDef: method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "GroupDef: method is invalid\n";
      return false;
    }
  }

  for (auto item : m_static_methods) {
    if (!item) {
      os << "GroupDef: static method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "GroupDef: static method is invalid\n";
      return false;
    }
  }

  for (auto item : m_fields) {
    if (!item) {
      os << "GroupDef: field is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "GroupDef: field is invalid\n";
      return false;
    }
  }

  return true;
}

void GroupDef::canonicalize_impl() {
  for (auto item : m_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_static_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_fields) {
    if (item) {
      item->canonicalize();
    }
  }
}

void GroupDef::print_impl(std::ostream &os, bool debug) const {
  os << "group " << m_name << " {\n";

  for (auto item : m_fields) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_static_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "}";
}

GroupDef *GroupDef::clone_impl() const {
  Type *type = m_type ? m_type->clone() : nullptr;

  GroupDefFields fields;
  for (auto item : m_fields) {
    if (item) {
      fields.push_back(item->clone());
    } else {
      fields.push_back(nullptr);
    }
  }

  GroupDefMethods methods;
  for (auto item : m_methods) {
    if (item) {
      methods.push_back(item->clone());
    } else {
      methods.push_back(nullptr);
    }
  }

  GroupDefStaticMethods static_methods;
  for (auto item : m_static_methods) {
    if (item) {
      static_methods.push_back(item->clone());
    } else {
      static_methods.push_back(nullptr);
    }
  }

  return GroupDef::get(m_name, static_cast<GroupTy *>(type), fields, methods, static_methods);
}

LIB_EXPORT void GroupDef::add_method(FnDecl *item) { m_methods.push_back(item); }
LIB_EXPORT void GroupDef::add_methods(std::initializer_list<FnDecl *> items) {
  m_methods.insert(m_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void GroupDef::clear_methods() { m_methods.clear(); }
LIB_EXPORT void GroupDef::remove_method(FnDecl *item) {
  std::erase_if(m_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void GroupDef::add_static_method(FnDecl *item) { m_static_methods.push_back(item); }
LIB_EXPORT void GroupDef::add_static_methods(std::initializer_list<FnDecl *> items) {
  m_static_methods.insert(m_static_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void GroupDef::clear_static_methods() { m_static_methods.clear(); }
LIB_EXPORT void GroupDef::remove_static_method(FnDecl *item) {
  std::erase_if(m_static_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void GroupDef::add_field(CompositeField *item) { m_fields.push_back(item); }
LIB_EXPORT void GroupDef::add_fields(std::initializer_list<CompositeField *> items) {
  m_fields.insert(m_fields.end(), items.begin(), items.end());
}
LIB_EXPORT void GroupDef::clear_fields() { m_fields.clear(); }
LIB_EXPORT void GroupDef::remove_field(CompositeField *item) {
  std::erase_if(m_fields, [item](auto &field) { return field == item; });
}

bool RegionDef::verify_impl(std::ostream &os) const {
  for (auto item : m_methods) {
    if (!item) {
      os << "RegionDef: method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "RegionDef: method is invalid\n";
      return false;
    }
  }

  for (auto item : m_static_methods) {
    if (!item) {
      os << "RegionDef: static method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "RegionDef: static method is invalid\n";
      return false;
    }
  }

  for (auto item : m_fields) {
    if (!item) {
      os << "RegionDef: field is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "RegionDef: field is invalid\n";
      return false;
    }
  }

  return true;
}

void RegionDef::canonicalize_impl() {
  for (auto item : m_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_static_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_fields) {
    if (item) {
      item->canonicalize();
    }
  }
}

void RegionDef::print_impl(std::ostream &os, bool debug) const {
  os << "region " << m_name << " {\n";

  for (auto item : m_fields) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_static_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "}";
}

RegionDef *RegionDef::clone_impl() const {
  Type *type = m_type ? m_type->clone() : nullptr;

  RegionDefFields fields;
  for (auto item : m_fields) {
    if (item) {
      fields.push_back(item->clone());
    } else {
      fields.push_back(nullptr);
    }
  }

  RegionDefMethods methods;
  for (auto item : m_methods) {
    if (item) {
      methods.push_back(item->clone());
    } else {
      methods.push_back(nullptr);
    }
  }

  RegionDefStaticMethods static_methods;
  for (auto item : m_static_methods) {
    if (item) {
      static_methods.push_back(item->clone());
    } else {
      static_methods.push_back(nullptr);
    }
  }

  return RegionDef::get(m_name, static_cast<RegionTy *>(type), fields, methods, static_methods);
}

LIB_EXPORT void RegionDef::add_method(FnDecl *item) { m_methods.push_back(item); }
LIB_EXPORT void RegionDef::add_methods(std::initializer_list<FnDecl *> items) {
  m_methods.insert(m_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void RegionDef::clear_methods() { m_methods.clear(); }
LIB_EXPORT void RegionDef::remove_method(FnDecl *item) {
  std::erase_if(m_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void RegionDef::add_static_method(FnDecl *item) { m_static_methods.push_back(item); }
LIB_EXPORT void RegionDef::add_static_methods(std::initializer_list<FnDecl *> items) {
  m_static_methods.insert(m_static_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void RegionDef::clear_static_methods() { m_static_methods.clear(); }
LIB_EXPORT void RegionDef::remove_static_method(FnDecl *item) {
  std::erase_if(m_static_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void RegionDef::add_field(CompositeField *item) { m_fields.push_back(item); }
LIB_EXPORT void RegionDef::add_fields(std::initializer_list<CompositeField *> items) {
  m_fields.insert(m_fields.end(), items.begin(), items.end());
}
LIB_EXPORT void RegionDef::clear_fields() { m_fields.clear(); }
LIB_EXPORT void RegionDef::remove_field(CompositeField *item) {
  std::erase_if(m_fields, [item](auto &field) { return field == item; });
}

bool UnionDef::verify_impl(std::ostream &os) const {
  for (auto item : m_methods) {
    if (!item) {
      os << "UnionDef: method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "UnionDef: method is invalid\n";
      return false;
    }
  }

  for (auto item : m_static_methods) {
    if (!item) {
      os << "UnionDef: static method is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "UnionDef: static method is invalid\n";
      return false;
    }
  }

  for (auto item : m_fields) {
    if (!item) {
      os << "UnionDef: field is NULL\n";
      return false;
    }

    if (!item->verify(os)) {
      os << "UnionDef: field is invalid\n";
      return false;
    }
  }

  return true;
}

void UnionDef::canonicalize_impl() {
  for (auto item : m_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_static_methods) {
    if (item) {
      item->canonicalize();
    }
  }

  for (auto item : m_fields) {
    if (item) {
      item->canonicalize();
    }
  }
}

void UnionDef::print_impl(std::ostream &os, bool debug) const {
  os << "union " << m_name << " {\n";

  for (auto item : m_fields) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "\n";

  for (auto item : m_static_methods) {
    if (item) {
      item->print(os, debug);
    } else {
      os << "?";
    }

    os << "\n";
  }

  os << "}";
}

UnionDef *UnionDef::clone_impl() const {
  Type *type = m_type ? m_type->clone() : nullptr;

  UnionDefFields fields;
  for (auto item : m_fields) {
    if (item) {
      fields.push_back(item->clone());
    } else {
      fields.push_back(nullptr);
    }
  }

  UnionDefMethods methods;
  for (auto item : m_methods) {
    if (item) {
      methods.push_back(item->clone());
    } else {
      methods.push_back(nullptr);
    }
  }

  UnionDefStaticMethods static_methods;
  for (auto item : m_static_methods) {
    if (item) {
      static_methods.push_back(item->clone());
    } else {
      static_methods.push_back(nullptr);
    }
  }

  return UnionDef::get(m_name, static_cast<UnionTy *>(type), fields, methods, static_methods);
}

LIB_EXPORT void UnionDef::add_method(FnDecl *item) { m_methods.push_back(item); }
LIB_EXPORT void UnionDef::add_methods(std::initializer_list<FnDecl *> items) {
  m_methods.insert(m_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void UnionDef::clear_methods() { m_methods.clear(); }
LIB_EXPORT void UnionDef::remove_method(FnDecl *item) {
  std::erase_if(m_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void UnionDef::add_static_method(FnDecl *item) { m_static_methods.push_back(item); }
LIB_EXPORT void UnionDef::add_static_methods(std::initializer_list<FnDecl *> items) {
  m_static_methods.insert(m_static_methods.end(), items.begin(), items.end());
}
LIB_EXPORT void UnionDef::clear_static_methods() { m_static_methods.clear(); }
LIB_EXPORT void UnionDef::remove_static_method(FnDecl *item) {
  std::erase_if(m_static_methods, [item](auto &field) { return field == item; });
}

LIB_EXPORT void UnionDef::add_field(CompositeField *item) { m_fields.push_back(item); }
LIB_EXPORT void UnionDef::add_fields(std::initializer_list<CompositeField *> items) {
  m_fields.insert(m_fields.end(), items.begin(), items.end());
}
LIB_EXPORT void UnionDef::clear_fields() { m_fields.clear(); }
LIB_EXPORT void UnionDef::remove_field(CompositeField *item) {
  std::erase_if(m_fields, [item](auto &field) { return field == item; });
}

bool EnumDef::verify_impl(std::ostream &os) const {
  for (auto item : m_items) {
    if (!item.second) {
      os << "EnumDef: item is NULL\n";
      return false;
    }

    if (!item.second->verify(os)) {
      os << "EnumDef: item is invalid\n";
      return false;
    }
  }

  return true;
}

void EnumDef::canonicalize_impl() {
  for (auto item : m_items) {
    if (item.second) {
      item.second->canonicalize();
    }
  }
}

void EnumDef::print_impl(std::ostream &os, bool debug) const {
  os << "enum " << m_name << " {\n";

  for (auto item : m_items) {
    os << item.first;

    if (item.second) {
      os << " = ";
      item.second->print(os, debug);
    }

    os << ",\n";
  }

  os << "}";
}

EnumDef *EnumDef::clone_impl() const {
  Type *type = m_type ? m_type->clone() : nullptr;

  EnumDefItems items;
  for (auto item : m_items) {
    if (item.second) {
      items.push_back({item.first, item.second->clone()});
    } else {
      items.push_back({item.first, nullptr});
    }
  }

  return EnumDef::get(m_name, type, items);
}

LIB_EXPORT void EnumDef::add_item(EnumItem item) { m_items.push_back(item); }
LIB_EXPORT void EnumDef::add_items(std::initializer_list<EnumItem> items) {
  m_items.insert(m_items.end(), items.begin(), items.end());
}
LIB_EXPORT void EnumDef::clear_items() { m_items.clear(); }
LIB_EXPORT void EnumDef::remove_item(EnumItem item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

bool SubsystemDecl::verify_impl(std::ostream &os) const {
  if (m_type) {
    os << "SubsystemDecl: type must be NULL\n";
    return false;
  }

  if (!m_body) {
    os << "SubsystemDecl: body is NULL\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "SubsystemDecl: body is invalid\n";
    return false;
  }

  return true;
}

void SubsystemDecl::canonicalize_impl() {
  if (m_body) {
    m_body->canonicalize();
  }
}

void SubsystemDecl::print_impl(std::ostream &os, bool debug) const {
  os << "subsystem " << m_name << " {\n";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }

  os << "}";
}

SubsystemDecl *SubsystemDecl::clone_impl() const {
  Block *body = m_body ? m_body->clone() : nullptr;

  return SubsystemDecl::get(m_name, body, m_deps);
}

LIB_EXPORT void SubsystemDecl::add_dep(qparse::String dep) { m_deps.insert(dep); }
LIB_EXPORT void qparse::SubsystemDecl::add_deps(const qparse::SubsystemDeps &deps) {
  m_deps.insert(deps.begin(), deps.end());
}
LIB_EXPORT void SubsystemDecl::clear_deps() { m_deps.clear(); }
LIB_EXPORT void SubsystemDecl::remove_dep(String dep) { m_deps.erase(dep); }

bool ExportDecl::verify_impl(std::ostream &os) const {
  if (m_type) {
    os << "ExportDecl: type must be NULL\n";
    return false;
  }

  if (!m_body) {
    os << "ExportDecl: body is NULL\n";
    return false;
  }

  if (!m_body->verify(os)) {
    os << "ExportDecl: body is invalid\n";
    return false;
  }

  return true;
}

void ExportDecl::canonicalize_impl() {
  if (m_body) {
    m_body->canonicalize();
  }
}

void ExportDecl::print_impl(std::ostream &os, bool debug) const {
  os << "export " << m_name << " {\n";

  if (m_body) {
    m_body->print(os, debug);
  } else {
    os << "?";
  }

  os << "}";
}

ExportDecl *ExportDecl::clone_impl() const {
  Block *body = m_body ? m_body->clone() : nullptr;
  return ExportDecl::get(body, m_abi_name);
}

///=============================================================================

LIB_EXPORT qparse_node_t *qparse_alloc(qparse_ty_t type, qcore_arena_t *arena) {
  if (!arena) {
    arena = &qparse_arena.get();
  }

  Node *node = nullptr;

  qparse_arena.swap(*arena);

  switch (type) {
    case QAST_NODE_STMT:
      qcore_panic("qparse_alloc(): QAST_NODE_STMT is not valid here");
    case QAST_NODE_TYPE:
      qcore_panic("qparse_alloc(): QAST_NODE_TYPE is not valid here");
    case QAST_NODE_DECL:
      qcore_panic("qparse_alloc(): QAST_NODE_DECL is not valid here");
    case QAST_NODE_EXPR:
      qcore_panic("qparse_alloc(): QAST_NODE_EXPR is not valid here");
    case QAST_NODE_CEXPR:
      node = ConstExpr::get();
      break;
    case QAST_NODE_UNRES_TY:
      node = UnresolvedType::get();
      break;
    case QAST_NODE_INFER_TY:
      node = InferType::get();
      break;
    case QAST_NODE_TEMPL_TY:
      node = TemplType::get();
      break;
    case QAST_NODE_U1_TY:
      node = U1::get();
      break;
    case QAST_NODE_U8_TY:
      node = U8::get();
      break;
    case QAST_NODE_U16_TY:
      node = U16::get();
      break;
    case QAST_NODE_U32_TY:
      node = U32::get();
      break;
    case QAST_NODE_U64_TY:
      node = U64::get();
      break;
    case QAST_NODE_U128_TY:
      node = U128::get();
      break;
    case QAST_NODE_I8_TY:
      node = I8::get();
      break;
    case QAST_NODE_I16_TY:
      node = I16::get();
      break;
    case QAST_NODE_I32_TY:
      node = I32::get();
      break;
    case QAST_NODE_I64_TY:
      node = I64::get();
      break;
    case QAST_NODE_I128_TY:
      node = I128::get();
      break;
    case QAST_NODE_F16_TY:
      node = F16::get();
      break;
    case QAST_NODE_F32_TY:
      node = F32::get();
      break;
    case QAST_NODE_F64_TY:
      node = F64::get();
      break;
    case QAST_NODE_F128_TY:
      node = F128::get();
      break;
    case QAST_NODE_VOID_TY:
      node = VoidTy::get();
      break;
    case QAST_NODE_PTR_TY:
      node = PtrTy::get();
      break;
    case QAST_NODE_OPAQUE_TY:
      node = OpaqueTy::get();
      break;
    case QAST_NODE_TUPLE_TY:
      node = TupleTy::get();
      break;
    case QAST_NODE_ARRAY_TY:
      node = ArrayTy::get();
      break;
    case QAST_NODE_ENUM_TY:
      node = EnumTy::get();
      break;
    case QAST_NODE_REF_TY:
      node = RefTy::get();
      break;
    case QAST_NODE_STRUCT_TY:
      node = StructTy::get();
      break;
    case QAST_NODE_GROUP_TY:
      node = GroupTy::get();
      break;
    case QAST_NODE_REGION_TY:
      node = RegionTy::get();
      break;
    case QAST_NODE_UNION_TY:
      node = UnionTy::get();
      break;
    case QAST_NODE_FN_TY:
      node = FuncTy::get();
      break;
    case QAST_NODE_UNEXPR:
      node = UnaryExpr::get();
      break;
    case QAST_NODE_BINEXPR:
      node = BinExpr::get();
      break;
    case QAST_NODE_POST_UNEXPR:
      node = PostUnaryExpr::get();
      break;
    case QAST_NODE_TEREXPR:
      node = TernaryExpr::get();
      break;
    case QAST_NODE_INT:
      node = ConstInt::get();
      break;
    case QAST_NODE_FLOAT:
      node = ConstFloat::get();
      break;
    case QAST_NODE_BOOL:
      node = ConstBool::get();
      break;
    case QAST_NODE_STRING:
      node = ConstString::get();
      break;
    case QAST_NODE_CHAR:
      node = ConstChar::get();
      break;
    case QAST_NODE_NULL:
      node = ConstNull::get();
      break;
    case QAST_NODE_UNDEF:
      node = ConstUndef::get();
      break;
    case QAST_NODE_CALL:
      node = Call::get();
      break;
    case QAST_NODE_LIST:
      node = List::get();
      break;
    case QAST_NODE_ASSOC:
      node = Assoc::get();
      break;
    case QAST_NODE_FIELD:
      node = Field::get();
      break;
    case QAST_NODE_INDEX:
      node = Index::get();
      break;
    case QAST_NODE_SLICE:
      node = Slice::get();
      break;
    case QAST_NODE_FSTRING:
      node = FString::get();
      break;
    case QAST_NODE_IDENT:
      node = Ident::get();
      break;
    case QAST_NODE_SEQ_POINT:
      node = SeqPoint::get();
      break;
    case QAST_NODE_STMT_EXPR:
      node = StmtExpr::get();
      break;
    case QAST_NODE_TYPE_EXPR:
      node = TypeExpr::get();
      break;
    case QAST_NODE_BLOCK:
      node = Block::get();
      break;
    case QAST_NODE_VOLSTMT:
      node = VolStmt::get();
      break;
    case QAST_NODE_CONST:
      node = ConstDecl::get();
      break;
    case QAST_NODE_VAR:
      node = VarDecl::get();
      break;
    case QAST_NODE_LET:
      node = LetDecl::get();
      break;
    case QAST_NODE_INLINE_ASM:
      node = InlineAsm::get();
      break;
    case QAST_NODE_IF:
      node = IfStmt::get();
      break;
    case QAST_NODE_WHILE:
      node = WhileStmt::get();
      break;
    case QAST_NODE_FOR:
      node = ForStmt::get();
      break;
    case QAST_NODE_FORM:
      node = FormStmt::get();
      break;
    case QAST_NODE_FOREACH:
      node = ForeachStmt::get();
      break;
    case QAST_NODE_BREAK:
      node = BreakStmt::get();
      break;
    case QAST_NODE_CONTINUE:
      node = ContinueStmt::get();
      break;
    case QAST_NODE_RETURN:
      node = ReturnStmt::get();
      break;
    case QAST_NODE_RETIF:
      node = ReturnIfStmt::get();
      break;
    case QAST_NODE_RETZ:
      node = RetZStmt::get();
      break;
    case QAST_NODE_RETV:
      node = RetVStmt::get();
      break;
    case QAST_NODE_CASE:
      node = CaseStmt::get();
      break;
    case QAST_NODE_TEMPL_CALL:
      node = TemplCall::get();
      break;
    case QAST_NODE_SWITCH:
      node = SwitchStmt::get();
      break;
    case QAST_NODE_TYPEDEF:
      node = TypedefDecl::get();
      break;
    case QAST_NODE_FNDECL:
      node = FnDecl::get();
      break;
    case QAST_NODE_FN:
      node = FnDef::get();
      break;
    case QAST_NODE_COMPOSITE_FIELD:
      node = CompositeField::get();
      break;
    case QAST_NODE_STRUCT:
      node = StructDef::get();
      break;
    case QAST_NODE_GROUP:
      node = GroupDef::get();
      break;
    case QAST_NODE_REGION:
      node = RegionDef::get();
      break;
    case QAST_NODE_UNION:
      node = UnionDef::get();
      break;
    case QAST_NODE_ENUM:
      node = EnumDef::get();
      break;
    case QAST_NODE_SUBSYSTEM:
      node = SubsystemDecl::get();
      break;
    case QAST_NODE_EXPORT:
      node = ExportDecl::get();
      break;
    case QAST_NODE_EXPR_STMT:
      node = ExprStmt::get();
      break;
  }

  qparse_arena.swap(*arena);

  return node;
}
