#pragma once
#include "..\Globals\framework.h"
#include "..\Third Party\xor.h"
#include "..\Memory\address.hpp"
#include "..\Vector\Vector2.h"
#include "..\Vector\Vector3.h"

extern int nigggg;
extern bool testing[10];

extern int sigcount;


namespace AuthStats {
	extern std::string Responce;
	extern std::string NumUsers;
	extern std::string Expiry;
}

namespace cfg {

	namespace Esp {

		extern bool Self_Esp;
		extern int InFov_Count;
		extern bool Platform;
		extern bool Device;
		extern bool Talking;

		namespace Drawing_Settings {
			extern float Font_Size;
			extern int Snapline_Pos;
			extern int box_Type;

		}
	}

	namespace Crosshair {
		extern float speed;
		extern float linelength;
		extern float linegap;
		extern float dotradius;
		extern bool enabledot;
		extern bool spin;
	}

	namespace radar {

		extern bool Enable;
		extern bool Ignore_Team;
		extern bool Ignore_Invis;
		extern bool Ignore_Knocked;
		extern float Alpha;

		namespace Color {
			extern float Team_Vis[4];
			extern float Team_non_Vis[4];
			extern float Enemy_Vis[4];
			extern float Enemy_Non_Vis[4];
		}


	}
	namespace Aim_Target {

		extern bool Target_SnapLine;

		namespace Color {

			extern float Target_Esp[4];
			extern float Target_Crosshair[4];
			extern float Target_FOV[4];
		}
	}

	namespace Exploits {

		namespace Melee_Lunge {
			extern bool Enable;
			extern float Max_Distance;
			extern bool Ignore_Invis;
			extern bool Ignore_Team;
			extern bool Ignore_Knocked;
			extern int Type;
		}

		namespace Auto_Reload {
			extern bool Enable;
			extern int Bullet_Count_AR;
			extern int Bullet_Count_Sniper;
			extern int Bullet_Count_LMG;
			extern int Bullet_Count_SMG;
			extern int Bullet_Count_Pistol;
			extern bool Enable_AR;
			extern bool Enable_Sniper;
			extern bool Enable_LMG;
			extern bool Enable_SMG;
			extern bool Enable_Pistol;
			extern bool Stop_When_In_View;
			extern bool Stop_When_Targeting;
		}

		namespace Rapid_fire {
			extern int Shot_Delay;
		}

		namespace Chat_Spam {
			extern bool Enable;
			extern bool Spam_Message;
			extern char Chat_Message[255];
			extern int Delay_Time;

		}


		namespace Profanity_Checks {
			extern bool Enable;
		}
	}


	namespace Aimbot {

		namespace Extras {
			extern bool Auto_Ads;
		}

		namespace Targeting {
			extern bool BoneScan;
			extern int Type;
		}
		namespace Health_Override {
			extern bool Enable;
			extern int Health_Trigger;
			extern int Bone;
		}
	}

	namespace Chams {
		extern bool Ignore_Team;
		extern bool Ignore_Invis;
		extern bool Ignore_Knocked;

		namespace Color {
			extern float Team_Vis[4];
			extern float Team_non_Vis[4];
			extern float Enemy_Vis[4];
			extern float Enemy_Non_Vis[4];
		}
	}
}

