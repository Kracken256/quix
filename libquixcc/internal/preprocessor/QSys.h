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

#ifndef __QUIXCC_PREP_QSYS_H__
#define __QUIXCC_PREP_QSYS_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <quixcc/Types.h>

namespace libquixcc::qsys {
#define QSYS_DECL(name) \
  bool name(quixcc_engine_t *, uint32_t, quixcc_expr_t **, uint32_t)

#define QSYS_DEFINE(_name, _desc)                             \
  bool libquixcc::qsys::_name(quixcc_engine_t *e, uint32_t n, \
                              quixcc_expr_t **v, uint32_t c)
#define QSYS_ARGASSERT(name, nargs)                                        \
  if (c != nargs) {                                                        \
    quixcc_engine_message(e, QUIXCC_MESSAGE_ERROR,                         \
                          "QSys Call \"%s\" expects %d arguments, got %d", \
                          #name, nargs, c);                                \
    return false;                                                          \
  }

#define QSYS_ARG_STRING(_qname, _varname, _idx)                           \
  if (c <= _idx) {                                                        \
    quixcc_engine_message(e, QUIXCC_MESSAGE_FATAL,                        \
                          "%s: Argument %d OUT OF RANGE", #_qname, _idx); \
    return false;                                                         \
  }                                                                       \
  size_t _varname##_len = 0;                                              \
  const char *_varname = quixcc_expr_to_string(v[_idx], &_varname##_len); \
  if (_varname == nullptr) {                                              \
    quixcc_engine_message(                                                \
        e, QUIXCC_MESSAGE_ERROR,                                          \
        "%s: Failed to convert argument %d to string \"" #_varname "\"",  \
        #_qname, _idx);                                                   \
    return false;                                                         \
  }

#define QSYS_ARG_INT64(_qname, _varname, _idx)                            \
  if (c <= _idx) {                                                        \
    quixcc_engine_message(e, QUIXCC_MESSAGE_FATAL,                        \
                          "%s: Argument %d OUT OF RANGE", #_qname, _idx); \
    return false;                                                         \
  }                                                                       \
  int64_t _varname = 0;                                                   \
  if (!quixcc_expr_to_int64(v[_idx], &_varname)) {                        \
    quixcc_engine_message(                                                \
        e, QUIXCC_MESSAGE_ERROR,                                          \
        "%s: Failed to convert argument %d to int64_t \"" #_varname "\"", \
        #_qname, _idx);                                                   \
    return false;                                                         \
  }

#define QSYS_NOT_IMPLEMENTED(name)                                       \
  bool libquixcc::qsys::name(quixcc_engine_t *e, uint32_t n,             \
                             quixcc_expr_t **v, uint32_t c) {            \
    quixcc_engine_message(e, QUIXCC_MESSAGE_WARNING,                     \
                          "QSys Call \"%s\" is not implemented", #name); \
    return true;                                                         \
  }
/*==================== TEXT IO ====================*/
QSYS_DECL(qsys_write_stdout);
QSYS_DECL(qsys_write_stderr);
QSYS_DECL(qsys_read_stdin);
QSYS_DECL(qsys_clear_terminal);
QSYS_DECL(qsys_set_terminal_title);
QSYS_DECL(qsys_set_terminal_color);
QSYS_DECL(qsys_set_cursor_position);
QSYS_DECL(qsys_set_cursor_visibility);
QSYS_DECL(qsys_set_cursor_blink_rate);
QSYS_DECL(qsys_enable_terminal_echo);
QSYS_DECL(qsys_bell);
QSYS_DECL(qsys_set_terminal_size);
QSYS_DECL(qsys_set_terminal_font);

/*==================== FILE IO ====================*/
QSYS_DECL(qsys_open_file);
QSYS_DECL(qsys_close_file);
QSYS_DECL(qsys_read_file);
QSYS_DECL(qsys_write_file);
QSYS_DECL(qsys_seek_file);
QSYS_DECL(qsys_tell_file);
QSYS_DECL(qsys_flush_file);
QSYS_DECL(qsys_delete_file);
QSYS_DECL(qsys_rename_file);
QSYS_DECL(qsys_create_directory);
QSYS_DECL(qsys_delete_directory);
QSYS_DECL(qsys_rename_directory);
QSYS_DECL(qsys_list_directory);
QSYS_DECL(qsys_get_file_attributes);
QSYS_DECL(qsys_set_file_attributes);

/*==================== SYSTEM ====================*/
QSYS_DECL(qsys_get_compiler_version);
QSYS_DECL(qsys_get_compiler_flags);
QSYS_DECL(qsys_unset_compiler_flag);
QSYS_DECL(qsys_set_compiler_flag);
QSYS_DECL(qsys_get_compiler_log_file);
QSYS_DECL(qsys_execute_os_command);
QSYS_DECL(qsys_abort_compilation);

/*==================== NETWORK ====================*/
QSYS_DECL(qsys_open_network_connection);
QSYS_DECL(qsys_close_network_connection);
QSYS_DECL(qsys_read_network_connection);
QSYS_DECL(qsys_write_network_connection);

/*==================== LANGUAGE ====================*/
QSYS_DECL(qsys_compile_and_execute_quix);
QSYS_DECL(qsys_get_type_of_item);
QSYS_DECL(qsys_undefine_function);
QSYS_DECL(qsys_undefine_macro);
QSYS_DECL(qsys_undeclare_item);
QSYS_DECL(qsys_get_macro_body);
QSYS_DECL(qsys_get_function_body);
QSYS_DECL(qsys_get_type_body);
QSYS_DECL(qsys_set_global_meta_variable);
QSYS_DECL(qsys_get_global_meta_variable);

void bind_qsyscalls(quixcc_job_t *job);
}  // namespace libquixcc::qsys

#endif  // __QUIXCC_PREP_QSYS_H__