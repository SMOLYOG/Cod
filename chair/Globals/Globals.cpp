#pragma once

#include "Globals.h"
#include <atlchecked.h>


int nigggg;
int sigcount;

bool testing[10];


namespace cfg {
	
	namespace Esp {

		bool Self_Esp;
		int InFov_Count;
		bool Platform;
		bool Device;
		bool Talking;

		namespace Drawing_Settings {
			float Font_Size = 5.f;
			int Snapline_Pos = 2;
			int box_Type;
		}
	}

	namespace Crosshair {
		float speed = 1.0f;
		float linelength = 30.0f;
		float linegap = 10.f;
		float dotradius = 2.5f;
		bool enabledot = true;
		bool spin = false;
	}

	namespace radar {

		bool Enable;
		bool Ignore_Team;
		bool Ignore_Invis;
		bool Ignore_Knocked;
		float Alpha = 1.0;

		namespace Color {
			float Team_Vis[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
			float Team_non_Vis[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
			float Enemy_Vis[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
			float Enemy_Non_Vis[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		}

	}
	
	namespace Aim_Target {

		bool Target_SnapLine;

		namespace Color {
			float Target_Esp[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
			float Target_Crosshair[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
			float Target_FOV[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		}
	}

	namespace Exploits {
		namespace Melee_Lunge {
			bool Enable;
			float Max_Distance;
			bool Ignore_Invis;
			bool Ignore_Team;
			bool Ignore_Knocked;
			int Type = 2;
		}

		namespace Auto_Reload {
			bool Enable;
			int Bullet_Count_AR;
			int Bullet_Count_Sniper;
			int Bullet_Count_LMG;
			int Bullet_Count_SMG;
			int Bullet_Count_Pistol;
			bool Enable_AR;
			bool Enable_Sniper;
			bool Enable_LMG;
			bool Enable_SMG;
			bool Enable_Pistol;
			bool Stop_When_In_View;
			bool Stop_When_Targeting;
		}

		namespace Rapid_fire {
			int Shot_Delay;
		}

		namespace Chat_Spam {
			bool Enable;
			bool Spam_Message;
			char Chat_Message[255];
			int Delay_Time;
		}

		namespace Profanity_Checks {
			bool Enable;
		}
	}

	namespace Aimbot {

		namespace Extras {
			bool Auto_Ads;
		}

		namespace Targeting {
			bool BoneScan; 
			int Type = 2;
		}

		namespace Health_Override {
			bool Enable;
			int Health_Trigger;
			int Bone;
		}
	}

	namespace Chams {
		bool Ignore_Team;
		bool Ignore_Invis;
		bool Ignore_Knocked;

		namespace Color {
			float Team_Vis[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
			float Team_non_Vis[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
			float Enemy_Vis[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
			float Enemy_Non_Vis[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		}
	}
}

namespace IncorrectOffset {
	bool DDL_NavigateBlueprint;
	bool DDL_CreateContext;
	bool WeaponDisplayName;
	bool RegisterFunction;
	bool UserCMDNumberAAB;
	bool UserCMDPackAngle;
	bool DDL_GetRootState;
	bool GetBonePosition;
	bool ConvertToString;
	bool GetIndexByName;
	bool DDL_MoveToPath;
	bool LUI_BeginTable;
	bool LUI_BeginEvent;
	bool MaxPlayerCount;
	bool GetClientInfo;
	bool WorldToScreen;
	bool GetPlayerTeam;
	bool GetPlayerName;
	bool GetEntityType;
	bool DecryptString;
	bool DDL_InitState;
	bool DDL_LoadAsset;
	bool DDL_GetBuffer;
	bool DDL_SetString;
	bool DDL_GetString;
	bool BluePrintData;
	bool UserCMDNumber;
	bool LUI_SetString;
	bool DDL_SetFloat;
	bool PartyDisband;
	bool LUI_EndTable;
	bool LUI_EndEvent;
	bool A_PacketDup;
	bool B_PacketDup;
	bool InGameCheck;
	bool DDL_GetType;
	bool DDL_SetEnum;
	bool UpdateBytes;
	bool ThirdPerson;
	bool LUI_SetBool;
	bool PlayerState;
	bool FindString;
	bool SightTrace;
	bool WeaponName;
	bool DDL_SetInt;
	bool DDL_GetInt;
	bool ShellShock;
	bool LUI_SetInt;
	bool Controller;
	bool PlaceFull;
	bool GetEntity;
	bool DDL_Parse;
	bool SelfChams;
	bool ANoRecoil;
	bool LUI_LuaVM;
	bool GetButton;
	bool GetField;
	bool PushBool;
	bool GetCamos;
	bool GameType;
	bool EndLobby;
	bool NoRecoil;
	bool UserCMD;
	bool GetData;
	bool ClanTag;
	bool CGArray;
	bool Tracers;
	bool RefDef;
	bool GetTop;
	bool SetTop;
	bool JmpRbx;
	bool Chams;
	bool FOV;

	bool ViewAngles;
	bool WeaponMap;
	bool ThirdPersonCrosshair;
	bool CalculateMuzzlePoint;
	bool WeaponFlash;
	bool GetAngle;
	bool WeaponSystemsArray;
	bool CLActive;
	bool PredictedPlayerState;
	bool RiotShield;
	bool UserCMDUnpackAngle;
	bool WorldPosistionToCompass;
	bool DrawMapLayer;
	bool GetPlayerFOV;
	bool EntityState;
	bool WeaponFireType;
	bool Score;
	bool LegacyTrace;
	bool BlackBoxIntalized;
}

namespace Exploits {
	bool DynamicThirdPerson;
	bool NoShellShock = false;
	bool ThirdPerson;
	bool NightVision;
	bool ExtendedFOV;
	bool UnlockAll;
	bool Airstuck;
	bool SpinBot;
	bool* Array[] = {
		&ThirdPerson,
		&NightVision,
		&NoShellShock, &DynamicThirdPerson,
	};
};

namespace Commands {
	bool BypassPrivateMatches;
	bool ProfanityNameBypass;

	bool DisableBlood;

	bool InGameCrosshair;
	bool NoShieldShake;
	bool SwapLoadouts;
	bool BreakCamera;
	bool DevPlayList;
	bool DrawFPS;
	bool NoFog = false;
	bool NoGun;
	float Map = 1.0f;
	float FOV = 170.0f;

	const char* CMDArray[] = {
		(xorstr_("#x3DF200A089A3B3FEB %i;")), (xorstr_("#x3A0B36B94898A1CCB %i;")), (xorstr_("#x34958E45561A1F918 %i;")),
		(xorstr_("#x3D80B69DE4DA004BE %i;")), (xorstr_("#x32F1C7266C0A91797 %i;")), (xorstr_("#x35D474D39E096F8F1 %i;")),
		(xorstr_("#x38BADBB201F2E8588 %i;")), (xorstr_("#x31F94AB661347AF15 %i;")), (xorstr_("#x3BB203010F77299D4 %i;")),
		(xorstr_("#x3EBB1AD2F73337342 %i;")),
	};
	char Input[100];
	bool* Array[] = {
		&NoGun,                &NoFog,           &DrawFPS,
		&BreakCamera,          &SwapLoadouts,    &NoShieldShake,
		&DevPlayList,          &InGameCrosshair, &ProfanityNameBypass,
		&BypassPrivateMatches,
	};
};

namespace KeyBinds {
	int DynamicThirdPerson;
	int Uninject = 35;
	int NightVision;
	int Menu = 36;
	int Overide;
	int Aimbot;
	int Aimbot2;
	int AirStuck;
	bool ControllerAirstuck;
	bool ControllerDynamicThirdPerson;
	bool ControllerNightVision;
	bool ControllerUninject;
	bool ControllerOveride;
	bool ControllerAimbot;
	bool ControllerAimbot2;
	bool ControllerMenu;
};

namespace Visuals {
	namespace Main {
		bool Draw_Box = true;
		bool DrawPlayerSnaplines;
		bool DrawPlayerSkeleton = true;
		bool DrawPlayerDistance = true;
		bool DrawPlayerAssists;
		bool DrawPlayerTeamID = true;
		bool DrawPlayerDeaths;
		bool DrawPlayerDamage;
		bool DrawPlayerHealth = true;
		bool DrawPlayerWeapon = true;
		bool DrawPlayerKills;
		bool DrawPlayerScore;
		bool DrawPlayerName = true;
		bool DrawPlayerPing;
		bool DrawPlayerRank;
		bool DrawPlayerKD;
		bool DrawFOV = true;
		bool DrawCrosshair = true;
		bool filled = true;
		bool Enable = true;
		int BoxType = 3;
		float crosshair_size = 8.0f;
		int crosshair_type = 0;
		float crosshair_thickness = 1.8f;

		bool* Array[] = {
			&Enable, &DrawPlayerKD, &DrawFOV, &DrawPlayerPing,
			&DrawPlayerKills, &DrawPlayerRank, &DrawPlayerScore, &DrawPlayerName,
			&DrawPlayerHealth, &DrawPlayerAssists, &DrawPlayerDeaths, &DrawPlayerTeamID,
			&DrawPlayerWeapon, &DrawPlayerDamage, &DrawPlayerDistance, &DrawPlayerSkeleton,
			&DrawPlayerSnaplines,
		};

		namespace Drawing {
			int healthPos;
			int SnapLinesPosX = 960, SnapLinesPosY = 1080;
			float SnaplinesDistance = 400.0f;
			float SkeletonDistance = 400.0f;
			float DistanceDistance = 400.0f;
			float AssistsDistance = 400.0f;
			float TeamIDDistance = 400.0f;
			float DeathsDistance = 400.0f;
			float DamageDistance = 400.0f;
			float HealthDistance = 400.0f;
			float WeaponDistance = 400.0f;
			float KillsDistance = 400.0f;
			float ScoreDistance = 400.0f;
			float PingDistance = 400.0f;
			float RankDistance = 400.0f;
			float NameDistance = 400.0f;
			float BoxDistance = 400.0f;
			float KDDistance = 400.0f;
			float all = 400.0f;
			float Bonethicness = 1.0f;
			bool SelfReviving = true;
			bool BeingRevived = true;
			bool GulagMatch = true;
			bool RiotShield = true;
			bool Teamates = true;
			bool Visible = true;
			bool Downed = true;
			bool Bots = true;
			bool Gulag = true;
			bool Enemy = true;
			bool* Array[] = {
				&Visible,    &Gulag,        &Teamates,
				&SelfReviving, &RiotShield, &BeingRevived,
				&Enemy,      &GulagMatch,   &Downed,
			};

			float* FloatArray[] = {
				&KDDistance, &BoxDistance, &PingDistance, &KillsDistance,
				&RankDistance, &ScoreDistance, &NameDistance, &HealthDistance,
				&AssistsDistance, &DeathsDistance, &TeamIDDistance, &WeaponDistance,
				&DamageDistance, &DistanceDistance, &SkeletonDistance, &SnaplinesDistance,
			};
		};

		namespace Checks {
			bool Spectated;
		};

		ImVec4 Rainbow;
	};

	namespace Miscellaneous {
		namespace Compass {
			int PosistionType;
			float Distance = 400.0f;
			int TriangleSize = 6;
			bool Enable = false;
			int Size = 180;
			bool Fill = true;

			namespace Drawing {
				bool SelfReviving = true;
				bool BeingRevived = true;
				bool GulagMatch = true;
				bool RiotShield = true;
				bool Teamates = true;
				bool Visible = true;
				bool Downed = true;
				bool Gulag = true;
				bool Enemy = true;
				bool Bots = true;

				bool* Array[] = {
					&Visible,    &Gulag,        &Teamates,
					&SelfReviving, &RiotShield, &BeingRevived,
					&Enemy,      &GulagMatch,   &Downed,
				};
			};
		};

		namespace Tracers {
			bool PlayerTracers = false;
			bool Objects = false;
			bool Players = false;
			bool Enable = false;
			float Tracer_Col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			float TracerThickness = 1.0f;
			int FadeInTime = 1000;
			int FadeOutTime, Duration, HitmarkerThickness;

			bool* Array[] = { &Objects, &Players, &PlayerTracers, };
		};

		namespace DynamicRadar {
			float TriangleSize = 0.04;
			const char* Image[1000];
			bool Enable = false;
			int ImageType;
			int RadarType = 1;
			bool filled;
			float blipsize = 4.0f;
			float Distance = 400.0f;

			namespace Drawing {
				bool SelfReviving = true;
				bool BeingRevived = true;
				bool GulagMatch = true;
				bool RiotShield = true;
				bool Teamates = true;
				bool Bots = true;
				bool Visible = true;
				bool Downed = true;
				bool Gulag = true;
				bool Enemy = true;

				bool* Array[] = {
					&Visible,    &Gulag,        &Teamates,
					&SelfReviving, &RiotShield, &BeingRevived,
					&Enemy,      &GulagMatch,   &Downed,
				};
			};
		};

		namespace LobbyStats {
			bool Enable = false;
			bool MapName = false;
			bool MaxPlayers = false;
			bool ViewOrgin = false;
			bool Position = false; 
			bool ViewAngle = false;
			bool ClientNum = false;
			bool TeamID = false;
			bool Name = false;
			bool Weapon = false;
			bool health = false;
			bool Ping = false;
			bool Rank = false;
			bool Score = false;
			bool Kills = false;
			bool Deaths = false; 
			bool Assists = false; 
			bool Damage = false;
		}
	};

	namespace Outlines {
		namespace Player {
			bool Invisible = false;
			bool Visible = false;
			bool Enable = false;
			bool Fill = false;
			int Width = 1;
			int Type;

			bool* Array[] = { &Enable, &Fill, &Visible, &Invisible, };
		};

		namespace Vehicle {
			bool Invisible;
			bool Visible;
			bool Enable;
			bool Fill;
			int Width = 1;
			int Type;

			bool* Array[] = { &Enable, &Fill, &Visible, &Invisible, };
		};

		namespace Self {
			bool Invisible = false;
			bool Visible = false;
			bool Enable = false;
			bool Fill = false;
			int Width = 1;
			int Type;

			bool* Array[] = { &Enable, &Fill, &Visible, &Invisible, };
		};

		namespace Miscellaneous {
			bool Invisible;
			bool Visible;
			bool Enable;
			bool Fill;
			int Width;
			int Type;

			bool* Array[] = { &Enable, &Fill, &Visible, &Invisible, };
		};

		int Rainbow;
	};
};

namespace loot_esp {
	bool enable;
	bool equipment;
	bool lethals;
	bool tacticals;
	bool lootboxes;
	bool ammo;
	bool money;
	bool weapon_crates;
	bool weapons;
	bool misc;
	bool armour;
	bool Wallbuys;
	bool ZMMachines;
	bool ZMEE;
	bool ZMTrap;
	bool ignoreinvis;
	int max_distance = 500;
	bool show_dist;
	float Loot_Color[4] = {0.0f, 1.0f, 0.0f, 1.0f};
	float Loot_Color_Non_Vis[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

}

namespace Color {

	float DynamicRadar[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float ChamsVec4[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float SnapLines[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Skeleton[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Distance[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Compass[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Assists[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float TeamID[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Deaths[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Damage[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Weapon[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Health[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Kills[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Score[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Ping[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Rank[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Name[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float Box[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float KD[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };
	float All[4][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f}, {0.17f, 0.17f, 0.81f, 1.0f} };

	float Tracer[3][4] = { {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.02f, 0.79f, 1.0f, 1.0f} };
	float Target[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float FOV[4] = { 1.0f, 1.0f, 1.0f, 0.5f };
	float HighlightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float crosshair[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int Chams[4];

	namespace Rainbow {

		bool DynamicRadar[4];
		bool SnapLines[4];
		bool Skeleton[4];
		bool Distance[4];
		bool Compass[4];
		bool Assists[4];
		bool TeamID[4];
		bool Deaths[4];
		bool Damage[4];
		bool Weapon[4];
		bool Health[4];
		bool Tracer[3];
		bool Chams[4];
		bool Kills[4];
		bool Score[4];
		bool Name[4];
		bool Ping[4];
		bool Rank[4];
		bool Box[4];
		bool Target;
		bool KD[4];
		bool FOV;
		bool crosshair;
		ImVec4 Rainbow;
	};
}

namespace AntiAim {
	namespace XAxis {
		bool Enable = true;
		int Type = 3;
	}
	namespace YAxis {
		bool Enable;
		int Type = 1;
	}//needed to set the mode preior else no worky as no menu option 
};

namespace Editors {
	namespace ForceSave {
		int Blueprint, Attach, Camo, Type;
		char Input[30], CamoInput[30];
	}
	namespace ClassName {
		char Input[30];
		int Loadout;
	};
	namespace ClanTag {
		int ClanTag, Color;
		char Input[30];
	};
	namespace Camo {
		int Camo, Loadout, Slot;
		char Input[30], CamoInput[30];
	};
	namespace Perk {
		int Package, Perk, Slot;
		char Input[30];
	}
}

namespace Globals {
	bool HooksEnabled;
	bool ScanComplete;
	bool KeyBoardLock;
	bool ChamsHooked;
	bool RainbowMenu;
	bool Open = true;
	bool GameType;
	bool InGame2;
	bool InGame = true;
	bool Moving;
	bool Steam;
	bool rainbowesp;
	int branding = 0;

	int ActiveTab = 1, ActiveSubTab = 1, Tab = 1, SubTab = 1, MaxPlayerCount, SpectatorCount;
	float TabAlpha, AddTab, SubTabAlpha, AddSubTab;

	TCHAR FilePath[MAX_PATH];
	uintptr_t BaseModule;
	DWORD ProcID;
	HANDLE HProc;
	HWND Hwind;
}

namespace Aimbot {
	bool Ignore_While_Spectated;
	int Spectator_Count;
	bool EnableSmoothing = true;
	float Acceration = 1.0f;
	float Smoothingx = 2.0f;
	float Smoothingy = 2.0f;
	float Smoothingz = 2.0f;

	bool RapidFire = false;
	bool AutoShoot = false;
	bool LockOn = false;
	bool Enable = true;
	float FOV = 200.0f;
	bool DynamicFOV = 0;
	int Type = 2;
	int Bone = 0;
	bool Silent;
	bool smart_bone_scan;
	float Strength = 1.0f;
	bool Bone_Scan;
	int mode = 0;
	bool Disable_on_kill;
	int switch_delay;
	int Miss_Chance;
	bool Enable_MissChance;
	int delay1;
	int delay2;
	bool canshoot;

	namespace Targeting {
		bool SelfReviving = true;
		bool BeingRevived = true;
		bool GulagMatch = true;
		bool RiotShield = true;
		bool Teamates = true;
		bool Visible = true;
		bool Downed = true;
		bool Gulag = true;
		bool Enemy = true;
		bool Bots = true;
		bool* Array[] = {
			&Visible,    &Gulag,        &Teamates,
			&SelfReviving, &RiotShield, &BeingRevived,
			&Enemy,      &GulagMatch,   &Downed,
		};
	}

	namespace Accuracy {
		bool Prediction;
		float Strength = 100.0f;
		bool NoRecoil;
	}

	namespace Overide {
		float Smoothing;
		float Strength;
		bool Enable;
		int Bone;
	}

	namespace Checks {
		bool DisableOnKill;
		bool Spectated;
		int Distance = 400.0f;
		int Type = 6;
	}
}

namespace Aim_Warning {
	int Looking_Max_Distance = 100;
	int Aiming_Max_distance = 100;
	bool Aiming_At_You;
	bool Looking_At_You;
	float AimingAtYou[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float LookingAtYou[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
}

//int testing;

namespace Offset {
	shared::address_t CL_PlayerData_SetCustomClanTag;
	shared::address_t targetassist;
	shared::address_t BG_GetPlayerEyePosition;
	shared::address_t commandqueue;
	shared::address_t packet_test;
	shared::address_t swapchain;
	shared::address_t Weaponmap;
	shared::address_t CG_Handler;
	shared::address_t BG_Ballistics_TravelTimeForDistance;
	shared::address_t nextState;
	shared::address_t v11_Offsets;
	uintptr_t CG_EntityMP_CalcLerpPositions;
	uintptr_t angle_offset;
	shared::address_t BG_GetBallisticInfoFunc;
	shared::address_t prevState;
	shared::address_t predictedPlayerState;
	shared::address_t trampoline;
	shared::address_t CG_GetEntWeapon;
	shared::address_t A_CG_SnapshotMP_GetNextSnap;
	shared::address_t A_CG_SnapshotMP_GetPrevSnap;
	shared::address_t A_BgTrajectory_EvaluatePosTrajectory;
	shared::address_t A_CgTrajectory_CgTrajectory;
	shared::address_t p_CgWeaponMap__ms_instance;
	shared::address_t bdEventInfo;
	shared::address_t bdEventLog;
	shared::address_t frametime;
	uintptr_t Get_Fov;

	uintptr_t DDL_GetEnum;
	uintptr_t A_CL_Input_ClearAutoForwardFlag;
	uintptr_t A_CG_Entity_GetPlayerViewOrigin;
	uintptr_t DDL_NavigateBlueprint;
	uintptr_t DDL_CreateContext;
	uintptr_t WeaponDisplayName;
	uintptr_t RegisterFunction;
	uintptr_t UserCMDNumberAAB;
	uintptr_t DDL_GetRootState;
	uintptr_t UserCMDPackAngle;
	uintptr_t GetBonePosition;
	uintptr_t ConvertToString;
	uintptr_t UserCMDWrapper;
	uintptr_t Clactive;
	uintptr_t UI_GetMapDisplayName_wrapper;
	uintptr_t GetIndexByName;
	uintptr_t DDL_MoveToPath;
	uintptr_t LUI_BeginTable;
	uintptr_t LUI_BeginEvent;
	uintptr_t MaxPlayerCount;
	uintptr_t GetClientInfo;
	uintptr_t WorldToScreen;
	uintptr_t GetPlayerTeam;
	uintptr_t GetPlayerName;
	uintptr_t GetPlayerNameWithHash;
	uintptr_t GetEntityType;
	uintptr_t DecryptString;
	uintptr_t DDL_InitState;
	uintptr_t DDL_LoadAsset;
	uintptr_t DDL_GetBuffer;
	uintptr_t DDL_SetString;
	uintptr_t DDL_GetString;
	uintptr_t BluePrintData;
	uintptr_t UserCMDNumber;
	uintptr_t LUI_SetString;
	uintptr_t DDL_SetFloat;
	uintptr_t PartyDisband;
	uintptr_t LUI_EndTable;
	uintptr_t LUI_EndEvent;
	uintptr_t InGameCheck;
	uintptr_t DDL_GetType;
	uintptr_t DDL_SetEnum;
	uintptr_t UpdateBytes;
	uintptr_t ThirdPerson;
	uintptr_t LUI_SetBool;
	uintptr_t PlayerState;
	uintptr_t FindString;
	uintptr_t SightTrace;
	uintptr_t WeaponName;
	uintptr_t DDL_SetInt;
	uintptr_t DDL_GetInt;
	uintptr_t ShellShock;
	uintptr_t LUI_SetInt;
	uintptr_t Controller;
	uintptr_t PlaceFull;
	uintptr_t GetEntity;
	DWORD64 A_PacketDup;
	DWORD64 B_PacketDup;
	uintptr_t DDL_Parse;
	uintptr_t SelfChams;
	uintptr_t ANoRecoil;
	uintptr_t LUI_LuaVM;
	uintptr_t GetButton;
	uintptr_t GetCamos;
	uintptr_t GameType;
	uintptr_t EndLobby;
	uintptr_t NoRecoil;
	uintptr_t GetField;
	uintptr_t PushBool;
	uintptr_t Tracers;
	uintptr_t UserCMD;
	uintptr_t GetData;
	uintptr_t ClanTag;
	uintptr_t CGArray;
	uintptr_t RefDef;
	uintptr_t JmpRbx;
	uintptr_t GetTop;
	uintptr_t SetTop;
	uintptr_t Chams;
	uintptr_t FOV;
	uintptr_t P_CG_ClientModel_RuntimeData;
	uintptr_t P_UI_VerifyString;
	uintptr_t P_ProfanityFilter_IsBadWord;
	uintptr_t P_unolkownind;
	uintptr_t P_LiveAntiCheat_ReportPlayer;
	uintptr_t newfunc;
	uintptr_t UI_SafeTranslateString;
	uintptr_t scriptable_id;
	shared::address_t CgHandler_GetScriptableDimensions;
	shared::address_t LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex;
	uintptr_t ClientContext;
	uintptr_t CL_Main_IsBRGameType;
	uintptr_t WeaponMap;
	uintptr_t ViewAngles;
	uintptr_t ThirdPersonCrosshair;
	uintptr_t CalculateMuzzlePoint;
	uintptr_t WeaponFlash;
	uintptr_t GetAngle;
	uintptr_t WeaponSystemsArray;
	uintptr_t CLActive;
	uintptr_t PredictedPlayerState;
	uintptr_t RiotShield;
	uintptr_t BG_WeaponIsDualWield;
	uintptr_t UserCMDUnpackAngle;
	uintptr_t WorldPosistionToCompass;
	uintptr_t DrawMapLayer;
	uintptr_t EntityState;
	uintptr_t GetPlayerFOV;
	uintptr_t WeaponFireType;
	uintptr_t Score;
	uintptr_t LegacyTrace;
	uintptr_t BlackBoxIntalized;
	uintptr_t GetInstance;
	uintptr_t GetConstInstance;
	uintptr_t SendMessageToChat;
	uintptr_t BG_GetBallisticMuzzleVelocityScale;
	uintptr_t BG_GetBallisticInfo;
	uintptr_t BG_Ballistics_HorizontalTravelTimeToTarget;
	uintptr_t CG_CalcTargetVelocity;
	uintptr_t BlockMouseInput;
	uintptr_t BlockKeyboardInput;
	uintptr_t BG_GetAmmoInClipForWeapon;
	uintptr_t BG_GetWeaponClass;
	uintptr_t IsKeyDown;
	uintptr_t Lobby_GetPartyData;
	uintptr_t getName;
	uintptr_t getPlatform;
	uintptr_t usingGamepad;
	uintptr_t getXUID;
	uintptr_t GetUniversalId;
	uintptr_t CL_IsPlayerTalking;
	uintptr_t CL_IsPlayerMuted;
	uintptr_t UI_KickPlayer;
	uintptr_t CL_IsPlayerBot;
	uintptr_t GetItemQuantity;
	uintptr_t UnknownName;
	uintptr_t Party_GetMemberTeam;
	uintptr_t Party_IsMemberDeafened;
	uintptr_t Com_GameMode_GetActiveGameMode;
}

std::vector<ClientInformation> Client(2048, ClientInformation());
std::vector<Lobby_Info> Lobby(2048, Lobby_Info());
__int64 a44;
DWORD64 a55;

bool failedhash = true;

__forceinline std::string StreamFileToMemString()
{
	const char* URL = xorstr_("https://flettz.com/files/chair/sigs/cmdq4");
	const char* header = xorstr_("Accept: *" "/" "*\r\n\r\n");
	HANDLE hBrowser = InternetOpen(xorstr_("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HANDLE hURL = InternetOpenUrl(hBrowser, URL, header, lstrlen(header), INTERNET_FLAG_DONT_CACHE, 0);

	char* dllBuff = new char[100000000]; //100mb

	memset(dllBuff, 0, 100000000);

	DWORD BytesRead = 1;

	std::string data;

	if (InternetReadFile(hURL, dllBuff, 100000000, &BytesRead))
	{
		data = std::string(dllBuff);
	}

	delete[] dllBuff;
	InternetCloseHandle(hBrowser);
	InternetCloseHandle(hURL);
	return data;
}
uintptr_t testingg;
uintptr_t testing2;

bool wanks;
DWORD64 testingggg;
__int64 testing69;

void Log_To_Notepad(const char* str, ...) {
	//va_list ap;
	//HWND notepad, edit;
	//char buf[1024];

	//va_start(ap, str);
	//vsprintf_s(buf, str, ap);
	//va_end(ap);
	//strcat_s(buf, "\n");

	//notepad = FindWindow(NULL, _TEXT("Untitled - Notepad"));
	//if (!notepad)
	//	notepad = FindWindow(NULL, _TEXT("*Untitled - Notepad"));

	//edit = FindWindowEx(notepad, NULL, _TEXT("EDIT"), NULL);
	//SendMessageA(edit, EM_REPLACESEL, 0, (LPARAM)buf);
}


Entitys Entity_t[2048];
lootItems loot_t[416];


int m_previous_target;
int				m_best_bone;
Vector3	m_best_pos;
bool			m_disabled2;
bool			m_disabled;
int aim_target;
int m_best_target;