#pragma once
#include "..\Structures\Structures.h"
#include "..\Vector\Vector2.h"
#include "..\Vector\Vector3.h"
#include "..\ImGui/imgui.h"
#include <IntSafe.h>
#include <vector>
#include "..\Globals\Globals.h"
#include "..\Third Party\SpoofCall\Spoof Call.h"
#include "..\Math\Math.h"


extern std::vector<Tracer_T> Tracer_V;
extern PlayerState_T* PlayerState;
extern DWORD64 C_Entity;
extern ImVec2 Screen;
extern MyClient_s MyClient;
#define OFFSETA( type, func, offset , i) type& func() { return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( GlobalPlayerData::GetEntity(i); + offset.casta() ); }

//#define EvaluateColor(i, TargetColor, IsRainbow, SolidColor) (i == PlayerDataBase::Target ? (Color::Rainbow::Target ? Color::Rainbow::Rainbow : TargetC) : (Entity_t[i].IsFriendly ? (Entity_t[i].Is_Visible ? (IsRainbow[2] ? Color::Rainbow::Rainbow : SolidColor[2]) : (IsRainbow[3] ? Color::Rainbow::Rainbow : SolidColor[3])) : (Entity_t[i].Is_Visible ? (IsRainbow[0] ? Color::Rainbow::Rainbow : SolidColor[0]) : (IsRainbow[1] ? Color::Rainbow::Rainbow : SolidColor[1]))))
#define EvaluateColor(i, TargetColor, IsRainbow, SolidColor,highlightcol) (Lobby[i].highlight ? highlightcol : (i == PlayerDataBase::Target ? (Color::Rainbow::Target ? Color::Rainbow::Rainbow : TargetColor) : (Entity_t[i].IsFriendly ? (Entity_t[i].Is_Visible ? (IsRainbow[2] ? Color::Rainbow::Rainbow : SolidColor[2]) : (IsRainbow[3] ? Color::Rainbow::Rainbow : SolidColor[3])) : (Entity_t[i].Is_Visible ? (IsRainbow[0] ? Color::Rainbow::Rainbow : SolidColor[0]) : (IsRainbow[1] ? Color::Rainbow::Rainbow : SolidColor[1])))))

extern void UA();

namespace PlayerDataVisuals {
	extern void drawString2(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i);
	extern void drawString3(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i);
}

namespace GlobalPlayerData {
	extern bool PopulateBoneData(int i, Vector2* BoneData, std::vector<std::string> Bone);
	extern bool SightTrace(const Vector3* Start, const Vector3* End, int LocalPlayer);
	extern bool SightTrace2(const Vector3* Start, const Vector3* End, int LocalPlayer);
	extern bool GetBonePosition(int ent, const char* Bone, Vector3* Origin);
	extern bool WorldToScreen(Vector3* WorldPosition, Vector2* OutPosition);
	extern unsigned __int64 getBoneHash(const char* input);
	extern void GetPlayerName(int i, char* Name);
	extern void GetPlayerNameWithHash(int i, char* Name);
	extern ClientData_T* GetClientInfo(int i);
	extern DWORD64 GetEntity(int i);
	extern int GetMaxPlayerCount();
	extern Vector3 GetAngle(DWORD64 C_Entity);
	extern Score_T* Score(int i);

}

extern void rotate_triangle(std::array<ImVec2, 3>& points, float rotation);

namespace PlayerDataBase {
	struct PlayerInformation
	{
	public:
		Vector2 RealScreenPosition;
		Vector2 Dimensions;
		Vector3 ViewAngles;
		std::string Weapon;
		bool InGulagMatch;
		bool BeingRevived;
		bool SelfReviving;
		std::string Names;
		Vector3 Position;
		bool RiotShield;
		float Distance;
		bool Crouched;
		bool InScreen;
		bool Friendly;
		float RealFOV;
		bool InGulag;
		bool Visible;
		bool Downed;
		int Assists;
		bool Prone;
		int Health;
		int Deaths;
		int Damage;
		float FOV;
		bool Draw;
		int Score;
		int Kills;
		int Ping;
		int Type;
		int Rank;
		int Team;
		float KD;
		bool targetbonevis;


