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

#include <core/Macro.h>
#include <qast/Nodes.h>
#include <quixcc/Library.h>
#include <quixcc/interface/SyntaxTreeNodes.h>

#include <cmath>
#include <cstring>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace libquixcc::qast;

///=============================================================================
thread_local libquixcc::qast::ArenaAllocatorImpl libquixcc::qast::g_allocator;

ArenaAllocatorImpl::ArenaAllocatorImpl() { quixcc_arena_open(&m_arena); }

ArenaAllocatorImpl::~ArenaAllocatorImpl() { quixcc_arena_close(&m_arena); }

void *ArenaAllocatorImpl::allocate(std::size_t size) {
  const std::size_t alignment = 16;

  return quixcc_arena_alloc_ex(&m_arena, size, alignment);
}

void ArenaAllocatorImpl::deallocate(void *ptr) noexcept {}

///=============================================================================

uint32_t Node::this_sizeof() const {
  quixcc_panic("Node::this_sizeof() is not implemented");

#define SIZEOF_ROW(__type) \
  { typeid(__type).hash_code(), sizeof(__type) }

  static const std::unordered_map<size_t, uint32_t> sizes = {
    //
  };

  assert(sizes.size() == QUIXCC_AST_NODE_COUNT);

  size_t id = typeid(*this).hash_code();
  assert(sizes.contains(id));

  return sizes.at(id);
}

quixcc_ast_ntype_t Node::this_typeid() const {
  quixcc_panic("Node::this_typeid() is not implemented");

  static const std::unordered_map<size_t, quixcc_ast_ntype_t> typeid_map = {
      //
  };

  assert(typeid_map.size() == QUIXCC_AST_NODE_COUNT);

  return typeid_map.at(typeid(*this).hash_code());
}

const char *Node::this_nameof() const { return typeid(*this).name(); }

size_t Node::children_count(bool recursive) const {
  /// TODO: Implement this function
  quixcc_panic("Node::children_count() is not implemented");
}

bool Node::inherits_from(quixcc_ast_ntype_t type) const {
  /// TODO: Implement this function
  quixcc_panic("Node::inherits_from() is not implemented");
}

bool Node::is_type() const { return inherits_from(QUIXCC_AST_NODE_TYPE); }

bool Node::is_stmt() const { return inherits_from(QUIXCC_AST_NODE_STMT); }

bool Node::is_decl() const { return inherits_from(QUIXCC_AST_NODE_DECL); }

bool Node::is_expr() const { return inherits_from(QUIXCC_AST_NODE_EXPR); }

bool Node::is_const_expr() const { return is_expr() && as<Expr>()->is_const(); }

bool Node::is(quixcc_ast_ntype_t type) const { return type == this_typeid(); }

bool Node::verify(std::ostream &os) const { return verify_impl(os); }

void Node::canonicalize() { canonicalize_impl(); }

///=============================================================================

uint64_t Type::infer_size_bits() const { return infer_size_bits_impl(); }
uint64_t Type::infer_size() const { return std::ceil(infer_size_bits() / 8.0); }

bool Type::is_primitive() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_primitive();
  }

  switch (this_typeid()) {
    case QUIXCC_AST_NODE_U1_TY:
    case QUIXCC_AST_NODE_U8_TY:
    case QUIXCC_AST_NODE_U16_TY:
    case QUIXCC_AST_NODE_U32_TY:
    case QUIXCC_AST_NODE_U64_TY:
    case QUIXCC_AST_NODE_U128_TY:
    case QUIXCC_AST_NODE_I8_TY:
    case QUIXCC_AST_NODE_I16_TY:
    case QUIXCC_AST_NODE_I32_TY:
    case QUIXCC_AST_NODE_I64_TY:
    case QUIXCC_AST_NODE_I128_TY:
    case QUIXCC_AST_NODE_F32_TY:
    case QUIXCC_AST_NODE_F64_TY:
    case QUIXCC_AST_NODE_VOID_TY:
      return true;
    default:
      return false;
  }
}

bool Type::is_array() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_array();
  }

  return this_typeid() == QUIXCC_AST_NODE_ARRAY_TY;
}

bool Type::is_vector() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_vector();
  }

  return this_typeid() == QUIXCC_AST_NODE_VECTOR_TY;
}

bool Type::is_tuple() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_tuple();
  }

  return this_typeid() == QUIXCC_AST_NODE_TUPLE_TY;
}

bool Type::is_set() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_set();
  }

  return this_typeid() == QUIXCC_AST_NODE_SET_TY;
}

bool Type::is_map() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_map();
  }

  return this_typeid() == QUIXCC_AST_NODE_MAP_TY;
}