namespace IncorrectOffset {
	extern bool DDL_NavigateBlueprint;
	extern bool DDL_CreateContext;
	extern bool WeaponDisplayName;
	extern bool RegisterFunction;
	extern bool UserCMDNumberAAB;
	extern bool DDL_GetRootState;
	extern bool GetBonePosition;
	extern bool ConvertToString;
	extern bool GetIndexByName;
	extern bool DDL_MoveToPath;
	extern bool LUI_BeginTable;
	extern bool LUI_BeginEvent;
	extern bool MaxPlayerCount;
	extern bool GetClientInfo;
	extern bool WorldToScreen;
	extern bool GetPlayerTeam;
	extern bool GetPlayerName;
	extern bool GetEntityType;
	extern bool DecryptString;
	extern bool DDL_InitState;
	extern bool DDL_LoadAsset;
	extern bool DDL_GetBuffer;
	extern bool DDL_SetString;
	extern bool DDL_GetString;
	extern bool BluePrintData;
	extern bool UserCMDNumber;
	extern bool LUI_SetString;
	extern bool UserCMDPackAngle;
	extern bool DDL_SetFloat;
	extern bool PartyDisband;
	extern bool LUI_EndTable;
	extern bool LUI_EndEvent;
	extern bool A_PacketDup;
	extern bool B_PacketDup;
	extern bool InGameCheck;
	extern bool DDL_GetType;
	extern bool DDL_SetEnum;
	extern bool UpdateBytes;
	extern bool ThirdPerson;
	extern bool LUI_SetBool;
	extern bool PlayerState;
	extern bool FindString;
	extern bool SightTrace;
	extern bool WeaponName;
	extern bool DDL_SetInt;
	extern bool DDL_GetInt;
	extern bool ShellShock;
	extern bool LUI_SetInt;
	extern bool Controller;
	extern bool PlaceFull;
	extern bool GetEntity;
	extern bool DDL_Parse;
	extern bool SelfChams;
	extern bool ANoRecoil;
	extern bool LUI_LuaVM;
	extern bool GetButton;
	extern bool GetCamos;
	extern bool GameType;
	extern bool EndLobby;
	extern bool NoRecoil;
	extern bool GetField;
	extern bool PushBool;
	extern bool Tracers;
	extern bool UserCMD;
	extern bool GetData;
	extern bool ClanTag;
	extern bool CGArray;
	extern bool RefDef;
	extern bool JmpRbx;
	extern bool GetTop;
	extern bool SetTop;
	extern bool Chams;
	extern bool FOV;

	extern bool ViewAngles;
	extern bool WeaponMap;
	extern bool ThirdPersonCrosshair;
	extern bool CalculateMuzzlePoint;
	extern bool WeaponFlash;
	extern bool GetAngle;
	extern bool WeaponSystemsArray;
	extern bool CLActive;
	extern bool PredictedPlayerState;
	extern bool RiotShield;
	extern bool UserCMDUnpackAngle;
	extern bool WorldPosistionToCompass;
	extern bool DrawMapLayer;
	extern bool EntityState;
	extern bool GetPlayerFOV;
	extern bool WeaponFireType;
	extern bool Score;
	extern bool LegacyTrace;
	extern bool BlackBoxIntalized;
}

namespace Exploits {
	extern bool DynamicThirdPerson;
	extern bool NoShellShock;
	extern bool ThirdPerson;
	extern bool NightVision;
	extern bool ExtendedFOV;
	extern bool UnlockAll;
	extern bool Airstuck;
	extern bool SpinBot;
	extern bool* Array[];
};

namespace Commands {
	extern bool BypassPrivateMatches;
	extern bool ProfanityNameBypass;
	extern bool DisableBlood;

	extern bool InGameCrosshair;
	extern bool NoShieldShake;
	extern bool SwapLoadouts;
	extern bool BreakCamera;
	extern bool DevPlayList;
	extern bool DrawFPS;
	extern bool NoFog;
	extern bool NoGun;
	extern float Map;
	extern float FOV;

	extern const char* CMDArray[];
	extern char Input[100];
	extern bool* Array[];
};

namespace KeyBinds {
	extern int DynamicThirdPerson;
	extern int NightVision;
	extern int Uninject;
	extern int Overide;
	extern int Aimbot;
	extern int Menu;
	extern int Aimbot2;
	extern int AirStuck;
	extern bool ControllerAirstuck;
	extern bool ControllerDynamicThirdPerson;
	extern bool ControllerNightVision;
	extern bool ControllerUninject;
	extern bool ControllerOveride;
	extern bool ControllerAimbot;
	extern bool ControllerAimbot2;
	extern bool ControllerMenu;
};

namespace Visuals {
	namespace Main {
		extern bool Draw_Box;
		extern bool DrawPlayerSkeleton;
		extern bool DrawPlayerDistance;
		extern bool DrawPlayerHealth;
		extern bool DrawPlayerWeapon;
		extern bool DrawPlayerName;
		extern bool DrawPlayerSnaplines;
		extern bool DrawPlayerAssists;
		extern bool DrawPlayerTeamID;
		extern bool DrawPlayerDeaths;
		extern bool DrawPlayerDamage;
		extern bool DrawPlayerKills;
		extern bool DrawPlayerScore;
		extern bool DrawPlayerPing;
		extern bool DrawPlayerRank;
		extern bool DrawPlayerKD;
		extern bool DrawFOV;
		extern bool Enable;
		extern int BoxType;
		extern bool DrawCrosshair;
		extern bool filled;
		extern float crosshair_size;
		extern int crosshair_type;

