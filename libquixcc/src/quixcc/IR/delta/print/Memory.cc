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

#include <quixcc/IR/delta/Memory.h>

bool libquixcc::ir::delta::Assign::print_impl(std::ostream &os,
                                              PState &state) const {
  os << "(";
  if (!var->print(os, state)) return false;

  os << " ";

  for (uint64_t i = 0; i < rank; i++) os << "*";

  os << "= ";

  if (!value->print(os, state)) return false;

  os << ")";

  return true;
}

bool libquixcc::ir::delta::PostInc::print_impl(
    std::ostream &os, libquixcc::ir::PState &state) const {
  os << "(";
  if (!var->print(os, state)) return false;
  os << "++)";
  return true;
}

bool libquixcc::ir::delta::PostDec::print_impl(
    std::ostream &os, libquixcc::ir::PState &state) const {
  os << "(";
  if (!var->print(os, state)) return false;
  os << "--)";
  return true;
}

bool libquixcc::ir::delta::AddressOf::print_impl(
    std::ostream &os, libquixcc::ir::PState &state) const {
  os << "(&";
  if (!lhs->print(os, state)) return false;
  os << ")";

  return true;
}

bool libquixcc::ir::delta::Deref::print_impl(
    std::ostream &os, libquixcc::ir::PState &state) const {
  os << "(*";
  if (!lhs->print(os, state)) return false;
  os << ")";

  return true;
}

bool libquixcc::ir::delta::Member::print_impl(
    std::ostream &os, libquixcc::ir::PState &state) const {
  os << "(";
  if (!lhs->print(os, state)) return false;

  os << "." << field;

  os << ")";

  return true;
}

bool libquixcc::ir::delta::Index::print_impl(std::ostream &os,
                                             PState &state) const {
  os << "(";
  if (!expr->print(os, state)) return false;
  os << "[";
  if (!index->print(os, state)) return false;
  os << "]";
  os << ")";

  return true;
}