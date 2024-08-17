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

#ifndef __QUIX_QXIR_CONFIG_H__
#define __QUIX_QXIR_CONFIG_H__

#if defined(__cplusplus) && defined(__QUIX_QXIR_IMPL__)
#include <initializer_list>
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum qxir_key_t {
  QQK_UNKNOWN = 0,
  QQK_CRASHGUARD,
  QQV_FASTERROR,
} qxir_key_t;

typedef enum qxir_val_t {
  QQV_UNKNOWN = 0,
  QQV_TRUE,
  QQV_FALSE,
  QQV_ON = QQV_TRUE,
  QQV_OFF = QQV_FALSE,
} qxir_val_t;

///==========================================================================///

struct qxir_conf_t;
typedef struct qxir_conf_t qxir_conf_t;

#if defined(__cplusplus) && defined(__QUIX_QXIR_IMPL__)
}
typedef struct qxir_setting_t {
  qxir_key_t key;
  qxir_val_t value;

#if defined(__cplusplus) && defined(__QUIX_QXIR_IMPL__)
  constexpr qxir_setting_t(const std::initializer_list<int> &list)
      : key(static_cast<qxir_key_t>(list.begin()[0])),
        value(static_cast<qxir_val_t>(list.begin()[1])) {}
#endif
} qxir_setting_t;

extern "C" {
#else

typedef struct qxir_setting_t {
  qxir_key_t key;
  qxir_val_t value;
} qxir_setting_t;

#endif

/**
 * @brief Create a new configuration object.
 *
 * @param use_defaults If true, the configuration object will be initialized
 * with default values. Otherwise, an empty configuration object will be
 * created.
 *
 * @return A pointer to the newly created configuration object on success OR
 * NULL on failure.
 *
 * @warning The caller is responsible for freeing the configuration object using
 * the `qxir_conf_free` function. Do NOT use the `free()` function to free
 * the configuration object directly.
 *
 * @note The default configuration values are specified in the documentation
 * and in the source code. See the `qxir_conf_getopts` function implementation
 * for more information.
 *
 * @note The exact values of the default configuration options are subject to
 * change in future versions of the library. A best effort is made to ensure that
 * the default values are reasonable and **SECURE** for the language sandbox, with a stronger
 * emphasis on security.
 *
 * @note This function is thread-safe.
 */
qxir_conf_t *qxir_conf_new(bool use_defaults);

/**
 * @brief Free a configuration object.
 *
 * @param conf A pointer to the configuration object to free or NULL.
 *
 *
 * @warning The caller for ensuring that the configuration object is not used
 * after it has been freed. This includes ensuring that no other threads or instances
 * have references to the configuration object.
 *
 * @note It is safe to pass NULL to this function.
 *
 * @note This function is thread-safe.
 */
void qxir_conf_free(qxir_conf_t *conf);

/**
 * @brief Set a configuration option for the qxir.
 *
 * @param conf A pointer to the configuration object to modify.
 * @param key The configuration option to set.
 * @param value The value to set the configuration option to.
 *
 * @return True if the configuration option was set successfully OR false if an
 * error occurred.
 *
 * @note The semantics of the configuration change will be validated on every
 * call to this function. If the configuration change causes a known issue, the
 * function will return false and the configuration will not be changed. This check is not
 * guaranteed to catch all issues, but it is a best effort to prevent common mistakes.
 *
 * @note This function is thread-safe.
 */
bool qxir_conf_setopt(qxir_conf_t *conf, qxir_key_t key, qxir_val_t value);

/**
 * @brief Get the value of a configuration option for the qxir.
 *
 * @param conf A pointer to the configuration object to query.
 * @param key The configuration option to query.
 * @param value A pointer to a variable to store the value of the configuration
 * option or NULL.
 *
 * @return True if the configuration option was found, false if the configuration
 * option was not found.
 *
 * @note This function is thread-safe.
 */
bool qxir_conf_getopt(qxir_conf_t *conf, qxir_key_t key, qxir_val_t *value);

/**
 * @brief Get readonly access to the configuration options.
 *
 * @param conf A pointer to the configuration object to query.
 * @param count A pointer to a variable to store the number of configuration
 * options.
 *
 * @return A pointer to an array of configuration options on success OR NULL
 * on failure.
 *
 * @note The caller should not modify the configuration options directly. If
 * the caller needs to modify the configuration options, they should use the
 * `qxir_conf_setopt` function.
 *
 * @note The caller should not free the configuration options array. The
 * configuration options array is owned by the configuration object and will be
 * freed when the configuration object is freed.
 *
 * @warning The returned pointer is only valid until the next call to this function within this
 * thread or this thread exits (thread-local storage).
 *
 * @note This function is thread-safe.
 */
const qxir_setting_t *qxir_conf_getopts(qxir_conf_t *conf, size_t *count);

/**
 * @brief Clear all configuration options from the configuration object.
 *
 * @param conf A pointer to the configuration object to clear.
 *
 * @note This function is like `qxir_conf_new` with the `use_defaults` parameter
 * set to false. The configuration object will be empty (and likely invalid if used dry).
 * @note This function is thread-safe.
 */
void qxir_conf_clear(qxir_conf_t *conf);

/**
 * @brief Dump the configuration options to a stream.
 *
 * @param conf A pointer to the configuration object to dump.
 * @param stream A pointer to the stream to dump the configuration options to.
 * @param field_delim The delimiter to use between the field and the value.
 * @param line_delim The delimiter to use between each configuration option.
 *
 * @return The number of bytes written to the stream on success OR 0 on failure.
 *
 * @note This function is thread-safe.
 */
size_t qxir_conf_dump(qxir_conf_t *conf, FILE *stream, const char *field_delim,
                      const char *line_delim);

#ifdef __cplusplus
}
#endif

#endif  // __QUIX_QXIR_CONFIG_H__