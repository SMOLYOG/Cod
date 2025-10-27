#pragma once
#include "..\Lobby Info/Lobby_Info.h"
#include "..\Entity Data\PlayerData.hpp"
#include "../Aimbot/Aimbot.h"


namespace Main_Game {

	extern DWORD64 fpCL_InputMP_ReadyToSendPacket;
	extern bool DetourCL_InputMP_ReadyToSendPacket(LocalClientNum_t localClientNum);

}

namespace Misc {

	extern char (*BlockMouseOrig)(__int64 a1, __int64 a2, __int64 a3, unsigned int a4, unsigned int a5);
	extern char BlockMouseHook(__int64 a1, __int64 a2, __int64 a3, unsigned int a4, unsigned int a5);

	extern bool (*BlockKeyboardOrig)(unsigned int a1, unsigned __int8 a2, unsigned __int8 a3, unsigned int a4, unsigned int a5, unsigned int a6, __int64 a7, char a8, char a9);
	extern bool BlockKeyboardHook(unsigned int a1, unsigned __int8 a2, unsigned __int8 a3, unsigned int a4, unsigned int a5, unsigned int a6, __int64 a7, char a8, char a9);

	extern int (*oGetItemQuantity)(__int64 s_instance);
	extern int hkGetItemQuantity(__int64 s_instance);

}