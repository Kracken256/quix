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

#ifndef __QUIX_PREP_PROCESS_H__
#define __QUIX_PREP_PROCESS_H__

#include <quix-lexer/Lexer.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new preprocessor context.
 *
 * @param file A seekable file stream.
 * @param filename Name of the file or NULL for default.
 * @param env Parent environment.
 *
 * @return New preprocessor context or NULL if an error occurred.
 * @note The lifetime of the file stream and environment must exceed the lifetime of the lexer.
 * @note This function is thread-safe.
 */
qlex_t *qprep_new(FILE *file, const char *filename, qcore_env_t env);

/**
 * @brief Fetch source code for a module by import name.
 *
 * @param ctx Preprocessor context.
 * @param import_name Import name of the module.
 * @param[out] content malloc'd buffer containing the module source code.
 * @param[out] content_size Size of the `content` buffer.
 * @param any User-defined data.
 *
 * @return True if the module was fetched successfully, false otherwise.
 * @note This function is thread-safe.
 */
typedef bool (*qprep_fetch_module_t)(qlex_t *ctx, const char *import_name, char **content,
                                     size_t *content_size, uintptr_t any);

/**
 * @brief Set the fetch module function for the preprocessor context.
 *
 * @param ctx Preprocessor context.
 * @param fetch_fn Fetch module function.
 * @param any User-defined data to pass to the fetch function.
 *
 * @note This function is thread-safe.
 */
void qprep_set_fetch_module(qlex_t *ctx, qprep_fetch_module_t fetch_fn, uintptr_t any);

#ifdef __cplusplus
}
#endif

#endif  // __QUIX_PREP_PROCESS_H__
