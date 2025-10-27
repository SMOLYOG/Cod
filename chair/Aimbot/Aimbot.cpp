#pragma once
#include "Aimbot.h"

bool isPlayerInsideCircle(Vector2 playerPosition, Vector2 boxDimensions, Vector2 circleCenter, int circleRadius) {
	Vector2 boxPosition = Vector2(playerPosition.x - boxDimensions.x / 2, playerPosition.y - boxDimensions.y / 2);

	float closestX = std::clamp(circleCenter.x, boxPosition.x, boxPosition.x + boxDimensions.x);
	float closestY = std::clamp(circleCenter.y, boxPosition.y, boxPosition.y + boxDimensions.y);

	float distanceX = circleCenter.x - closestX;
	float distanceY = circleCenter.y - closestY;
	float distanceSquared = distanceX * distanceX + distanceY * distanceY;

	return distanceSquared <= (circleRadius * circleRadius);
}

bool is_key_active()
{
	if ((GetAsyncKeyState(KeyBinds::Aimbot) & 0x8000) || (GetAsyncKeyState(KeyBinds::Aimbot2) & 0x8000) || KeyBinds::ControllerAimbot || KeyBinds::ControllerAimbot2)
		return true;

	return false;
}

bool is_key_active_override()
{
	return ((GetAsyncKeyState(KeyBinds::Overide) & 0x8000) || KeyBinds::ControllerOveride);
}

bool is_alive() {

	if (!Entity_t[m_best_target].CanDraw)
		return false;

	if (Entity_t[m_best_target].C_Entity)
		return true;

	return false;
}


void Start() {

	if (Aimbot::Disable_on_kill && m_best_target)
	{
		if (!is_alive())
			m_disabled = true;
	}

	if (Aimbot::Disable_on_kill && m_best_target)
	{
		if (!is_alive())
			m_disabled2 = true;
	}

	aim_target = -1;
	m_best_target = -1;

	if (!is_key_active())
	{
		m_disabled = false;
	}
	if (!is_key_active_override())
	{
		m_disabled2 = false;
	}
}

void Find_Target() {

	int NewTarget = 0, Target = 100000000;
	int FinalTarget = -1;
	float ClosestDistance = 999.9f;
	float CurrentDistance = 0.0f;
	auto Ps = *(PlayerState_T*)(Offset::CGArray + Offset::PlayerState);

	Vector3 Target_pos;

	for (int i = 0; i < 2048; i++) {
		if (!Entity_t[i].CanDraw)
			continue;

		if (Aimbot::Targeting::Teamates && Entity_t[i].IsFriendly)
			continue;
		if (Aimbot::Targeting::Visible && !Entity_t[i].Is_Visible)
			continue;
		if (Aimbot::Targeting::Downed && Entity_t[i].IsDowned)
			continue;
		if (Aimbot::Targeting::Bots && Entity_t[i].E_Type != EntityType_T::ET_PLAYER)
			continue;

		if (cfg::Aimbot::Health_Override::Enable && MyClient.Client_Health <= cfg::Aimbot::Health_Override::Health_Trigger)
			Target_pos = Entity_t[i].Health_Target_Bone_Pos;
		else
			Target_pos = Entity_t[i].Target_Bone_Pos;

		if (cfg::Aimbot::Targeting::Type == 0) {
			if (Entity_t[i].distance > Aimbot::Checks::Distance)
				continue;

			CurrentDistance = Entity_t[i].distance;

			if (CurrentDistance < ClosestDistance) {
				ClosestDistance = CurrentDistance;

				NewTarget = Math::SmartCheck(Ps.ViewAngles, MyClient.View_Origin, Target_pos);

				if (NewTarget < Target) {
					Target = NewTarget;
					FinalTarget = i;
				}
			}
		}
		else if (cfg::Aimbot::Targeting::Type == 1) {

			bool validTarget2 = false;

			if (!Aimbot::DynamicFOV) {
				if (Vector3(Ps.ViewAngles - Math::CalculateAngle(MyClient.View_Origin, Target_pos)).Normalize().Length() > Aimbot::FOV)
					continue;
			}
			else {
				float radius = tan(Math::Deg2Rad(Aimbot::FOV) / 2.f) / tan(Math::Deg2Rad(MyClient.FOVReal) / 2.f) * (Screen.x / 2);
				if (!isPlayerInsideCircle(Entity_t[i].tag_origin_2D, Entity_t[i].Dimentions, Vector2(Screen.x / 2, Screen.y / 2), radius))
					continue;
			}

		}

		else if (cfg::Aimbot::Targeting::Type == 2) {

			if (Entity_t[i].distance > Aimbot::Checks::Distance)
				continue;

			if (!Aimbot::DynamicFOV) {
				if (Vector3(Ps.ViewAngles - Math::CalculateAngle(MyClient.View_Origin, Target_pos)).Normalize().Length() > Aimbot::FOV)
					continue;
			}
			else {
				float radius = tan(Math::Deg2Rad(Aimbot::FOV) / 2.f) / tan(Math::Deg2Rad(MyClient.FOVReal) / 2.f) * (Screen.x / 2);
				if (!isPlayerInsideCircle(Entity_t[i].tag_origin_2D, Entity_t[i].Dimentions, Vector2(Screen.x / 2, Screen.y / 2), radius))
					continue;
			}


			CurrentDistance = Entity_t[i].distance;
			if (CurrentDistance < ClosestDistance) {
				ClosestDistance = CurrentDistance;

				NewTarget = Math::SmartCheck(Ps.ViewAngles, MyClient.View_Origin, Target_pos);

				if (NewTarget < Target) {
					Target = NewTarget;
					FinalTarget = i;
				}

				m_best_target = FinalTarget;
			}

		}

	}
}

