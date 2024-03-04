#ifndef __J_CC_MANGLE_SYMBOL_H__
#define __J_CC_MANGLE_SYMBOL_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <memory>
#include <string>
#include <parse/nodes/basic.h>

namespace libjcc
{
    class Symbol
    {
        Symbol() = delete;

    public:
        static std::string mangle(const std::shared_ptr<DeclNode> node, const std::string &prefix = "");
        static std::string mangle(const DeclNode *node, const std::string &prefix = "");

        static std::shared_ptr<DeclNode> demangle(const std::string &mangled);
    };
}

#endif // __J_CC_MANGLE_SYMBOL_H__