bool Type::is_pointer() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_pointer();
  }

  return this_typeid() == QUIXCC_AST_NODE_PTR_TY;
}

bool Type::is_function() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_function();
  }

  return this_typeid() == QUIXCC_AST_NODE_FN_TY;
}

bool Type::is_composite() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_composite();
  }

  switch (this_typeid()) {
    case QUIXCC_AST_NODE_ARRAY_TY:
    case QUIXCC_AST_NODE_VECTOR_TY:
    case QUIXCC_AST_NODE_TUPLE_TY:
    case QUIXCC_AST_NODE_SET_TY:
    case QUIXCC_AST_NODE_MAP_TY:
    case QUIXCC_AST_NODE_STRUCT_TY:
    case QUIXCC_AST_NODE_GROUP_TY:
    case QUIXCC_AST_NODE_REGION_TY:
    case QUIXCC_AST_NODE_RESULT_TY:
      return true;
    default:
      return false;
  }
}

bool Type::is_union() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_union();
  }

  return this_typeid() == QUIXCC_AST_NODE_UNION_TY;
}

bool Type::is_numeric() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_numeric();
  }

  switch (this_typeid()) {
    case QUIXCC_AST_NODE_U1_TY:
    case QUIXCC_AST_NODE_U8_TY:
    case QUIXCC_AST_NODE_U16_TY:
    case QUIXCC_AST_NODE_U32_TY:
    case QUIXCC_AST_NODE_U64_TY:
    case QUIXCC_AST_NODE_U128_TY:
    case QUIXCC_AST_NODE_I8_TY:
    case QUIXCC_AST_NODE_I16_TY:
    case QUIXCC_AST_NODE_I32_TY:
    case QUIXCC_AST_NODE_I64_TY:
    case QUIXCC_AST_NODE_I128_TY:
    case QUIXCC_AST_NODE_F32_TY:
    case QUIXCC_AST_NODE_F64_TY:
      return true;
    default:
      return false;
  }
}

bool Type::is_integral() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_integral();
  }

  switch (this_typeid()) {
    case QUIXCC_AST_NODE_U1_TY:
    case QUIXCC_AST_NODE_U8_TY:
    case QUIXCC_AST_NODE_U16_TY:
    case QUIXCC_AST_NODE_U32_TY:
    case QUIXCC_AST_NODE_U64_TY:
    case QUIXCC_AST_NODE_U128_TY:
    case QUIXCC_AST_NODE_I8_TY:
    case QUIXCC_AST_NODE_I16_TY:
    case QUIXCC_AST_NODE_I32_TY:
    case QUIXCC_AST_NODE_I64_TY:
    case QUIXCC_AST_NODE_I128_TY:
      return true;
    default:
      return false;
  }
}

bool Type::is_floating_point() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_floating_point();
  }

  switch (this_typeid()) {
    case QUIXCC_AST_NODE_F32_TY:
    case QUIXCC_AST_NODE_F64_TY:
      return true;
    default:
      return false;
  }
}

bool Type::is_signed() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_signed();
  }

  switch (this_typeid()) {
    case QUIXCC_AST_NODE_I8_TY:
    case QUIXCC_AST_NODE_I16_TY:
    case QUIXCC_AST_NODE_I32_TY:
    case QUIXCC_AST_NODE_I64_TY:
    case QUIXCC_AST_NODE_I128_TY:
    case QUIXCC_AST_NODE_F32_TY:
    case QUIXCC_AST_NODE_F64_TY:
      return true;
    default:
      return false;
  }
}

bool Type::is_unsigned() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_unsigned();
  }

  switch (this_typeid()) {
    case QUIXCC_AST_NODE_U1_TY:
    case QUIXCC_AST_NODE_U8_TY:
    case QUIXCC_AST_NODE_U16_TY:
    case QUIXCC_AST_NODE_U32_TY:
    case QUIXCC_AST_NODE_U64_TY:
    case QUIXCC_AST_NODE_U128_TY:
      return true;
    default:
      return false;
  }
}

bool Type::is_void() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_void();
  }

  return this_typeid() == QUIXCC_AST_NODE_VOID_TY;
}

bool Type::is_bool() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_bool();
  }

  return this_typeid() == QUIXCC_AST_NODE_U1_TY;
}

bool Type::is_mutable() const {
  return this_typeid() == QUIXCC_AST_NODE_MUT_TY;
}

bool Type::is_const() const { return !is_mutable(); }

bool Type::is_volatile() const {
  quixcc_panic("Type::is_volatile() is not implemented");
}

