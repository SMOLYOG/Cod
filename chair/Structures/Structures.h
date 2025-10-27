#pragma once
#include "..\ImGui\imgui.h"
#include "..\Vector\Vector3.h"
#include "..\Vector\Vector2.h"
#include <vector>
#include <IntSafe.h>


enum weapClass_t : __int32
{
	WEAPCLASS_NONE = 0x0,
	WEAPCLASS_RIFLE = 0x1,
	WEAPCLASS_SNIPER = 0x2,
	WEAPCLASS_MG = 0x3,
	WEAPCLASS_SMG = 0x4,
	WEAPCLASS_SPREAD = 0x5,
	WEAPCLASS_PISTOL = 0x6,
	WEAPCLASS_GRENADE = 0x7,
	WEAPCLASS_ROCKETLAUNCHER = 0x8,
	WEAPCLASS_TURRET = 0x9,
	WEAPCLASS_THROWINGKNIFE = 0xA,
	WEAPCLASS_NON_PLAYER = 0xB,
	WEAPCLASS_ITEM = 0xC,
	WEAPCLASS_BEAM = 0xD,
	WEAPCLASS_BALL = 0xE,
	WEAPCLASS_FIST = 0xF,
	WEAPCLASS_NUM = 0x10,
};

enum WeaponFireType_T : __int32 {
	WEAPON_FIRETYPE_FULLAUTO = 0x0,
	WEAPON_FIRETYPE_SINGLESHOT = 0x1,
	WEAPON_FIRETYPE_BURST = 0x2,
	WEAPON_FIRETYPE_DOUBLEBARREL = 0x3,
	WEAPON_FIRETYPE_DOUBLEBARREL_DUALTRIGGER = 0x4,
	WEAPON_FIRETYPE_BEAM = 0x5,
	WEAPON_FIRETYPECOUNT = 0x6,
};

struct PlayerState_T
{
	char pad_0[0x168];                        // 0x0
	Vector3 DeltaAngles;                    // 0x168
	char pad_1[0x19C];                        // 0x174
	int ClientNumber;                            // 0x310
	char pad_3[0x8];                        // 0x314
	Vector3 ViewAngles;                        // 0x31
	char pad_4[0x730C];
};


struct Pose_T {
	unsigned __int8 Type;
	unsigned __int8 CullIn;
	unsigned __int8 PosePrecise;
	unsigned __int8 Origin;
	volatile int MDAOCullIn;
	unsigned __int8 RagdollFlag;
	unsigned __int8 EntityPose;
	unsigned __int8 HasEntityPos;
	unsigned __int8 MayhemInstance;
	bool Mayhem;
	bool ReuseSkeletlePose;
	int RagDollHandle;
	int KillCamRagDoll;
	int PhysicsId;
};

class OutlineInfo_T {
public:
	char pad[8]; //0x0
	uint32_t Color;//0x0
	char pad1[8];
	bool Visible;
	bool NonVisible;
	char pad2[1];
	bool Fill;
	char pad3[5];
	uint8_t Render;
	uint8_t Width;
	char pad4[8510];
};
struct ShaderData_T {

	char pad[0xA8];
	OutlineInfo_T OutlineInfo;
};

struct ClientData_T {
	char pad_0000[112]; //0x0000
	int32_t Flags; //0x0070
	char pad_0074[16]; //0x0074
	int32_t Health; //0x0084
	char pad_1[0x40];
};

struct ClientInfo_T {
	char pad[0x1838];
	ClientData_T ClientInfo[200];
};

struct UsableRef_T {
	unsigned int useIndex;
	unsigned __int16 usePartitionIndex;
	__int8 useClass;
	unsigned __int8 useData;
};

struct ClientFov_T {
	float Adjustment;
	float Final;
	float Base;
};

enum scr_string_T : __int32 {

};

