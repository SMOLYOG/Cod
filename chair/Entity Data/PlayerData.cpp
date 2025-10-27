#pragma once
#include "..\Vector\Vector3.h"
#include "..\Globals\Globals.h"
#include "..\GameSDK\GameSDK.h"
#include "PlayerData.hpp"
#include <tchar.h>


std::array<std::string, 18> bones = { xorstr_("j_head"), xorstr_("j_neck"), xorstr_("j_spine4"), xorstr_("j_spineupper"), xorstr_("j_spinelower"), xorstr_("j_mainroot"), xorstr_("j_shoulder_le"), xorstr_("j_shoulder_ri"), xorstr_("j_hip_le"), xorstr_("j_hip_ri"), xorstr_("j_elbow_le"), xorstr_("j_elbow_ri"), xorstr_("j_knee_le"), xorstr_("j_knee_ri"), xorstr_("j_ankle_le"), xorstr_("j_ankle_ri"), xorstr_("j_wrist_le"), xorstr_("j_wrist_ri") };

bool bonescan(int i, const char*& bone) {
	Vector3 origin;

	if (!cfg::Aimbot::Targeting::BoneScan)
		return false;

	for (int l = 0; l < bones.size(); l++) {

		if (!GlobalPlayerData::GetBonePosition(i, bones[l].c_str(), &origin))
			continue;

		if (GlobalPlayerData::SightTrace(&MyClient.Head_Pos, &origin, MyClient.Client_Num)) {
			bone = bones[l].c_str();
			Entity_t[i].Is_Visible = true;
			return true;
		}
	}
	Entity_t[i].Is_Visible = false;
	return false;
}


bool GrabMyClient() {

	char Client_Name[48];

	MyClient.Got_Client = false;

	if (!Globals::InGame2)
		return false;

	auto Ps = *(PlayerState_T*)(Offset::CGArray + Offset::PlayerState);

	MyClient.Client_Num = Ps.ClientNumber;

	MyClient.C_Entity = GlobalPlayerData::GetEntity(MyClient.Client_Num);
	if (MyClient.C_Entity == NULL)
		return false;

	GameCall<void>(Offset::A_CG_Entity_GetPlayerViewOrigin)(Ps, &MyClient.View_Origin);

	if (!GlobalPlayerData::GetBonePosition(MyClient.Client_Num, xorstr_("tag_origin"), &MyClient.Position))
		return false;
	if (!GlobalPlayerData::GetBonePosition(MyClient.Client_Num, xorstr_("j_head"), &MyClient.Head_Pos))
		return false;

	MyClient.FOV = *reinterpret_cast<float*>(Offset::CGArray + Offset::GetPlayerFOV);
	MyClient.FOVReal = Math::GetFOVValue(MyClient.FOV);

	MyClient.Client_Health = GlobalPlayerData::GetClientInfo(MyClient.Client_Num)->Health;

	MyClient.Client_Team = GlobalPlayerData::Score(MyClient.Client_Num)->team;

	MyClient.View_Angles = GlobalPlayerData::GetAngle(MyClient.C_Entity);
	MyClient.View_Angles2 = Ps.ViewAngles;

	MyClient.Client_Weapon = PlayerDataBase::GetWeaponName(MyClient.Client_Num, MyClient.C_Entity);

	GlobalPlayerData::GetPlayerName(MyClient.Client_Num, Client_Name);
	MyClient.Client_Name = Client_Name;
	MyClient.Got_Client = true;

	return true;
}

int getType(DWORD64 Centity) {
	return *(short*)(Centity + Offset::nextState + 0x8);
}

