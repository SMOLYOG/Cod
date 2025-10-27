#pragma once
#include "GameSDK.h"
#include "..\Menu\Misc\Render.h"
#include <algorithm>
#include "..\Scanners\Scanners.h"
#include "..\Entity Data\PlayerData.hpp"
#include "..\Menu\Misc\Menu Helper.h"
#include "..\ImGui/imgui_settings.h"
#include <tchar.h>
#include "..\Hooks/Hooks.h"
#include "..\Third Party\MinHook\MinHook.h"

std::vector<Tracer_T> Tracer_V;
PlayerState_T* PlayerState;
DWORD64 C_Entity;
MyClient_s MyClient;
ImVec2 Screen;

bool hooked = false;
void UA() {
	if (!hooked) {
		if (MH_CreateHook((LPVOID*)(Offset::GetItemQuantity), &Misc::hkGetItemQuantity, (LPVOID*)(&Misc::oGetItemQuantity)) != MH_OK)
			hooked = false;

		if (MH_EnableHook((LPVOID*)(Offset::GetItemQuantity)) != MH_OK)
			hooked = false;

		hooked = true;
	}
	else if (hooked) {
		if (MH_DisableHook((LPVOID*)(Offset::GetItemQuantity)) != MH_OK)
			hooked = true;

		hooked = false;
	}
}

bool Delay_Timer(bool should_delay, int Delay)
{
	if (Delay < 1)
		return false;

	static std::chrono::seconds delta_time = std::chrono::seconds(0);

	if (should_delay && !delta_time.count())
		delta_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()) + std::chrono::seconds(Delay);

	if (delta_time >= std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()))
		return true;
	else if (delta_time.count())
		delta_time = std::chrono::seconds(0);

	return false;
}

namespace PlayerDataVisuals {


	void drawString2(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i)
	{
		ImVec2 strSize = ImGui::CalcTextSize(string);
		ImVec2 calc = { position.x + strSize.x, position.y + strSize.y };

		ImGui::SetWindowFontScale(1.5f);

		ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x - (strSize.x / 2 - 30), position.y - 2.2f), ImColor(colorText), string);

	}

	void drawString3(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i)
	{
		ImVec2 strSize = ImGui::CalcTextSize(string);
		ImVec2 calc = { position.x + strSize.x, position.y + strSize.y };
		ImGui::SetWindowFontScale(1.5f);
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x - (strSize.x / 2 - 30), position.y - 2.2f), ImColor(colorText), string);
	}

	
}

namespace GlobalPlayerData {


	bool PopulateBoneData(int i, Vector2* BoneData, std::vector<std::string> Bone) {
		Vector3 Position3D; Vector2 Position2D;
		for (int j = 0; j < Bone.size(); j++) {
			if (!GlobalPlayerData::GetBonePosition(i, Bone[j].c_str(), &Position3D)) return false;
			if (!GlobalPlayerData::WorldToScreen(&Position3D, &Position2D)) return false;

			BoneData[j] = Position2D;
		}
		return true;
	}

	bool SightTrace(const Vector3* Start, const Vector3* End, int LocalPlayer) {
		return GameCall<bool>(Offset::SightTrace)(3, Start, End, LocalPlayer, LocalPlayer, 0x280EC93) == 0;
	}

	bool SightTrace2(const Vector3* Start, const Vector3* End, int LocalPlayer) {
		return GameCall<bool>(Offset::SightTrace)(2, Start, End, LocalPlayer, LocalPlayer, 0x280EC93) == 0;
	}

	bool GetBonePosition(int ent, const char* Bone, Vector3* Origin) {
		Vector3 m[4];
		return VariadicCall<char>(Offset::JmpRbx, Offset::GetBonePosition, 0, ent, GlobalPlayerData::getBoneHash(Bone), m, Origin);
	}

	bool WorldToScreen(Vector3* WorldPosition, Vector2* OutPosition) {
		return VariadicCall<bool>(Offset::JmpRbx, Offset::WorldToScreen, 0, Offset::PlaceFull, WorldPosition, OutPosition);
	}