		extern float crosshair_thickness;
		extern bool* Array[];

		namespace Drawing {
			extern int SnapLinesPosX, SnapLinesPosY;
			extern int healthPos;
			extern float SnaplinesDistance;
			extern float SkeletonDistance;
			extern float DistanceDistance;
			extern float AssistsDistance;
			extern float TeamIDDistance;
			extern float DeathsDistance;
			extern float DamageDistance;
			extern float HealthDistance;
			extern float WeaponDistance;
			extern float KillsDistance;
			extern float ScoreDistance;
			extern float PingDistance;
			extern float RankDistance;
			extern float NameDistance;
			extern float BoxDistance;
			extern float KDDistance;
			extern float all;
			extern float Bonethicness;

			extern bool SelfReviving;
			extern bool BeingRevived;
			extern bool GulagMatch;
			extern bool RiotShield;
			extern bool Teamates;
			extern bool Visible;
			extern bool Downed;
			extern bool Gulag;
			extern bool Enemy;
			extern bool Bots;

			extern float* FloatArray[];
			extern bool* Array[];
		};

		namespace Checks {
			extern bool Spectated;
		};

		extern ImVec4 Rainbow;
	};

	namespace Miscellaneous {
		namespace Compass {
			extern int PosistionType;
			extern int TriangleSize;
			extern float Distance;
			extern bool Enable;
			extern int Size;
			extern bool Fill;
			namespace Drawing {
				extern bool SelfReviving;
				extern bool BeingRevived;
				extern bool GulagMatch;
				extern bool RiotShield;
				extern bool Teamates;
				extern bool Bots;
				extern bool Visible;
				extern bool Downed;
				extern bool Gulag;
				extern bool Enemy;
				extern bool* Array[];
			};
		};

		namespace Tracers {
			extern bool PlayerTracers;
			extern float Distance;
			extern bool Objects;
			extern bool Players;
			extern bool Enable;
			extern float Tracer_Col[4];
			extern float TracerThickness;
			extern int FadeInTime;
			extern int FadeOutTime, Duration, HitmarkerThickness;
			extern bool* Array[];
		};

		namespace LobbyStats {
			extern bool Enable;
			extern bool MapName;
			extern bool MaxPlayers;
			extern bool ViewOrgin;
			extern bool Position;
			extern bool ViewAngle;
			extern bool ClientNum;
			extern bool TeamID;
			extern bool Name;
			extern bool Weapon;
			extern bool health;
			extern bool Ping;
			extern bool Rank;
			extern bool Score;
			extern bool Kills;
			extern bool Deaths;
			extern bool Assists;
			extern bool Damage;
		}

		namespace DynamicRadar {
			extern const char* Image[1000];
			extern float TriangleSize;
			extern int ImageType;
			extern bool Enable;
			extern int RadarType;
			extern bool filled;
			extern float blipsize;
			extern float Distance;
			namespace Drawing {
				extern bool SelfReviving;
				extern bool BeingRevived;
				extern bool GulagMatch;
				extern bool RiotShield;
				extern bool Teamates;
				extern bool Bots;
				extern bool Visible;
				extern bool Downed;
				extern bool Gulag;
				extern bool Enemy;

				extern bool* Array[];
			};
		};
	};

	namespace Outlines {
		namespace Player {
			extern bool Invisible;
			extern bool Visible;
			extern bool Enable;
			extern bool Fill;
			extern int Width;
			extern int Type;

			extern bool* Array[];
		};

		namespace Vehicle {
			extern bool Invisible;
			extern bool Visible;
			extern bool Enable;
			extern bool Fill;
			extern int Width;
			extern int Type;

			extern bool* Array[];
		};

		namespace Self {
			extern bool Invisible;
			extern bool Visible;
			extern bool Enable;
			extern bool Fill;
			extern int Width;
			extern int Type;

			extern bool* Array[];
		};