__forceinline bool GetEntitys() {
	if (!MyClient.Got_Client)
		return false;

	char Name[48];
	const char* targetbone;
	for (int i = 0; i < 2048; i++) {

		if (i == MyClient.Client_Num)
			continue;

		Entity_t[i].CanDraw = false;
		Entity_t[i].C_Entity = NULL;
		Entity_t[i].E_Type = 0;
		Entity_t[i].tag_origin = Vector3(-9999, -9999, -9999);
		Entity_t[i].ViewAngles = Vector3(-9999, -9999, -9999);

		Entity_t[i].C_Entity = GlobalPlayerData::GetEntity(i);
		if (Entity_t[i].C_Entity == NULL)
			continue;

		Entity_t[i].E_Type = getType(Entity_t[i].C_Entity);
		if (Entity_t[i].E_Type != EntityType_T::ET_ACTOR && Entity_t[i].E_Type != EntityType_T::ET_AGENT && Entity_t[i].E_Type != EntityType_T::ET_PLAYER)
			continue;

		if (!GlobalPlayerData::GetBonePosition(i, xorstr_("tag_origin"), &Entity_t[i].tag_origin)) 
			continue;

		Entity_t[i].distance = Math::UnitsToMeters(Math::GetDistance(MyClient.View_Origin, Entity_t[i].tag_origin));
		
		if (Entity_t[i].distance >= 400)
			continue;
		
		if (!GlobalPlayerData::GetBonePosition(i, xorstr_("tag_eye"), &Entity_t[i].tag_eye))
			continue;
		
		Entity_t[i].ViewAngles = GlobalPlayerData::GetAngle(Entity_t[i].C_Entity); 
		
		Entity_t[i].tag_eye_Visible = GlobalPlayerData::SightTrace(&MyClient.Head_Pos, &Entity_t[i].tag_eye, MyClient.Client_Num);
	
		if (!GlobalPlayerData::GetClientInfo(i)) {
			Entity_t[i].health = 127;
			Entity_t[i].IsDowned = false;
		}
		else {
			Entity_t[i].IsDowned = GlobalPlayerData::GetClientInfo(i)->Flags & Flags_T::Downed;
			Entity_t[i].health = GlobalPlayerData::GetClientInfo(i)->Health;
		}
	
		if (!GlobalPlayerData::Score(i))
			Entity_t[i].team = 0;
		else {
			Entity_t[i].team = GlobalPlayerData::Score(i)->team;
		}
		
		Entity_t[i].IsFriendly = Entity_t[i].team == MyClient.Client_Team;
	
		if (Entity_t[i].E_Type == EntityType_T::ET_ACTOR) {
			Entity_t[i].Weapon = xorstr_("NULL");
			Entity_t[i].Name = xorstr_("ACTOR");
		}
		else if (Entity_t[i].E_Type == EntityType_T::ET_AGENT)
		{
			Entity_t[i].Weapon = xorstr_("NULL");
			Entity_t[i].Name = xorstr_("AGENT");
		}
		else if (Entity_t[i].E_Type == EntityType_T::ET_PLAYER)
		{
			GlobalPlayerData::GetPlayerName(i, Name);
			Entity_t[i].Name = Name;
			Entity_t[i].Weapon = PlayerDataBase::GetWeaponName(i, Entity_t[i].C_Entity);
		}
	
		if (!bonescan(i, targetbone)) {
			if (!GlobalPlayerData::GetBonePosition(i, PlayerDataBase::GetBones(Aimbot::Bone), &Entity_t[i].Target_Bone_Pos))
				continue;
			Entity_t[i].Is_Visible = GlobalPlayerData::SightTrace(&MyClient.Head_Pos, &Entity_t[i].Target_Bone_Pos, MyClient.Client_Num);
		}
		else 		
			if (!GlobalPlayerData::GetBonePosition(i, targetbone, &Entity_t[i].Target_Bone_Pos))
				continue;
	
		if (Aimbot::Overide::Enable)		
			if (!GlobalPlayerData::GetBonePosition(i, PlayerDataBase::GetBones(Aimbot::Overide::Bone), &Entity_t[i].Override_Target_Bone_Pos))
				continue;
	
		if (cfg::Aimbot::Health_Override::Enable)			
			if (!GlobalPlayerData::GetBonePosition(i, PlayerDataBase::GetBones(cfg::Aimbot::Health_Override::Bone), &Entity_t[i].Health_Target_Bone_Pos))
				continue;
	
		Entity_t[i].Is_In_View = GlobalPlayerData::WorldToScreen(&Entity_t[i].tag_origin, &Entity_t[i].tag_origin_2D);
	
		Entity_t[i].CanDraw = true;
	
		if (!PlayerDataBase::CalculateBoneESP(i))
			continue;
		
		if (!PlayerDataBase::CalculateBoxEsp(i))
			continue;
		
	}

	return true;

}