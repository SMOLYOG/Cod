#pragma once

#define is_valid_ptr(p) ((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))

#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <timeapi.h>
#include <unordered_map>
#include <map>
#include <timeapi.h>
#include <sysinfoapi.h>
#include <filesystem>
#include <functional>
#include <..\Third Party\Json\json.hpp>
#include <vector>

#include "..\Third Party\LazyImporter.h"

#include "..\ImGui/imgui.h"
#include "..\ImGui/imgui_internal.h"

#include "..\ImGui/imgui_impl_win32.h"
#include "..\ImGui/imgui_impl_dx12.h"
#include "../ImGui/imgui_settings.h"

#include <dxgi1_4.h>

#include "..\Third Party\Kiero\Kiero.h"

#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#include "../Structures/Structures.h"
#include "Globals.h"
#include "../Math/Math.h"

