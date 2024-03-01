#include <jcc.h>
#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <openssl/rand.h>

#include <llvm-ctx.hpp>
#include <generate.hpp>
#include <lex.hpp>
#include <message.hpp>
#include <parse.hpp>

#define LIB_EXPORT extern "C" __attribute__((visibility("default")))

static void *safe_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        std::cerr << "error: out of memory" << std::endl;
        exit(1);
    }
    return ptr;
}

static void *safe_realloc(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr)
    {
        std::cerr << "error: out of memory" << std::endl;
        exit(1);
    }
    return new_ptr;
}

static char *safe_strdup(const char *str)
{
    char *new_str = strdup(str);
    if (!new_str)
    {
        std::cerr << "error: out of memory" << std::endl;
        exit(1);
    }
    return new_str;
}

static jcc_uuid_t jcc_uuid()
{
    jcc_uuid_t uuid;
    if (RAND_bytes((unsigned char *)&uuid, sizeof(jcc_uuid_t)) != 1)
    {
        uuid.m_high = (uint64_t)rand() << 32 | rand();
        uuid.m_low = (uint64_t)rand() << 32 | rand();
    }
    return uuid;
}

LIB_EXPORT jcc_job_t *jcc_new()
{
    jcc_job_t *job = (jcc_job_t *)safe_malloc(sizeof(jcc_job_t));
    memset(job, 0, sizeof(jcc_job_t));

    job->m_id = jcc_uuid();

    job->m_inner = new libj::LLVMContext();

    return job;
}

LIB_EXPORT bool jcc_dispose(jcc_job_t *job)
{
    if (!job)
        return false;

    for (uint32_t i = 0; i < job->m_options.m_count; i++)
    {
        jcc_option_t *option = job->m_options.m_options[i];
        if (!option)
            continue;

        if (option->m_u)
            free((void *)option->m_u);
        if (option->m_v)
            free((void *)option->m_v);

        option->m_u = nullptr;
        option->m_v = nullptr;
        free(option);

        job->m_options.m_options[i] = nullptr;
    }

    if (job->m_options.m_options)
        free(job->m_options.m_options);
    job->m_options.m_count = 0;
    job->m_options.m_options = nullptr;

    if (job->m_result)
    {
        for (uint32_t i = 0; i < job->m_result->m_feedback.m_count; i++)
        {
            jcc_msg_t *msg = job->m_result->m_feedback.m_messages[i];
            if (!msg)
                continue;

            if (msg->message)
                free((void *)msg->message);

            msg->message = nullptr;
            free(msg);

            job->m_result->m_feedback.m_messages[i] = nullptr;
        }

        if (job->m_result->m_feedback.m_messages)
            free(job->m_result->m_feedback.m_messages);
        job->m_result->m_feedback.m_count = 0;
        job->m_result->m_feedback.m_messages = nullptr;

        free(job->m_result);
    }

    if (job->m_inner)
        delete (libj::LLVMContext *)job->m_inner;

    if (job->m_filename)
    {
        free((void *)job->m_filename);
        job->m_filename = nullptr;
    }

    memset(job, 0, sizeof(jcc_job_t));

    free(job);

    return true;
}

LIB_EXPORT void jcc_add_option(jcc_job_t *job, const char *name, const char *value, bool enabled)
{
    jcc_option_t *option;

    if (!job || !name)
        return;

    option = (jcc_option_t *)safe_malloc(sizeof(jcc_option_t));
    option->m_enabled = enabled;

    option->m_u = safe_strdup(name);

    if (value)
        option->m_v = safe_strdup(value);
    else
        option->m_v = nullptr;

    job->m_options.m_options = (jcc_option_t **)safe_realloc(job->m_options.m_options, (job->m_options.m_count + 1) * sizeof(jcc_option_t *));
    job->m_options.m_options[job->m_options.m_count++] = option;
}

LIB_EXPORT void jcc_remove_option(jcc_job_t *job, const char *name)
{
    if (!job || !name)
        return;

    for (uint32_t i = 0; i < job->m_options.m_count; i++)
    {
        jcc_option_t *option = job->m_options.m_options[i];
        if (!option)
            continue;

        if (strcmp(option->m_u, name) == 0)
        {
            if (option->m_u)
                free((void *)option->m_u);
            if (option->m_v)
                free((void *)option->m_v);

            option->m_u = nullptr;
            option->m_v = nullptr;
            free(option);

            job->m_options.m_options[i] = job->m_options.m_options[job->m_options.m_count - 1];
            job->m_options.m_options[job->m_options.m_count - 1] = nullptr;
            job->m_options.m_count--;

            break;
        }
    }
}

