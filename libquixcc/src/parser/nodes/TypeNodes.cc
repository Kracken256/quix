////////////////////////////////////////////////////////////////////////////////////
///                                                                              ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///      ░▒▓█▓▒░                                                                 ///
///       ░▒▓██▓▒░                                                               ///
///                                                                              ///
///     * QUIX LANG COMPILER - The official compiler for the Quix language.      ///
///     * Copyright (c) 2024, Wesley C. Jones. All rights reserved.              ///
///     * License terms may be found in the LICENSE file.                        ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#define QUIXCC_INTERNAL

#include <parse/nodes/AllNodes.h>

std::shared_ptr<libquixcc::U8TypeNode> libquixcc::U8TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::U16TypeNode> libquixcc::U16TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::U32TypeNode> libquixcc::U32TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::U64TypeNode> libquixcc::U64TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::I8TypeNode> libquixcc::I8TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::I16TypeNode> libquixcc::I16TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::I32TypeNode> libquixcc::I32TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::I64TypeNode> libquixcc::I64TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::F32TypeNode> libquixcc::F32TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::F64TypeNode> libquixcc::F64TypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::BoolTypeNode> libquixcc::BoolTypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::CharTypeNode> libquixcc::CharTypeNode::m_instance = nullptr;
std::shared_ptr<libquixcc::VoidTypeNode> libquixcc::VoidTypeNode::m_instance = nullptr;

std::shared_ptr<libquixcc::StringTypeNode> libquixcc::StringTypeNode::m_instance = nullptr;