		namespace Miscellaneous {
			extern bool Invisible;
			extern bool Visible;
			extern bool Enable;
			extern bool Fill;
			extern int Width;
			extern int Type;

			extern bool* Array[];
		};

		extern int Rainbow;
	};
};

namespace loot_esp {
	extern bool enable;
	extern bool equipment;
	extern bool lethals;
	extern bool tacticals;
	extern bool lootboxes;
	extern bool ammo;
	extern bool money;
	extern bool weapon_crates;
	extern bool weapons;
	extern bool misc;
	extern bool armour;
	extern bool Wallbuys;
	extern bool ZMMachines;
	extern bool ZMEE;
	extern bool ZMTrap;
	extern bool ignoreinvis;
	extern int max_distance;
	extern bool show_dist;
	extern float Loot_Color[4];
	extern float Loot_Color_Non_Vis[4];
}
namespace Color {
	//Invisible, Visible, Team Invisible, Team Visible	Example: Box[0][1] - Invisible, R Value
	//Tracer - Tracer, Hitmarker, Shadow  Example: Tracer[0][1] - Tracer, R Value
	//Chams - Player, Self, Vehicle, Misc  Example: Chams[0][1] - Player, R Value
	extern float DynamicRadar[4][4];
	extern float ChamsVec4[4][4];
	extern float SnapLines[4][4];
	extern float Skeleton[4][4];
	extern float Distance[4][4];
	extern float Compass[4][4];
	extern float Weapon[4][4];
	extern float Health[4][4];
	extern float Tracer[3][4];
	extern float Name[4][4];
	extern float Box[4][4];
	extern float Target[4];
	extern float FOV[4];
	extern float HighlightColor[4];
	extern int Chams[4];
	extern float crosshair[4];
	extern float Assists[4][4];
	extern float TeamID[4][4];
	extern float Deaths[4][4];
	extern float Damage[4][4];
	extern float Kills[4][4];
	extern float Score[4][4];
	extern float Ping[4][4];
	extern float Rank[4][4];
	extern float KD[4][4];
	extern float All[4][4];
	namespace Rainbow {
		extern bool DynamicRadar[4];
		extern bool SnapLines[4];
		extern bool Skeleton[4];
		extern bool Distance[4];
		extern bool Compass[4];
		extern bool Weapon[4];
		extern bool Health[4];
		extern bool Tracer[3];
		extern bool Chams[4];
		extern bool Name[4];
		extern bool Box[4];
		extern bool Target;
		extern bool FOV;

		extern bool Assists[4];
		extern bool TeamID[4];
		extern bool Deaths[4];
		extern bool Damage[4];
		extern bool Kills[4];
		extern bool Score[4];
		extern bool Ping[4];
		extern bool Rank[4];
		extern bool KD[4];
		extern bool crosshair;
		extern ImVec4 Rainbow;
	};
}

namespace AntiAim {
	namespace XAxis {
		extern bool Enable;
		extern int Type;
	};

	namespace YAxis {
		extern bool Enable;
		extern int Type;
	};
};

namespace Editors {
	namespace ClassName {

		extern int  Loadout;
		extern char Input[30];
	};
	namespace ForceSave {
		extern int Blueprint, Attach, Camo, Type;
		extern char Input[30], CamoInput[30];
	};
	namespace ClanTag {
		extern int  ClanTag, Color;
		extern char Input[30];
	};
	namespace Camo {
		extern int  Camo, Loadout, Slot;
		extern char Input[30], CamoInput[30];
	};
	namespace Perk {
		extern int Package, Perk, Slot;
		extern char Input[30];
	}
};

namespace Globals {
	extern bool HooksEnabled;
	extern bool ScanComplete;
	extern bool KeyBoardLock;
	extern bool RainbowMenu;
	extern bool GameType;
	extern bool InGame2;
	extern bool InGame;
	extern bool Moving;
	extern bool Steam;
	extern bool Open;
	extern int branding;
	extern bool rainbowesp;

	extern int ActiveTab, ActiveSubTab, Tab, SubTab, MaxPlayerCount, SpectatorCount;
	extern float TabAlpha, AddTab, SubTabAlpha, AddSubTab;

	extern TCHAR FilePath[MAX_PATH];
	extern uintptr_t BaseModule;
	extern DWORD ProcID;
	extern HANDLE HProc;
	extern HWND Hwind;
}

