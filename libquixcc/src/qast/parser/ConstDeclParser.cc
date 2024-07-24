////////////////////////////////////////////////////////////////////////////////
///                                                                          ///
///  ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
///  ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
///    ░▒▓█▓▒░                                                               ///
///     ░▒▓██▓▒░                                                             ///
///                                                                          ///
///   * QUIX LANG COMPILER - The official compiler for the Quix language.    ///
///   * Copyright (C) 2024 Wesley C. Jones                                   ///
///                                                                          ///
///   The QUIX Compiler Suite is free software; you can redistribute it or   ///
///   modify it under the terms of the GNU Lesser General Public             ///
///   License as published by the Free Software Foundation; either           ///
///   version 2.1 of the License, or (at your option) any later version.     ///
///                                                                          ///
///   The QUIX Compiler Suite is distributed in the hope that it will be     ///
///   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of ///
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      ///
///   Lesser General Public License for more details.                        ///
///                                                                          ///
///   You should have received a copy of the GNU Lesser General Public       ///
///   License along with the QUIX Compiler Suite; if not, see                ///
///   <https://www.gnu.org/licenses/>.                                       ///
///                                                                          ///
////////////////////////////////////////////////////////////////////////////////

#define QUIXCC_INTERNAL

#include <core/Macro.h>
#include <qast/Parser.h>
#include <quixcc/core/Logger.h>

using namespace libquixcc::qast::parser;

namespace libquixcc::qast::parser {
  static bool parse_decl(quixcc_cc_job_t &job, Token tok, Scanner *scanner,
                         std::pair<std::string, Type *> &decl) {
    std::string name = tok.as_string();

    tok = scanner->peek();
    if (!tok.is<Punctor>(Colon)) {
      decl = std::make_pair(name, nullptr);
      return true;
    }

    scanner->next();

    Type *type = nullptr;

    if (!parse_type(job, scanner, &type)) {
      LOG(ERROR) << core::feedback[CONST_DECL_TYPE_ERR] << name << tok << std::endl;
      return false;
    }

    decl = std::make_pair(name, type);
    return true;
  }
} // namespace libquixcc::qast::parser

bool libquixcc::qast::parser::parse_const(quixcc_cc_job_t &job, Scanner *scanner,
                                          StmtListItems &nodes) {
  Token tok = scanner->next();

  std::vector<std::pair<std::string, Type *>> decls;
  bool multi_decl = false;
  if (tok.is<Punctor>(OpenBracket)) {
    multi_decl = true;

    while (true) {
      tok = scanner->next();

      std::pair<std::string, Type *> decl;
      if (!parse_decl(job, tok, scanner, decl))
        return false;

      decls.push_back(decl);

      tok = scanner->next();
      if (tok.is<Punctor>(Comma))
        continue;
      else if (tok.is<Punctor>(CloseBracket))
        break;
      else {
        LOG(ERROR) << core::feedback[CONST_DECL_MISSING_PUNCTOR] << decl.first << tok << std::endl;
        return false;
      }
    }
  } else if (tok.is(tName)) {
    // Parse single variable declaration
    std::pair<std::string, Type *> decl;
    if (!parse_decl(job, tok, scanner, decl))
      return false;

    decls.push_back(decl);
  } else {
    LOG(ERROR) << core::feedback[CONST_DECL_MISSING_IDENTIFIER] << tok << std::endl;
    return false;
  }

  if (decls.empty()) {
    LOG(ERROR) << core::feedback[CONST_DECL_MISSING_IDENTIFIER] << tok << std::endl;
    return false;
  }

  tok = scanner->next();
  if (tok.is<Punctor>(Semicolon)) {
    // No initializer
    for (auto &decl : decls) {
      ConstDecl *const_decl = ConstDecl::get(decl.first, decl.second, nullptr);
      nodes.push_back(const_decl);
    }
  } else if (tok.is<Operator>(OpAssign)) {
    if (multi_decl)
      throw std::runtime_error("Initializer not implemented for multiple declarations");

    // Parse initializer
    Expr *init = nullptr;
    if (!parse_expr(job, scanner, {Token(tPunc, Semicolon)}, &init))
      return false;

    tok = scanner->next();
    if (!tok.is<Punctor>(Semicolon)) {
      LOG(ERROR) << core::feedback[CONST_DECL_MISSING_PUNCTOR] << decls[0].first << tok
                 << std::endl;
      return false;
    }

    ConstDecl *const_decl = ConstDecl::get(decls[0].first, decls[0].second, init);
    nodes.push_back(const_decl);
  } else {
    LOG(ERROR) << core::feedback[CONST_DECL_MISSING_PUNCTOR] << tok << std::endl;
    return false;
  }

  return true;
}