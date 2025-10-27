#pragma once
#include "Loot data.h"

std::string get_name_from_model(std::string model, int i) {

	if (loot_esp::equipment) {
		if (stringContains(model, xorstr_("keycard")))
			return xorstr_("Keycard");
		/*	if (stringContains(model, xorstr_("offhand_")) && loot_esp::equipment)
				return xorstr_("Equipment");*/
		if (stringContains(model, xorstr_("locker_key")) && loot_esp::equipment)
			return xorstr_("Locker Key");
		if (stringContains(model, xorstr_("vault_key")) && loot_esp::equipment)
			return xorstr_("Vault Key");
		if (stringContains(model, xorstr_("token_")) && loot_esp::equipment)
			return xorstr_("Token");
	}

	if (loot_esp::lethals) {
		if (stringContains(model, xorstr_("grenade_frag")))
			return xorstr_("Frag");
		if (stringContains(model, xorstr_("grenade_semtex")) && loot_esp::lethals)
			return xorstr_("Semtex");
		if (stringContains(model, xorstr_("grenade_thermite")) && loot_esp::lethals)
			return xorstr_("Thermite");
		if (stringContains(model, xorstr_("t10_molotov")))
			return xorstr_("Molotov");
	}

	if (loot_esp::tacticals) {
		if (stringContains(model, xorstr_("grenade_flash")))
			return xorstr_("Flash");
		if (stringContains(model, xorstr_("grenade_snapshot")) && loot_esp::tacticals)
			return xorstr_("Snapshot");
		if (stringContains(model, xorstr_("smoke")) && loot_esp::tacticals)
			return xorstr_("Smoke");
		if (stringContains(model, xorstr_("grenade_concussion")) && loot_esp::tacticals)
			return xorstr_("Concussion");
		if (stringContains(model, xorstr_("grenade_decoy")) && loot_esp::tacticals)
			return xorstr_("Decoy");
		if (stringContains(model, xorstr_("wm_stim")) && loot_esp::tacticals)
			return xorstr_("Stim");
	}

	if (loot_esp::lootboxes) {
		if (stringContains(model, xorstr_("backpack")) && loot_esp::lootboxes)
			return xorstr_("Backpack");
		if (stringContains(model, xorstr_("duffle_bag")) && loot_esp::lootboxes)
			return xorstr_("Duffle Bag");
		if (stringContains(model, xorstr_("medicine_cabinet")) && loot_esp::lootboxes)
			return xorstr_("Medicine Cabinet");
		if (stringContains(model, xorstr_("tool_box")) && loot_esp::lootboxes)
			return xorstr_("Tool Box");
		if (stringContains(model, xorstr_("drug_brick")) && loot_esp::lootboxes)
			return xorstr_("Drugs");
		if (stringContains(model, xorstr_("fuel_")) && loot_esp::lootboxes)
			return xorstr_("Fuel Container");
		if (stringContains(model, xorstr_("store_cash")) && loot_esp::lootboxes)
			return xorstr_("Cash Register");
		if (stringContains(model, xorstr_("utility_metal_crate")) && loot_esp::lootboxes)
			return xorstr_("Utility Crate");
		if (stringContains(model, xorstr_("medical_")) && loot_esp::lootboxes)
			return xorstr_("Medical Supplies");
		if (stringContains(model, xorstr_("locker_")) && loot_esp::lootboxes)
			return xorstr_("Locker");
	}

	if (loot_esp::ammo)
		if (stringContains(model, xorstr_("ammo")) && loot_esp::ammo)
			return xorstr_("Ammo");

	if (loot_esp::money)
		if (stringContains(model, xorstr_("money")) && loot_esp::money)
			return xorstr_("Cash");

	if (loot_esp::armour)
		if (stringContains(model, xorstr_("loot_wm_armor")) && loot_esp::armour)
			return xorstr_("Armor Plate");

	if (loot_esp::weapon_crates)
		if (stringContains(model, xorstr_("crate")) && loot_esp::weapon_crates)
			return xorstr_("Loot Crate");

	if (loot_esp::misc) {
		if (stringContains(model, xorstr_("activity_phone")) && loot_esp::misc)
			return xorstr_("Activity Phone");
		if (stringContains(model, xorstr_("radio")) && loot_esp::misc)
			return xorstr_("Radio");
		if (stringContains(model, xorstr_("cassette_player")) && loot_esp::misc)
			return xorstr_("ZM Intel");
		if (stringContains(model, xorstr_("zm_junk_parts")) && loot_esp::misc)
			return xorstr_("ZM Salvage");
		if (stringContains(model, xorstr_("zm_crystal")) && loot_esp::misc)
			return xorstr_("Aether Crystal");
		if (stringContains(model, xorstr_("power_up")) && loot_esp::misc)
			return xorstr_("ZM Power Up");
	}

	//wall buys
	if (loot_esp::Wallbuys)
		if (stringContains(model, xorstr_("zm_chalk_buy")) && loot_esp::Wallbuys)
			return xorstr_("Wall Buy");

	//GG / Perks / Power
	if (loot_esp::ZMMachines) {
		if (stringContains(model, xorstr_("gg_machine")) && loot_esp::ZMMachines)
			return xorstr_("Gobble Gum Machine");
		if (stringContains(model, xorstr_("zm_machine_amp_crystal")) && loot_esp::ZMMachines)
			return xorstr_("Power Machine");
		if (stringContains(model, xorstr_("zm_machine")) && !stringContains(model, xorstr_("zm_machine_amp_crystal")) && loot_esp::ZMMachines)
			return xorstr_("Perk Machine");
	}

	//EE
	if (loot_esp::ZMEE) {
		if (stringContains(model, xorstr_("ob_mrg")) && loot_esp::ZMEE)
			return xorstr_("EE Bear");

		if (stringContains(model, xorstr_("ob_mrp")) && loot_esp::ZMEE)
			return xorstr_("EE Bear");

		if (stringContains(model, xorstr_("zm_aetherella")) && loot_esp::ZMEE)
			return xorstr_("EE Aetherella");

		if (stringContains(model, xorstr_("wonder_weapon_quest_water")) && loot_esp::ZMEE)
			return xorstr_("EE Water Valve");

		if (stringContains(model, xorstr_("toy_stuffed_animal")) && loot_esp::ZMEE)
			return xorstr_("EE Stuffed Animal");

		if (stringContains(model, xorstr_("ww_handbrake")) && loot_esp::ZMEE)
			return xorstr_("WW Part");
	}
	//Traps
	if (loot_esp::ZMTrap) {
		if (stringContains(model, xorstr_("aether_field_emitter")) && loot_esp::ZMTrap)
			return xorstr_("ZM Trap");

		if (stringContains(model, xorstr_("tentacle_trap")) && loot_esp::ZMTrap)
			return xorstr_("ZM Trap");
	}
	return "NULL"; //model;
}