	unsigned __int64 getBoneHash(const char* input) {
		unsigned __int64 v8 = 0xCBF29CE484222325;
		const char* v6 = input;

		while (*v6) {
			char v7 = *v6;
			char v9 = tolower(v7); // Convert character to lowercase
			++v6;
			v8 = 0x100000001B3 * (v8 ^ v9);
		}

		return v8;
	}

	void GetPlayerName(int i, char* Name) {
		GameCall<void>(Offset::GetPlayerName)(0, i, 47, Name, 1);
	}

	void GetPlayerNameWithHash(int i, char* Name) {
		GameCall<void>(Offset::GetPlayerNameWithHash)(0, i, 47, Name, 1);
	}

	ClientData_T* GetClientInfo(int i) {
		auto ms_cgameStatics = *(ClientInfo_T**)(Offset::GetClientInfo);
		if (!ms_cgameStatics)
			return nullptr;

		return &ms_cgameStatics->ClientInfo[i];
	}


	DWORD64 GetEntity(int i) {
		UsableRef_T Ref;
		memset(&Ref, 0, sizeof(UsableRef_T));
		Ref.useIndex = i;

		return VariadicCall<DWORD64>(Offset::JmpRbx, Offset::GetEntity, 0, &Ref);
	}

	Vector3 GetAngle(DWORD64 C_Entity) {
		return *(Vector3*)(C_Entity + Offset::GetAngle);
	}

	int GetMaxPlayerCount()
	{
		return *(int*)(Offset::MaxPlayerCount);
	}

	Score_T* Score(int i)
	{
		return VariadicCall<Score_T*>(Offset::JmpRbx, Offset::Score, 0, i);
	}
}

namespace PlayerDataBase {
	std::vector<PlayerInformation> PlayerList(2048, PlayerInformation());
	int EntityNumber;
	int Target = -1;
	Vector3 ViewOrigin;

	std::string GetWeaponName(int i, DWORD64 Centity) {
		char WeaponNameBuffer[255];

		auto Weapon = GameCall<Weapon_T*>(Offset::WeaponName)(0, Centity);
		if (Weapon == NULL)
			return xorstr_("None");

		GameCall<char*>(Offset::WeaponDisplayName)(Weapon, 0, false, WeaponNameBuffer, sizeof(WeaponNameBuffer), 0);

		std::string WeaponName = WeaponNameBuffer;
		if (WeaponName.find(xorstr_(" ")) != std::string::npos) {
			WeaponName.erase(WeaponName.find(xorstr_(" ")), 2);

			std::copy(WeaponName.begin(), WeaponName.end(), WeaponNameBuffer);
			WeaponNameBuffer[WeaponName.size()] = '\0';
		}

		return std::string(WeaponNameBuffer);

	}

	const char* GetBones(int Bone) {
		switch (Bone) {
		case 0: return ("j_head");
		case 1: return ("j_neck");
		case 2: return ("j_spine4");
		case 3: return ("j_shoulder_le");
		case 4: return ("j_shoulder_ri");
		case 5: return ("j_elbow_le");
		case 6: return ("j_elbow_ri");
		case 7: return ("j_wrist_le");
		case 8: return ("j_wrist_ri");
		case 9: return ("j_mainroot");
		case 10: return ("j_knee_le");
		case 11: return ("j_knee_ri");
		case 12: return ("j_ankle_le");
		case 13: return ("j_ankle_ri");
		default: return ("j_mainroot");
		};
	}

