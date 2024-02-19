#include <parse.hpp>
#include <macro.h>
#include <message.hpp>

using namespace libj;

bool libj::parse_type(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::ParseNode> &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libj::Err::ERROR, "Expected identifier in typename");
        return false;
    }

    static std::set<std::string> primitive_types = {
        "u8",
        "u16",
        "u32",
        "u64",
        "i8",
        "i16",
        "i32",
        "i64",
    };

    if (primitive_types.find(std::get<std::string>(tok.val())) == primitive_types.end())
    {
        PARMSG(tok, libj::Err::ERROR, "Unknown primitive type");
        return false;
    }

    if (std::get<std::string>(tok.val()) == "u8")
    {
        node = std::make_shared<U8TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "u16")
    {
        node = std::make_shared<U16TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "u32")
    {
        node = std::make_shared<U32TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "u64")
    {
        node = std::make_shared<U64TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i8")
    {
        node = std::make_shared<I8TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i16")
    {
        node = std::make_shared<I16TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i32")
    {
        node = std::make_shared<I32TypeNode>();
    }
    else if (std::get<std::string>(tok.val()) == "i64")
    {
        node = std::make_shared<I64TypeNode>();
    }
    else
    {
        PARMSG(tok, libj::Err::ERROR, "Unknown type");
        return false;
    }

    return true;
}
