#pragma once

#include "..\Menu\Misc\Menu Helper.h"
#include "..\Globals\framework.h"
#include "..\GameSDK\GameSDK.h"
#include "Sdk.h"
#include "..\Entity Drawing\Player_Drawing.hpp"
#include "../D3D/D3DDrawing.h"
#include "..\Loot Drawing\Loot Drawing.h"

namespace Process
{
	BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)
	{
		DWORD dwPid = 0;
		GetWindowThreadProcessId(hWnd, &dwPid);
		if (dwPid == lParam)
		{
			hwnd = hWnd;
			return FALSE;
		}
		return TRUE;
	}
	HWND get_process_window()
	{
		if (hwnd)
			return hwnd;

		EnumWindows(EnumWindowCallBack, GetCurrentProcessId());

		if (hwnd == NULL) 0;

		return hwnd;
	}
	HWND hwnd;
}

namespace Main
{
	void MainLoop(ImFont* font)
	{
		Menu::UpdateRainbowColor();
		Visuals::Outlines::Rainbow = ImGui::ColorConvertFloat4ToU32(ImVec4((float)Menu::Rainbow[0] / 255, (float)Menu::Rainbow[1] / 255, (float)Menu::Rainbow[2] / 255, 1.0f));
		Visuals::Main::Rainbow = ImVec4((float)Menu::Rainbow[0] / 255, (float)Menu::Rainbow[1] / 255, (float)Menu::Rainbow[2] / 255, 1.0f);
		Color::Rainbow::Rainbow = ImVec4((float)Menu::Rainbow[0] / 255, (float)Menu::Rainbow[1] / 255, (float)Menu::Rainbow[2] / 255, 1.0f);
	}
	void Init(ImFont* font)
	{
		Begin();


		if (Globals::ScanComplete) {
			ESP_Loop();

			if (Visuals::Miscellaneous::Tracers::Enable)
				D3D_Draw_Tracers();

			if (Visuals::Miscellaneous::Compass::Enable)
				Compass_Loop();

			if (loot_esp::enable)
				Loot_Loop();

	
			Color::Rainbow::Distance[0] = Globals::rainbowesp;
			Color::Rainbow::Distance[1] = Globals::rainbowesp;
			Color::Rainbow::Distance[2] = Globals::rainbowesp;
			Color::Rainbow::Distance[3] = Globals::rainbowesp;
			Color::Rainbow::FOV = Globals::rainbowesp;
			Color::Rainbow::crosshair = Globals::rainbowesp;
			Color::Rainbow::DynamicRadar[0] = Globals::rainbowesp;
			Color::Rainbow::DynamicRadar[1] = Globals::rainbowesp;
			Color::Rainbow::DynamicRadar[2] = Globals::rainbowesp;
			Color::Rainbow::DynamicRadar[3] = Globals::rainbowesp;
			Color::Rainbow::Compass[0] = Globals::rainbowesp;
			Color::Rainbow::Compass[1] = Globals::rainbowesp;
			Color::Rainbow::Compass[2] = Globals::rainbowesp;
			Color::Rainbow::Compass[3] = Globals::rainbowesp;
			Color::Rainbow::Chams[0] = Globals::rainbowesp;
			Color::Rainbow::Chams[1] = Globals::rainbowesp;
			Color::Rainbow::Chams[2] = Globals::rainbowesp;
			Color::Rainbow::Chams[3] = Globals::rainbowesp;
		
		}

		MainLoop(font);
		End();

	}
	void Begin()
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::Begin(xorstr_("V"), reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
	}
	void End()
	{
		ImGui::GetCurrentWindow()->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
	}
}