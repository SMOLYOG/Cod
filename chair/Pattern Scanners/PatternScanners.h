#pragma once
#include "..\Globals\framework.h"
#include "..\Third Party\Zydis\Zydis.h"

extern DWORD64 SCAN(const char* sig, DWORD64 start_address = NULL, DWORD64 end_length = NULL);
extern DWORD64 RESOLVE(DWORD64 instr, DWORD offset, DWORD instrSize);
extern void DECODE(DWORD64 addr, ZydisDecodedInstruction* instruction, ZydisDecodedOperand* operands);
