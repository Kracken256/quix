#ifndef __J_CC_OPTIMIZE_EXPR_FOLDER_H__
#define __J_CC_OPTIMIZE_EXPR_FOLDER_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>

#include <parse/parser.h>

namespace libjcc::optimize
{
    void fold_expr(std::shared_ptr<libjcc::AST> ast);
}

#endif // __J_CC_OPTIMIZE_EXPR_FOLDER_H__