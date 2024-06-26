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

#include <IR/Q/Memory.h>

bool libquixcc::ir::q::Assign::print_impl(std::ostream &os,
                                          libquixcc::ir::PState &state) const {
  os << "(";
  if (!lhs->print(os, state)) return false;
  os << "=";
  if (!rhs->print(os, state)) return false;
  os << ")";
  return true;
}

bool libquixcc::ir::q::PostInc::print_impl(std::ostream &os,
                                           libquixcc::ir::PState &state) const {
  os << "(";
  if (!lhs->print(os, state)) return false;
  os << "++)";
  return true;
}

bool libquixcc::ir::q::PostDec::print_impl(std::ostream &os,
                                           libquixcc::ir::PState &state) const {
  os << "(";
  if (!lhs->print(os, state)) return false;
  os << "--)";
  return true;
}

bool libquixcc::ir::q::AddressOf::print_impl(
    std::ostream &os, libquixcc::ir::PState &state) const {
  os << "(&";
  if (!lhs->print(os, state)) return false;
  os << ")";
  return true;
}

bool libquixcc::ir::q::Deref::print_impl(std::ostream &os,
                                         libquixcc::ir::PState &state) const {
  os << "(*";
  if (!lhs->print(os, state)) return false;
  os << ")";
  return true;
}

bool libquixcc::ir::q::Member::print_impl(std::ostream &os,
                                          libquixcc::ir::PState &state) const {
  os << "(";
  if (!lhs->print(os, state)) return false;
  os << "." << field;
  os << ")";
  return true;
}

bool libquixcc::ir::q::Index::print_impl(std::ostream &os,
                                         libquixcc::ir::PState &state) const {
  os << "(";
  if (!lhs->print(os, state)) return false;
  os << "[";
  if (!index->print(os, state)) return false;
  os << "]";
  os << ")";
  return true;
}