namespace Aimbot {
	extern bool Ignore_While_Spectated;
	extern int Spectator_Count;
	extern bool EnableSmoothing;

	extern float Acceration;
	extern float Smoothingx;
	extern float Smoothingy;
	extern float Smoothingz;
	extern bool DynamicFOV;
	extern bool RapidFire;
	extern bool AutoShoot;
	extern float Strength;
	extern bool LockOn;
	extern bool Enable;
	extern float FOV;
	extern int Type;
	extern int Bone;
	extern bool Silent;
	extern bool smart_bone_scan;
	extern bool Bone_Scan;
	extern int mode;
	extern bool Disable_on_kill;
	extern int switch_delay;
	extern int Miss_Chance;
	extern bool Enable_MissChance;
	extern int delay1;
	extern int delay2;
	extern bool canshoot;

	namespace Targeting {
		extern bool SelfReviving;
		extern bool BeingRevived;
		extern bool GulagMatch;
		extern bool RiotShield;
		extern bool Teamates;
		extern bool Visible;
		extern bool Downed;
		extern bool Gulag;
		extern bool Enemy;
		extern bool Bots;
		extern bool* Array[];
	};

	namespace Accuracy {
		extern bool Prediction;
		extern float Strength;
		extern bool NoRecoil;
	};

	namespace Overide {
		extern float Smoothing;
		extern float Strength;
		extern bool Enable;
		extern int Bone;
	};

	namespace Checks {
		extern bool DisableOnKill;
		extern bool Spectated;
		extern int Distance;
		extern int Type;
	};
}

namespace Aim_Warning {
	extern int Looking_Max_Distance;
	extern int Aiming_Max_distance;
	extern bool Aiming_At_You;
	extern bool Looking_At_You;
	extern float AimingAtYou[4];
	extern float LookingAtYou[4];
}
namespace Offset {
	extern shared::address_t CL_PlayerData_SetCustomClanTag;
	extern shared::address_t targetassist;
	extern shared::address_t commandqueue;
	extern shared::address_t swapchain;
	extern shared::address_t packet_test;
	extern shared::address_t BG_GetPlayerEyePosition;
	extern shared::address_t Weaponmap;
	extern shared::address_t CG_Handler;
	extern shared::address_t BG_Ballistics_TravelTimeForDistance;
	extern shared::address_t BG_GetBallisticInfoFunc;
	extern shared::address_t nextState;
	extern shared::address_t prevState;
	extern shared::address_t trampoline;
	extern shared::address_t CG_GetEntWeapon;
	extern shared::address_t A_CG_SnapshotMP_GetNextSnap;
	extern shared::address_t A_CG_SnapshotMP_GetPrevSnap;
	extern shared::address_t A_BgTrajectory_EvaluatePosTrajectory;
	extern shared::address_t A_CgTrajectory_CgTrajectory;
	extern shared::address_t p_CgWeaponMap__ms_instance;
	extern shared::address_t bdEventInfo;
	extern shared::address_t bdEventLog;
	extern shared::address_t v11_Offsets;
	extern uintptr_t CG_EntityMP_CalcLerpPositions;
	extern uintptr_t angle_offset;
	extern shared::address_t frametime;
	extern shared::address_t predictedPlayerState;

	inline shared::address_t CL_InputMP_ReadyToSendPacket = {};

	extern uintptr_t A_CL_Input_ClearAutoForwardFlag;
	extern uintptr_t Clactive;
	extern uintptr_t Get_Fov;
	extern uintptr_t UI_GetMapDisplayName_wrapper;
	extern uintptr_t A_CG_Entity_GetPlayerViewOrigin;
	extern uintptr_t DDL_NavigateBlueprint;
	extern uintptr_t DDL_CreateContext;
	extern uintptr_t WeaponDisplayName;
	extern uintptr_t RegisterFunction;
	extern uintptr_t DDL_GetEnum;
	extern uintptr_t UserCMDNumberAAB;
	extern uintptr_t DDL_GetRootState;
	extern uintptr_t GetBonePosition;
	extern uintptr_t ConvertToString;
	extern uintptr_t UserCMDWrapper;
	extern uintptr_t GetIndexByName;
	extern uintptr_t DDL_MoveToPath;
	extern uintptr_t LUI_BeginTable;
	extern uintptr_t LUI_BeginEvent;
	extern uintptr_t MaxPlayerCount;
	extern uintptr_t GetClientInfo;
	extern uintptr_t WorldToScreen;
	extern uintptr_t GetPlayerTeam;
	extern uintptr_t GetPlayerName;
	extern uintptr_t GetPlayerNameWithHash;