Weapon_T get_weapon_ptr(int i) {
	return *(Weapon_T*)(Offset::P_CG_ClientModel_RuntimeData + (0x34C + (i * 0x3E0)));
}

DWORD64 get_ptr(int i) {
	return (Offset::P_CG_ClientModel_RuntimeData + (i * 0x3E0)); 
}

int get_modelcount(DWORD64 ptr) {
	return *(short*)(ptr + 0x110);
}

Vector3 get_pos(DWORD64 ptr) {
	return *(Vector3*)(ptr + 0x170); 
}

struct lootdef {
	char name[64];
};

void Get_Loot() 
{ // This method only works for BR gametypes
	char WeaponNameBuffer[255];

	if (!loot_esp::enable)
		return;

	if (!MyClient.Got_Client)
		return;

	//if (!GameCall<bool>(Offset::CL_Main_IsBRGameType)(0))
	//	return;

	if (!Globals::InGame2)
		return;

	DWORD64 ptr;

	for (int i = 0; i < 384; i++) {

		ptr = get_ptr(i);
		Log_To_Notepad("ptr = 0x%p", ptr);
		
		loot_t[i].canDrawLoot = false;
		loot_t[i].distance = 0;
		loot_t[i].visible = false;
		loot_t[i].origin = Vector3(-9999, -9999, -9999);

		if (get_modelcount(ptr))
		{
			Log_To_Notepad("get_modelcount = %i", get_modelcount(ptr));

			Vector3 pos = get_pos(ptr);
			if (get_modelcount(ptr) == 0 || get_modelcount(ptr) > 16)
				continue;
	
			Log_To_Notepad("pos.x = %f | pos.y = %f | pos.z = %f", pos.x,pos.y, pos.z);

			//ptr = *(DWORD64*)ptr;
			//if (ptr < 0x10000000000 || ptr > 0x50000000000)
			//	continue;
			//Log_To_Notepad("ptr = 0x%p", ptr);

			DWORD64 ptr1 = *(DWORD64*)(ptr + 0x8);
			if (ptr1 < 0x10000000000 || ptr1 > 0x50000000000)
				continue;
		//	Log_To_Notepad("ptr1 = 0x%p", ptr1);

			auto weapon = get_weapon_ptr(i);
			Log_To_Notepad("weapon = 0x%p", weapon);

			int weaponClassIdx = GameCall<int>(Offset::BG_GetWeaponClass)(weapon, false);
	
			Log_To_Notepad("weaponClassIdx = %i", weaponClassIdx);

			lootdef model = *(lootdef*)ptr1;
	
			Log_To_Notepad("model.name = %s", model.name);

			if (!std::string(model.name).empty()) {
				Log_To_Notepad("model.name = %s", model.name);

				loot_t[i].origin = pos;
				loot_t[i].distance = (CalculateDistance3D(MyClient.Head_Pos, pos) / 55);

				if (!GlobalPlayerData::WorldToScreen(&pos, &loot_t[i].screenPos))
					continue;

				if (loot_esp::weapons && (weaponClassIdx == WEAPCLASS_RIFLE || weaponClassIdx == WEAPCLASS_SNIPER || weaponClassIdx == WEAPCLASS_MG || weaponClassIdx == WEAPCLASS_SMG || weaponClassIdx == WEAPCLASS_SPREAD || weaponClassIdx == WEAPCLASS_PISTOL || weaponClassIdx == WEAPCLASS_GRENADE || weaponClassIdx == WEAPCLASS_ROCKETLAUNCHER))
				{
					GameCall<char*>(Offset::WeaponDisplayName)(weapon, 0, false, WeaponNameBuffer, sizeof(WeaponNameBuffer), 0);

					std::string WeaponName = WeaponNameBuffer;
					if (WeaponName.find(xorstr_(" ")) != std::string::npos) {
						WeaponName.erase(WeaponName.find(xorstr_(" ")), 2);

						std::copy(WeaponName.begin(), WeaponName.end(), WeaponNameBuffer);
						WeaponNameBuffer[WeaponName.size()] = '\0';
					}

					loot_t[i].name = WeaponNameBuffer;

				}
				else
				{
					loot_t[i].name = get_name_from_model(model.name, i);
				}
				Log_To_Notepad("loot_t[i].name = %s", loot_t[i].name);
				loot_t[i].visible = GlobalPlayerData::SightTrace2(&MyClient.View_Origin, &loot_t[i].origin, MyClient.Client_Num);

				if (loot_t[i].name != "NULL") {
					loot_t[i].canDrawLoot = true;
				}
					
			}
		}
	}
}