	bool CalculateBoneESP(int i) {

		std::vector<std::string> LeftArm = { xorstr_("j_neck"), xorstr_("j_clavicle_le"), xorstr_("j_shoulder_le"), xorstr_("j_elbow_le"), xorstr_("j_wrist_le") };
		std::vector<std::string> RightArm = { xorstr_("j_neck"), xorstr_("j_clavicle_ri"), xorstr_("j_shoulder_ri"), xorstr_("j_elbow_ri"), xorstr_("j_wrist_ri") };
		if (!GlobalPlayerData::PopulateBoneData(i, Entity_t[i].LeftArm, LeftArm) || !GlobalPlayerData::PopulateBoneData(i, Entity_t[i].RightArm, RightArm))
			return false;

		std::vector<std::string> Body = {/* xorstr_("j_helmet"), */xorstr_("j_head"), xorstr_("j_neck"), xorstr_("j_spine4"), xorstr_("j_spineupper"), xorstr_("j_spinelower"), xorstr_("j_mainroot") };
		if (!GlobalPlayerData::PopulateBoneData(i, Entity_t[i].Body, Body))
			return false;

		std::vector<std::string> LeftLeg = { xorstr_("j_mainroot"), xorstr_("j_hip_le"), xorstr_("j_knee_le"), xorstr_("j_ankle_le"), xorstr_("j_ball_le") };
		std::vector<std::string> RightLeg = { xorstr_("j_mainroot"), xorstr_("j_hip_ri"), xorstr_("j_knee_ri"), xorstr_("j_ankle_ri"), xorstr_("j_ball_ri") };
		if (!GlobalPlayerData::PopulateBoneData(i, Entity_t[i].LeftLeg, LeftLeg) || !GlobalPlayerData::PopulateBoneData(i, Entity_t[i].RightLeg, RightLeg))
			return false;

		return true;
	}

	bool CalculateBoxEsp(int i) {
		Vector3 Origin[2];
		Vector2 W2S[2];

		if (!GlobalPlayerData::GetBonePosition(i, xorstr_("tag_origin"), &Origin[0])) return false;
		if (!GlobalPlayerData::GetBonePosition(i, xorstr_("j_head"), &Origin[1])) return false;

		Origin[0].z -= 12;
		Origin[1].z += 4;

		if (GlobalPlayerData::WorldToScreen(&Origin[1], &W2S[1]) && GlobalPlayerData::WorldToScreen(&Origin[0], &W2S[0])) {

			float Height = abs(W2S[0].y - W2S[1].y);
			float Width = Height / 1.8f;

			Entity_t[i].Dimentions.x = Height / 1.8f;
			Entity_t[i].Dimentions.y = Height;
			return true;
		}

		return false;
	}

	void CalculateTracers() {
		if (Tracer_V.empty() || !Visuals::Miscellaneous::Tracers::Enable) return;

		for (auto Tracer = Tracer_V.begin(); Tracer != Tracer_V.end(); Tracer++)
		{
			if (Tracer->W2SSuccess = GlobalPlayerData::WorldToScreen(&Tracer->HitPos3D, &Tracer->HitPos2D)) {
				GlobalPlayerData::WorldToScreen(&Tracer->StartPos3D, &Tracer->StartPos2D);
				int DeltaTime = GetTickCount64() - Tracer->StartTime;

				Tracer->HitMarkerColor.w = (1.0f - ((float)DeltaTime / Visuals::Miscellaneous::Tracers::FadeInTime)) * Tracer->HitMarkerAlpha;
				Tracer->ShadowColor.w = (1.0f - ((float)DeltaTime / Visuals::Miscellaneous::Tracers::FadeInTime)) * Tracer->ShadowAlpha;
				Tracer->TracerColor.w = (1.0f - ((float)DeltaTime / Visuals::Miscellaneous::Tracers::FadeInTime)) * Tracer->TracerAlpha;

				if (Tracer->ShadowColor.w <= 0.0f && Tracer->HitMarkerColor.w <= 0.0f && Tracer->TracerColor.w <= 0.0f)
				{
					Tracer = Tracer_V.erase(Tracer) - 1;
				}

			}
		}
	}
}

