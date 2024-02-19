#include <error.hpp>
#include <stdarg.h>
#include <string.h>

namespace libj
{
    static void push_message_to_job(jcc_job_t &job, Err type, const std::string &message) {
        job.m_result->m_feedback.m_messages = (jcc_msg_t **)realloc(job.m_result->m_feedback.m_messages, (job.m_result->m_feedback.m_count + 1) * sizeof(jcc_msg_t *));
        jcc_msg_t *msg = (jcc_msg_t *)malloc(sizeof(jcc_msg_t));
        msg->line = 0;
        msg->column = 0;
        msg->filename = job.m_filename;
        msg->message = strdup(message.c_str());
        msg->m_level = (jcc_msg_level_t)type;
        msg->m_allocated = true;
        job.m_result->m_feedback.m_messages[job.m_result->m_feedback.m_count] = msg;
        job.m_result->m_feedback.m_count++;
    }

    void message(jcc_job_t &job, Err type, const std::string &format, ...)
    {
        std::string message;

        switch (type)
        {
        case Err::DEBUG:
            message = "[DEBUG] " + format;
            break;
        case Err::INFO:
            message = "[INFO] " + format;
            break;
        case Err::WARN:
            message = "[WARN] " + format;
            break;
        case Err::ERROR:
            message = "[ERROR] " + format;
            break;
        case Err::FATAL:
            message = "[FATAL] " + format;
            break;
        
        default:
            break;
        }

        message.resize(message.size() + 1024);
        va_list args;
        va_start(args, format);
        int n = vsnprintf((char *)message.c_str(), message.size(), format.c_str(), args);
        va_end(args);
        message.resize(n);

        push_message_to_job(job, type, message);
    }
};