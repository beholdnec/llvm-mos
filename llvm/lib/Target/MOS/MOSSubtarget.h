//===-- MOSSubtarget.h - Define Subtarget for the MOS -----------*- C++ -*-===//
//
// Part of LLVM-MOS, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the MOS specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MOS_SUBTARGET_H
#define LLVM_MOS_SUBTARGET_H

#include "llvm/CodeGen/GlobalISel/InlineAsmLowering.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/Utils.h"
#include "llvm/CodeGen/Register.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#include "MOSCallLowering.h"
#include "MOSFrameLowering.h"
#include "MOSISelLowering.h"
#include "MOSInstrInfo.h"
#include "MOSLegalizerInfo.h"
#include "MOSRegisterBankInfo.h"
#include "MOSRegisterInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "MOSGenSubtargetInfo.inc"

namespace llvm {

class MOSTargetMachine;

/// A specific MOS target MCU.
class MOSSubtarget : public MOSGenSubtargetInfo {
public:
  MOSSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
               const MOSTargetMachine &TM);

  /// Gets the ELF architecture for the e_flags field
  /// of an ELF object file.
  unsigned getELFArch() const {
    assert(ELFArch != 0 &&
           "every device must have an associate ELF architecture");
    return ELFArch;
  }

  const MOSFrameLowering *getFrameLowering() const override;
  const MOSInstrInfo *getInstrInfo() const override;
  const MOSRegisterInfo *getRegisterInfo() const override;
  const MOSTargetLowering *getTargetLowering() const override;
  const CallLowering *getCallLowering() const override;
  const LegalizerInfo *getLegalizerInfo() const override;
  const RegisterBankInfo *getRegBankInfo() const override;
  InstructionSelector *getInstructionSelector() const override;
  const InlineAsmLowering *getInlineAsmLowering() const override;

  bool enableMachineScheduler() const override { return true; }
  bool enableSubRegLiveness() const override { return true; }

  void overrideSchedPolicy(MachineSchedPolicy &Policy,
                           unsigned NumRegionInstrs) const override;

  // Subtarget feature getters.
  // See MOS.td for details.
  bool hasTinyEncoding() const { return HasTinyEncoding; }

  MOSSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS,
                                                const TargetMachine &TM);

  /// Parses a subtarget feature string, setting appropriate options.
  /// \note Definition of function is auto generated by `tblgen`.
  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  bool has6502() const { return Has6502Insns; }
  bool has65C02() const { return Has65C02Insns; }

private:
  /// The ELF e_flags architecture.
  unsigned ELFArch;

  // Subtarget feature settings
  // See MOS.td for details.
  bool HasTinyEncoding = false;

  bool Has6502Insns = false;
  bool Has6502BCDInsns = false;
  bool Has6502XInsns = false;
  bool Has65C02Insns = false;
  bool HasR65C02Insns = false;
  bool HasW65C02Insns = false;
  bool HasW65816Insns = false;
  bool Has65EL02Insns = false;
  bool Has65CE02Insns = false;
  bool HasSWEET16Insns = false;

  bool LongRegisterNames = false;

  // Dummy member, used by FeatureSet's. We cannot have a SubtargetFeature with
  // no variable, so we instead bind pseudo features to this variable.
  bool FeatureSetDummy = false;

  MOSInstrInfo InstrInfo;
  MOSRegisterInfo RegInfo;
  MOSFrameLowering FrameLowering;
  MOSTargetLowering TLInfo;
  MOSCallLowering CallLoweringInfo;
  MOSLegalizerInfo Legalizer;
  MOSRegisterBankInfo RegBankInfo;
  std::unique_ptr<InstructionSelector> InstSelector;
  InlineAsmLowering InlineAsmLoweringInfo;
};

} // end namespace llvm

#endif // LLVM_MOS_SUBTARGET_