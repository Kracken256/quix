#include <parse/parser.h>
#include <macro.h>
#include <error/message.h>
#include <stack>

using namespace libjcc;

bool libjcc::parse_const_expr(jcc_job_t &job, std::shared_ptr<libjcc::Scanner> scanner, Token terminator, std::shared_ptr<libjcc::ConstExprNode> &node)
{
    std::stack<std::shared_ptr<libjcc::ConstExprNode>> stack;

    while (true)
    {
        auto tok = scanner->peek();
        if (tok.type() == TokenType::Eof)
            return false;

        if (tok == terminator)
        {
            if (stack.size() != 1)
            {
                PARMSG(tok, libjcc::Err::ERROR, "Expected a single expression");
                return false;
            }

            node = stack.top();
            return true;
        }

        scanner->next();

        switch (tok.type())
        {
        case TokenType::IntegerLiteral:
            stack.push(std::make_shared<libjcc::IntegerLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::FloatingLiteral:
            stack.push(std::make_shared<libjcc::FloatLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::StringLiteral:
            stack.push(std::make_shared<libjcc::StringLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::CharLiteral:
            stack.push(std::make_shared<libjcc::CharLiteralNode>(std::get<std::string>(tok.val())));
            continue;
        case TokenType::Keyword:
            switch (std::get<Keyword>(tok.val()))
            {
            case Keyword::True:
                stack.push(std::make_shared<libjcc::BoolLiteralNode>(true));
                continue;
            case Keyword::False:
                stack.push(std::make_shared<libjcc::BoolLiteralNode>(false));
                continue;
            default:
                PARMSG(tok, libjcc::Err::ERROR, "Unexpected token %s 1",  tok.serialize().c_str());
                return false;
            }
            break;
        case TokenType::Punctor:
            switch (std::get<Punctor>(tok.val()))
            {
            case Punctor::OpenParen:
            {
                std::shared_ptr<libjcc::ConstExprNode> expr;
                if (!parse_const_expr(job, scanner, terminator, expr))
                    return false;
                stack.push(expr);
                continue;
            }
            case Punctor::CloseParen:
            {
                if (stack.size() != 1)
                {
                    PARMSG(tok, libjcc::Err::ERROR, "Expected a single expression");
                    return false;
                }

                node = stack.top();
                stack.pop();
                return true;
            }
            default:
                PARMSG(tok, libjcc::Err::ERROR, "Unexpected token %s 2",  tok.serialize().c_str());
                return false;
            }
            break;
        case TokenType::Operator:
        {
            auto op = std::get<Operator>(tok.val());
            std::shared_ptr<libjcc::ConstExprNode> expr;
            if (!parse_const_expr(job, scanner, terminator, expr))
                return false;

            if (stack.empty())
            {
                // Unary operator
                stack.push(std::make_shared<libjcc::ConstUnaryExprNode>(op, expr));
                continue;
            }
            else if (stack.size() == 1)
            {
                // Binary operator
                auto left = stack.top();
                stack.pop();
                stack.push(std::make_shared<libjcc::ConstBinaryExprNode>(op, left, expr));
                continue;
            }
            else
            {
                PARMSG(tok, libjcc::Err::ERROR, "Unexpected token %s",  tok.serialize().c_str());
                return false;
            }
            break;
        }
        default:
            PARMSG(tok, libjcc::Err::ERROR, "Unexpected token %s",  tok.serialize().c_str());
            return false;
        }
    }

    return false;
}