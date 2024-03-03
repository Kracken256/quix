#include <error/message.h>
#include <error/exceptions.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

using namespace libj;

#define STRING_BUFFER_SIZE 4096

static bool __G_is_color_enabled = getenv("JCC_COLOR") == nullptr;

static void push_message_to_job(jcc_job_t &job, Err type, const std::string &message)
{
    job.m_result->m_feedback.m_messages = (jcc_msg_t **)realloc(job.m_result->m_feedback.m_messages, (job.m_result->m_feedback.m_count + 1) * sizeof(jcc_msg_t *));
    jcc_msg_t *msg = (jcc_msg_t *)malloc(sizeof(jcc_msg_t));
    msg->line = 0;
    msg->column = 0;
    msg->message = strdup(message.c_str());
    msg->m_level = (jcc_msg_level_t)type;
    msg->m_allocated = true;
    job.m_result->m_feedback.m_messages[job.m_result->m_feedback.m_count] = msg;
    job.m_result->m_feedback.m_count++;
}

static bool is_color_enabled()
{
#if defined(_WIN32) || defined(_WIN64)
    return false;
#else
    return __G_is_color_enabled;
#endif
}

static std::string make_message_colored(Err type, const std::string &format, va_list args)
{
    std::string msg;

    switch (type)
    {
    case Err::DEBUG:
        msg = "\x1b[49;1mdebug:\x1b[0m " + format;
        break;
    case Err::INFO:
        msg = "\x1b[37;49;1minfo:\x1b[0m \x1b[37;49m" + format;
        break;
    case Err::WARN:
        msg = "\x1b[33;49;1mwarn:\x1b[0m \x1b[37;49;1m" + format;
        break;
    case Err::ERROR:
        msg = "\x1b[31;49;1merror:\x1b[0m \x1b[37;49;1m" + format;
        break;
    case Err::FATAL:
        msg = "\x1b[31;49;1mINTERNAL COMPILER ERROR:\x1b[0m \x1b[37;49;1m" + format;
        break;
    }

    size_t len = msg.size();

    std::string tmp;
    tmp.resize(STRING_BUFFER_SIZE + len);
    len += vsnprintf(&tmp[0], tmp.size() - 1, msg.c_str(), args);
    msg = tmp.substr(0, len);

    return msg + "\x1b[0m";
}

static std::string make_message_nocolor(Err type, const std::string &format, va_list args)
{
    std::string msg;

    switch (type)
    {
    case Err::DEBUG:
        msg = "(debug): " + format;
        break;
    case Err::INFO:
        msg = "(info): " + format;
        break;
    case Err::WARN:
        msg = "(warn): " + format;
        break;
    case Err::ERROR:
        msg = "(ERROR): " + format;
        break;
    case Err::FATAL:
        msg = "(FATAL): " + format;
        break;
    }

    size_t len = msg.size();

    std::string tmp;
    tmp.resize(STRING_BUFFER_SIZE + len);
    len += vsnprintf(&tmp[0], tmp.size() - 1, msg.c_str(), args);
    msg = tmp.substr(0, len);

    return msg;
}

static std::string make_parser_message_colored(const std::string &file, const libj::Token &tok, Err type, const std::string &format, va_list args)
{
    std::string msg = "\x1b[49;1m" + file + ":";

    msg += std::to_string(tok.loc().line) + ":" + std::to_string(tok.loc().col) + ":\x1b[0m ";

    switch (type)
    {
    case Err::DEBUG:
        msg += "\x1b[49;1mdebug:\x1b[0m " + format;
        break;
    case Err::INFO:
        msg += "\x1b[37;49;1minfo:\x1b[0m \x1b[37;49m" + format;
        break;
    case Err::WARN:
        msg += "\x1b[33;49;1mwarn:\x1b[0m \x1b[37;49;1m" + format;
        break;
    case Err::ERROR:
        msg += "\x1b[31;49;1merror:\x1b[0m \x1b[37;49;1m" + format;
        break;
    case Err::FATAL:
        msg += "\x1b[31;49;1mINTERNAL COMPILER ERROR:\x1b[0m \x1b[37;49;1m" + format;
        break;
    }

    size_t len = msg.size();

    std::string tmp;
    tmp.resize(STRING_BUFFER_SIZE + len);
    len += vsnprintf(&tmp[0], tmp.size() - 1, msg.c_str(), args);
    msg = tmp.substr(0, len);

    return msg + "\x1b[0m";
}

static std::string make_parser_message_nocolor(const std::string &file, const libj::Token &tok, Err type, const std::string &format, va_list args)
{
    std::string msg = file + ":";

    msg += std::to_string(tok.loc().line) + ":" + std::to_string(tok.loc().col) + ": ";

    switch (type)
    {
    case Err::DEBUG:
        msg += "(debug): " + format;
        break;
    case Err::INFO:
        msg += "(info): " + format;
        break;
    case Err::WARN:
        msg += "(warn): " + format;
        break;
    case Err::ERROR:
        msg += "(ERROR): " + format;
        break;
    case Err::FATAL:
        msg += "(FATAL): " + format;
        break;
    }

    size_t len = msg.size();

    std::string tmp;
    tmp.resize(STRING_BUFFER_SIZE + len);
    len += vsnprintf(&tmp[0], tmp.size() - 1, msg.c_str(), args);
    msg = tmp.substr(0, len);

    return msg;
}

void libj::message(jcc_job_t &job, Err type, const std::string &format, ...)
{
    va_list args;
    va_start(args, format);
    std::string msg;

    if (is_color_enabled())
        msg = make_message_colored(type, format, args);
    else
        msg = make_message_nocolor(type, format, args);

    va_end(args);

    push_message_to_job(job, type, msg);
}

void libj::parmsg(jcc_job_t &job, const libj::Token &tok, libj::Err type, const std::string &format, ...)
{
    va_list args;
    va_start(args, format);
    std::string msg;
    std::string filename = tok.loc().file;
    if (filename.empty())
        filename = job.m_filename;

    if (is_color_enabled())
        msg = make_parser_message_colored(filename, tok, type, format, args);
    else
        msg = make_parser_message_nocolor(filename, tok, type, format, args);

    va_end(args);

    push_message_to_job(job, type, msg);

    throw libj::ParseException();
}

void libj::prepmsg(jcc_job_t &job, const libj::Token &tok, libj::Err type, const std::string &format, ...)
{
    va_list args;
    va_start(args, format);
    std::string msg;
    std::string filename = tok.loc().file;
    if (filename.empty())
        filename = job.m_filename;

    if (is_color_enabled())
        msg = make_parser_message_colored(filename, tok, type, format, args);
    else
        msg = make_parser_message_nocolor(filename, tok, type, format, args);

    va_end(args);

    push_message_to_job(job, type, msg);

    throw libj::PreprocessorException();
}