namespace NoRecoil {
	__forceinline uintptr_t SecuredVector3::Base(int idx) const {
		return reinterpret_cast<uintptr_t>(&Keys[idx]);
	}
	void SecuredVector3::Set(float x, float y, float z) {
		int v42, v43, v54[3];
		v42 = Keys[3];
		v54[0] = static_cast<int>(Keys[0] ^ ((Base(0) ^ v42) * ((Base(0) ^ v42) + 2)));
		v54[1] = static_cast<int>(Keys[1] ^ ((Base(1) ^ v42) * ((Base(1) ^ v42) + 2)));
		v54[2] = static_cast<int>(Keys[2] ^ ((v42 ^ Base(2)) * ((v42 ^ Base(2)) + 2)));

		*reinterpret_cast<float*>(&v54[0]) = x;
		*reinterpret_cast<float*>(&v54[1]) = y;
		*reinterpret_cast<float*>(&v54[2]) = z;

		v43 = v42 + Keys[4];
		Keys[3] = v43;
		Keys[0] = static_cast<int>(v54[0] ^ ((v43 ^ Base(0)) * ((v43 ^ Base(0)) + 2)));
		Keys[1] = static_cast<int>(v54[1] ^ ((v43 ^ Base(1)) * ((v43 ^ Base(1)) + 2)));
		Keys[2] = static_cast<int>(v54[2] ^ ((v43 ^ Base(2)) * ((v43 ^ Base(2)) + 2)));
	}
	void SecuredVector3::Set(Vector3 value) {
		return Set(value.x, value.y, value.z);
	}
	Vector3 SecuredVector3::Get() const {
		int v42 = 0, v54[3] = {};
		v42 = Keys[3];
		v54[0] = static_cast<int>(Keys[0] ^ ((Base(0) ^ v42) * ((Base(0) ^ v42) + 2)));
		v54[1] = static_cast<int>(Keys[1] ^ ((Base(1) ^ v42) * ((Base(1) ^ v42) + 2)));
		v54[2] = static_cast<int>(Keys[2] ^ ((v42 ^ Base(2)) * ((v42 ^ Base(2)) + 2)));
		return Vector3(*reinterpret_cast<float*>(&v54[0]), *reinterpret_cast<float*>(&v54[1]), *reinterpret_cast<float*>(&v54[2]));
	}
	SecuredVector3& GetKickAngles2() {
		return *reinterpret_cast<SecuredVector3*>(Offset::CGArray + Offset::ANoRecoil);
	}
	SecuredVector3& GetKickAngles() {
		return *reinterpret_cast<SecuredVector3*>(Offset::CGArray + Offset::NoRecoil);
	}
	void NoRecoil() {
		if (!MyClient.Got_Client)
			return;

		if (Offset::CGArray == NULL)
			return;

		float Multiplier = 1.f - (Aimbot::Accuracy::Strength / 100.f);
		GetKickAngles().Set(GetKickAngles().Get() * Multiplier);

	}
}




#define minny(a,b)            (((a) < (b)) ? (a) : (b))

uint64_t CgHandler(LocalClientNum_t localClient)
{
	return VariadicCall<uintptr_t>(Offset::JmpRbx, Offset::CG_Handler, localClient);
}

namespace AimBot {

	void SetViewAngles(Vector3 angle) {
		VariadicCall<void>(Offset::JmpRbx, Offset::ViewAngles, Offset::CGArray, &angle);
	}

	float get_fov(const Vector3 viewangle, const Vector3 aim_angle)
	{
		Vector3 delta = aim_angle - viewangle;
		delta = delta.normalize();
		delta = delta.clamp();
		return minny(std::hypot(delta.x, delta.y), 180.0f);
	}

	void vector_angles(const Vector3& vec, Vector3& out)
	{
		if (vec.x == 0.0f && vec.y == 0.0f)
		{
			out.x = (vec.z > 0.0f) ? 270.0f : 90.0f;
			out.y = 0.0f;
		}
		else
		{
			out.x = atan2(-vec.z, vec.length_2d()) * 180.f / static_cast<float>(M_PI);
			out.y = atan2(vec.y, vec.x) * 180.f / static_cast<float>(M_PI);
		}

		out.z = 0.f;
	}

	Vector3 calc_angle2(const Vector3 src, const Vector3 dst)
	{
		auto ret = Vector3();

		auto vec_delta = dst - src;

		vector_angles(vec_delta, ret);

		return ret;
	}

