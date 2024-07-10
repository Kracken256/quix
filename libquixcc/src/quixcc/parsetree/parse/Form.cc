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
#include <quixcc/core/Logger.h>
#include <quixcc/parsetree/Parser.h>

using namespace libquixcc;

bool libquixcc::parse_form(quixcc_cc_job_t &job, libquixcc::Scanner *scanner,
                           std::shared_ptr<libquixcc::StmtNode> &node) {
  Token tok = scanner->next();
  bool has_parens = false;
  if (tok.is<Punctor>(OpenParen)) {
    tok = scanner->next();
    has_parens = true;
  }

  if (tok.type() != tName) {
    LOG(ERROR) << core::feedback[FORM_EXPECTED_IDENTIFIER] << tok << std::endl;
    return false;
  }

  std::string var = tok.as<std::string>();

  tok = scanner->next();
  if (!tok.is<Operator>(In)) {
    LOG(ERROR) << core::feedback[FORM_EXPECTED_IN] << tok << std::endl;
    return false;
  }

  std::shared_ptr<ExprNode> expr;
  if (has_parens) {
    if (!parse_expr(job, scanner, {Token(tPunc, CloseParen)}, expr)) {
      LOG(ERROR) << core::feedback[FORM_EXPECTED_EXPR] << tok << std::endl;
      return false;
    }
    tok = scanner->next();
    if (!tok.is<Punctor>(CloseParen)) {
      LOG(ERROR) << core::feedback[FORM_EXPECTED_CLOSE_PAREN] << tok
                 << std::endl;
      return false;
    }
  } else {
    if (!parse_expr(job, scanner,
                    {Token(tPunc, OpenBrace), Token(tOper, Arrow)}, expr)) {
      LOG(ERROR) << core::feedback[FORM_EXPECTED_EXPR] << tok << std::endl;
      return false;
    }
  }

  tok = scanner->peek();

  std::shared_ptr<BlockNode> block;
  if (tok.is<Operator>(Arrow)) {
    scanner->next();
    if (!parse(job, scanner, block, false, true)) {
      LOG(ERROR) << core::feedback[FORM_EXPECTED_BLOCK] << tok << std::endl;
      return false;
    }
  } else {
    if (!parse(job, scanner, block)) {
      LOG(ERROR) << core::feedback[FORM_EXPECTED_BLOCK] << tok << std::endl;
      return false;
    }
  }

  node = std::make_shared<FormStmtNode>(var, expr, block);

  return true;
}