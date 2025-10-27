#pragma once
#include "..\Globals\Globals.h"


struct GamePad_T {
	char pad_0[0x88];     // 0x0
	bool Keyboard;        // 0x88
	int Digit;            // 0x8C
	int LastDigit;        // 0x90
	float Analog[2];      // 0x94
	float LastAnalog[2];  // 0x9C
	char pad_1[0x19C];    // 0xA4
};

enum GamePadButton_T : __int32 {
	GPAD_NONE = 0x0,
	Up = 0x10000001,
	Down = 0x10000002,
	Left = 0x10000004,
	Right = 0x10000008,
	Start = 0x10000010,
	Back = 0x10000020,
	L3 = 0x10000040,
	R3 = 0x10000080,
	A = 0x10001000,
	B = 0x10002000,
	X = 0x10004000,
	Y = 0x10008000,
	LBumper = 0x10000100,
	RBumper = 0x10000200,
	LTrigger = 0x20000000,
	RTrigger = 0x20000001,
};


extern std::string ResolveString(int Button);
extern bool ButtonActive(int Button);
extern float Get(GamePadButton_T Button);
extern int ResolveButton();