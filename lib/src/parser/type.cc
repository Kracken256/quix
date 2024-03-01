#include <parse/parser.hpp>
#include <macro.h>
#include <error/message.hpp>

using namespace libj;

bool libj::parse_type(jcc_job_t &job, libj::Lexer &lexer, std::shared_ptr<libj::ParseNode> &node)
{
    Token tok = lexer.next();
    if (tok.type() != TokenType::Identifier)
    {
        PARMSG(tok, libj::Err::ERROR, "Expected identifier in typename");
        return false;
    }

    static std::map<std::string, std::shared_ptr<TypeNode>> primitive_types = {
        {"u8", std::make_shared<U8TypeNode>()},
        {"u16", std::make_shared<U16TypeNode>()},
        {"u32", std::make_shared<U32TypeNode>()},
        {"u64", std::make_shared<U64TypeNode>()},
        {"i8", std::make_shared<I8TypeNode>()},
        {"i16", std::make_shared<I16TypeNode>()},
        {"i32", std::make_shared<I32TypeNode>()},
        {"i64", std::make_shared<I64TypeNode>()},
        {"f32", std::make_shared<F32TypeNode>()},
        {"f64", std::make_shared<F64TypeNode>()},
        {"bool", std::make_shared<BoolTypeNode>()},
        {"char", std::make_shared<CharTypeNode>()},
        {"string", std::make_shared<StringTypeNode>()},
        {"void", std::make_shared<VoidTypeNode>()}};

    if (primitive_types.find(std::get<std::string>(tok.val())) == primitive_types.end())
    {
        PARMSG(tok, libj::Err::ERROR, "Unknown primitive type");
        return false;
    }

    for (auto &type : primitive_types)
    {
        if (type.first == std::get<std::string>(tok.val()))
        {
            node = type.second;
            return true;
        }
    }

    PARMSG(tok, libj::Err::ERROR, "Unknown type");
    return false;
}
