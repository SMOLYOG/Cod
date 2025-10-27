#pragma once

#include "Player_Drawing.hpp"
#include "../D3D/D3DDrawing.h"

float get_entity_fov(int ent)
{
	auto angle_to_client = calc_angle(vec3_t(Entity_t[ent].tag_eye.x, Entity_t[ent].tag_eye.y, Entity_t[ent].tag_eye.z), vec3_t(MyClient.View_Origin.x, MyClient.View_Origin.y, MyClient.View_Origin.z));

	auto view = angle_t(Entity_t[ent].ViewAngles.x, Entity_t[ent].ViewAngles.y, Entity_t[ent].ViewAngles.z);
	auto delta = angle_to_client - view;

	delta.normalize();
	delta.clamp();

	return (std::min)(std::hypot(delta.x, delta.y), 180.f);
}

int saved = 0;
int saved2 = 0;
bool reset = false;
bool reset2 = false;

void ESP_Loop() {

	Screen = ImGui::GetIO().DisplaySize;

	ImVec4 FOVC;
	ImVec4 crosshairc;

	ImVec4 Aimingatyou = ImVec4(Aim_Warning::AimingAtYou[0], Aim_Warning::AimingAtYou[1], Aim_Warning::AimingAtYou[2], Aim_Warning::AimingAtYou[3]);
	ImVec4 Lookingatyou = ImVec4(Aim_Warning::LookingAtYou[0], Aim_Warning::LookingAtYou[1], Aim_Warning::LookingAtYou[2], Aim_Warning::LookingAtYou[3]);

	if (PlayerDataBase::Target == -1) {
		crosshairc = ImVec4(Color::crosshair[0], Color::crosshair[1], Color::crosshair[2], Color::crosshair[3]);
		FOVC = ImVec4(Color::FOV[0], Color::FOV[1], Color::FOV[2], 0.5f);
	}		
	else {
		crosshairc = ImVec4(cfg::Aim_Target::Color::Target_Crosshair[0], cfg::Aim_Target::Color::Target_Crosshair[1], cfg::Aim_Target::Color::Target_Crosshair[2], cfg::Aim_Target::Color::Target_Crosshair[3]);
		FOVC = ImVec4(cfg::Aim_Target::Color::Target_Crosshair[0], cfg::Aim_Target::Color::Target_Crosshair[1], cfg::Aim_Target::Color::Target_Crosshair[2], cfg::Aim_Target::Color::Target_Crosshair[3]);
	}

	if (Visuals::Main::DrawFOV && Aimbot::DynamicFOV == 1)
	{
		float radius = tan(Math::Deg2Rad(Aimbot::FOV) / 2.f) / tan(Math::Deg2Rad(MyClient.FOVReal) / 2.f) * (Screen.x / 2);
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Screen.x / 2, Screen.y / 2), radius, Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(FOVC), 360);
	}
	else if (Visuals::Main::DrawFOV && Aimbot::DynamicFOV == 0)
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Screen.x / 2, Screen.y / 2), tan(Math::Deg2Rad(Aimbot::FOV) / 2.f) / tan(Math::Deg2Rad(130) / 2.f) * Screen.x, Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(FOVC), 360);

	if (Visuals::Main::DrawCrosshair)
		D3D_Draw_Crosshair(Color::Rainbow::crosshair ? ImColor(Color::Rainbow::Rainbow) : ImColor(crosshairc));

	if (!Offset::CGArray || !Globals::InGame2 || !Visuals::Main::Enable) 
		return;

	ImVec4 SnapLinesC[4] = { ImVec4(Color::SnapLines[1][0], Color::SnapLines[1][1], Color::SnapLines[1][2], Color::SnapLines[1][3]), ImVec4(Color::SnapLines[0][0], Color::SnapLines[0][1], Color::SnapLines[0][2], Color::SnapLines[0][3]), ImVec4(Color::SnapLines[3][0], Color::SnapLines[3][1], Color::SnapLines[3][2], Color::SnapLines[3][3]), ImVec4(Color::SnapLines[2][0], Color::SnapLines[2][1], Color::SnapLines[2][2], Color::SnapLines[2][3]) };
	ImVec4 SkeletonC[4] = { ImVec4(Color::Skeleton[1][0], Color::Skeleton[1][1], Color::Skeleton[1][2], Color::Skeleton[1][3]), ImVec4(Color::Skeleton[0][0], Color::Skeleton[0][1], Color::Skeleton[0][2], Color::Skeleton[0][3]), ImVec4(Color::Skeleton[3][0], Color::Skeleton[3][1], Color::Skeleton[3][2], Color::Skeleton[3][3]), ImVec4(Color::Skeleton[2][0], Color::Skeleton[2][1], Color::Skeleton[2][2], Color::Skeleton[2][3]) };
	ImVec4 DistanceC[4] = { ImVec4(Color::Distance[1][0], Color::Distance[1][1], Color::Distance[1][2], Color::Distance[1][3]), ImVec4(Color::Distance[0][0], Color::Distance[0][1], Color::Distance[0][2], Color::Distance[0][3]), ImVec4(Color::Distance[3][0], Color::Distance[3][1], Color::Distance[3][2], Color::Distance[3][3]), ImVec4(Color::Distance[2][0], Color::Distance[2][1], Color::Distance[2][2], Color::Distance[2][3]) };
	ImVec4 AssistsC[4] = { ImVec4(Color::Assists[1][0], Color::Assists[1][1], Color::Assists[1][2], Color::Assists[1][3]), ImVec4(Color::Assists[0][0], Color::Assists[0][1], Color::Assists[0][2], Color::Assists[0][3]), ImVec4(Color::Assists[3][0], Color::Assists[3][1], Color::Assists[3][2], Color::Assists[3][3]), ImVec4(Color::Assists[2][0], Color::Assists[2][1], Color::Assists[2][2], Color::Assists[2][3]) };
	ImVec4 WeaponC[4] = { ImVec4(Color::Weapon[1][0], Color::Weapon[1][1], Color::Weapon[1][2], Color::Weapon[1][3]), ImVec4(Color::Weapon[0][0], Color::Weapon[0][1], Color::Weapon[0][2], Color::Weapon[0][3]), ImVec4(Color::Weapon[3][0], Color::Weapon[3][1], Color::Weapon[3][2], Color::Weapon[3][3]), ImVec4(Color::Weapon[2][0], Color::Weapon[2][1], Color::Weapon[2][2], Color::Weapon[2][3]) };
	ImVec4 TeamIDC[4] = { ImVec4(Color::TeamID[1][0], Color::TeamID[1][1], Color::TeamID[1][2], Color::TeamID[1][3]), ImVec4(Color::TeamID[0][0], Color::TeamID[0][1], Color::TeamID[0][2], Color::TeamID[0][3]), ImVec4(Color::TeamID[3][0], Color::TeamID[3][1], Color::TeamID[3][2], Color::TeamID[3][3]), ImVec4(Color::TeamID[2][0], Color::TeamID[2][1], Color::TeamID[2][2], Color::TeamID[2][3]) };
	ImVec4 DeathsC[4] = { ImVec4(Color::Deaths[1][0], Color::Deaths[1][1], Color::Deaths[1][2], Color::Deaths[1][3]), ImVec4(Color::Deaths[0][0], Color::Deaths[0][1], Color::Deaths[0][2], Color::Deaths[0][3]), ImVec4(Color::Deaths[3][0], Color::Deaths[3][1], Color::Deaths[3][2], Color::Deaths[3][3]), ImVec4(Color::Deaths[2][0], Color::Deaths[2][1], Color::Deaths[2][2], Color::Deaths[2][3]) };
	ImVec4 DamageC[4] = { ImVec4(Color::Damage[1][0], Color::Damage[1][1], Color::Damage[1][2], Color::Damage[1][3]), ImVec4(Color::Damage[0][0], Color::Damage[0][1], Color::Damage[0][2], Color::Damage[0][3]), ImVec4(Color::Damage[3][0], Color::Damage[3][1], Color::Damage[3][2], Color::Damage[3][3]), ImVec4(Color::Damage[2][0], Color::Damage[2][1], Color::Damage[2][2], Color::Damage[2][3]) };
	ImVec4 KillsC[4] = { ImVec4(Color::Kills[1][0], Color::Kills[1][1], Color::Kills[1][2], Color::Kills[1][3]), ImVec4(Color::Kills[0][0], Color::Kills[0][1], Color::Kills[0][2], Color::Kills[0][3]), ImVec4(Color::Kills[3][0], Color::Kills[3][1], Color::Kills[3][2], Color::Kills[3][3]), ImVec4(Color::Kills[2][0], Color::Kills[2][1], Color::Kills[2][2], Color::Kills[2][3]) };
	ImVec4 ScoreC[4] = { ImVec4(Color::Score[1][0], Color::Score[1][1], Color::Score[1][2], Color::Score[1][3]), ImVec4(Color::Score[0][0], Color::Score[0][1], Color::Score[0][2], Color::Score[0][3]), ImVec4(Color::Score[3][0], Color::Score[3][1], Color::Score[3][2], Color::Score[3][3]), ImVec4(Color::Score[2][0], Color::Score[2][1], Color::Score[2][2], Color::Score[2][3]) };
	ImVec4 NameC[4] = { ImVec4(Color::Name[1][0], Color::Name[1][1], Color::Name[1][2], Color::Name[1][3]), ImVec4(Color::Name[0][0], Color::Name[0][1], Color::Name[0][2], Color::Name[0][3]), ImVec4(Color::Name[3][0], Color::Name[3][1], Color::Name[3][2], Color::Name[3][3]), ImVec4(Color::Name[2][0], Color::Name[2][1], Color::Name[2][2], Color::Name[2][3]) };
	ImVec4 PingC[4] = { ImVec4(Color::Ping[1][0], Color::Ping[1][1], Color::Ping[1][2], Color::Ping[1][3]), ImVec4(Color::Ping[0][0], Color::Ping[0][1], Color::Ping[0][2], Color::Ping[0][3]), ImVec4(Color::Ping[3][0], Color::Ping[3][1], Color::Ping[3][2], Color::Ping[3][3]), ImVec4(Color::Ping[2][0], Color::Ping[2][1], Color::Ping[2][2], Color::Ping[2][3]) };
	ImVec4 RankC[4] = { ImVec4(Color::Rank[1][0], Color::Rank[1][1], Color::Rank[1][2], Color::Rank[1][3]), ImVec4(Color::Rank[0][0], Color::Rank[0][1], Color::Rank[0][2], Color::Rank[0][3]), ImVec4(Color::Rank[3][0], Color::Rank[3][1], Color::Rank[3][2], Color::Rank[3][3]), ImVec4(Color::Rank[2][0], Color::Rank[2][1], Color::Rank[2][2], Color::Rank[2][3]) };
	ImVec4 BoxC[4] = { ImVec4(Color::Box[1][0], Color::Box[1][1], Color::Box[1][2], Color::Box[1][3]), ImVec4(Color::Box[0][0], Color::Box[0][1], Color::Box[0][2], Color::Box[0][3]), ImVec4(Color::Box[3][0], Color::Box[3][1], Color::Box[3][2], Color::Box[3][3]), ImVec4(Color::Box[2][0], Color::Box[2][1], Color::Box[2][2], Color::Box[2][3]) };
	ImVec4 KDC[4] = { ImVec4(Color::KD[1][0], Color::KD[1][1], Color::KD[1][2], Color::KD[1][3]), ImVec4(Color::KD[0][0], Color::KD[0][1], Color::KD[0][2], Color::KD[0][3]), ImVec4(Color::KD[3][0], Color::KD[3][1], Color::KD[3][2], Color::KD[3][3]), ImVec4(Color::KD[2][0], Color::KD[2][1], Color::KD[2][2], Color::KD[2][3]) };
	ImVec4 TargetC = ImVec4(cfg::Aim_Target::Color::Target_Esp[0], cfg::Aim_Target::Color::Target_Esp[1], cfg::Aim_Target::Color::Target_Esp[2], cfg::Aim_Target::Color::Target_Esp[3]);
	ImVec4 CompassC[4] = { ImVec4(Color::Compass[1][0], Color::Compass[1][1], Color::Compass[1][2], Color::Compass[1][3]), ImVec4(Color::Compass[0][0], Color::Compass[0][1], Color::Compass[0][2], Color::Compass[0][3]), ImVec4(Color::Compass[3][0], Color::Compass[3][1], Color::Compass[3][2], Color::Compass[3][3]), ImVec4(Color::Compass[2][0], Color::Compass[2][1], Color::Compass[2][2], Color::Compass[2][3]) };
	float CompassSize;
	ImVec4 Highlight = ImVec4(Color::HighlightColor[0], Color::HighlightColor[1], Color::HighlightColor[2], Color::HighlightColor[3]);

	for (int i = 0; i < 2048; i++) {
		if ( !Offset::CGArray || !Globals::InGame2) 
			continue;

		if (i == MyClient.Client_Num)
			continue;

		if (reset)
		{
			cfg::Esp::InFov_Count = 0;
			reset = false;
		}

		if (reset2)
		{
			saved2 = 0;
			reset2 = false;
		}

		if (Entity_t[i].CanDraw && Entity_t[i].tag_eye_Visible && !Entity_t[i].IsFriendly && i != MyClient.Client_Num)
		{
			auto value = get_entity_fov(i);

			if (Entity_t[i].distance < Aim_Warning::Looking_Max_Distance && value < 70.f && Aim_Warning::Looking_At_You) {
				cfg::Esp::InFov_Count++;
			}

			if (Entity_t[i].distance < Aim_Warning::Aiming_Max_distance && value < 10.f && Aim_Warning::Aiming_At_You) {
				saved2++;
			}
		}

		ImVec4 Color = EvaluateColor(i, TargetC, Color::Rainbow::Distance, DistanceC, Highlight);
		ImVec4 Compass = EvaluateColor(i, TargetC, Color::Rainbow::Compass, CompassC, Highlight);


		if (Visuals::Main::Drawing::Teamates && Entity_t[i].IsFriendly)
			continue;
		if (Visuals::Main::Drawing::Visible && !Entity_t[i].Is_Visible)
			continue;
		if (Visuals::Main::Drawing::Downed && Entity_t[i].IsDowned)
			continue;
		if (Visuals::Main::Drawing::Bots && Entity_t[i].E_Type != EntityType_T::ET_PLAYER)
			continue;

		if (i == PlayerDataBase::Target && Entity_t[i].CanDraw && (cfg::Aim_Target::Target_SnapLine || Visuals::Main::DrawPlayerSnaplines) && i != MyClient.Client_Num)
			D3D_Draw_SnapLines(i, Color);
		if (Visuals::Main::DrawPlayerSnaplines && Entity_t[i].CanDraw && (Entity_t[i].distance < Visuals::Main::Drawing::all) && i != MyClient.Client_Num)
			D3D_Draw_SnapLines(i, Color);
		if (Entity_t[i].CanDraw && Entity_t[i].Is_In_View && (Entity_t[i].distance < Visuals::Main::Drawing::all) && i != MyClient.Client_Num)
			D3D_Draw_Distance(i, Color);
		if (Visuals::Main::DrawPlayerSkeleton && Entity_t[i].CanDraw && Entity_t[i].Is_In_View && (Entity_t[i].distance < Visuals::Main::Drawing::all) && i != MyClient.Client_Num)
			D3D_Draw_Bones(i, Color);
		if (Entity_t[i].CanDraw && Entity_t[i].Is_In_View && (Entity_t[i].distance < Visuals::Main::Drawing::all) && i != MyClient.Client_Num)
			D3D_Draw_PlayerNames(i, Color);
		if (Visuals::Main::DrawPlayerHealth && Entity_t[i].CanDraw && Entity_t[i].Is_In_View && (Entity_t[i].distance < Visuals::Main::Drawing::all) && i != MyClient.Client_Num)
			D3D_Draw_Health(i);
		if (Visuals::Main::Draw_Box && Entity_t[i].CanDraw && Entity_t[i].Is_In_View && (Entity_t[i].distance < Visuals::Main::Drawing::all) && i != MyClient.Client_Num)
			D3D_Draw_Border(i, ImVec2(Entity_t[i].tag_origin_2D.x - Entity_t[i].Dimentions.x / 2.0f, Entity_t[i].tag_origin_2D.y - Entity_t[i].Dimentions.y), ImVec2(Entity_t[i].Dimentions.x, Entity_t[i].Dimentions.y), Visuals::Main::filled, Color);
		if (Lobby[i].Can_Draw && Entity_t[i].CanDraw && Entity_t[i].Is_In_View && (Entity_t[i].distance < Visuals::Main::Drawing::all) && i != MyClient.Client_Num)
			D3D_Draw_Platform(i, Color);

	}

	if (Aim_Warning::Looking_At_You && cfg::Esp::InFov_Count >= 1) {
		auto formatted_str = std::format("{} Players Are Looking At You", cfg::Esp::InFov_Count);
		PlayerDataVisuals::drawString3(ImVec2((Screen.x / 2), Screen.y / 5), formatted_str.c_str(), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(Lookingatyou), ImColor(50, 50, 50, 255), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(Lookingatyou), 0);
		reset = true;
    }
	if (Aim_Warning::Aiming_At_You && saved2 >= 1) {
		auto formatted_str = std::format("{} Players Are Aiming At You", saved2);
		PlayerDataVisuals::drawString3(ImVec2((Screen.x / 2), (Screen.y / 5) - 30.f), formatted_str.c_str(), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(Aimingatyou), ImColor(50, 50, 50, 255), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(Aimingatyou), 0);
		reset2 = true;
	}
}
void Compass_Loop() {
	if (!Offset::CGArray || !Globals::InGame2) 
		return;

	if (!Visuals::Miscellaneous::Compass::Enable)
		return;

	ImVec4 CompassC[4] = { ImVec4(Color::Compass[1][0], Color::Compass[1][1], Color::Compass[1][2], Color::Compass[1][3]), ImVec4(Color::Compass[0][0], Color::Compass[0][1], Color::Compass[0][2], Color::Compass[0][3]), ImVec4(Color::Compass[3][0], Color::Compass[3][1], Color::Compass[3][2], Color::Compass[3][3]), ImVec4(Color::Compass[2][0], Color::Compass[2][1], Color::Compass[2][2], Color::Compass[2][3]) };
	ImVec4 TargetC = ImVec4(cfg::Aim_Target::Color::Target_Esp[0], cfg::Aim_Target::Color::Target_Esp[1], cfg::Aim_Target::Color::Target_Esp[2], cfg::Aim_Target::Color::Target_Esp[3]);
	ImVec4 Highlight = ImVec4(Color::HighlightColor[0], Color::HighlightColor[1], Color::HighlightColor[2], Color::HighlightColor[3]);

	float CompassSize;
	for (int i = 0; i < 2048; i++) {

		if (!Entity_t[i].CanDraw)
			continue;

		if ( !Offset::CGArray || !Globals::InGame2 )
			continue;

		ImVec4 Compass = EvaluateColor(i, TargetC, Color::Rainbow::Compass, CompassC, Highlight);

		if (i == MyClient.Client_Num) 
			continue;

		if (Entity_t[i].distance >= Visuals::Miscellaneous::Compass::Distance)
			continue;
		if (Visuals::Miscellaneous::Compass::Drawing::Teamates && Entity_t[i].IsFriendly)
			continue;
		if (Visuals::Miscellaneous::Compass::Drawing::Visible && !Entity_t[i].Is_Visible)
			continue;
		if (Visuals::Miscellaneous::Compass::Drawing::Downed && Entity_t[i].IsDowned)
			continue;
		if (Visuals::Miscellaneous::Compass::Drawing::Bots && Entity_t[i].E_Type != EntityType_T::ET_PLAYER)
			continue;

		if (Visuals::Miscellaneous::Compass::Enable && Entity_t[i].CanDraw && (Entity_t[i].distance < Visuals::Miscellaneous::Compass::Distance) && i != MyClient.Client_Num) {
			CompassSize = Visuals::Miscellaneous::Compass::PosistionType ? Visuals::Miscellaneous::Compass::Size : Aimbot::FOV + 1;

			if (Aimbot::DynamicFOV == 0)
				D3D_Draw_Compass(i, tan(Math::Deg2Rad(CompassSize) / 2.f) / tan(Math::Deg2Rad(130) / 2.f) * ImGui::GetIO().DisplaySize.x, Compass);
			else if (Aimbot::DynamicFOV == 1) {
				if (Visuals::Miscellaneous::Compass::PosistionType == 1)
					D3D_Draw_Compass(i, tan(Math::Deg2Rad(CompassSize) / 2.f) / tan(Math::Deg2Rad(130) / 2.f) * ImGui::GetIO().DisplaySize.x, Compass);
				else {
					float radius = (tanf(Math::Deg2Rad(Aimbot::FOV + 1) / 2.f) / tanf(Math::Deg2Rad(MyClient.FOVReal) / 2.f) * (ImGui::GetIO().DisplaySize.x / 2));
					D3D_Draw_Compass(i, radius, Compass);
				}

			}
		}
	}
}
