#pragma once
#include "Loot Drawing.h"

void Loot_Loop() {
	if (!loot_esp::enable)
		return;
	if (!Globals::InGame2)
		return;
	if (!MyClient.Got_Client)
		return;

	ImVec4 col;

	for (int i = 0; i < 416; i++) {

		if (!loot_t[i].canDrawLoot)
			continue;

		if (loot_t[i].distance > loot_esp::max_distance)
			continue;

		if (!loot_t[i].visible && loot_esp::ignoreinvis)
			continue;

		if (loot_t[i].visible)
			col = ImVec4({ loot_esp::Loot_Color[0],loot_esp::Loot_Color[1],loot_esp::Loot_Color[2],loot_esp::Loot_Color[3] });
		else
			col = ImVec4({ loot_esp::Loot_Color_Non_Vis[0],loot_esp::Loot_Color_Non_Vis[1],loot_esp::Loot_Color_Non_Vis[2],loot_esp::Loot_Color_Non_Vis[3] });

		if (loot_esp::show_dist && !loot_t[i].name.empty()) {

			ImVec2 vStringSize, vPosition, center;
			auto formatted_str = std::format("{} [ {}.m ]", loot_t[i].name.c_str(), Math::RoundFloat(loot_t[i].distance));
			vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
			center = ImVec2(loot_t[i].screenPos.x,loot_t[i].screenPos.y);
			vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
			D3D_Draw_String1(vPosition, formatted_str.c_str(), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(col), ImColor(50, 50, 50, 155), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(col), 0);
		}
		else {
			ImVec2 vStringSize, vPosition, center;
			vStringSize = ImVec2(ImGui::CalcTextSize(loot_t[i].name.c_str()).x + 4, ImGui::CalcTextSize(loot_t[i].name.c_str()).y);
			center = ImVec2(loot_t[i].screenPos.x, loot_t[i].screenPos.y);
			vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
			D3D_Draw_String1(vPosition, loot_t[i].name.c_str(), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(col), ImColor(50, 50, 50, 155), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(col), 0);
		}
	}

}