void Apply_Aim() {

	PlayerDataBase::Target = m_best_target;
	if (PlayerDataBase::Target == -1)
		return;

	auto Ps = *(PlayerState_T*)(Offset::CGArray + Offset::PlayerState);

	Vector3 Target_pos = Vector3(-9999, -9999, -9999);

	if (cfg::Aimbot::Health_Override::Enable && MyClient.Client_Health <= cfg::Aimbot::Health_Override::Health_Trigger)
		Target_pos = Entity_t[m_best_target].Health_Target_Bone_Pos;
	else
		Target_pos = Entity_t[m_best_target].Target_Bone_Pos;

	Vector3 Aim_Pos = Target_pos - MyClient.View_Origin;

	bool new_target = m_previous_target != m_best_target;
	if (Delay_Timer(new_target , Aimbot::switch_delay))
		return;



	if (m_best_target && is_key_active() && !m_disabled)
	{
		if (is_alive())
		{
			if (Aimbot::Silent) {

				if (Aimbot::Enable_MissChance) {
					bool Should_Miss = rand() % 100 + 1 <= Aimbot::Miss_Chance;
					if (Should_Miss)
						return;
				}

				Vector3 angle = Vector3(0, 0, 0);
				VectorAnglesa(Aim_Pos, angle);
				angle.x = angleNormalize180(angle.x);
				angle.y = angleNormalize180(angle.y);
				angle.z = angleNormalize180(angle.z);

				CMD->Angle[0] = UserCMDPackAngle(angle.x - Ps.DeltaAngles.x);
				CMD->Angle[1] = UserCMDPackAngle(angle.y - Ps.DeltaAngles.y);
			}
			if (!Aimbot::Silent)
			{
				Vector3 Angle = Vector3(0, 0, 0);

				Math::VectorAngles(Aim_Pos, Angle);
				Angle.x = angleNormalize180(Angle.x);
				Angle.y = angleNormalize180(Angle.y);
				Angle.z = angleNormalize180(Angle.z);

				if (Aimbot::Smoothingx > 0.f) {
					Vector3 ViewAngle = Ps.ViewAngles.Normalize();
					Vector3 AngleDelta = (Angle - Ps.ViewAngles).Normalize();
					Angle = (ViewAngle + (AngleDelta / Aimbot::Smoothingx));
					Angle = Angle.Normalize();
				}
				AimBot::SetViewAngles(Angle);
			}

			m_previous_target = m_best_target;

			if (Aimbot::AutoShoot) {
				WeaponFireType_T WeaponType = GameCall<WeaponFireType_T>(Offset::WeaponFireType)(&CMD->Weapon, false);
				if (WeaponType == WEAPON_FIRETYPE_SINGLESHOT || WeaponType == WEAPON_FIRETYPE_BURST) {
					CMD->Buttons.Add(0x80000000);
					UserCMD_T* OldCMD = GetUserCMD(GetCMDNumber() - 1);
					if (OldCMD->Buttons.Has(0x80000000))
						CMD->Buttons.Remove(0x80000000);
				}
				else {
					CMD->Buttons.Add(0x80000000);
				}
			}

			if (cfg::Aimbot::Extras::Auto_Ads)
				CMD->Buttons.Add(0x404000);
		}

	}

	if (m_best_target && is_key_active_override() && !m_disabled2 && Aimbot::Overide::Enable) {

		Vector3 Angle = Vector3(0, 0, 0);
		Vector3 Directionnormal = Entity_t[PlayerDataBase::Target].Override_Target_Bone_Pos - MyClient.View_Origin;

		Math::VectorAngles(Directionnormal, Angle);

		if (Aimbot::Overide::Smoothing > 0.f) {
			Vector3 ViewAngle = Ps.ViewAngles.Normalize();
			Vector3 AngleDelta = (Angle - Ps.ViewAngles).Normalize();
			Angle = (ViewAngle + (AngleDelta / Aimbot::Overide::Smoothing));
			Angle = Angle.Normalize();
		}
		AimBot::SetViewAngles(Angle);
	}

}

void Aimbot_Loop() {

	if (!Globals::InGame2)
		return;

	if (Aimbot::Ignore_While_Spectated)
		if (JUP::SpectatorCount() >= Aimbot::Spectator_Count)
			return;

	Start();

	Find_Target();

	Apply_Aim();

}