	extern uintptr_t GetEntityType;
	extern uintptr_t DecryptString;
	extern uintptr_t DDL_InitState;
	extern uintptr_t DDL_LoadAsset;
	extern uintptr_t DDL_GetBuffer;
	extern uintptr_t DDL_SetString;
	extern uintptr_t DDL_GetString;
	extern uintptr_t BluePrintData;
	extern uintptr_t UserCMDNumber;
	extern uintptr_t LUI_SetString;
	extern uintptr_t UserCMDPackAngle;
	extern uintptr_t DDL_SetFloat;
	extern uintptr_t PartyDisband;
	extern uintptr_t LUI_EndTable;
	extern uintptr_t LUI_EndEvent;
	extern uintptr_t InGameCheck;
	extern uintptr_t DDL_GetType;
	extern uintptr_t DDL_SetEnum;
	extern uintptr_t UpdateBytes;
	extern uintptr_t ThirdPerson;
	extern uintptr_t LUI_SetBool;
	extern uintptr_t PlayerState;
	extern uintptr_t FindString;
	extern uintptr_t SightTrace;
	extern uintptr_t WeaponName;
	extern uintptr_t DDL_SetInt;
	extern uintptr_t DDL_GetInt;
	extern uintptr_t ShellShock;
	extern uintptr_t LUI_SetInt;
	extern uintptr_t Controller;
	extern uintptr_t PlaceFull;
	extern uintptr_t GetEntity;
	extern uintptr_t BG_WeaponIsDualWield;
	extern DWORD64 A_PacketDup;
	extern DWORD64 B_PacketDup;
	extern uintptr_t DDL_Parse;
	extern uintptr_t SelfChams;
	extern uintptr_t ANoRecoil;
	extern uintptr_t LUI_LuaVM;
	extern uintptr_t GetButton;
	extern uintptr_t GetCamos;
	extern uintptr_t GameType;
	extern uintptr_t EndLobby;
	extern uintptr_t NoRecoil;
	extern uintptr_t GetField;
	extern uintptr_t PushBool;
	extern uintptr_t Tracers;
	extern uintptr_t UserCMD;
	extern uintptr_t GetData;
	extern uintptr_t ClanTag;
	extern uintptr_t CGArray;
	extern uintptr_t RefDef;
	extern uintptr_t JmpRbx;
	extern uintptr_t GetTop;
	extern uintptr_t SetTop;
	extern uintptr_t Chams;
	extern uintptr_t FOV;
	extern uintptr_t P_CG_ClientModel_RuntimeData;
	extern uintptr_t P_UI_VerifyString;
	extern uintptr_t P_ProfanityFilter_IsBadWord;
	extern uintptr_t P_unolkownind;
	extern uintptr_t P_LiveAntiCheat_ReportPlayer;
	extern uintptr_t newfunc;

	extern uintptr_t UI_SafeTranslateString;
	extern uintptr_t scriptable_id;
	extern shared::address_t CgHandler_GetScriptableDimensions;