bool Type::is_ptr_to(const Type *type) const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_ptr_to(type);
  }

  if (!is_pointer()) {
    return false;
  }

  Type *item = as<PtrTy>()->get_item();
  while (item->is<MutTy>()) {
    item = item->as<MutTy>()->get_item();
  }

  return item->is(type->this_typeid());
}

bool Type::is_mut_ptr_to(const Type *type) const {
  if (!is<MutTy>()) {
    return false;
  }

  return as<MutTy>()->get_item()->is_ptr_to(type);
}

bool Type::is_const_ptr_to(const Type *type) const {
  if (is<MutTy>()) {
    return false;
  }

  return is_ptr_to(type);
}

bool Type::is_ptr_to_mut(const Type *type) const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_ptr_to_mut(type);
  }

  if (!is_pointer()) {
    return false;
  }

  Type *item = as<PtrTy>()->get_item();
  if (!item->is<MutTy>()) {
    return false;
  }

  while (item->is<MutTy>()) {
    item = item->as<MutTy>()->get_item();
  }

  return item->is(type->this_typeid());
}

bool Type::is_ptr_to_const(const Type *type) const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_ptr_to_const(type);
  }

  if (!is_pointer()) {
    return false;
  }

  return as<PtrTy>()->get_item()->is(type->this_typeid());
}

bool Type::is_mut_ptr_to_mut(const Type *type) const {
  if (!is<MutTy>()) {
    return false;
  }

  return as<MutTy>()->get_item()->is_ptr_to_mut(type);
}

bool Type::is_mut_ptr_to_const(const Type *type) const {
  if (!is<MutTy>()) {
    return false;
  }

  return as<MutTy>()->get_item()->is_ptr_to_const(type);
}

bool Type::is_const_ptr_to_mut(const Type *type) const {
  if (is<MutTy>()) {
    return false;
  }

  return is_ptr_to_mut(type);
}

bool Type::is_const_ptr_to_const(const Type *type) const {
  if (is<MutTy>()) {
    return false;
  }

  return is_ptr_to_const(type);
}

bool Type::is_string() const {
  if (is<MutTy>()) {
    return as<MutTy>()->get_item()->is_string();
  }

  return this_typeid() == QUIXCC_AST_NODE_STRING_TY;
}

///=============================================================================

bool Decl::decl_has_name() const { return get_name_impl().has_value(); }
std::string_view Decl::get_decl_name() const { return get_name_impl().value(); }

const std::set<std::string_view, std::less<std::string_view>,
               Arena<std::string_view>> &
Decl::get_tags() const {
  return m_tags;
}
void Decl::add_tag(std::string_view tag) { m_tags.insert(tag); }
void Decl::add_tags(std::initializer_list<std::string_view> tags) {
  for (auto tag : tags) {
    add_tag(tag);
  }
}
void Decl::clear_tags() { m_tags.clear(); }
void Decl::remove_tag(std::string_view tag) {
  std::erase_if(m_tags, [tag](std::string_view t) { return t == tag; });
}

bool Decl::has_type() const { return infer_type() != nullptr; }

Type *Decl::infer_type() const { return infer_type_impl(); }

///=============================================================================

Type *Expr::infer_type() const { return infer_type_impl(); }

bool Expr::is_const() const { return is_const_impl(); }
bool Expr::is_stochastic() const { return is_stochastic_impl(); }

bool Expr::is_binexpr() const {
  if (is<BinExpr>()) {
    return true;
  }

  if (!is<ConstExpr>()) {
    return false;
  }

  return as<ConstExpr>()->get_value()->is_binexpr();
}

bool Expr::is_unaryexpr() const {
  if (is<UnaryExpr>()) {
    return true;
  }

  if (!is<ConstExpr>()) {
    return false;
  }

  return as<ConstExpr>()->get_value()->is_unaryexpr();
}

bool Expr::is_ternaryexpr() const {
  if (is<TernaryExpr>()) {
    return true;
  }

  if (!is<ConstExpr>()) {
    return false;
  }

  return as<ConstExpr>()->get_value()->is_ternaryexpr();
}

///=============================================================================

Type *ConstExpr::infer_type_impl() const { return get_value()->infer_type(); }
bool ConstExpr::is_const_impl() const { return true; }
bool ConstExpr::is_stochastic_impl() const { return false; }

Expr *ConstExpr::get_value() const {
  assert(m_value);
  return m_value;
}

void ConstExpr::set_value(Expr *value) { m_value = value; }

bool ConstExpr::verify_impl(std::ostream &os) const {
  quixcc_panic("ConstExpr::verify_impl() is not implemented");
}

void ConstExpr::canonicalize_impl() {
  quixcc_panic("ConstExpr::canonicalize_impl() is not implemented");
}

