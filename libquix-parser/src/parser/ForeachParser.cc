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

#include <parser/Parse.h>

using namespace qparse::parser;
using namespace qparse::diag;

bool qparse::parser::parse_foreach(qparse_t &job, qlex_t *rd, Stmt **node) {
  qlex_tok_t tok = qlex_next(rd);
  bool has_parens = false;

  if (tok.is<qPuncLPar>()) {
    has_parens = true;
    tok = qlex_next(rd);
  }

  if (!tok.is(qName)) {
    syntax(tok, "Expected identifier as index variable in foreach statement");
  }
  std::string first_ident = tok.as_string(rd), second_ident;

  tok = qlex_next(rd);

  if (tok.is<qPuncComa>()) {
    tok = qlex_next(rd);
    if (!tok.is(qName)) {
      syntax(tok, "Expected identifier as value variable in foreach statement");
    }

    second_ident = tok.as_string(rd);

    tok = qlex_next(rd);
  } else {
    second_ident = "_";
  }

  if (!tok.is<qOpIn>()) {
    syntax(tok, "Expected 'in' after value variable in foreach statement");
  }

  Expr *expr = nullptr;
  if (has_parens) {
    if (!parse_expr(job, rd, {qlex_tok_t(qPunc, qPuncRPar)}, &expr) || !expr) {
      syntax(tok, "Expected expression after '(' in foreach statement");
    }
    tok = qlex_next(rd);
    if (!tok.is<qPuncRPar>()) {
      syntax(tok, "Expected ')' after expression in foreach statement");
    }
  } else {
    if (!parse_expr(job, rd, {qlex_tok_t(qPunc, qPuncLCur), qlex_tok_t(qOper, qOpArrow)}, &expr) ||
        !expr) {
      syntax(tok, "Expected expression after 'in' in foreach statement");
    }
  }

  tok = qlex_peek(rd);

  Block *block = nullptr;
  if (tok.is<qOpArrow>()) {
    qlex_next(rd);
    if (!parse(job, rd, &block, false, true)) {
      syntax(tok, "Expected block or statement list after '=>' in foreach statement");
    }
  } else {
    if (!parse(job, rd, &block)) {
      syntax(tok, "Expected block or statement list after '=>' in foreach statement");
    }
  }

  *node = ForeachStmt::get(first_ident, second_ident, expr, block);
  (*node)->set_end_pos(block->get_end_pos());

  return true;
}
