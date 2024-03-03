#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>

using namespace libj;

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

bool libj::parse_type(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, std::shared_ptr<libj::TypeNode> &node)
{
    Token tok = scanner->next();
    if (tok.type() == TokenType::Identifier)
    {
        if (primitive_types.contains(std::get<std::string>(tok.val())))
        {
            node = primitive_types[std::get<std::string>(tok.val())];
            return true;
        }
        else
        {
            node = std::make_shared<UserTypeNode>(std::get<std::string>(tok.val()));
            return true;
        }
    }
    else if (tok.type() == TokenType::Punctor && std::get<Punctor>(tok.val()) == Punctor::OpenBracket)
    {
        // Array type
        // syntax [type; size]
        std::shared_ptr<TypeNode> type;
        if (!parse_type(job, scanner, type))
        {
            PARMSG(tok, libj::Err::ERROR, feedback[TYPE_EXPECTED_TYPE]);
            return false;
        }

        tok = scanner->next();
        if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::Semicolon)
        {
            PARMSG(tok, libj::Err::ERROR, feedback[TYPE_EXPECTED_SEMICOLON]);
            return false;
        }

        std::shared_ptr<ConstExprNode> size;
        if (!parse_const_expr(job, scanner, Token(TokenType::Punctor, Punctor::CloseBracket), size))
        {
            PARMSG(tok, libj::Err::ERROR, feedback[TYPE_EXPECTED_CONST_EXPR]);
            return false;
        }

        tok = scanner->next();
        if (tok.type() != TokenType::Punctor || std::get<Punctor>(tok.val()) != Punctor::CloseBracket)
        {
            PARMSG(tok, libj::Err::ERROR, feedback[TYPE_EXPECTED_CLOSE_BRACKET]);
            return false;
        }

        node = std::make_shared<ArrayTypeNode>(type, size);
        return true;
    }
    else
    {
        PARMSG(tok, libj::Err::ERROR, feedback[TYPE_EXPECTED_IDENTIFIER_OR_BRACKET]);
        return false;
    }
}
