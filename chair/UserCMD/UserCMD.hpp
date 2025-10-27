#pragma once
#include "../Structures/Structures.h"
#include "..\Globals\Globals.h"
#include "../GameSDK/GameSDK.h"

extern DWORD64 ClActiveClient_GetClient();
extern UserCMD_T* GetUserCMD(int Number);
extern int UserCMDPackAngle(float Angle);
extern void SetCMDNumber(int num);
extern int GetCMDNumber();
extern UserCMD_T* NewCMD;
extern UserCMD_T* CMD;
extern int CurrentCMD;
extern Vector3 Angle;
extern int OldCMD;