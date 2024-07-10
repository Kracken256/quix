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

#ifndef __QUIXCC_PARSE_NODES_CONST_EXPR_H__
#define __QUIXCC_PARSE_NODES_CONST_EXPR_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <quixcc/lexer/Token.h>
#include <quixcc/llvm/LLVMWrapper.h>
#include <quixcc/parsetree/nodes/BasicNodes.h>
#include <quixcc/parsetree/nodes/LiteralNode.h>

#include <memory>
#include <string>
#include <vector>

namespace libquixcc {
class ConstUnaryExprNode : public ConstExprNode {
 public:
  ConstUnaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &expr)
      : m_op(op), m_expr(expr) {
    ntype = NodeType::ConstUnaryExprNode;
  }

  Operator m_op;
  std::shared_ptr<ConstExprNode> m_expr;
};

class ConstPostUnaryExprNode : public ConstExprNode {
 public:
  ConstPostUnaryExprNode(Operator op,
                         const std::shared_ptr<ConstExprNode> &expr)
      : m_op(op), m_expr(expr) {
    ntype = NodeType::ConstPostUnaryExprNode;
  }

  Operator m_op;
  std::shared_ptr<ConstExprNode> m_expr;
};

class ConstBinaryExprNode : public ConstExprNode {
 public:
  ConstBinaryExprNode(Operator op, const std::shared_ptr<ConstExprNode> &lhs,
                      const std::shared_ptr<ConstExprNode> &rhs)
      : m_op(op), m_lhs(lhs), m_rhs(rhs) {
    ntype = NodeType::ConstBinaryExprNode;
  }

  Operator m_op;
  std::shared_ptr<ConstExprNode> m_lhs;
  std::shared_ptr<ConstExprNode> m_rhs;
};
}  // namespace libquixcc

#endif  // __QUIXCC_PARSE_NODES_CONST_EXPR_H__