	inline float Rad2Deg(float rad)
	{
		return rad * (180.0f / M_PI);
	}

	int oldtarget;
	int delay;
	int delay2;

}

int test;

namespace Hooks {
	void(*Tracers)(uintptr_t thisptr, int sourceEntityNum, int targetEntityNum, unsigned int targetScriptableIndex, unsigned __int8 boneIndex, __int64 weapon, bool isAlternate, const Vector3* initialPos, const Vector3* startPos, const Vector3* position, const Vector3* normal, int surfType, int event, unsigned int impactEffects, int hitContents, const int hitImpactDelayOverride, __int64 hitArmorType, __int64 hitmarkerType, const  __int64 optionalEventLodData, char unknown);
	__int64(*SelfChams)(int localClientNum, __int64 a2, __int64 a3, unsigned int EntityNumber, int renderFlags, __int64 a6, OutlineInfo_T* hudOutlineInfo, __int64 a8, float materialTime, unsigned int a10, char markableViewmodel);
	void(*Chams)(__int64 a1, Pose_T* a2, int a3, int EntityNumber, int renderFlags, ShaderData_T* a6, uint32_t* a7, int a8);
	void(*ShellShock)(unsigned int unk, __int64 CGArray, __int64  unk2, int unk3, int  unk4);
	ClientFov_T* (*FOV)(ClientFov_T* result, int entNum, int fovSpace, bool updateFovWeights, unsigned int* a5);
	__int64* (*CLActive)(__int64 a1, __int64 _RDX, int a3);
	bool(*ThirdPerson)(__int64 a1, __int64 a2);
	bool(*BlackBoxIntalized);
	void(*sub_7FF6D083F570_o)(__int64 a1);
	uintptr_t CG_PredictMP_PredictPlayerState_original;

	void (*oCG_EntityMP_CalcLerpPositions)(int localClientNum, DWORD64 centity);
	void hkCG_EntityMP_CalcLerpPositions(int localClientNum, DWORD64 centity) {

		if (!Globals::InGame2)
			return oCG_EntityMP_CalcLerpPositions(localClientNum, centity);

		if (centity != MyClient.C_Entity)
			return oCG_EntityMP_CalcLerpPositions(localClientNum, centity);

		if (!Exploits::SpinBot)
			return oCG_EntityMP_CalcLerpPositions(localClientNum, centity);

		auto Ps = *(PlayerState_T*)(Offset::CGArray + Offset::PlayerState);

		static float spinangle = 0.0f;

		if (spinangle > 360.0f)
			spinangle -= -360.0f;

		spinangle += 15.0f;

		Vector3 angles = *(Vector3*)(centity + Offset::GetAngle);
		angles.y = spinangle - Ps.DeltaAngles.y;
		*(Vector3*)(centity + Offset::GetAngle) = angles;

	}

	int fuckmaths;
	
