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

#ifndef __QUIX_QXIR_MODULE_H__
#define __QUIX_QXIR_MODULE_H__

#include <quix-lexer/Lexer.h>
#include <quix-qxir/TypeDecl.h>

#include <quix-core/Classes.hh>

#ifdef __cplusplus
extern "C" {
#endif

qlex_t *qxir_get_lexer(qmodule_t *mod);
void qxir_set_lexer(qmodule_t *mod, qlex_t *lexer);
qxir_node_t *qxir_base(qmodule_t *mod);
qxir_conf_t *qxir_get_conf(qmodule_t *mod);
void qxir_set_conf(qmodule_t *mod, qxir_conf_t *conf);

#ifdef __cplusplus
}
#endif

#if (defined(__cplusplus) && defined(QXIR_USE_CPP_API)) || defined(__QUIX_IMPL__)

#include <quix-core/Arena.h>

#include <boost/bimap.hpp>
#include <cstdint>
#include <limits>
#include <memory>
#include <optional>
#include <quix-qxir/Report.hh>
#include <string>
#include <unordered_set>
#include <vector>

namespace qxir {
  typedef uint16_t ModuleId;

  struct TypeID {
    uint64_t m_id : 40;

    TypeID(uint64_t id) : m_id(id) {}
  } __attribute__((packed));

  class Type;

  class TypeManager {
    std::vector<Type *> m_types;

  public:
    TypeManager() = default;

    TypeID add(Type *type) {
      m_types.push_back(type);
      return TypeID(m_types.size() - 1);
    }

    Type *get(TypeID tid) { return m_types.at(tid.m_id); }
  };

  constexpr size_t MAX_MODULE_INSTANCES = std::numeric_limits<ModuleId>::max();

  struct TargetInfo {
    uint16_t m_pointer_size;

    TargetInfo() : m_pointer_size(8) {}

    uint16_t getPointerSize() const { return m_pointer_size; }
  };

  class Expr;

}  // namespace qxir

namespace qxir {
  class Expr;
  class Type;
  class BinExpr;
  class UnExpr;
  class PostUnExpr;
  class U1Ty;
  class U8Ty;
  class U16Ty;
  class U32Ty;
  class U64Ty;
  class U128Ty;
  class I8Ty;
  class I16Ty;
  class I32Ty;
  class I64Ty;
  class I128Ty;
  class F16Ty;
  class F32Ty;
  class F64Ty;
  class F128Ty;
  class VoidTy;
  class PtrTy;
  class OpaqueTy;
  class StructTy;
  class UnionTy;
  class ArrayTy;
  class FnTy;
  class Int;
  class Float;
  class List;
  class Call;
  class Seq;
  class Index;
  class Ident;
  class Extern;
  class Local;
  class Ret;
  class Brk;
  class Cont;
  class If;
  class While;
  class For;
  class Form;
  class Case;
  class Switch;
  class Fn;
  class Asm;
#ifdef __QUIX_IMPL__
  class Tmp;
#endif
}  // namespace qxir

struct qmodule_t {
private:
  std::vector<std::string> m_passes_applied;
  std::unordered_set<std::string> m_strings;
  boost::bimap<std::string_view, std::pair<qxir::FnTy *, qxir::Expr *>> functions;
  boost::bimap<std::string_view, qxir::Local *> variables;
  std::unordered_map<std::string_view,
                     std::vector<std::tuple<std::string, qxir::Type *, qxir::Expr *>>>
      m_parameters;
  std::unordered_map<std::string_view, qxir::Type *> m_typedef_map;
  std::unordered_map<std::string_view,
                     std::vector<std::tuple<std::string, qxir::Type *, qxir::Expr *>>>
      m_composite_fields;
  std::unordered_map<std::string_view, qxir::Expr *> m_named_constants;
  std::unique_ptr<qxir::diag::DiagnosticManager> m_diag;
  std::unique_ptr<qxir::TypeManager> m_type_mgr;
  qxir::TargetInfo m_target_info;
  std::string m_module_name;
  qcore_arena m_node_arena;
  qxir_conf_t *m_conf;
  qlex_t *m_lexer;
  qxir::Expr *m_root;
  qxir::ModuleId m_id;
  bool m_diagnostics_enabled;
  bool m_failbit;

public:
  qmodule_t(qxir::ModuleId id, const std::string &name = "?");
  ~qmodule_t();

  /**
   * @brief Get the module ID.
   * @return ModuleId
   */
  qxir::ModuleId getModuleId() noexcept;

  /**
   * @brief Lookup a type by its type ID.
   * @param tid Type ID
   * @return Type* or nullptr if not found
   */
  qxir::Type *lookupType(qxir::TypeID tid);

  void setRoot(qxir::Expr *root) noexcept;
  qxir::Expr *&getRoot() noexcept;

  void setLexer(qlex_t *lexer) noexcept;
  qlex_t *getLexer() noexcept;

  void setConf(qxir_conf_t *conf) noexcept;
  qxir_conf_t *getConf() noexcept;

  /**
   * @brief Enable or disable diagnostics.
   * @param is_enabled Enable diagnostics
   */
  void enableDiagnostics(bool is_enabled) noexcept;

  bool isDiagnosticsEnabled() const noexcept { return m_diagnostics_enabled; }

  /**
   * @brief Make it known that a pass has been applied to the module.
   * @param label Pass label
   */
  void applyPassLabel(const std::string &label) { m_passes_applied.push_back(label); }
  const auto &getPassesApplied() const { return m_passes_applied; }

  /**
   * @brief Check if a pass has been applied to the module.
   * @param label Pass label
   */
  bool hasPassBeenRun(const std::string &label) {
    return std::find(m_passes_applied.begin(), m_passes_applied.end(), label) !=
           m_passes_applied.end();
  }

  const std::string getName() const { return m_module_name; }
  void setName(const std::string &name) { m_module_name = name; }

  auto &getFunctions() { return functions; }
  auto &getGlobalVariables() { return variables; }
  auto &getParameterMap() { return m_parameters; }
  auto &getTypeMap() { return m_typedef_map; }
  auto &getCompositeFields() { return m_composite_fields; }
  auto &getNamedConstants() { return m_named_constants; }

  /**
   * @brief Intern a string.
   * @param sv String view
   * @return reference to the interned string
   */
  std::string_view internString(std::string_view sv);

  qcore_arena_t &getNodeArena() { return *m_node_arena.get(); }

  qxir::diag::DiagnosticManager &getDiag() { return *m_diag; }

  const qxir::TargetInfo &getTargetInfo() const { return m_target_info; }

  void setFailbit(bool fail) { m_failbit = fail; }
  bool getFailbit() const { return m_failbit; }
};

#define QMODULE_SIZE sizeof(qmodule_t)

namespace qxir {
  qmodule_t *getModule(ModuleId mid);
  qmodule_t *createModule(std::string name = "?");
}  // namespace qxir

#endif

#endif  // __QUIX_QXIR_MODULE_H__
