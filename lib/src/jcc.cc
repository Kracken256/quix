#include <jcc.h>
#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <openssl/rand.h>

#include <lex.hpp>

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

            if (msg->filename)
                free((void *)msg->filename);
            if (msg->message)
                free((void *)msg->message);

            msg->filename = nullptr;
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

LIB_EXPORT void jcc_set_input(jcc_job_t *job, FILE *in)
{
    if (!job || !in)
        return;

    job->m_in = in;
}

LIB_EXPORT void jcc_set_output(jcc_job_t *job, FILE *out)
{
    if (!job || !out)
        return;

    job->m_out = out;
}

LIB_EXPORT bool jcc_run(jcc_job_t *job)
{
    if (!job->m_in || !job->m_out)
        return false;

    using namespace libj;

    Lexer lexer;
    lexer.set_source(job->m_in);

    /*  DEBUG */

    std::vector<Token> tokens;
    while (true)
    {
        Token token = lexer.next();
        if (token.type() == TokenType::Eof)
            break;
        tokens.push_back(token);
    }

    for (const Token &token : tokens)
    {
        fprintf(job->m_out, "%s\n", token.serialize(true).c_str());
    }


    return true;
}

LIB_EXPORT const jcc_result_t *jcc_result(jcc_job_t *job)
{
    return job->m_result;
}