	void HookTracers(uintptr_t thisptr, int sourceEntityNum, int targetEntityNum, unsigned int targetScriptableIndex, unsigned __int8 boneIndex, __int64 weapon, bool isAlternate, const Vector3* initialPos, const Vector3* startPos, const Vector3* position, const Vector3* normal, int surfType, int event, unsigned int impactEffects, int hitContents, const int hitImpactDelayOverride, __int64 hitArmorType, __int64 hitmarkerType, const  __int64 optionalEventLodData, char unknown) {
		if (!Visuals::Miscellaneous::Tracers::Enable || !MyClient.Got_Client)
			return VariadicCall<void>(Offset::JmpRbx, (__int64)Tracers, thisptr, sourceEntityNum, targetEntityNum, targetScriptableIndex, boneIndex, weapon, isAlternate, initialPos, startPos, position, normal, surfType, event, impactEffects, hitContents, hitImpactDelayOverride, hitArmorType, hitmarkerType, optionalEventLodData, unknown);

		Tracer_T Tracer;

		if (Visuals::Miscellaneous::Tracers::PlayerTracers && MyClient.Client_Num == sourceEntityNum) {

			if (Visuals::Miscellaneous::Tracers::Players && (MyClient.Client_Type == EntityType_T::ET_PLAYER || MyClient.Client_Type == EntityType_T::ET_AGENT || MyClient.Client_Type == EntityType_T::ET_ACTOR)) {
				Tracer.StartTime = GetTickCount64();
				Tracer.StartPos3D = *startPos;
				Tracer.HitMarkerAlpha = 255.0f;
				Tracer.HitPos3D = *position;
				Tracer.ShadowAlpha = 255.0f;
				Tracer.TracerAlpha = 255.0f;
				Tracer_V.push_back(Tracer);
			}
			if (Visuals::Miscellaneous::Tracers::Objects && (MyClient.Client_Type != EntityType_T::ET_PLAYER && MyClient.Client_Type != EntityType_T::ET_ACTOR && MyClient.Client_Type != EntityType_T::ET_AGENT)) {
				Tracer.StartTime = GetTickCount64();
				Tracer.StartPos3D = *startPos;
				Tracer.HitMarkerAlpha = 255.0f;
				Tracer.HitPos3D = *position;
				Tracer.ShadowAlpha = 255.0f;
				Tracer.TracerAlpha = 255.0f;
				Tracer_V.push_back(Tracer);
			}
		}
		else if (!Visuals::Miscellaneous::Tracers::PlayerTracers) {
			if (Visuals::Miscellaneous::Tracers::Players && (Client[targetEntityNum].Client_Type == EntityType_T::ET_PLAYER && Client[targetEntityNum].Client_Type == EntityType_T::ET_AGENT && Client[targetEntityNum].Client_Type == EntityType_T::ET_ACTOR)) {
				Tracer.StartTime = GetTickCount64();
				Tracer.StartPos3D = *startPos;
				Tracer.HitMarkerAlpha = 255.0f;
				Tracer.HitPos3D = *position;
				Tracer.ShadowAlpha = 255.0f;
				Tracer.TracerAlpha = 255.0f;
				Tracer_V.push_back(Tracer);
			}

			if (Visuals::Miscellaneous::Tracers::Objects && (Client[targetEntityNum].Client_Type != EntityType_T::ET_PLAYER && Client[targetEntityNum].Client_Type != EntityType_T::ET_ACTOR && Client[targetEntityNum].Client_Type != EntityType_T::ET_AGENT)) {
				Tracer.StartTime = GetTickCount64();
				Tracer.StartPos3D = *startPos;
				Tracer.HitMarkerAlpha = 255.0f;
				Tracer.HitPos3D = *position;
				Tracer.ShadowAlpha = 255.0f;
				Tracer.TracerAlpha = 255.0f;
				Tracer_V.push_back(Tracer);
			}
		}

		return VariadicCall<void>(Offset::JmpRbx, (__int64)Tracers, thisptr, sourceEntityNum, targetEntityNum, targetScriptableIndex, boneIndex, weapon, isAlternate, initialPos, startPos, position, normal, surfType, event, impactEffects, hitContents, hitImpactDelayOverride, hitArmorType, hitmarkerType, optionalEventLodData, unknown);
	}
	
