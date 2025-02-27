//===--- MOS.cpp - MOS Helpers for Tools ------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MOS.h"
#include "clang/Driver/Options.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang::driver::tools;
using namespace llvm::opt;
using namespace llvm;

/// getMOSTargetCPU - Get the (LLVM) name of the MOS cpu we are targeting.
std::string mos::getMOSTargetCPU(const ArgList &Args) {
  if (Arg *A = Args.getLastArg(clang::driver::options::OPT_mcpu_EQ)) {
    StringRef CPUName = A->getValue();

    return llvm::StringSwitch<const char *>(CPUName)
        .Cases("mos6502", "6502", "mos6502")
        .Cases("mos6502x", "6502x", "mos6502x")
        .Cases("mos65c02", "65c02", "mos65c02")
        .Cases("mosr65c02", "r65c02", "mosr65c02")
        .Cases("mosw65c02", "w65c02", "mosw65c02")
        .Cases("mosw65816", "w65816", "mosw65816")
        .Cases("mosw65el02", "w65el02", "mosw65el02")
        .Cases("mosw65ce02", "w65ce02", "mosw65ce02")
        .Cases("mossweet16", "sweet16", "mossweet16")
        .Default("");
  }

  return "";
}
