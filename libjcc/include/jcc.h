#ifndef __JCC_H__
#define __JCC_H__

#include <stdint.h>
#include <stdbool.h>
#include <bits/types/FILE.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define JCC_VERSION "0.1.0"
#define JCC_VERSION_MAJOR 0
#define JCC_VERSION_MINOR 1
#define JCC_VERSION_PATCH 0

#define JCC_OK 0

    enum jcc_msg_level_t
    {
        /// @brief Debug message
        JCC_DEBUG,

        /// @brief Information message
        JCC_INFO,

        /// @brief Warning message
        JCC_WARN,

        /// @brief Error message
        JCC_ERROR,

        /// @brief Internal compiler error
        JCC_FATAL
    };

    struct jcc_msg_t
    {
        uint64_t line;
        uint64_t column;
        const char *message;

        /// @brief Message level
        enum jcc_msg_level_t m_level;

        /// @brief Is the message allocated dynamically?
        bool m_allocated;
    };

    struct jcc_feedback_t
    {
        /// @brief Messages
        struct jcc_msg_t **m_messages;

        /// @brief Message count
        uint32_t m_count;
    };

    struct jcc_result_t
    {
        /// @brief Feedback
        struct jcc_feedback_t m_feedback;

        /// @brief Internal flags
        uint32_t m_internal_flags;
    };

    typedef struct jcc_option_t
    {
        /// @brief Identifier
        const char *m_u;

        /// @brief Value
        const char *m_v;
    } jcc_option_t;

    typedef struct jcc_options_t
    {
        /// @brief Options
        jcc_option_t **m_options;

        /// @brief Option count
        uint32_t m_count;
    } jcc_options_t;

    typedef struct jcc_uuid_t
    {
        uint64_t m_low;
        uint64_t m_high;
    } jcc_uuid_t;

#if defined(__cplusplus) && defined(JCC_INTERNAL)
}

#include <map>
#include <string>

typedef struct jcc_job_t
{
    jcc_uuid_t m_id;

    /// @brief Options
    jcc_options_t m_options;

    /// @brief Result
    jcc_result_t *m_result;

    FILE *m_in;
    FILE *m_out;

    const char *m_filename;

    /// @brief Job priority
    uint8_t m_priority;

    /// @brief Internal flags
    uint32_t m_internal_flags;

    /// @brief Internal data
    void *m_inner;

    std::map<std::string, std::string> *m_argset;

    /// @brief User may set to true to enable debug messages
    bool m_debug;
} jcc_job_t;

extern "C"
{
#else
typedef struct jcc_job_t jcc_job_t;
#endif

    /// @brief Create a new compiler job
    /// @return A new compiler job
    /// @note The caller is responsible for disposing the structure
    /// @note The returned structure is in a valid state
    /// @note The returned structure is allocated dynamically
    /// @note This function is thread-safe
    jcc_job_t *jcc_new();

    /// @brief Dispose a compiler job
    /// @param job The compiler job
    /// @note The job is disposed and ALL associated resources are released
    /// @note This function is thread-safe
    /// @note This function is safe to call with NULL
    /// @note This function will return false if the job is in use
    /// @return True if the job was disposed
    bool jcc_dispose(jcc_job_t *job);

    /// @brief Add an option to a compiler job
    /// @param job The compiler job
    /// @param name The option name
    /// @param value The option value
    /// @param enabled Is the option enabled?
    /// @note This function is thread-safe
    /// @note This function is safe to call with NULL
    void jcc_add_option(jcc_job_t *job, const char *name, const char *value, bool enabled);

    /// @brief Remove an option from a compiler job
    /// @param job The compiler job
    /// @param name The option name
    /// @note This function is thread-safe
    /// @note This function is safe to call with NULL
    void jcc_remove_option(jcc_job_t *job, const char *name);

    /// @brief Set the input stream for a compiler job
    /// @param job The compiler job
    /// @param in The input stream
    /// @param filename The input filename (required for error messages)
    /// @note This function is thread-safe
    /// @note This function is safe to call with NULL
    void jcc_set_input(jcc_job_t *job, FILE *in, const char *filename);

    /// @brief Set the output stream for a compiler job
    /// @param job The compiler job
    /// @param out The output stream
    /// @note This function is thread-safe
    /// @note This function is safe to call with NULL
    void jcc_set_output(jcc_job_t *job, FILE *out);

    /// @brief Run a compiler job
    /// @param job The compiler job
    /// @return The result of the job
    /// @note This function is thread-safe
    /// @note This function is safe to call with NULL
    /// @return true if the job completed successfully (the output stream is usable and correct).
    /// @note Use `jcc_status()` for a detailed result
    bool jcc_run(jcc_job_t *job);

    /// @brief Get the result of a compiler job
    /// @param job The compiler job
    /// @return The result of the job
    /// @note This function is thread-safe
    /// @note This function is safe to call with NULL
    /// @note This function will return NULL if the job is still running
    const jcc_result_t *jcc_result(jcc_job_t *job);

#ifdef __cplusplus
}
#endif

#endif // __JCC_H__