	__int64 HookSelfChams(int localClientNum, __int64 a2, __int64 a3, unsigned int EntityNumber, int renderFlags, __int64 a6, OutlineInfo_T* hudOutlineInfo, __int64 a8, float materialTime, unsigned int a10, char markableViewmodel) {
		if (!Globals::InGame2)
			return VariadicCall<__int64>(Offset::JmpRbx, (__int64)SelfChams, localClientNum, a2, a3, EntityNumber, renderFlags, a6, hudOutlineInfo, a8, materialTime, a10, markableViewmodel);

		if (Visuals::Outlines::Self::Enable)
		{
			hudOutlineInfo->Color = Color::Rainbow::Chams[1] ? Visuals::Outlines::Rainbow : Color::Chams[1];
			hudOutlineInfo->NonVisible = true;
			hudOutlineInfo->Visible = true;
			hudOutlineInfo->Fill = Visuals::Outlines::Self::Fill;
			hudOutlineInfo->Width = Visuals::Outlines::Self::Width;
			hudOutlineInfo->Render = Visuals::Outlines::Self::Type;
		}

		return VariadicCall<__int64>(Offset::JmpRbx, (__int64)SelfChams, localClientNum, a2, a3, EntityNumber, renderFlags, a6, hudOutlineInfo, a8, materialTime, a10, markableViewmodel);
	}
	int visteam;
	int nonvisteam;
	int vis;
	int nonvis;
	int coll;
	void HookChams(__int64 a1, Pose_T* a2, int a3, int EntityNumber, int renderFlags, ShaderData_T* a6, uint32_t* a7, int a8) {
		
		if (Visuals::Outlines::Player::Enable && a2->Type == EntityType_T::ET_PLAYER) {
			a6->OutlineInfo.Color = Color::Rainbow::Chams[0] ? Visuals::Outlines::Rainbow : Color::Chams[0];
			a6->OutlineInfo.NonVisible = true;
			a6->OutlineInfo.Visible = true;
			a6->OutlineInfo.Fill = Visuals::Outlines::Player::Fill;
			a6->OutlineInfo.Width = Visuals::Outlines::Player::Width;
			a6->OutlineInfo.Render = Visuals::Outlines::Player::Type;
		}
		return VariadicCall<void>(Offset::JmpRbx, (__int64)Chams, a1, a2, a3, EntityNumber, renderFlags, a6, a7, a8);
	}

	void HookShellShock(unsigned int unk, __int64 CGArray, __int64  unk2, int unk3, int  unk4) {
		VariadicCall<void>(Offset::JmpRbx, (__int64)ShellShock, unk, CGArray, unk2, unk3, unk4);
		if (!CGArray) 
			return;

		Offset::CGArray = CGArray;

		if (!Exploits::NoShellShock)
			return ShellShock(unk, CGArray, unk2, unk3, unk4);

		return;
	}

	float get_ingame_fov_value(float actualFov)
	{
		float viewAspect = 1.78f; // 16.0f / 9.0f (screenW / screenH)
		float scale = 0.75f; // 3.0f / 4.0f
		float ingameFOV = atan(tan((actualFov / 2) / 57.2957795) / (viewAspect * scale)) / 0.0087266462;
		return ingameFOV;
	}

	ClientFov_T* HookFOV(ClientFov_T* result, int entNum, int fovSpace, bool updateFovWeights, unsigned int* a5) {
		ClientFov_T* fovData = VariadicCall<ClientFov_T*>(Offset::JmpRbx, (DWORD64)FOV, result, entNum, fovSpace, updateFovWeights, a5);

		if (!Globals::InGame2)
			return fovData;

		if (Exploits::ExtendedFOV) {
			fovData->Adjustment = get_ingame_fov_value(Commands::FOV);
			return fovData;

		}

		return fovData;
	}

	bool HookThirdPerson(__int64 a1, __int64 a2)
	{
		VariadicCall<bool>(Offset::JmpRbx, (__int64)ThirdPerson, a1, a2);

		if (Exploits::ThirdPerson && !Exploits::DynamicThirdPerson) {
			return true;
		}

		if (Exploits::DynamicThirdPerson)
		{
			if ((GetAsyncKeyState(KeyBinds::DynamicThirdPerson) & 0x8000) || KeyBinds::ControllerDynamicThirdPerson) {
				return false;
			}
			return true;
		}

		return false;
	}

	bool HookBlackBoxIntalized()
	{
		VariadicCall<bool>(Offset::JmpRbx, (uintptr_t)BlackBoxIntalized);
		return false;
	}
}

namespace Radar {
	float Scale = 8.51f;
	float Angle;

	ImVec2 BlipPosistion[2048];
	ImVec2 Posistion;
	ImVec2 Center;
	ImVec2 Size;

	bool Enabled;
	bool BigMap;
};

namespace JUP {

