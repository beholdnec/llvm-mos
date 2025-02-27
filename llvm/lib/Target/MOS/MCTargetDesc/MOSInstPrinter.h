//===- MOSInstPrinter.h - Convert MOS MCInst to assembly syntax -*- C++ -*-===//
//
// Part of LLVM-MOS, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an MOS MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MOS_INST_PRINTER_H
#define LLVM_MOS_INST_PRINTER_H

#include "llvm/MC/MCInstPrinter.h"
#include "MCTargetDesc/MOSMCTargetDesc.h"
#include <utility>

namespace llvm {

/// Prints MOS instructions to a textual stream.
class MOSInstPrinter : public MCInstPrinter {
public:
  MOSInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                 const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

  bool printAliasInstr(const MCInst *MI, uint64_t Address, raw_ostream &OS);

  void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                 const MCSubtargetInfo &STI, raw_ostream &O) override;
  void printRegName(raw_ostream &O, unsigned RegNo) const override;

  std::pair<const char *, uint64_t> getMnemonic(const MCInst *MI) override;

// generated by TableGen
  void printInstruction(const MCInst *MI, uint64_t Address, raw_ostream &O);
  void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  static const char *getRegisterName(unsigned RegNo);
  static const char *getRegisterName(unsigned RegNo, unsigned AltIdx);

  /// Utility function to print immediates in decimal or hex.
  format_object<int64_t> formatImm(int64_t Value) const {
    return PrintImmHex ? formatHex(Value) : formatDec(Value);
  }

  /// Utility functions to print decimal/hexadecimal values.
  format_object<int64_t> formatHex(int64_t Value) const;
  format_object<uint64_t> formatHex(uint64_t Value) const;
};

class MOSInstPrinterCA65 : public MOSInstPrinter {
  public:
  MOSInstPrinterCA65(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                     const MCRegisterInfo &MRI)
      : MOSInstPrinter(MAI, MII, MRI) {}

}; 

class MOSInstPrinterXA65 : public MOSInstPrinter
{
  public:
    MOSInstPrinterXA65(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                     const MCRegisterInfo &MRI)
      : MOSInstPrinter(MAI, MII, MRI) {}
};

} // end namespace llvm

#endif // LLVM_MOS_INST_PRINTER_H
