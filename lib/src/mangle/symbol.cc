#include <mangle/symbol.h>

#include <parse/nodes/nodes.h>

const std::string abiprefix = "_ZJ0";

static std::string serialize_ns(const std::string &ns)
{
    std::string s;

    for (size_t i = 0; i < ns.size(); i++)
    {
        if (ns[i] == ':')
        {
            s += "_";
            i++;
        }
        else if (ns[i] == '_')
        {
            s += "__";
        }
        else
        {
            s += ns[i];
        }
    }

    return s;
}

static std::string deserialize_ns(const std::string &ns)
{
    std::string s;

    for (size_t i = 0; i < ns.size(); i++)
    {
        if (ns[i] == '_')
        {
            if (ns[i + 1] == '_')
            {
                s += "_";
                i++;
            }
            else
            {
                s += ":";
                i++;
            }
        }
        else
        {
            s += ns[i];
        }
    }

    return s;
}

static std::string serialize_type(const libj::TypeNode *type)
{
    using namespace libj;

    static std::map<libj::NodeType, std::string> basic_typesmap = {
        {NodeType::U8TypeNode, "u0"},
        {NodeType::U16TypeNode, "u1"},
        {NodeType::U32TypeNode, "u2"},
        {NodeType::U64TypeNode, "u3"},
        {NodeType::I8TypeNode, "i0"},
        {NodeType::I16TypeNode, "i1"},
        {NodeType::I32TypeNode, "i2"},
        {NodeType::I64TypeNode, "i3"},
        {NodeType::F32TypeNode, "f0"},
        {NodeType::F64TypeNode, "f1"},
        {NodeType::BoolTypeNode, "b"},
        {NodeType::CharTypeNode, "c"},
        {NodeType::StringTypeNode, "s"},
        {NodeType::VoidTypeNode, "v"},
    };

    if (basic_typesmap.contains(type->ntype))
        return basic_typesmap[type->ntype];

    return "";
}

static bool deserialize_type(const std::string &type, std::shared_ptr<libj::TypeNode> out)
{
    using namespace libj;

    static std::map<std::string, std::shared_ptr<TypeNode>> basic_typesmap = {
        {"u0", std::make_shared<U8TypeNode>()},
        {"u1", std::make_shared<U16TypeNode>()},
        {"u2", std::make_shared<U32TypeNode>()},
        {"u3", std::make_shared<U64TypeNode>()},
        {"i0", std::make_shared<I8TypeNode>()},
        {"i1", std::make_shared<I16TypeNode>()},
        {"i2", std::make_shared<I32TypeNode>()},
        {"i3", std::make_shared<I64TypeNode>()},
        {"f0", std::make_shared<F32TypeNode>()},
        {"f1", std::make_shared<F64TypeNode>()},
        {"b", std::make_shared<BoolTypeNode>()},
        {"c", std::make_shared<CharTypeNode>()},
        {"s", std::make_shared<StringTypeNode>()},
        {"v", std::make_shared<VoidTypeNode>()},
    };

    if (basic_typesmap.contains(type))
    {
        out = basic_typesmap[type];
        return true;
    }

    return false;
}

static std::string wrap_tag(const std::string &tag)
{
    return std::to_string(tag.size()) + tag;
}

static bool unwrap_tags(const std::string &input, std::vector<std::string> &out)
{
    size_t i = 0;
    while (i < input.size())
    {
        std::string len;
        while (std::isdigit(input[i]))
        {
            len += input[i];
            i++;
        }

        if (len.empty())
            return false;

        size_t l = std::stoi(len);
        out.push_back(input.substr(i, l));
        i += l;
    }

    return true;
}

std::string libj::Symbol::mangle(std::shared_ptr<libj::DeclNode> node, const std::string &prefix)
{
    return mangle(node.get(), prefix);
}

std::string libj::Symbol::mangle(const libj::DeclNode *node, const std::string &prefix)
{
    std::string res = abiprefix;

    switch (node->ntype)
    {
    case libj::NodeType::VarDeclNode:
    {
        res += "v";
        auto var = static_cast<const libj::VarDeclNode *>(node);
        res += wrap_tag(serialize_ns(prefix + var->m_name));
        res += wrap_tag(serialize_type(var->m_type.get()));

        std::string flags;
        if (var->m_is_mut)
            flags += "m";
        if (var->m_is_thread_local)
            flags += "t";
        if (var->m_is_static)
            flags += "s";
        if (var->m_is_deprecated)
            flags += "d";

        res += wrap_tag(flags);

        return res;
    }

    default:
        break;
    }

    return "";
}

std::shared_ptr<libj::DeclNode> libj::Symbol::demangle(const std::string &mangled)
{
    std::shared_ptr<libj::DeclNode> res;
    std::string input;

    if (!mangled.starts_with(abiprefix))
        return nullptr;

    input = mangled.substr(abiprefix.size());

    try
    {
        std::vector<std::string> parts;

        switch (input[0])
        {
        case 'v':
        {
            if (!unwrap_tags(input.substr(1), parts))
                return nullptr;

            auto var = std::make_shared<libj::VarDeclNode>();
            var->m_name = deserialize_ns(parts[0]);
            if (!deserialize_type(parts[1], var->m_type))
                return nullptr;

            std::string flags = parts[2];
            for (size_t i = 0; i < flags.size(); i++)
            {
                switch (flags[i])
                {
                case 'm':
                    var->m_is_mut = true;
                    break;
                case 't':
                    var->m_is_thread_local = true;
                    break;
                case 's':
                    var->m_is_static = true;
                    break;
                case 'd':
                    var->m_is_deprecated = true;
                    break;
                default:
                    return nullptr;
                }
            }

            return var;
        }
        break;

        default:
            break;
        }
    }
    catch (std::exception &e)
    {
        return nullptr;
    }

    return nullptr;
}
