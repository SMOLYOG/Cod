#pragma once
#include "..\Globals\Globals.h"
#include "..\Memory\address.hpp"

namespace Memory {
	extern uintptr_t PatternScanEx(HANDLE hProcess, uintptr_t Start, uintptr_t size, const char* sig, const char* mask);
	extern bool MemCompare(const BYTE* bData, const BYTE* bMask, const char* szMask);
	extern DWORD GetProcId(LPCSTR procName);
	extern shared::address_t find_ida_sig(const char* mod, const char* sig);

};