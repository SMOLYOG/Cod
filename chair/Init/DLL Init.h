#pragma once
#include "..\Scanners\Scanners.h"
#include "..\SDK\Sdk.h"
#include "..\Memory\Memory.h"
#include "..\third Party\xor.h"
#include "..\Memory\address.hpp"
#include <iostream>
#include <windows.h>
#include <string>
#include "..\Config/Config2.h"
#include "..\Third Party\MinHook\MinHook.h"
#include "..\Hooks/Hooks.h"
#include <atlchecked.h>
#include "..\Menu\Misc\Render.h"

namespace DLL_Init {
	extern __forceinline DWORD WINAPI Init_Point(HMODULE hModule);
}