		struct BonePoints {
			Vector2 RightArm[5];
			Vector2 RightLeg[5];
			Vector2 LeftArm[5];
			Vector2 LeftLeg[5];
			Vector2 Body[7];

			Vector3 TargetOverride;
			Vector3 SelfOrigin;
			Vector3 SelfHead;
			Vector3 Target;
			Vector3 bonescanvischeck;
			Vector3 selfeye;
			Vector3 j_head;
			Vector3 j_neck;
			Vector3 j_spine4;
			Vector3 j_shoulder_le;
			Vector3 j_shoulder_ri;
			Vector3 j_elbow_le;
			Vector3 j_elbow_ri;
			Vector3 j_wrist_le;
			Vector3 j_wrist_ri;
			Vector3 j_mainroot;
			Vector3 j_knee_le;
			Vector3 j_knee_ri;
			Vector3 j_ankle_le;
			Vector3 j_ankle_ri;
			Vector3 tag_eye;
		};

		struct Bones {
			BonePoints Bones;
		};

		Bones PlayerBones[2048];

		PlayerInformation() : RealScreenPosition(), ViewAngles(), Weapon(), InGulagMatch(), BeingRevived(), SelfReviving(), Dimensions(), Names(), Position(), RiotShield(), Distance(), Crouched(), InScreen(), Friendly(), InGulag(), Visible(), Downed(), Assists(), Health(), Prone(), Deaths(), Damage(), Draw(), Score(), Kills(), Ping(), Type(), Rank(), FOV(), Team(), KD(), PlayerBones() { }
	}; extern std::vector<PlayerInformation> PlayerList;

	extern std::string GetWeaponName(int i, DWORD64 Centity);
	extern const char* GetBones(int bone);
	extern bool CalculateBoneESP(int i);
	extern bool CalculateBoxEsp(int i);
	extern void CalculateTracers();
	extern int EntityNumber;
	extern int Target;
}
extern int test;


namespace NoRecoil {
	class SecuredVector3 {
	private:
		int Keys[5];

		__forceinline uintptr_t Base(int idx) const;
	public:
		void Set(float x, float y, float z);
		void Set(Vector3 value);
		Vector3 Get() const;
	};

	extern void NoRecoil();
}


namespace AimBot {

	enum boneIndex : int32_t
	{
		tag_origin,
		tag_sync,
		j_mainroot,
		j_spinelower,
		j_spineupper,
		j_spine4,
		j_neck,
		j_head,
		j_helmet,
		j_clavicle_le,
		j_shoulder_le,
		j_elbow_le,
		j_wrist_le,
		j_clavicle_ri,
		j_shoulder_ri,
		j_elbow_ri,
		j_wrist_ri,
		j_hip_le,
		j_knee_le,
		j_ankle_le,
		j_ball_le,
		j_hip_ri,
		j_knee_ri,
		j_ankle_ri,
		j_ball_ri,
		tag_stowed_hip_rear,
		j_hiptwist_le,
		j_hiptwist_ri,
		tag_inhand,
		tag_shield_back,
		tag_weapon_chest,
		j_gun_adjust,
		j_gun,
		j_shouldertwist_le,
		j_shouldertwist_ri,
		tag_eye,
		tag_weapon_right,
		j_sheild_ri,
		j_wristfronttwist1_le,
		tag_reflector_arm_le,
		tag_reflector_arm_ri,
		tag_helmetlight,
		tag_accessory_left,
		tag_accessory_right,
		tag_weapon_left,
		tag_ik_wrist_loc_le,
		tag_ik_wrist_loc_ri,
		j_hipholster_le,
		j_hipholster_ri,
		j_hip_proc_le,
		j_hip_proc_ri,
		j_dummy_knee_dist,
		j_spinelower_lift,
		j_proc_spinelower,
		j_proc_spinelower2,
		j_proc_spineupper,
		j_ik_foot_root,
		tag_ik_foot_loc_le,
		tag_ik_foot_loc_ri,
		j_antislide_ik,
		tag_wrist_attach_le,
		j_proc_hip_lift_le,
		j_proc_hip_lift_ri,
		j_proc_hip_lift_aim_le,
		j_proc_hip_lift_aim_ri,
		j_proc_dummy_spinelift,
		j_chest,
		j_dummy_slingcenteraim,
		j_dummy_sling_spine,
		j_groinprotector,
		j_proc_lift_clavicle_le,
		j_proc_lift_clavicle_ri,
		j_proc_stowed_chest,
		j_proc_spinelift,
		j_proc_spinelower_lift,
		j_proc_spineupper_lift,
		j_sling_spine
	};


