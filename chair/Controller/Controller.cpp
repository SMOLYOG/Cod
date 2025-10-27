#pragma once
#include "Controller.h"

std::string ResolveString(int Button) {
	switch (Button)
	{
	case LTrigger: return xorstr_("Left Trigger");
	case RTrigger: return xorstr_("Right Trigger");
	case RBumper:  return xorstr_("Right Bumper");
	case LBumper:  return xorstr_("Left Bumper");
	case Right:    return xorstr_("Right");
	case Start:    return xorstr_("Start");
	case A:        return xorstr_("Gamepad A");
	case B:        return xorstr_("Gamepad B");
	case X:        return xorstr_("Gamepad X");
	case Y:        return xorstr_("Gamepad Y");
	case Down:     return xorstr_("Down");
	case Left:     return xorstr_("Left");
	case Back:     return xorstr_("Back");
	case Up:       return xorstr_("Up");
	case L3:       return xorstr_("L3");
	case R3:       return xorstr_("R3");
	default:       return xorstr_("Unknown");
	}
}
bool ButtonActive(int Button) {
	bool pressed = false, held = false;

	GamePad_T* data = (GamePad_T*)(Offset::Controller);
	if ((Button & 0x10000000) != 0)
	{
		pressed = (Button & data->Digit & 0xEFFFFFFF) != 0;
		held = (Button & data->LastDigit & 0xEFFFFFFF) != 0;
	}
	else
	{
		if ((Button & 0x20000000) == 0)
			return 0;
		unsigned __int64 v5 = (int)Button & 0xFFFFFFFFDFFFFFFFui64;
		pressed = data->Analog[v5] > 0.0;
		held = data->LastAnalog[v5] > 0.0;
	}
	return pressed || held;
}
float Get(GamePadButton_T Button) {
	return GameCall<float>(Offset::GetButton)(0, Button);
}
int ResolveButton() {
	int Button = -1;

	if (Get(LTrigger) > 0.0f) Button = LTrigger;
	if (Get(RTrigger) > 0.0f) Button = RTrigger;
	if (Get(LBumper) > 0.0f) Button = LBumper;
	if (Get(RBumper) > 0.0f) Button = RBumper;
	if (Get(Right) > 0.0f) Button = Right;
	if (Get(Start) > 0.0f) Button = Start;
	if (Get(Down) > 0.0f) Button = Down;
	if (Get(Left) > 0.0f) Button = Left;
	if (Get(Back) > 0.0f) Button = Back;
	if (Get(Up) > 0.0f) Button = Up;
	if (Get(L3) > 0.0f) Button = L3;
	if (Get(R3) > 0.0f) Button = R3;
	if (Get(A) > 0.0f) Button = A;
	if (Get(B) > 0.0f) Button = B;
	if (Get(X) > 0.0f) Button = X;
	if (Get(Y) > 0.0f) Button = Y;

	return Button;
}