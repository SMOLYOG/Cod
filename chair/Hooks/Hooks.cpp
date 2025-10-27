#pragma once
#include "Hooks.h"
#include "../Controller/Controller.h"
#include "../Exploits/Exploits.h"
#include "../UserCMD/UserCMD.hpp"
#include "../Loot Data/Loot data.h"


namespace Main_Game{

	DWORD64 fpCL_InputMP_ReadyToSendPacket = NULL;

	bool DetourCL_InputMP_ReadyToSendPacket(LocalClientNum_t localClientNum)
	{
		if (Globals::ScanComplete)
		{

			KeyBinds::ControllerDynamicThirdPerson = ButtonActive(KeyBinds::DynamicThirdPerson);
			KeyBinds::ControllerOveride = ButtonActive(KeyBinds::ControllerOveride);
			KeyBinds::ControllerUninject = ButtonActive(KeyBinds::Uninject);
			KeyBinds::ControllerAimbot = ButtonActive(KeyBinds::Aimbot);
			KeyBinds::ControllerAimbot2 = ButtonActive(KeyBinds::Aimbot2);
			KeyBinds::ControllerAirstuck = ButtonActive(KeyBinds::AirStuck);
			KeyBinds::ControllerMenu = ButtonActive(KeyBinds::Menu);

			Color::Chams[0] = ImGui::ColorConvertFloat4ToU32(ImVec4(Color::ChamsVec4[0][0], Color::ChamsVec4[0][1], Color::ChamsVec4[0][2], Color::ChamsVec4[0][3]));
			Color::Chams[1] = ImGui::ColorConvertFloat4ToU32(ImVec4(Color::ChamsVec4[1][0], Color::ChamsVec4[1][1], Color::ChamsVec4[1][2], Color::ChamsVec4[1][3]));

			Globals::MaxPlayerCount = GlobalPlayerData::GetMaxPlayerCount();
			Globals::InGame2 = JUP::InGameCheck2();
			Chat_Spam();
			Grab_Lobby_Info();

			if (!Globals::InGame2) {
				Offset::CGArray = NULL;
				return VariadicCall<bool>(Offset::JmpRbx, fpCL_InputMP_ReadyToSendPacket, localClientNum);
			}

			if (Offset::CGArray == 0ui64)
				return VariadicCall<bool>(Offset::JmpRbx, fpCL_InputMP_ReadyToSendPacket, localClientNum);

			Offset::UserCMDWrapper = ClActiveClient_GetClient();

			if (Offset::UserCMDWrapper != 0ui64) {

				CMD = Offset::UserCMDWrapper ? GetUserCMD(GetCMDNumber()) : nullptr;
				if (CMD != nullptr)
				{

					if (Aimbot::Accuracy::NoRecoil)
						NoRecoil::NoRecoil();

					GrabMyClient();

					GetEntitys();

						
					if (loot_esp::enable)
						Get_Loot();

					if (Aimbot::Enable)
						Aimbot_Loop();

					if (Visuals::Miscellaneous::Tracers::Enable)
						PlayerDataBase::CalculateTracers();

					if (Exploits::Airstuck && (GetAsyncKeyState(KeyBinds::AirStuck) & 0x8000) || KeyBinds::ControllerAirstuck)
						CMD->serverTime = 0;

					if (Exploits::NightVision && (GetAsyncKeyState(KeyBinds::NightVision) & 0x8000) || KeyBinds::ControllerNightVision)
						CMD->Buttons.Add(0x8000);

					if (Aimbot::RapidFire)
						Rapid_Fire(CMD);

					if (cfg::Exploits::Auto_Reload::Enable)
						Auto_Reload(CMD);
				}
			}

		}

		return VariadicCall<bool>(Offset::JmpRbx, fpCL_InputMP_ReadyToSendPacket, localClientNum);
	}
}


namespace Misc {

	char (*BlockMouseOrig)(__int64 a1, __int64 a2, __int64 a3, unsigned int a4, unsigned int a5);
	char BlockMouseHook(__int64 a1, __int64 a2, __int64 a3, unsigned int a4, unsigned int a5)
	{
		if (Globals::Open)
			return 0;

		return BlockMouseOrig(a1, a2, a3, a4, a5);
	}

	bool (*BlockKeyboardOrig)(unsigned int a1, unsigned __int8 a2, unsigned __int8 a3, unsigned int a4, unsigned int a5, unsigned int a6, __int64 a7, char a8, char a9);
	bool BlockKeyboardHook(unsigned int a1, unsigned __int8 a2, unsigned __int8 a3, unsigned int a4, unsigned int a5, unsigned int a6, __int64 a7, char a8, char a9)
	{
		if (Globals::Open)
			return 0;

		return BlockKeyboardOrig(a1, a2, a3, a4, a5, a6, a7, a8, a9);
	}

	int (*oGetItemQuantity)(__int64 s_instance);
	int hkGetItemQuantity(__int64 s_instance) {
		return 10;

	}

}