LIB_EXPORT void jcc_set_input(jcc_job_t *job, FILE *in, const char *filename)
{
    if (!job || !in || !filename)
        return;

    job->m_in = in;
    job->m_filename = safe_strdup(filename);
}

LIB_EXPORT void jcc_set_output(jcc_job_t *job, FILE *out)
{
    if (!job || !out)
        return;

    job->m_out = out;
}

static std::string get_datetime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

static std::string base64_encode(const std::string &in)
{
    std::string out;

    int val = 0, valb = -6;
    for (unsigned char c : in)
    {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0)
        {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    return out;
}

LIB_EXPORT bool jcc_run(jcc_job_t *job)
{
    if (!job->m_in || !job->m_out)
        return false;

    // Allocate memory for the result
    job->m_result = (jcc_result_t *)safe_malloc(sizeof(jcc_result_t));
    memset(job->m_result, 0, sizeof(jcc_result_t));

    libj::message(*job, libj::Err::DEBUG, "Starting jcc run @ %s", get_datetime().c_str());

    // Create an AST before goto statements
    libj::AST ast;

    ///=========================================
    /// BEGIN: LEXER
    ///=========================================
    libj::Lexer lexer;
    if (!lexer.set_source(job->m_in))
    {
        libj::message(*job, libj::Err::ERROR, "failed to set source");
        goto error;
    }
    ///=========================================
    /// END: LEXER
    ///=========================================

    ///=========================================
    /// BEGIN: PARSER
    ///=========================================
    libj::Parser parser;
    libj::message(*job, libj::Err::DEBUG, "Building AST 1");
    if (!parser.parse(*job, lexer, ast))
        goto error;
    libj::message(*job, libj::Err::DEBUG, "Finished building AST 1");
    libj::message(*job, libj::Err::DEBUG, "Dumping AST 1 (base64 JSON): %s",
                  base64_encode(ast.to_json()).c_str());
    ///=========================================
    /// END: PARSER
    ///=========================================

    ///=========================================
    /// BEGIN: GENERATOR
    ///=========================================
    libj::Generator gen;
    libj::message(*job, libj::Err::DEBUG, "Generating output");
    if (!gen.synthesize_LLVM_IR(*job, ast))
    {
        libj::message(*job, libj::Err::ERROR, "failed to generate output");
        goto error;
    }
    ///=========================================
    /// END: GENERATOR
    ///=========================================

    libj::message(*job, libj::Err::DEBUG, "Finished jcc run @ %s", get_datetime().c_str());

    return true;

error:
    libj::message(*job, libj::Err::ERROR, "Compilation failed");
    libj::message(*job, libj::Err::DEBUG, "Finished jcc run @ %s", get_datetime().c_str());
    return false;
}

LIB_EXPORT const jcc_result_t *jcc_result(jcc_job_t *job)
{
    jcc_result_t *result = job->m_result;

    if (job->m_debug)
        return result;

    // remove debug messages
    uint32_t i = 0;

    while (i < result->m_feedback.m_count)
    {
        jcc_msg_t *msg = result->m_feedback.m_messages[i];
        if (msg->m_level != JCC_DEBUG)
        {
            i++;
            continue;
        }

        if (msg->message)
            free((void *)msg->message);
        msg->message = nullptr;
        free(msg);

        memmove(&result->m_feedback.m_messages[i], &result->m_feedback.m_messages[i + 1], (result->m_feedback.m_count - i - 1) * sizeof(jcc_msg_t *));
        result->m_feedback.m_count--;
    }

    if (result->m_feedback.m_count == 0)
    {
        free(result->m_feedback.m_messages);
        result->m_feedback.m_messages = nullptr;
    }
    else
    {
        result->m_feedback.m_messages = (jcc_msg_t **)safe_realloc(result->m_feedback.m_messages, result->m_feedback.m_count * sizeof(jcc_msg_t *));
    }

    return result;
}
