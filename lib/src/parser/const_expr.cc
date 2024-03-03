#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>
#include <stack>

using namespace libj;

bool libj::parse_const_expr(jcc_job_t &job, std::shared_ptr<libj::Scanner> scanner, Token terminator, std::shared_ptr<libj::ConstExprNode> &node)
{
    std::stack<std::shared_ptr<libj::ConstExprNode>> stack;

    while (true)
    {
        auto tok = scanner->peek();
        if (tok.type() == TokenType::Eof)
            return false;

        if (tok == terminator)
        {
            if (stack.size() != 1)
            {
                PARMSG(tok, libj::Err::ERROR, "Expected a single expression");
                return false;
            }

            node = stack.top();
            return true;
        }

        scanner->next();

        switch (tok.type())
        {
        case TokenType::IntegerLiteral:
            stack.push(std::make_shared<libj::IntegerLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::FloatingLiteral:
            stack.push(std::make_shared<libj::FloatLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::StringLiteral:
            stack.push(std::make_shared<libj::StringLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::CharLiteral:
            stack.push(std::make_shared<libj::CharLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::Punctor:
            switch (std::get<Punctor>(tok.val()))
            {
            case Punctor::OpenParen:
            {
                std::shared_ptr<libj::ConstExprNode> expr;
                if (!parse_const_expr(job, scanner, terminator, expr))
                    return false;
                stack.push(expr);
                continue;
            }
            case Punctor::CloseParen:
            {
                if (stack.size() != 1)
                {
                    PARMSG(tok, libj::Err::ERROR, "Expected a single expression");
                    return false;
                }

                node = stack.top();
                stack.pop();
                return true;
            }
            default:
                PARMSG(tok, libj::Err::ERROR, "Unexpected token %s 2",  tok.serialize().c_str());
                return false;
            }
            break;
        case TokenType::Operator:
        {
            auto op = std::get<Operator>(tok.val());
            std::shared_ptr<libj::ConstExprNode> expr;
            if (!parse_const_expr(job, scanner, terminator, expr))
                return false;

            if (stack.empty())
            {
                // Unary operator
                stack.push(std::make_shared<libj::ConstUnaryExprNode>(op, expr));
                continue;
            }
            else if (stack.size() == 1)
            {
                // Binary operator
                auto left = stack.top();
                stack.pop();
                stack.push(std::make_shared<libj::ConstBinaryExprNode>(op, left, expr));
                continue;
            }
            else
            {
                PARMSG(tok, libj::Err::ERROR, "Unexpected token %s",  tok.serialize().c_str());
                return false;
            }
            break;
        }
        default:
            PARMSG(tok, libj::Err::ERROR, "Unexpected token %s",  tok.serialize().c_str());
            return false;
        }
    }

    return false;
}