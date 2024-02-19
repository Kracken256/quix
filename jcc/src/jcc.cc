#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <jcc.h>

int main(int argc, char *argv[])
{
    std::vector<std::string> args(argv, argv + argc);

    std::string file_in;
    std::string file_out;
    bool debug = false;

    for (size_t i = 1; i < args.size(); i++)
    {
        if (args[i] == "--debug")
        {
            debug = true;
        }
        else if (args[i] == "-o")
        {
            if (i + 1 < args.size())
            {
                file_out = args[i + 1];
                i++;
            }
            else
            {
                std::cerr << "error: missing output file" << std::endl;
                return 1;
            }
        }
        else
        {
            try
            {
                if (std::filesystem::exists(args[i]))
                {
                    file_in = args[i];
                }
                else
                {
                    std::cerr << "error: file not found" << std::endl;
                    return 1;
                }
            }
            catch (std::exception &e)
            {
                std::cerr << "error: " << e.what() << std::endl;
                return 1;
            }
        }
    }

    if (file_in.empty())
    {
        std::cerr << "error: missing input file" << std::endl;
        return 1;
    }

    if (file_out.empty())
    {
        file_out = file_in + ".out";
    }

    FILE *in = fopen(file_in.c_str(), "r");
    if (!in)
    {
        std::cerr << "error: failed to open input file" << std::endl;
        return 1;
    }

    FILE *out = fopen(file_out.c_str(), "w");
    if (!out)
    {
        std::cerr << "error: failed to open output file" << std::endl;
        fclose(in);
        return 1;
    }

    jcc_job_t *job = jcc_new();
    if (!job)
    {
        std::cerr << "error: failed to create job" << std::endl;
        fclose(in);
        fclose(out);
        return 1;
    }
    
    job->m_debug = debug;

    jcc_set_input(job, in, file_in.c_str());
    jcc_set_output(job, out);

    bool success = jcc_run(job);

    fclose(in);
    fclose(out);

    const jcc_result_t *result = jcc_result(job);
    if (!result)
    {
        std::cerr << "error: failed to get result" << std::endl;
        jcc_dispose(job);
        return 1;
    }

    for (uint32_t i = 0; i < result->m_feedback.m_count; i++)
    {
        const jcc_msg_t *msg = result->m_feedback.m_messages[i];

        std::cout << msg->message << std::endl;
    }

    jcc_dispose(job);

    if (!success)
        return 1;

    return 0;
}