void ConstExpr::print_impl(std::ostream &os, bool debug) const {
  quixcc_panic("ConstExpr::print_impl() is not implemented");
}

ConstExpr *ConstExpr::clone_impl() const {
  quixcc_panic("ConstExpr::clone_impl() is not implemented");
}

///=============================================================================

#define TRIVIAL_TYPE_IMPL(__typename, __dumpstr, __bits)                   \
  bool __typename::verify_impl(std::ostream &os) const { return true; }    \
  void __typename::canonicalize_impl() {}                                  \
  void __typename::print_impl(std::ostream &os, bool debug) const {        \
    os << __dumpstr;                                                       \
  }                                                                        \
  __typename *__typename::clone_impl() const { return __typename::get(); } \
  uint64_t __typename::infer_size_bits_impl() const { return __bits; }

TRIVIAL_TYPE_IMPL(U1, "u1", 8)
TRIVIAL_TYPE_IMPL(U8, "u8", 8)
TRIVIAL_TYPE_IMPL(U16, "u16", 16)
TRIVIAL_TYPE_IMPL(U32, "u32", 32)
TRIVIAL_TYPE_IMPL(U64, "u64", 64)
TRIVIAL_TYPE_IMPL(U128, "u128", 128)
TRIVIAL_TYPE_IMPL(I8, "i8", 8)
TRIVIAL_TYPE_IMPL(I16, "i16", 16)
TRIVIAL_TYPE_IMPL(I32, "i32", 32)
TRIVIAL_TYPE_IMPL(I64, "i64", 64)
TRIVIAL_TYPE_IMPL(I128, "i128", 128)
TRIVIAL_TYPE_IMPL(F32, "f32", 32)
TRIVIAL_TYPE_IMPL(F64, "f64", 64)
TRIVIAL_TYPE_IMPL(Void, "void", 0)
TRIVIAL_TYPE_IMPL(StringTy, "string", 8)

bool PtrTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "PtrTy: item type is NULL\n";
    return false;
  }

  return m_item->verify(os);
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
  if (m_item) {
    return PtrTy::get(m_item->clone(), m_is_volatile);
  }

  return PtrTy::get(nullptr, m_is_volatile);
}

uint64_t PtrTy::infer_size_bits_impl() const {
  quixcc_panic("PtrTy::infer_size_bits_impl() is not implemented");
}

Type *PtrTy::get_item() const { return m_item; }
void PtrTy::set_item(Type *item) { m_item = item; }
bool PtrTy::is_volatile() const { return m_is_volatile; }
void PtrTy::set_volatile(bool is_volatile) { m_is_volatile = is_volatile; }

bool OpaqueTy::verify_impl(std::ostream &os) const {
  if (m_name.empty()) {
    os << "OpaqueTy: name is empty\n";
    return false;
  }

  return true;
}

void OpaqueTy::canonicalize_impl() {}
void OpaqueTy::print_impl(std::ostream &os, bool debug) const {
  os << "opaque<" << m_name << ">";
}
OpaqueTy *OpaqueTy::clone_impl() const { return OpaqueTy::get(m_name); }

uint64_t OpaqueTy::infer_size_bits_impl() const {
  quixcc_panic("OpaqueTy::infer_size_bits_impl() is not implemented");
}

std::string_view OpaqueTy::get_name() const { return m_name; }
void OpaqueTy::set_name(std::string_view name) { m_name = name; }

bool VectorTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "VectorTy: item type is NULL\n";
    return false;
  }

  return m_item->verify(os);
}

void VectorTy::canonicalize_impl() {
  if (m_item) {
    m_item->canonicalize();
  }
}

void VectorTy::print_impl(std::ostream &os, bool debug) const {
  if (!m_item) {
    os << "vec<?>";
    return;
  }

  os << "vec<";
  m_item->print(os, debug);
  os << ">";
}

VectorTy *VectorTy::clone_impl() const {
  if (m_item) {
    return VectorTy::get(m_item->clone());
  }

  return VectorTy::get(nullptr);
}

uint64_t VectorTy::infer_size_bits_impl() const {
  quixcc_panic("VectorTy::infer_size_bits_impl() is not implemented");
}

bool SetTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "SetTy: item type is NULL\n";
    return false;
  }

  return m_item->verify(os);
}

void SetTy::canonicalize_impl() {
  if (m_item) {
    m_item->canonicalize();
  }
}

void SetTy::print_impl(std::ostream &os, bool debug) const {
  if (!m_item) {
    os << "set<?>";
    return;
  }

  os << "set<";
  m_item->print(os, debug);
  os << ">";
}

SetTy *SetTy::clone_impl() const {
  if (m_item) {
    return SetTy::get(m_item->clone());
  }

  return SetTy::get(nullptr);
}