	extern uintptr_t ClientContext;
	extern shared::address_t LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex;
	extern uintptr_t CL_Main_IsBRGameType;
	extern uintptr_t ViewAngles;
	extern uintptr_t WeaponMap;
	extern uintptr_t ThirdPersonCrosshair;
	extern uintptr_t CalculateMuzzlePoint;
	extern uintptr_t WeaponFlash;
	extern uintptr_t GetAngle;
	extern uintptr_t WeaponSystemsArray;
	extern uintptr_t CLActive;
	extern uintptr_t PredictedPlayerState;
	extern uintptr_t RiotShield;
	extern uintptr_t UserCMDUnpackAngle;
	extern uintptr_t WorldPosistionToCompass;
	extern uintptr_t DrawMapLayer;
	extern uintptr_t EntityState;
	extern uintptr_t GetPlayerFOV;
	extern uintptr_t WeaponFireType;
	extern uintptr_t Score;
	extern uintptr_t LegacyTrace;
	extern uintptr_t BlackBoxIntalized;
	extern uintptr_t GetClientPlatform;
	extern uintptr_t GetInstance;
	extern uintptr_t GetConstInstance;
	extern uintptr_t SendMessageToChat;
	extern uintptr_t BG_GetBallisticMuzzleVelocityScale;
	extern uintptr_t BG_GetBallisticInfo;
	extern uintptr_t BG_Ballistics_HorizontalTravelTimeToTarget;
	extern uintptr_t CG_CalcTargetVelocity;
	extern uintptr_t BlockMouseInput;
	extern uintptr_t BlockKeyboardInput;
	extern uintptr_t BG_GetAmmoInClipForWeapon;
	extern uintptr_t BG_GetWeaponClass;
	extern uintptr_t IsKeyDown;
	extern uintptr_t Lobby_GetPartyData;
	extern uintptr_t getName;
	extern uintptr_t getPlatform;
	extern uintptr_t usingGamepad;
	extern uintptr_t getXUID;
	extern uintptr_t GetUniversalId;
	extern uintptr_t CL_IsPlayerTalking;
	extern uintptr_t CL_IsPlayerMuted;
	extern uintptr_t UI_KickPlayer;
	extern uintptr_t CL_IsPlayerBot;
	extern uintptr_t GetItemQuantity;
	extern uintptr_t UnknownName;
	extern uintptr_t Party_GetMemberTeam;
	extern uintptr_t Party_IsMemberDeafened;
	extern uintptr_t Com_GameMode_GetActiveGameMode;

}

extern __int64 a44;
extern DWORD64 a55;

struct MyClient_s
{
	int Client_Num;
	int Client_Shield;
	Vector3 View_Origin;
	Vector3 View_Angles;
	Vector3 View_Angles2;

	Vector3 Head_Pos;
	Vector3 Position;
	bool Got_Client;
	float Fov;
	float Real_Fov;
	const char* Map_Name;
	float FOV;
	float FOVReal = 119.f;
	int Client_Health;
	int Client_Deaths;
	int Client_Damage;
	int Client_Score;
	int Client_Kills;
	int Client_Ping;
	int Client_Rank;
	int Client_Type;
	int Client_Team;
	int Client_Assists;
	bool Is_DualWeild;
	std::string Client_Name;
	std::string Client_Weapon;
	DWORD64 C_Entity;
};

struct ClientInformation
{
public:
	int Compass_Client_Distance;
	bool Compass_Client_IsFriendly;
	bool Compass_Client_IsVisible;
	bool Compass_Can_Draw;
	int Compass_Client_Health;
	int Compass_Client_Type;
	DWORD64 Compass_Client_C_Entity;

	int Radar_Client_Distance;
	bool Radar_Client_IsFriendly;
	bool Radar_Client_IsVisible;
	bool Radar_Can_Draw;
	int Radar_Client_Health;
	int Radar_Client_Type;
	Vector3 Radar_Client_ViewAngles;
	DWORD64 Radar_Client_C_Entity;

	Vector2 Client_Screen_Pos_2D;
	Vector2 Client_Dimentions;
	Vector3 Client_ViewAngles;
	std::string Client_Weapon;
	bool Client_In_Gulag_Match;
	bool Client_Being_Revived;
	bool Client_Self_Reviving;
	std::string Client_Name;
	Vector3 Client_Position_3D;
	Vector3 Client_OldPos_3D;
	Vector3 Client_NewPos_3D;

	Vector3 Velocity_Value;
	bool Client_Has_Riot_Shield;
	float Client_Distance;
	bool Client_Is_Crouched;
	bool Client_Is_In_Screen;
	bool Client_Is_Friendly;
	bool Client_Is_In_Gulag;
	bool Client_Is_Visible;
	bool Client_Is_Downed;
	int Client_Assists;
	bool Client_Is_Prone;
	int Client_Health;
	int Client_Deaths;
	int Client_Damage;
	int Client_Score;
	int Client_Kills;
	int Client_Ping;
	int Client_Type;
	int Client_Rank;
	int Client_Team;
	float Client_KD;
	bool Got_Client;
	Vector3 View_Origin;
	bool head_vis;
	DWORD64 C_Entity;

