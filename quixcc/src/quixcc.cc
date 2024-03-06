#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <quixcc.h>

int main(int argc, char *argv[])
{
    std::vector<std::string> args(argv, argv + argc);

    std::string file_in;
    std::string file_out;
    std::vector<std::pair<std::string, std::string>> switches;

    for (size_t i = 1; i < args.size(); i++)
    {
        if (args[i] == "-o")
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
        else if (args[i].starts_with("-"))
        {
            if (args[i].size() < 2)
            {
                std::cerr << "error: invalid switch" << std::endl;
                return 1;
            }

            char next = args[i][1];
            if (!std::isalpha(next))
            {
                std::cerr << "error: invalid switch" << std::endl;
                return 1;
            }

            if (args[i].size() > 2)
            {
                switches.push_back({args[i].substr(1, 1), args[i].substr(2)});
            }
            else
            {
                switches.push_back({args[i].substr(1, 1), ""});
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

    quixcc_job_t *job = quixcc_new();
    if (!job)
    {
        std::cerr << "error: failed to create job" << std::endl;
        fclose(in);
        fclose(out);
        return 1;
    }

    quixcc_set_input(job, in, file_in.c_str());
    quixcc_set_output(job, out);

    for (const auto &sw : switches)
        quixcc_add_option(job, sw.first.c_str(), sw.second.c_str(), true);

    bool success = quixcc_run(job);

    fclose(in);
    fclose(out);

    const quixcc_result_t *result = quixcc_result(job);
    if (!result)
    {
        std::cerr << "error: failed to get result" << std::endl;
        quixcc_dispose(job);
        std::remove(file_out.c_str());
        return 1;
    }

    for (uint32_t i = 0; i < result->m_feedback.m_count; i++)
    {
        const quixcc_msg_t *msg = result->m_feedback.m_messages[i];

        std::cout << msg->message << std::endl;
    }

    quixcc_dispose(job);

    if (!success)
    {
        std::remove(file_out.c_str());
        return 1;
    }

    try
    {
        std::filesystem::permissions(file_out, std::filesystem::perms::owner_all | std::filesystem::perms::group_all | std::filesystem::perms::others_read | std::filesystem::perms::others_exec);
    }
    catch (std::exception &e)
    {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}