uint64_t SetTy::infer_size_bits_impl() const {
  quixcc_panic("SetTy::infer_size_bits_impl() is not implemented");
}

bool MapTy::verify_impl(std::ostream &os) const {
  if (!m_key) {
    os << "MapTy: key type is NULL\n";
    return false;
  }

  if (!m_value) {
    os << "MapTy: value type is NULL\n";
    return false;
  }

  return m_key->verify(os) && m_value->verify(os);
}

void MapTy::canonicalize_impl() {
  if (m_key) {
    m_key->canonicalize();
  }

  if (m_value) {
    m_value->canonicalize();
  }
}

void MapTy::print_impl(std::ostream &os, bool debug) const {
  if (!m_key) {
    os << "map<?, ";
  } else {
    os << "map<";
    m_key->print(os, debug);
    os << ", ";
  }

  if (!m_value) {
    os << "?>";
  } else {
    m_value->print(os, debug);
    os << ">";
  }
}

MapTy *MapTy::clone_impl() const {
  Type *key = m_key ? m_key->clone() : nullptr;
  Type *value = m_value ? m_value->clone() : nullptr;

  return MapTy::get(key, value);
}

uint64_t MapTy::infer_size_bits_impl() const {
  quixcc_panic("MapTy::infer_size_bits_impl() is not implemented");
}

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

uint64_t TupleTy::infer_size_bits_impl() const {
  quixcc_panic("TupleTy::infer_size_bits_impl() is not implemented");
}

bool OptionalTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "OptionalTy: item type is NULL\n";
    return false;
  }

  return m_item->verify(os);
}

void OptionalTy::canonicalize_impl() {
  if (m_item) {
    m_item->canonicalize();
  }
}

void OptionalTy::print_impl(std::ostream &os, bool debug) const {
  if (!m_item) {
    os << "opt<?>";
    return;
  }

  os << "opt<";
  m_item->print(os, debug);
  os << ">";
}

OptionalTy *OptionalTy::clone_impl() const {
  if (m_item) {
    return OptionalTy::get(m_item->clone());
  }

  return OptionalTy::get(nullptr);
}