	void SetCbuff(const char* fmt, ...)
	{
		if (IncorrectOffset::EndLobby || IncorrectOffset::PartyDisband) return;
		char cmd[512]{};
		char post[512]{};

		va_list ap;
		va_start(ap, fmt);
		vsprintf_s(cmd, fmt, ap);
		va_end(ap);;

		memcpy(post, (BYTE*)Offset::PartyDisband, 512);
		strcpy((char*)Offset::PartyDisband, cmd);
		reinterpret_cast<void(*)(void*)>(Offset::EndLobby)(nullptr); 
		Globals::BaseModule + Offset::EndLobby;
		memcpy((BYTE*)Offset::PartyDisband, post, 512);
	}
	int SpectatorCount() {

		if (!GameCall<bool>(Offset::CL_Main_IsBRGameType)(0))
			return 0;

		auto CG_Omnvar_GetData = reinterpret_cast<unsigned int(*)(int, int, unsigned int*)>(Offset::GetData);
		auto BG_Omnvar_GetIndexByName = reinterpret_cast<int(*)(const char*)>(Offset::GetIndexByName);
		int Spectators = BG_Omnvar_GetIndexByName(xorstr_("ui_br_active_spectators"));

		if (Spectators == -1)
			return 0;

		unsigned int IndexData;
		CG_Omnvar_GetData(0, Spectators, &IndexData);

		return IndexData;
	}
	bool InGameCheck2() {
		return !*(char*)(Offset::InGameCheck);
	}

}

#define DegreesToRadians(a) ((a)*((float)M_PI/180.0f))
#define RadiansToDegrees(a) ((a)*(180.0f/(float)M_PI))

void rotate_triangle(std::array<ImVec2, 3>& points, float rotation)
{
	ImVec2 points_center = ImVec2(points.at(0).x + points.at(1).x + points.at(2).x, points.at(0).y + points.at(1).y + points.at(2).y);
	points_center = ImVec2(points_center.x / 3, points_center.y / 3);

	for (auto& point : points)
	{
		point = ImVec2(point.x - points_center.x, point.y - points_center.y);

		const auto temp_x = point.x;
		const auto temp_y = point.y;

		const auto theta = DegreesToRadians(rotation);
		const auto c = cosf(theta);
		const auto s = sinf(theta);

		point.x = temp_x * c - temp_y * s;
		point.y = temp_x * s + temp_y * c;

		point = ImVec2(point.x + points_center.x, point.y + points_center.y);
	}

}

bool disableonkill = true;
int delay;
float prediction_value = 1.f;

bool fire_delay(bool should_delay)
{
	if (Aimbot::switch_delay < 1)
		return false;

	static std::chrono::milliseconds delta_time = std::chrono::milliseconds(0);

	if (should_delay && !delta_time.count())
		delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()) + std::chrono::milliseconds(Aimbot::switch_delay);

	if (delta_time >= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()))
		return true;
	else if (delta_time.count())
		delta_time = std::chrono::milliseconds(0);

	return false;
}

float toRadians(float deg)
{
	return 0.01745329238474369f * deg;
}

void angleVectors(Vector3 angles, Vector3* forward, Vector3* right, Vector3* up)
{
	float angle;
	static float sr, sp, sy, cr, cp, cy;

	angle = toRadians(angles.y);
	sy = sinf(angle);
	cy = cosf(angle);

	angle = toRadians(angles.x);
	sp = sinf(angle);
	cp = cosf(angle);

	angle = toRadians(angles.z);
	sr = sinf(angle);
	cr = cosf(angle);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1.0f * sr * sp * cy + -1.0f * cr * -sy);
		right->y = (-1.0f * sr * sp * sy + -1.0f * cr * cy);
		right->z = -1.0f * sr * cp;
	}

	if (up)
	{
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

Vector3 ImVec3Normalize(const Vector3& vec) {
	float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	Vector3 normalized_vec;
	if (magnitude > 0.0f) {
		normalized_vec.x = vec.x / magnitude;
		normalized_vec.y = vec.y / magnitude;
		normalized_vec.z = vec.z / magnitude;
	}
	else {
		normalized_vec.x = normalized_vec.y = normalized_vec.z = 0.0f;
	}
	return normalized_vec;
}