	struct BonePoints {
		Vector2 RightArm[5];
		Vector2 RightLeg[5];
		Vector2 LeftArm[5];
		Vector2 LeftLeg[5];
		Vector2 Body[7];

		Vector3 HealthOverride;
		Vector3 TargetOverride;
		Vector3 Target;
		Vector3 bonescanvischeck;
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


		Vector3 Compass_Pos_3D;
		Vector3 Radar_Pos_3D;

	};

	struct Bones {
		BonePoints Bones;
	};

	Bones ClientBones[2048];

	ClientInformation() : Client_Screen_Pos_2D(), Client_ViewAngles(), Client_Weapon(), Client_In_Gulag_Match(), Client_Being_Revived(), Client_Self_Reviving(), Client_Dimentions(), Client_Name(), Client_Position_3D(), Client_Has_Riot_Shield(), Client_Distance(), Client_Is_Crouched(), Client_Is_In_Screen(), Client_Is_Friendly(), Client_Is_In_Gulag(), Client_Is_Visible(), Client_Is_Downed(), Client_Assists(), Client_Health(), Client_Is_Prone(), Client_Deaths(), Client_Damage(), Got_Client(), Client_Score(), Client_Kills(), Client_Ping(), Client_Type(), Client_Rank(), Client_Team(), Client_KD(), ClientBones(), Velocity_Value(){ }
}; extern std::vector<ClientInformation> Client;

struct Lobby_Info {
	int client_Number;
	__int8 platform;
	std::string platform_String;
	std::string GPad_String;
	std::string Talking_String;
	const char* gamertag;
	bool gamepad;
	bool IsTalking;
	bool IsBot;
	bool IsMuted;
	int Deaths;
	int Damage;
	int Score;
	int Kills;
	int Ping;
	int Rank;
	int Team;
	bool Can_Draw;
	int Prestige;
	bool highlight;
	unsigned __int64 xuid;

	Lobby_Info() :  platform(), platform_String(), GPad_String(), Talking_String(), gamertag(), gamepad(), IsTalking(), IsBot(), xuid(), client_Number(), IsMuted(), Deaths(), Damage() , Score() , Kills () , Ping () , Rank () , Team (), Prestige(), highlight(){ }

};  extern std::vector<Lobby_Info> Lobby;

extern bool getHash();
extern bool getHash2();

extern bool failedhash;


extern const char* sig();
extern __forceinline std::string StreamFileToMemString();

extern void Log_To_Notepad(const char* str, ...);

extern uintptr_t testingg;
extern DWORD64 testingggg;
extern uintptr_t testing2;

extern __int64 testing69;
struct Entitys {
	DWORD64 C_Entity;
	int E_Type;
	bool CanDraw;
	bool tag_eye_Visible;
	Vector3 ViewAngles;
	Vector3 tag_origin;
	Vector3 tag_eye;
	Vector3 Target_Bone_Pos;
	Vector3 Override_Target_Bone_Pos;
	Vector3 Health_Target_Bone_Pos;
	bool Is_Visible;
	float distance;
	int health;
	int team;
	bool IsFriendly;
	bool IsDowned;
	std::string Name;
	std::string Weapon;
	Vector2 tag_origin_2D;
	bool Is_In_View;
	Vector2 RightArm[5];
	Vector2 RightLeg[5];
	Vector2 LeftArm[5];
	Vector2 LeftLeg[5];
	Vector2 Body[7];
	Vector2 Dimentions;

}; extern Entitys Entity_t[2048];

struct lootItems {
	Vector3 origin;
	Vector2 screenPos;
	std::string name;
	int distance;
	Vector2 BoxSize;
	bool visible;
	int type;
	bool canDrawLoot;
}; extern lootItems loot_t[416];

extern int m_previous_target;
extern int				m_best_bone;
extern Vector3	m_best_pos;
extern bool			m_disabled2;
extern bool			m_disabled;
extern int aim_target;
extern int m_best_target;

template <typename T> inline T(*GameCall(unsigned __int64 address))(...) {
	__int64 func_address = address;
	T(*func)(...) = (T(*)(...))func_address;
	return func;
}