uint64_t OptionalTy::infer_size_bits_impl() const {
  quixcc_panic("OptionalTy::infer_size_bits_impl() is not implemented");
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

  if (!m_item->verify(os) || !m_size->verify(os)) {
    os << "ArrayTy: item or size is invalid\n";
    return false;
  }

  if (!m_size->infer_type()->is_unsigned()) {
    os << "ArrayTy: size is not an unsigned integral type\n";
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

uint64_t ArrayTy::infer_size_bits_impl() const {
  assert(m_item);
  assert(m_size);

  return m_item->infer_size_bits() * m_size->eval_as<uint64_t>();
}

Type *ArrayTy::get_item() const { return m_item; }
void ArrayTy::set_item(Type *item) { m_item = item; }
ConstExpr *ArrayTy::get_size() const { return m_size; }
void ArrayTy::set_size(ConstExpr *size) { m_size = size; }

bool EnumTy::verify_impl(std::ostream &os) const {
  if (!m_memtype) {
    os << "EnumTy: member item type is NULL\n";
    return false;
  }

  return m_memtype->verify(os);
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

uint64_t EnumTy::infer_size_bits_impl() const {
  assert(m_memtype);

  return m_memtype->infer_size_bits();
}

std::string_view EnumTy::get_name() const { return m_name; }
void EnumTy::set_name(std::string_view name) { m_name = name; }
Type *EnumTy::get_memtype() const { return m_memtype; }
void EnumTy::set_memtype(Type *memtype) { m_memtype = memtype; }

bool MutTy::verify_impl(std::ostream &os) const {
  if (!m_item) {
    os << "MutTy: item type is NULL\n";
    return false;
  }

  return m_item->verify(os);
}

void MutTy::canonicalize_impl() {
  if (m_item) {
    m_item->canonicalize();
  }
}

void MutTy::print_impl(std::ostream &os, bool debug) const {
  if (!m_item) {
    os << "mut<?>";
    return;
  }

  os << "mut<";
  m_item->print(os, debug);
  os << ">";
}

MutTy *MutTy::clone_impl() const {
  if (m_item) {
    return MutTy::get(m_item->clone());
  }

  return MutTy::get(nullptr);
}

uint64_t MutTy::infer_size_bits_impl() const {
  assert(m_item);

  return m_item->infer_size_bits();
}

Type *MutTy::get_item() const { return m_item; }
void MutTy::set_item(Type *item) { m_item = item; }

bool StructTy::verify_impl(std::ostream &os) const {
  std::unordered_set<std::string_view> names;

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

uint64_t StructTy::infer_size_bits_impl() const {
  quixcc_panic("StructTy::infer_size_bits_impl() is not implemented");
}

const std::vector<StructItem, Arena<StructItem>> &StructTy::get_items() const {
  return m_items;
}

void StructTy::add_item(std::string_view name, Type *item) {
  m_items.push_back({name, item});
}

void StructTy::add_items(std::initializer_list<StructItem> fields) {
  for (auto [name, item] : fields) {
    add_item(name, item);
  }
}

void StructTy::clear_items() { m_items.clear(); }

void StructTy::remove_item(std::string_view name) {
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

uint64_t GroupTy::infer_size_bits_impl() const {
  quixcc_panic("GroupTy::infer_size_bits_impl() is not implemented");
}

const std::vector<Type *, Arena<Type *>> &GroupTy::get_items() const {
  return m_items;
}

void GroupTy::add_item(Type *item) { m_items.push_back(item); }

void GroupTy::add_items(std::initializer_list<Type *> fields) {
  for (auto field : fields) {
    add_item(field);
  }
}

void GroupTy::clear_items() { m_items.clear(); }

void GroupTy::remove_item(Type *item) {
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

uint64_t RegionTy::infer_size_bits_impl() const {
  size_t size = 0;
  for (auto item : m_items) {
    size += item->infer_size_bits();
  }

  return size;
}

const std::vector<Type *, Arena<Type *>> &RegionTy::get_items() const {
  return m_items;
}

void RegionTy::add_item(Type *item) { m_items.push_back(item); }

void RegionTy::add_items(std::initializer_list<Type *> fields) {
  for (auto field : fields) {
    add_item(field);
  }
}

void RegionTy::clear_items() { m_items.clear(); }

void RegionTy::remove_item(Type *item) {
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

uint64_t UnionTy::infer_size_bits_impl() const {
  size_t size = 0;
  for (auto item : m_items) {
    size = std::max(size, item->infer_size_bits());
  }

  return size;
}

const std::vector<Type *, Arena<Type *>> &UnionTy::get_items() const {
  return m_items;
}

void UnionTy::add_item(Type *item) { m_items.push_back(item); }

void UnionTy::add_items(std::initializer_list<Type *> fields) {
  for (auto field : fields) {
    add_item(field);
  }
}

void UnionTy::clear_items() { m_items.clear(); }

void UnionTy::remove_item(Type *item) {
  std::erase_if(m_items, [item](auto &field) { return field == item; });
}

bool FuncTy::verify_impl(std::ostream &os) const {
  if (!m_return) {
    os << "FuncTy: return type is NULL\n";
    return false;
  }

  std::unordered_set<std::string_view> names;
  for (size_t i = 0; i < m_params.size(); i++) {
    if (names.contains(std::get<0>(m_params[i]))) {
      os << "FuncTy: duplicate param name '" << std::get<0>(m_params[i])
         << "'\n";
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

  return FuncTy::get(ret, params, m_variadic, m_purity, m_is_foreign,
                     m_crashpoint, m_noexcept, m_noreturn);
}

uint64_t FuncTy::infer_size_bits_impl() const {
  quixcc_panic("FuncTy::infer_size_bits_impl() is not implemented");
}

bool FuncTy::is_noreturn() const { return m_noreturn; }
void FuncTy::set_noreturn(bool noreturn) { m_noreturn = noreturn; }
Type *FuncTy::get_return_ty() const { return m_return; }
void FuncTy::set_return_ty(Type *ty) { m_return = ty; }
const std::vector<FuncParam, Arena<FuncParam>> &FuncTy::get_params() const {
  return m_params;
}
void FuncTy::add_param(std::string_view name, Type *ty, Expr *default_val) {
  m_params.push_back({name, ty, default_val});
}
void FuncTy::add_params(std::initializer_list<FuncParam> params) {
  for (auto [name, ty, expr] : params) {
    add_param(name, ty, expr);
  }
}
void FuncTy::clear_params() { m_params.clear(); }
void FuncTy::remove_param(std::string_view name) {
  std::erase_if(m_params,
                [name](auto &param) { return std::get<0>(param) == name; });
}

FuncPurity FuncTy::get_purity() const { return m_purity; }
void FuncTy::set_purity(FuncPurity purity) { m_purity = purity; }

bool FuncTy::is_variadic() const { return m_variadic; }
void FuncTy::set_variadic(bool variadic) { m_variadic = variadic; }

bool FuncTy::is_foreign() const { return m_is_foreign; }
void FuncTy::set_foreign(bool is_foreign) { m_is_foreign = is_foreign; }

bool FuncTy::is_crashpoint() const { return m_crashpoint; }
void FuncTy::set_crashpoint(bool crashpoint) { m_crashpoint = crashpoint; }

bool FuncTy::is_noexcept() const { return m_noexcept; }
void FuncTy::set_noexcept(bool _noexcept) { m_noexcept = _noexcept; }

///=============================================================================

bool UnaryExpr::verify_impl(std::ostream &os) const {
  if (!m_rhs) {
    os << "UnaryExpr: rhs is NULL\n";
    return false;
  }

  if (m_op == UnaryOp::UNKNOWN) {
    os << "UnaryExpr: unknown operator\n";
    return false;
  }

  return m_rhs->verify(os);
}

void UnaryExpr::canonicalize_impl() {
  if (m_rhs) {
    m_rhs->canonicalize();
  }
}

void UnaryExpr::print_impl(std::ostream &os, bool debug) const {
  os << "(";

  switch (m_op) {
    case UnaryOp::UNKNOWN:
      os << "unknown";
      break;
  }

  if (m_rhs) {
    m_rhs->print(os, debug);
  } else {
    os << "?";
  }
}

UnaryExpr *UnaryExpr::clone_impl() const {
  if (m_rhs) {
    return UnaryExpr::get(m_op, m_rhs->clone());
  }

  return UnaryExpr::get(m_op, nullptr);
}

Type *UnaryExpr::infer_type_impl() const {
  quixcc_panic("UnaryExpr::infer_type_impl() is not implemented");
}

bool UnaryExpr::is_const_impl() const {
  assert(m_rhs);
  return m_rhs->is_const();
}

bool UnaryExpr::is_stochastic_impl() const {
  assert(m_rhs);
  return m_rhs->is_stochastic();
}

UnaryOp UnaryExpr::get_op() const { return m_op; }
void UnaryExpr::set_op(UnaryOp op) { m_op = op; }

Expr *UnaryExpr::get_rhs() const {
  assert(m_rhs);
  return m_rhs;
}
void UnaryExpr::set_rhs(Expr *rhs) { m_rhs = rhs; }

bool BinExpr::verify_impl(std::ostream &os) const {
  if (!m_lhs) {
    os << "BinExpr: lhs is NULL\n";
    return false;
  }

  if (!m_rhs) {
    os << "BinExpr: rhs is NULL\n";
    return false;
  }

  if (m_op == BinOp::UNKNOWN) {
    os << "BinExpr: unknown operator\n";
    return false;
  }

  return m_lhs->verify(os) && m_rhs->verify(os);
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

  switch (m_op) {
    case BinOp::UNKNOWN:
      os << " unknown ";
      break;
  }

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

Type *BinExpr::infer_type_impl() const {
  quixcc_panic("BinExpr::infer_type_impl() is not implemented");
}

bool BinExpr::is_const_impl() const {
  assert(m_lhs);
  assert(m_rhs);
  return m_lhs->is_const() && m_rhs->is_const();
}

bool BinExpr::is_stochastic_impl() const {
  assert(m_lhs);
  assert(m_rhs);
  return m_lhs->is_stochastic() || m_rhs->is_stochastic();
}

BinOp BinExpr::get_op() const { return m_op; }
void BinExpr::set_op(BinOp op) { m_op = op; }

Expr *BinExpr::get_lhs() const {
  assert(m_lhs);
  return m_lhs;
}
void BinExpr::set_lhs(Expr *lhs) { m_lhs = lhs; }

Expr *BinExpr::get_rhs() const {
  assert(m_rhs);
  return m_rhs;
}
void BinExpr::set_rhs(Expr *rhs) { m_rhs = rhs; }

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

  return m_cond->verify(os) && m_lhs->verify(os) && m_rhs->verify(os);
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

Type *TernaryExpr::infer_type_impl() const {
  quixcc_panic("TernaryExpr::infer_type_impl() is not implemented");
}

bool TernaryExpr::is_const_impl() const {
  assert(m_cond);
  assert(m_lhs);
  assert(m_rhs);
  return m_cond->is_const() && m_lhs->is_const() && m_rhs->is_const();
}

bool TernaryExpr::is_stochastic_impl() const {
  assert(m_cond);
  assert(m_lhs);
  assert(m_rhs);
  return m_cond->is_stochastic() || m_lhs->is_stochastic() ||
         m_rhs->is_stochastic();
}

Expr *TernaryExpr::get_cond() const {
  assert(m_cond);
  return m_cond;
}
void TernaryExpr::set_cond(Expr *cond) { m_cond = cond; }

Expr *TernaryExpr::get_lhs() const {
  assert(m_lhs);
  return m_lhs;
}
void TernaryExpr::set_lhs(Expr *lhs) { m_lhs = lhs; }

Expr *TernaryExpr::get_rhs() const {
  assert(m_rhs);
  return m_rhs;
}
void TernaryExpr::set_rhs(Expr *rhs) { m_rhs = rhs; }

///=============================================================================

bool ConstInt::verify_impl(std::ostream &os) const {
  if (m_value.empty()) {
    os << "ConstInt: value is empty\n";
    return false;
  }

  quixcc_panic("ConstInt::verify_impl() is not implemented");

  return true;
}

void ConstInt::canonicalize_impl() {
  quixcc_panic("ConstInt::canonicalize_impl() is not implemented");
}

void ConstInt::print_impl(std::ostream &os, bool debug) const { os << m_value; }

ConstInt *ConstInt::clone_impl() const { return ConstInt::get(m_value); }

std::string_view ConstInt::get_value() const { return m_value; }

bool ConstFloat::verify_impl(std::ostream &os) const {
  if (m_value.empty()) {
    os << "ConstFloat: value is empty\n";
    return false;
  }

  quixcc_panic("ConstFloat::verify_impl() is not implemented");

  return true;
}

void ConstFloat::canonicalize_impl() {
  quixcc_panic("ConstFloat::canonicalize_impl() is not implemented");
}

void ConstFloat::print_impl(std::ostream &os, bool debug) const {
  os << m_value;
}

ConstFloat *ConstFloat::clone_impl() const { return ConstFloat::get(m_value); }

std::string_view ConstFloat::get_value() const { return m_value; }

bool ConstBool::verify_impl(std::ostream &os) const { return true; }

void ConstBool::canonicalize_impl() {}

void ConstBool::print_impl(std::ostream &os, bool debug) const {
  os << (m_value ? "true" : "false");
}

ConstBool *ConstBool::clone_impl() const { return ConstBool::get(m_value); }

bool ConstBool::get_value() const { return m_value; }

bool ConstChar::verify_impl(std::ostream &os) const {
  if (m_value.empty()) {
    os << "ConstChar: value is empty\n";
    return false;
  }

  quixcc_panic("ConstChar::verify_impl() is not implemented");

  return true;
}

void ConstChar::canonicalize_impl() {
  quixcc_panic("ConstChar::canonicalize_impl() is not implemented");
}

void ConstChar::print_impl(std::ostream &os, bool debug) const {
  os << "'" << m_value << "'";
}

ConstChar *ConstChar::clone_impl() const { return ConstChar::get(m_value); }

std::string_view ConstChar::get_value() const { return m_value; }

bool ConstString::verify_impl(std::ostream &os) const {
  if (m_value.empty()) {
    os << "ConstString: value is empty\n";
    return false;
  }

  quixcc_panic("ConstString::verify_impl() is not implemented");

  return true;
}

void ConstString::canonicalize_impl() {
  quixcc_panic("ConstString::canonicalize_impl() is not implemented");
}

void ConstString::print_impl(std::ostream &os, bool debug) const {
  os << "\"" << m_value << "\"";
}

ConstString *ConstString::clone_impl() const {
  return ConstString::get(m_value);
}

std::string_view ConstString::get_value() const { return m_value; }

bool ConstNull::verify_impl(std::ostream &os) const { return true; }
void ConstNull::canonicalize_impl() {}
void ConstNull::print_impl(std::ostream &os, bool debug) const { os << "null"; }
ConstNull *ConstNull::clone_impl() const { return ConstNull::get(); }

bool ConstUndef::verify_impl(std::ostream &os) const { return true; }
void ConstUndef::canonicalize_impl() {}
void ConstUndef::print_impl(std::ostream &os, bool debug) const {
  os << "undef";
}
ConstUndef *ConstUndef::clone_impl() const { return ConstUndef::get(); }

///=============================================================================

LIB_EXPORT quixcc_ast_node_t *quixcc_ast_alloc(quixcc_ast_ntype_t type,
                                               quixcc_arena_t *arena) {
  quixcc_panic("quixcc_ast_alloc() is not implemented");
}

LIB_EXPORT void quixcc_ast_done(quixcc_ast_node_t *node) {
  node->~quixcc_ast_node_t();
}

///=============================================================================
///=============================================================================

LIB_EXPORT void quixcc_test_hook() {
  using namespace libquixcc::qast;

  std::vector<FuncParam, Arena<FuncParam>> params = {
      {"x", I32::get(), ConstInt::get("42")}};

  FuncTy *ftp = FuncTy::get(VectorTy::get(I32::get()), params);

  (void)ftp;

  // ftp->dump();

  // std::cout << "\n";
}