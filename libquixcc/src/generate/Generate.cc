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

#include <core/Logger.h>
#include <generate/CodeGen.h>
#include <generate/Generate.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/LLVMWrapper.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <stdlib.h>

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace libquixcc;
using namespace libquixcc::codegen;

static std::map<std::string, std::string> acceptable_objgen_flags = {
    {"-O0", "-O0"},     {"-O1", "-O1"},     {"-O2", "-O2"},
    {"-O3", "-O3"},     {"-g", "-g"},       {"-v", "-v"},
    {"-flto", "-flto"}, {"-fPIC", "-fPIC"}, {"-fPIE", "-fPIE"}};

class CFILE_raw_pwrite_ostream : public llvm::raw_pwrite_stream {
 public:
  explicit CFILE_raw_pwrite_ostream(FILE *file)
      : llvm::raw_pwrite_stream(true) {
    m_file = file;
  }

 protected:
  FILE *m_file;

  void pwrite_impl(const char *Ptr, size_t Size, uint64_t Offset) override {
    size_t CurPos = ftell(m_file);
    if (fseek(m_file, Offset, SEEK_SET) == -1)
      llvm::report_fatal_error("Failed to seek in file");

    if (fwrite(Ptr, 1, Size, m_file) != Size)
      llvm::report_fatal_error("Failed to write to file");

    if (fseek(m_file, CurPos, SEEK_SET) == -1)
      llvm::report_fatal_error("Failed to seek in file");

    fflush(m_file);

    std::cout << "pwrite_impl(" << (void *)Ptr << ", " << Size << ", " << Offset
              << ")" << std::endl;
  }

  void write_impl(const char *Ptr, size_t Size) override {
    if (fwrite(Ptr, 1, Size, m_file) != Size)
      llvm::report_fatal_error("Failed to write to file");

    fflush(m_file);

    std::cout << "write_impl(" << (void *)Ptr << ", " << Size << ")"
              << std::endl;
  }

  uint64_t current_pos() const override {
    fflush(m_file);

    long pos = ftell(m_file);
    if (pos == -1)
      llvm::report_fatal_error("Failed to get current position in file");

    std::cout << "current_pos() -> " << pos << std::endl;

    return pos;
  }
};

bool libquixcc::codegen::write_IR(quixcc_job_t &ctx,
                                  std::unique_ptr<ir::delta::IRDelta> &ir,
                                  FILE *out, bool generate_bitcode) {
  std::error_code ec;
  CFILE_raw_pwrite_ostream os(out);

  if (!LLVM14Codegen::codegen(ir, ctx.m_inner)) {
    LOG(ERROR) << log::raw << ctx.m_filename.top()
               << ": Failed to generate LLVM IR" << std::endl;
    return false;
  }

  LOG(DEBUG) << "Verifying LLVM module" << std::endl;
  std::string err;
  llvm::raw_string_ostream err_stream(err);

  // Verify the module
  if (llvm::verifyModule(*ctx.m_inner.m_module, &err_stream)) {
    if (ctx.m_debug)
      LOG(FAILED) << log::raw << ctx.m_filename.top()
                  << "LLVM IR generation failed. The Ptree must have been "
                     "semantically incorrect: "
                  << err_stream.str() << std::endl;
    else
      LOG(ERROR) << log::raw << ctx.m_filename.top()
                 << "LLVM IR generation failed. The Ptree must have been "
                    "semantically incorrect: "
                 << err_stream.str() << std::endl;
  }

  LOG(DEBUG) << "Generating LLVM IR" << std::endl;

  if (generate_bitcode) {
    LOG(DEBUG) << "Generating LLVM Bitcode" << std::endl;
    throw std::runtime_error("LLVM Bitcode generation is not yet implemented");
    LOG(DEBUG) << "Finished generating LLVM Bitcode" << std::endl;
  } else {
    LOG(DEBUG) << "Generating LLVM IR" << std::endl;
    ctx.m_inner.m_module->print(os, nullptr, ctx.m_argset.contains("-g"));
  }

  LOG(DEBUG) << "Finished generating LLVM IR" << std::endl;

  return true;
}

bool libquixcc::codegen::write_c11(quixcc_job_t &ctx,
                                   std::unique_ptr<ir::delta::IRDelta> &ir,
                                   FILE *out) {
  LOG(DEBUG) << "Generating C" << std::endl;

  std::stringstream stream;

  if (!C11Codegen::codegen(ir, stream)) {
    LOG(ERROR) << "Failed to generate C11 code" << std::endl;
    return false;
  }

  std::string code = stream.str();

  if (fwrite(code.c_str(), 1, code.size(), out) != code.size()) {
    LOG(ERROR) << "Failed to write C11 code to file" << std::endl;
    return false;
  }

  fflush(out);

  LOG(DEBUG) << "Finished generating C" << std::endl;

  return true;
}