	extern void SetViewAngles(Vector3 angle);

}

namespace Hooks {
	extern void(*Tracers)(uintptr_t thisptr, int sourceEntityNum, int targetEntityNum, unsigned int targetScriptableIndex, unsigned __int8 boneIndex, __int64 weapon, bool isAlternate, const Vector3* initialPos, const Vector3* startPos, const Vector3* position, const Vector3* normal, int surfType, int event, unsigned int impactEffects, int hitContents, const int hitImpactDelayOverride, __int64 hitArmorType, __int64 hitmarkerType, const  __int64 optionalEventLodData, char unknown);
	extern __int64(*SelfChams)(int localClientNum, __int64 a2, __int64 a3, unsigned int EntityNumber, int renderFlags, __int64 a6, OutlineInfo_T* hudOutlineInfo, __int64 a8, float materialTime, unsigned int a10, char markableViewmodel);
	extern void(*Chams)(__int64 a1, Pose_T* a2, int a3, int EntityNumber, int renderFlags, ShaderData_T* a6, uint32_t* a7, int a8);
	extern void(*ShellShock)(unsigned int unk, __int64 CGArray, __int64  unk2, int unk3, int  unk4);
	extern ClientFov_T* (*FOV)(ClientFov_T* result, int entNum, int fovSpace, bool updateFovWeights, unsigned int* a5);
	extern __int64* (*CLActive)(__int64 a1, __int64 _RDX, int a3);
	extern bool(*ThirdPerson)(__int64 a1, __int64 a2);
	extern void(*PredictedPlayerState)(__int64 a1);
	extern bool(*BlackBoxIntalized);
	extern void(*sub_7FF6D083F570_o)(__int64 a1);
	inline uintptr_t packet_hook_orginal;
	extern uintptr_t CG_PredictMP_PredictPlayerState_original;
	extern void (*oCG_EntityMP_CalcLerpPositions)(int localClientNum, DWORD64 centity);
	extern void hkCG_EntityMP_CalcLerpPositions(int localClientNum, DWORD64 centity);
	extern void HookTracers(uintptr_t thisptr, int sourceEntityNum, int targetEntityNum, unsigned int targetScriptableIndex, unsigned __int8 boneIndex, __int64 weapon, bool isAlternate, const Vector3* initialPos, const Vector3* startPos, const Vector3* position, const Vector3* normal, int surfType, int event, unsigned int impactEffects, int hitContents, const int hitImpactDelayOverride, __int64 hitArmorType, __int64 hitmarkerType, const  __int64 optionalEventLodData, char unknown);
	extern __int64 HookSelfChams(int localClientNum, __int64 a2, __int64 a3, unsigned int EntityNumber, int renderFlags, __int64 a6, OutlineInfo_T* hudOutlineInfo, __int64 a8, float materialTime, unsigned int a10, char markableViewmodel);
	extern void HookChams(__int64 a1, Pose_T* a2, int a3, int EntityNumber, int renderFlags, ShaderData_T* a6, uint32_t* a7, int a8);
	extern void HookShellShock(unsigned int unk, __int64 CGArray, __int64  unk2, int unk3, int  unk4);
	extern ClientFov_T* HookFOV(ClientFov_T* result, int entNum, int fovSpace, bool updateFovWeights, unsigned int* a5);
	extern bool HookThirdPerson(__int64 a1, __int64 a2);
	extern bool HookBlackBoxIntalized();

}
namespace JUP {

	extern void SetCbuff(const char* fmt, ...);
	extern int SpectatorCount();
	extern bool InGameCheck2();

}

extern DWORD64 C_Entity;

extern bool Delay_Timer(bool should_delay, int Delay);

#define ADD_INTERFACE2( type, var_name, address ) type* var_name = address.casta< type* >();
