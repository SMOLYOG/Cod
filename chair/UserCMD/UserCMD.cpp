#pragma once
#include "UserCMD.hpp"

UserCMD_T* NewCMD;
UserCMD_T* CMD;
int CurrentCMD;
Vector3 Angle;
int OldCMD;

DWORD64 ClActiveClient_GetClient()
{
	return VariadicCall<DWORD64>(Offset::JmpRbx, Offset::A_CL_Input_ClearAutoForwardFlag, 0);
}

UserCMD_T* GetUserCMD(int sequence_number) {
	auto cmdList = reinterpret_cast<UserCMD_S*>(Offset::UserCMDWrapper + Offset::UserCMD);
	auto cmd = &cmdList[sequence_number & 0x7F];
	return cmd;
	//return reinterpret_cast<UserCMD_S*>((uintptr_t)Offset::UserCMDWrapper + Offset::UserCMD + (sequence_number & 0x7F));

}
float UserCMDUnpackAngle(__int64 Angle) {
	//auto MSG_UnpackSignedFloat = ctx::mem.gamefunction.MSG_UnPackSignedFloat.cast<float(*)(int, float, unsigned int)>();
	auto MSG_UnpackSignedFloat = reinterpret_cast<float(__fastcall*)(int, float, unsigned int)>(Offset::UserCMDUnpackAngle);
	double v1 = MSG_UnpackSignedFloat(Angle, 180.0, 20);
	v1 *= 0.0027777778;
	__m128 v2 = _mm_set_ss(v1 + 0.5);
	v2 = _mm_round_ss(v2, v2, 1);
	v1 -= v2.m128_f32[0];
	return v1 * 360.0;
}
int UserCMDPackAngle(float Angle) {
	auto MSG_PackSignedFloat = reinterpret_cast<int(__fastcall*)(float, float, unsigned int)>(Offset::UserCMDPackAngle);

	__m128 v26 = { 0ui64, 0ui64 }, v27 = { 0ui64, 0ui64 }, nullm128 = { 0ui64, 0ui64 };
	v26.m128_f32[0] = Angle * 0.0027777778f;
	v27 = v26;
	v27.m128_f32[0] = v26.m128_f32[0] + 0.5f;
	return MSG_PackSignedFloat((float)(v26.m128_f32[0] - _mm_round_ss(nullm128, v27, 1).m128_f32[0]) * 360.0, 180.0, 20);
}

void SetCMDNumber(int num) {
	auto a1 = Offset::UserCMDWrapper;
	auto v5 = (__int64)(a1 + Offset::UserCMDNumber);
	v5 ^= *(int*)(a1 + Offset::UserCMDNumberAAB);
	*(int*)(a1 + Offset::UserCMDNumber) = ((v5 + 2) * v5) ^ num;
}
int GetCMDNumber() {
	auto a1 = Offset::UserCMDWrapper;
	return *(int*)(a1 + Offset::UserCMDNumber) ^ ((*(int*)(a1 + Offset::UserCMDNumberAAB) ^ (a1 + Offset::UserCMDNumber)) * ((*(int*)(a1 + Offset::UserCMDNumberAAB) ^ (a1 + Offset::UserCMDNumber)) + 2));
}
