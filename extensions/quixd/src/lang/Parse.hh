#pragma once

#include <core/SyncFS.hh>
#include <memory>
#include <optional>
#include <quix-lexer/Classes.hh>
#include <quix-parser/Classes.hh>
#include <unordered_map>

namespace lang {
  class ParseTreeWrapper {
    qlex m_lexer;
    qparser context;
    const qparse::Node* m_root;

  public:
    ParseTreeWrapper();
    ~ParseTreeWrapper();

    bool is_okay() const { return m_root != nullptr; }
    bool from_syncfs(const std::string& uri);

    const qparse::Node* root() const { return m_root; }
    qlex_t* lexer() { return m_lexer.get(); }
  };
  using ParseTree = std::shared_ptr<ParseTreeWrapper>;

  class ParseTreeCache {
    std::unordered_map<std::string, std::pair<SyncFS::Digest, ParseTree>> m_cache;
    size_t m_cache_size = DEFAULT_CACHE_LIMIT;

  public:
    constexpr static size_t DEFAULT_CACHE_LIMIT = 1024 * 1024 * 10;  // 10 MB

    static ParseTreeCache& the();

    std::optional<ParseTree> get(std::string_view uri, bool permit_outdated = false) const;

    void clear();
    void set_cache_limit(size_t max_bytes);
  };
}  // namespace lang