enum EntityType_T : __int16 {
	ET_FIRST = 0x0,
	ET_GENERAL = 0x0,
	ET_PLAYER = 0x1,
	ET_PLAYER_CORPSE = 0x2,
	ET_ITEM = 0x3,
	ET_MISSILE = 0x4,
	ET_INRIPTMOVER = 0x6,
	ET_SOVISIBLE = 0x5,
	ET_SCUND = 0x7,
	ET_FX = 0x8,
	ET_LOOP_FX = 0x9,
	ET_PRIMARY_LIGHT = 0xA,
	ET_TURRET = 0xB,
	ET_HELICOPTER = 0xC,
	ET_PLANE = 0xD,
	ET_VEHICLE = 0xE,
	ET_VEHICLE_CORPSE = 0xF,
	ET_VEHICLE_SPAWNER = 0x10,
	ET_AGENT = 0x10,	
	ET_ACTOR = 0x12,
	ET_AGENT_CORPSE = 0x13,
	ET_ACTOR_SPAWNER = 0x14,
	ET_ACTOR_CORPSE = 0x15,
	ET_PHYSICS_CHILD = 0x16,
	ET_BEAM = 0x17,
	ET_CLIENT_CHARACTER = 0x18,
	ET_RAGDOLL_CONSTRAINT = 0x19,
	ET_PHYSICS_VOLUME = 0x1A,
	ET_COVERWALL = 0x1B,
	ET_INFO_VOLUME_GRAPPLE = 0x1C,
	ET_EVENTS = 0x1D,
	ET_COUNT = 0x1E,
	ET_MAX = 0x100,
};

struct BitFlag_T {
	BitFlag_T() = default;

	BitFlag_T(uintptr_t flags) : m_flags(flags) {}

	~BitFlag_T() = default;

	uintptr_t  m_flags{};

	inline bool Has(uintptr_t flag) {
		return m_flags & flag;
	}

	inline void Add(uintptr_t flag) {
		m_flags |= flag;
	}

	inline void Remove(uintptr_t flag) {
		m_flags &= ~flag;
	}

	inline bool Empty() {
		return !m_flags;
	}
};

struct Weapon_T
{
	unsigned __int16 weaponIdx;
	char pad[0x44];
}; // Size: 0x46 | 70

enum LocalClientNum_t
{
	LOCAL_CLIENT_INVALID = 0xFFFFFFFF,
	LOCAL_CLIENT_0 = 0x0,
	LOCAL_CLIENT_1 = 0x1,
	LOCAL_CLIENT_LAST = 0x1,
	LOCAL_CLIENT_COUNT = 0x2,
};

class Tracer_T {
public:
	bool W2SSuccess, Animation;
	int StartTime;
	Vector2 HitPos2D, StartPos2D;
	Vector3 HitPos3D, StartPos3D;
	ImVec4 ShadowColor, HitMarkerColor, TracerColor;
	float ShadowAlpha, HitMarkerAlpha, TracerAlpha;
};

struct Score_T
{
	int client; // 0x00
	int status; // I didn't reverse this, I am just keeping it as a padding since it matches. It could be valid anyways.
	int score; // 0x08
	int ping; // I didn't reverse this, I am just keeping it as a padding since it matches. It could be valid anyways.
	int deaths; // 0x10
	int team; // 0x14
	bool isBot;
	int kills; // 0x1C
	int Rank;
	int prestige_mp;
	const char* rankDisplayLevel;
	int assists; // 0x2C
	char pad_0x30[0x60];
}; // size 0x90

enum Flags_T : uint32_t {
	InGulag = 0x2 << 8,
	InGulagMatch = 0x4 << 8,
	Downed = 0x08 << 8,
	BeingRevived = 0x10 << 8,
	SelfReviving = 0x20 << 8,

};
typedef struct UserCMD_S {
	BitFlag_T Buttons;        // 0x0
	char pad_0008[0x14];    // 0x8
	int serverTime;            // 0x1C
	char pad_0020[0x8];        // 0x20
	int CommandTime;        // 0x28
	char pad_002C[4];        // 0x2C
	int Angle[3];            // 0x30
	Weapon_T Weapon;            // 0x3C
	char pad_0[0x56];        // 0x8C
	unsigned __int16 meleeChargeEnt;    // 0xE2
	char pad_003C[0x154];                // 0xE4
	char pad_0010[0x10];                // 0xE4
} UserCMD_T;