bool libquixcc::codegen::write_llvm(quixcc_job_t &ctx,
                                    std::unique_ptr<ir::delta::IRDelta> &ir,
                                    FILE *out, llvm::CodeGenFileType mode) {
#if !defined(__linux__) && !defined(__APPLE__) && !defined(__unix__) && \
    !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__NetBSD__)
  LOG(FATAL) << "Unsupported operating system" << std::endl;
  throw std::runtime_error("Unsupported operating system");
#else
  auto &TargetTriple = ctx.m_triple;

  LOG(DEBUG) << log::raw << "Generating code for target: " << TargetTriple
             << std::endl;

  std::string Error;
  auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

  if (!Target) {
    llvm::errs() << Error;
    return false;
  }

  auto Features = "";

  llvm::TargetOptions opt;
  auto TargetMachine = Target->createTargetMachine(
      TargetTriple, ctx.m_cpu, Features, opt, llvm::Reloc::PIC_);

  ctx.m_inner.m_module->setDataLayout(TargetMachine->createDataLayout());
  ctx.m_inner.m_module->setTargetTriple(TargetTriple);

  std::error_code ec;
  CFILE_raw_pwrite_ostream os(out);

  if (!LLVM14Codegen::codegen(ir, ctx.m_inner)) {
    LOG(ERROR) << log::raw << "Failed to generate LLVM Code for file"
               << ctx.m_filename.top() << std::endl;
    return false;
  }

  LOG(DEBUG) << "Verifying LLVM module" << std::endl;
  std::string err;
  llvm::raw_string_ostream err_stream(err);

  // Verify the module
  if (llvm::verifyModule(*ctx.m_inner.m_module, &err_stream)) {
    if (ctx.m_debug)
      LOG(FAILED) << log::raw
                  << "LLVM Code generation failed. The Ptree must have been "
                     "semantically incorrect: "
                  << err_stream.str() << std::endl;
    else
      LOG(ERROR) << log::raw
                 << "LLVM Code generation failed. The Ptree must have been "
                    "semantically incorrect: "
                 << err_stream.str() << std::endl;
  }

  llvm::PassManagerBuilder builder;
  llvm::legacy::PassManager pass;

  if (ctx.m_argset.contains("-O0")) {
    builder.OptLevel = 0;

    builder.populateModulePassManager(pass);
  } else if (ctx.m_argset.contains("-Os")) {
    builder.SizeLevel = 1;
    builder.populateModulePassManager(pass);
  } else if (ctx.m_argset.contains("-Oz")) {
    builder.SizeLevel = 2;
    builder.populateModulePassManager(pass);
  } else {
    builder.SizeLevel = 0;

    if (ctx.m_argset.contains("-O1"))
      builder.OptLevel = 1;
    else if (ctx.m_argset.contains("-O2"))
      builder.OptLevel = 2;
    else if (ctx.m_argset.contains("-O3"))
      builder.OptLevel = 3;

    builder.Inliner = llvm::createFunctionInliningPass(
        builder.OptLevel, builder.SizeLevel, false);

    builder.populateModulePassManager(pass);
  }

  if (TargetMachine->addPassesToEmitFile(pass, os, nullptr, mode)) {
    llvm::errs() << "TheTargetMachine can't emit a file of this type";
    return false;
  }

  pass.run(*ctx.m_inner.m_module);
  fflush(out);

  return true;
#endif
}

bool libquixcc::codegen::generate(quixcc_job_t &job,
                                  std::unique_ptr<ir::delta::IRDelta> &ir) {
  if (job.m_argset.contains("-emit-ir"))
    return write_IR(job, ir, job.m_out, false);

  if (job.m_argset.contains("-emit-bc"))
    return write_IR(job, ir, job.m_out, true);

  if (job.m_argset.contains("-emit-c11")) return write_c11(job, ir, job.m_out);

  if (job.m_argset.contains("-S"))
    return write_llvm(job, ir, job.m_out, llvm::CGFT_AssemblyFile);

  if (job.m_argset.contains("-c"))
    return write_llvm(job, ir, job.m_out, llvm::CGFT_ObjectFile);

  LOG(ERROR) << "Output format was not specified. Expected: [-emit-ir, "
                "-emit-quix-ir, -emit-delta-ir, "
                "-emit-c11, -emit-bc, -S, -c]"
             << std::endl;

  return false;
}