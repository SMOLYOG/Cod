#pragma once

#include "Scanners.h"
#include "..\Memory\Memory.h"
#include "..\Pattern Scanners\PatternScanners.h"

bool debug = true;

bool MiscDone = false;
bool Visualsdone = false;
bool UsercmdDone = false;
bool DDLDone = false;
bool Luidone = false;
bool AllDone = false;
bool gotcmdq = false;
bool gotpacket = false;
uintptr_t test;

namespace ScanSigs {
	namespace Miscellaneous {
		void ScanSigs() {
			if (!AllDone)
			{

				Offset::GetItemQuantity = SCAN(xorstr_("E8 ? ? ? ? 33 C9 48 8D 7F")); 
				if (Offset::GetItemQuantity) {
					Offset::GetItemQuantity = RESOLVE(Offset::GetItemQuantity, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetItemQuantity = 0x%p", Offset::GetItemQuantity);

	
				Offset::BlackBoxIntalized = SCAN(xorstr_("E8 ?? ?? ?? ?? 84 C0 74 2A 48 8D 54 24 ?? 8B CB E8 ?? ?? ?? ??"));
				if (Offset::BlackBoxIntalized) {
					Offset::BlackBoxIntalized = RESOLVE(Offset::BlackBoxIntalized, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::BlackBoxIntalized = 0x%p", Offset::BlackBoxIntalized);

				Offset::GetInstance = SCAN(xorstr_("E8 ?? ?? ?? ?? 4C 8D 4C 24 ?? C6 44 24 ?? ?? 4C 8D 44 24 ?? 8B D7"));
				if (Offset::GetInstance) {
					Offset::GetInstance = RESOLVE(Offset::GetInstance, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetInstance = 0x%p", Offset::GetInstance);

				Offset::GetConstInstance = SCAN(xorstr_("E8 ?? ?? ?? ?? 45 33 C0 48 8B CB C5 F8 10 B0"));
				if (Offset::GetConstInstance) {
					Offset::GetConstInstance = RESOLVE(Offset::GetConstInstance, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetConstInstance = 0x%p", Offset::GetConstInstance);

				Offset::SendMessageToChat = SCAN(xorstr_("C5 F9 7F 74 24 ?? E8 ?? ?? ?? ?? 33 D2 84 C0 0F 95 C2"));
				if (Offset::SendMessageToChat) {
					Offset::SendMessageToChat = RESOLVE(Offset::SendMessageToChat + 6, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::SendMessageToChat = 0x%p", Offset::SendMessageToChat);

				Offset::BG_GetWeaponClass = SCAN(xorstr_("E8 ? ? ? ? 0F B6 C8 E8 ? ? ? ? 48 8B CE 48 8B F8"));
				if (Offset::BG_GetWeaponClass) {
					Offset::BG_GetWeaponClass = RESOLVE(Offset::BG_GetWeaponClass, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::BG_GetWeaponClass = 0x%p", Offset::BG_GetWeaponClass);

				Offset::BG_GetAmmoInClipForWeapon = SCAN(xorstr_("E8 ?? ?? ?? ?? B9 ?? ?? ?? ?? 8B D8 E8 ?? ?? ?? ?? 85 C0 78"));
				if (Offset::BG_GetAmmoInClipForWeapon) {
					Offset::BG_GetAmmoInClipForWeapon = RESOLVE(Offset::BG_GetAmmoInClipForWeapon, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::BG_GetAmmoInClipForWeapon = 0x%p", Offset::BG_GetAmmoInClipForWeapon);

				Offset::nextState = SCAN(xorstr_("41 8B F8 48 8B DA 8B F1 7C"));
				if (Offset::nextState) {
					Offset::nextState = *(uint32_t*)(Offset::nextState + 0xD) - 0x8;
					sigcount++;
				}
				Log_To_Notepad("Offset::nextState = 0x%p", Offset::nextState);


				Offset::CL_Main_IsBRGameType = SCAN(xorstr_("E8 ? ? ? ? 4D 8D 46 69"));
				if (Offset::CL_Main_IsBRGameType) {
					Offset::CL_Main_IsBRGameType = RESOLVE(Offset::CL_Main_IsBRGameType, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::CL_Main_IsBRGameType = 0x%p", Offset::CL_Main_IsBRGameType);

				Offset::UI_SafeTranslateString = SCAN(xorstr_("40 53 48 83 EC ? 80 39 1F 48 8B D9"));
				if (Offset::UI_SafeTranslateString) {
					sigcount++;
				}
				Log_To_Notepad("Offset::UI_SafeTranslateString = 0x%p", Offset::UI_SafeTranslateString);

				Offset::P_CG_ClientModel_RuntimeData = SCAN(xorstr_("48 C1 E1 07 48 03 CB 48 69 F1"));
				if (Offset::P_CG_ClientModel_RuntimeData) {
					Offset::P_CG_ClientModel_RuntimeData = RESOLVE(Offset::P_CG_ClientModel_RuntimeData - 11, 3, 7);
					sigcount++;
				}
				Log_To_Notepad("Offset::P_CG_ClientModel_RuntimeData = 0x%p", Offset::P_CG_ClientModel_RuntimeData);

				Offset::A_CG_Entity_GetPlayerViewOrigin = SCAN(xorstr_("8B 41 ?? 89 02 8B 41 ?? 89 42 04 C5 FA 10 41 ?? C5 FA 11 42 ?? C5 FA 58 81 ?? ?? ?? ?? C5 FA 11 42 ?? C3"));
				if (Offset::A_CG_Entity_GetPlayerViewOrigin)
					sigcount++;
				Log_To_Notepad("Offset::A_CG_Entity_GetPlayerViewOrigin = 0x%p", Offset::A_CG_Entity_GetPlayerViewOrigin);

				
				Offset::EndLobby = SCAN(xorstr_("48 8B 54 24 ?? 4C 8B C0 E8 ?? ?? ?? ?? 4C 8B BC 24 ?? ?? ?? ??"));
				Log_To_Notepad("Offset::EndLobby = 0x%p", Offset::EndLobby);

				if (Offset::EndLobby != 0ui64) {
					//DWORD64 temp_endlobby = SCAN(xorstr_("40 55"), (DWORD64)Offset::EndLobby, 0x76);
					//Log_To_Notepad("Offset::EndLobby = 0x%p", Offset::EndLobby);

					//if (temp_endlobby == NULL)
					//	temp_endlobby = SCAN(xorstr_("4C 8B"), (DWORD64)Offset::EndLobby, 0x76);
					//Log_To_Notepad("Offset::EndLobby = 0x%p", Offset::EndLobby);

				//	if (temp_endlobby == NULL)
						DWORD64	temp_endlobby = SCAN(xorstr_("48 89 5C 24 10"), (DWORD64)Offset::EndLobby, 0x76);
					Log_To_Notepad("Offset::EndLobby = 0x%p", Offset::EndLobby);

					Offset::EndLobby = temp_endlobby;
					sigcount++;

				}
				Log_To_Notepad("Offset::EndLobby = 0x%p", Offset::EndLobby);

				Offset::Chams = SCAN(xorstr_("E8 ?? ?? ?? ?? 48 81 C3 ?? ?? ?? ?? 48 83 EE 01 0F 85 ?? ?? ?? ?? 48 8B 74 24 ?? 48 8B 5C 24 ?? 48 8D 7C 24"));
				if (Offset::Chams) {
					Offset::Chams = RESOLVE(Offset::Chams, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::Chams = 0x%p", Offset::Chams);

				Offset::GetData = SCAN(xorstr_("48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC 20 48 63 D9 49 8B F0 8B CA 8B FA E8"));
				if (Offset::GetData)
					sigcount++;
				Log_To_Notepad("Offset::GetData = 0x%p", Offset::GetData);

				Offset::PartyDisband = SCAN(xorstr_("78 70 61 72 74 79 64 69 73 62 61 6E 64 61 66 74 65 72 72 6f 75 6E 64"));
				if (Offset::PartyDisband)
					sigcount++;
				Log_To_Notepad("Offset::PartyDisband = 0x%p", Offset::PartyDisband);

				Offset::GetIndexByName = SCAN(xorstr_("E8 ?? ?? ?? ?? 8B C8 8B D8 E8 ?? ?? ?? ?? 8B 0D ?? ?? ?? ?? 4C"));
				if (Offset::GetIndexByName) {
					Offset::GetIndexByName = RESOLVE(Offset::GetIndexByName, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetIndexByName = 0x%p", Offset::GetIndexByName);

				Offset::GetButton = SCAN(xorstr_("E8 ?? ?? ?? ?? C5 FA 59 CE BA ?? ?? ?? ?? 33 C9 C5 FA 2C F9 E8"));
				if (Offset::GetButton) {
					Offset::GetButton = RESOLVE(Offset::GetButton, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetButton = 0x%p", Offset::GetButton);

				Offset::SelfChams = SCAN(xorstr_("E8 ?? ?? ?? ?? FF ?? 83 ?? 02 0F 82 ?? ?? ?? ?? 4C 8D 9C"));
				if (Offset::SelfChams) {
					Offset::SelfChams = RESOLVE(Offset::SelfChams, 1, 5);
					sigcount++;

				}
				Log_To_Notepad("Offset::SelfChams = 0x%p", Offset::SelfChams);

				Offset::ShellShock = SCAN(xorstr_("E8 ?? ?? ?? ?? 44 8B ?? ?? ?? ?? ?? 41 8B CE 44 8B"));
				if (Offset::ShellShock) {
					Offset::ShellShock = RESOLVE(Offset::ShellShock, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::ShellShock = 0x%p", Offset::ShellShock);

			
				Offset::WeaponFireType = SCAN(xorstr_("E8 ?? ?? ?? ?? 40 0F B6 D6 48 8B CF 0F B6 D8 E8 ?? ?? ?? ?? 3C 09 0F 94 C0"));
				if (Offset::WeaponFireType) {
					Offset::WeaponFireType = RESOLVE(Offset::WeaponFireType, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::WeaponFireType = 0x%p", Offset::WeaponFireType);

				Offset::ThirdPerson = SCAN(xorstr_("E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 41 8B CE"));
				if (Offset::ThirdPerson) {
					Offset::ThirdPerson = RESOLVE(Offset::ThirdPerson, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::ThirdPerson = 0x%p", Offset::ThirdPerson);

				Offset::Controller = SCAN(xorstr_("48 8D 05 ?? ?? ?? ?? 48 03 C8 0F BA E2 1C"));
				if (Offset::Controller) {
					Offset::Controller = RESOLVE(Offset::Controller, 3, 7);
					sigcount++;
				}
				Log_To_Notepad("Offset::Controller = 0x%p", Offset::Controller);

				Offset::FOV = SCAN(xorstr_("E8 ? ? ? ? 48 8B CB C5 FA 10 00"));
				if (Offset::FOV) {
					Offset::FOV = RESOLVE(Offset::FOV, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::FOV = 0x%p", Offset::FOV);

				Offset::InGameCheck = SCAN(xorstr_("80 3D ?? ?? ?? ?? ?? 75 63 C6 05 ?? ?? ?? ?? ?? E8 ?? ?? ?? ??"));
				if (Offset::InGameCheck) {
					Offset::InGameCheck = RESOLVE(Offset::InGameCheck, 2, 7);
					sigcount++;
				}
				Log_To_Notepad("Offset::InGameCheck = 0x%p", Offset::InGameCheck);

				Offset::NoRecoil = SCAN(xorstr_("4C 8D BF ? ? ? ? 41 8B C6"));
				if (Offset::NoRecoil) {
					Offset::NoRecoil = *(uint32_t*)(Offset::NoRecoil + 3);
					sigcount++;
				}
				Log_To_Notepad("Offset::NoRecoil = 0x%p", Offset::NoRecoil);

				Offset::GetPlayerName = SCAN(xorstr_("40 53 55 56 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48 63 E9 49 8B F1 8B CD"));
				if (Offset::GetPlayerName)
					sigcount++;
				Log_To_Notepad("Offset::GetPlayerName = 0x%p", Offset::GetPlayerName);


				Offset::Tracers = SCAN(xorstr_("4C 8B DC 49 89 5B 10 49 89 6B 18 49 89 73 20 49 89 4B 08 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 33 C0 41 8B F8"));
				if (Offset::Tracers)
					sigcount++;
				Log_To_Notepad("Offset::Tracers = 0x%p", Offset::Tracers);

				Offset::GetBonePosition = SCAN(xorstr_("8B CE E8 ?? ?? ?? ?? 48 8B B4 24 ?? ?? ?? ?? 48 8B AC 24 ?? ?? ?? ?? 48 8B 9C 24"));
				if (Offset::GetBonePosition) {
					Offset::GetBonePosition = RESOLVE(Offset::GetBonePosition + 2, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetBonePosition = 0x%p", Offset::GetBonePosition);

				Offset::GetEntity = SCAN(xorstr_("E8 ?? ?? ?? ?? 8B CD 48 8B F0 0F BF"));
				if (Offset::GetEntity) {
					Offset::GetEntity = RESOLVE(Offset::GetEntity, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetEntity = 0x%p", Offset::GetEntity);

				Offset::PlaceFull = SCAN(xorstr_("48 8D 15 ?? ?? ?? ?? 48 8B 5C 24 ?? 48 8B 74 24 ?? 48 83 C4 20"));
				if (Offset::PlaceFull) {
					Offset::PlaceFull = RESOLVE(Offset::PlaceFull, 3, 7);
					sigcount++;

				}
				else {
					Offset::PlaceFull = SCAN(xorstr_("48 8D 15 ?? ?? ?? ?? E9 ?? ?? ?? ?? 41 F7 C0 ?? ?? ?? ?? 0F 85 ?? ?? ?? ??"));
					if (Offset::PlaceFull) {
						Offset::PlaceFull = RESOLVE(Offset::PlaceFull, 3, 7);
						sigcount++;
					}
				}
				Log_To_Notepad("Offset::PlaceFull = 0x%p", Offset::PlaceFull);

				Offset::Score = SCAN(xorstr_("E8 ?? ?? ?? ?? 4C 8B C8 45 8B C5 48 8B D6 48 8B CD E8 ?? ?? ?? ??"));
				if (Offset::Score) {
					Offset::Score = RESOLVE(Offset::Score, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::Score = 0x%p", Offset::Score);

				Offset::MaxPlayerCount = SCAN(xorstr_("8B 15 ?? ?? ?? ?? E8 ?? ?? ?? ?? FF C3 89 07 48 8D 7F 04"));
				if (Offset::MaxPlayerCount) {
					Offset::MaxPlayerCount = RESOLVE(Offset::MaxPlayerCount, 2, 6);
					sigcount++;
				}
				Log_To_Notepad("Offset::MaxPlayerCount = 0x%p", Offset::MaxPlayerCount);

				Offset::PlayerState = SCAN(xorstr_("48 8D 8A ?? ?? ?? ?? E8 ?? ?? ?? ?? C5 F0 57 C9"));
				if (Offset::PlayerState == NULL) {
					Offset::PlayerState = SCAN(xorstr_("49 8D 48 ?? E8 ?? ?? ?? ?? C5 F0 57 C9"));
					Offset::PlayerState = *(byte*)(Offset::PlayerState + 3);
					sigcount++;
				}
				else {
					Offset::PlayerState = *(uint32_t*)(Offset::PlayerState + 3);
					sigcount++;
				}
				Log_To_Notepad("Offset::PlayerState = 0x%p", Offset::PlayerState);

		
				Offset::GetAngle = SCAN(xorstr_("48 63 44 24 ?? 48 69 C8 ?? ?? ?? ?? 41 8B 47 7C")); //broke not needed
				if (Offset::GetAngle) {
					ZydisDecodedInstruction instruction{};
					ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
					DECODE(Offset::GetAngle + 13, &instruction, operands);

					if (operands[1].mem.disp.has_displacement)
						Offset::GetAngle = operands[1].mem.disp.value;

				}
				else {
					ZydisDecoder decoder;
					ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

					auto decode = [&decoder](ZyanU8* data) -> std::pair<ZydisDecodedInstruction, std::array<ZydisDecodedOperand, ZYDIS_MAX_OPERAND_COUNT>> {
						ZydisDecodedInstruction instruction;
						std::array<ZydisDecodedOperand, ZYDIS_MAX_OPERAND_COUNT> operands;
						if (ZYAN_FAILED(ZydisDecoderDecodeFull(&decoder, data, 20,
							&instruction, operands.data())))
							return {};

						return std::make_pair(instruction, operands);
						};


					Offset::GetAngle = [&]() -> uintptr_t {
						auto address = (ZyanU8*)SCAN(xorstr_("C5 FA 10 05 ?? ?? ?? ?? 48 8B D1"));
						if (!address)
							return 0;

						auto [instruction, operands] = decode(address);
						while (instruction.mnemonic != ZYDIS_MNEMONIC_LEA)
						{
							address += 1;
							std::tie(instruction, operands) = decode(address);
						}

						if (operands[0].reg.value != ZYDIS_REGISTER_R9 || !operands[1].mem.disp.has_displacement)
							return 0;


						return operands[1].mem.disp.value;
						}();
				}
				if (Offset::GetAngle)
					sigcount++;
				Log_To_Notepad("Offset::GetAngle = 0x%p", Offset::GetAngle);


				Offset::GetClientInfo = SCAN(xorstr_("48 8D 0D ?? ?? ?? ?? 48 8B 0C D1 8B D3 48 8B 01 FF 90"));
				if (Offset::GetClientInfo) {
					Offset::GetClientInfo = RESOLVE(Offset::GetClientInfo, 3, 7);
					sigcount++;
				}
				Log_To_Notepad("Offset::GetClientInfo = 0x%p", Offset::GetClientInfo);
				Offset::WorldToScreen = SCAN(xorstr_("E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? C5 FA 10 94 24 ? ? ? ? C5 CA 58"));
				if (Offset::WorldToScreen) {
					Offset::WorldToScreen = RESOLVE(Offset::WorldToScreen, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::WorldToScreen = 0x%p", Offset::WorldToScreen);

				Offset::WeaponDisplayName = SCAN(xorstr_("E8 ?? ?? ?? ?? 48 C7 C7 ?? ?? ?? ?? 66 0F 1F 44 00 ??"));
				if (Offset::WeaponDisplayName) {
					Offset::WeaponDisplayName = RESOLVE(Offset::WeaponDisplayName, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::WeaponDisplayName = 0x%p", Offset::WeaponDisplayName);

				Offset::SightTrace = SCAN(xorstr_("E8 ?? ?? ?? ?? 84 C0 74 32 FF C3 48 83 C7 0C"));
				if (Offset::SightTrace) {
					Offset::SightTrace = RESOLVE(Offset::SightTrace, 1, 5);
					sigcount++;

				}
				Log_To_Notepad("Offset::SightTrace = 0x%p", Offset::SightTrace);

				Offset::ViewAngles = SCAN(xorstr_("41 8B 46 08 41 89 44 24 ?? E8 ?? ?? ?? FF"));
				if (Offset::ViewAngles) {
					Offset::ViewAngles = RESOLVE(Offset::ViewAngles + 9, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::ViewAngles = 0x%p", Offset::ViewAngles);

				Offset::WeaponName = SCAN(xorstr_("8B CF 48 89 6C 24 ?? E8 ?? ?? ?? ?? 8D 4B CF 83 F9 1A 77 0E"));
				if (Offset::WeaponName) {
					Offset::WeaponName = RESOLVE(Offset::WeaponName + 7, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::WeaponName = 0x%p", Offset::WeaponName);

				Offset::GetEntityType = SCAN(xorstr_("E8 ? ? ? ? 0F B7 C0 83 C0 FE"));
				if (Offset::GetEntityType) {
					Offset::GetEntityType = RESOLVE(Offset::GetEntityType, 1, 5);
					sigcount++;

				}
				Log_To_Notepad("Offset::GetEntityType = 0x%p", Offset::GetEntityType);

				Offset::UserCMDNumberAAB = SCAN(xorstr_("8D 47 44 33 87 ?? ?? ?? ?? 8D 58 02"));
				if (Offset::UserCMDNumberAAB) {
					ZydisDecodedInstruction instruction{};
					ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
					DECODE(Offset::UserCMDNumberAAB, &instruction, operands);

					// typeshit
					DECODE(Offset::UserCMDNumberAAB + instruction.length, &instruction, operands);

					if (operands[1].mem.disp.has_displacement)
						Offset::UserCMDNumberAAB = operands[1].mem.disp.value;

					sigcount++;

				}
				else {
					Offset::UserCMDNumberAAB = SCAN(xorstr_("8D 87 ? ? ? ? 33 87 ? ? ? ? 8D 58 02 0F AF D8 33 9F ? ? ? ? 3B F3 7E 17 41 B8 ? ? ? ? 48 8D 15 ? ? ? ?"));
					if (Offset::UserCMDNumberAAB) {
						ZydisDecodedInstruction instruction{};
						ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
						DECODE(Offset::UserCMDNumberAAB, &instruction, operands);

						// typeshit
						DECODE(Offset::UserCMDNumberAAB + instruction.length, &instruction, operands);

						if (operands[1].mem.disp.has_displacement)
							Offset::UserCMDNumberAAB = operands[1].mem.disp.value;

						sigcount++;

					} 
					else {
						Offset::UserCMDNumberAAB = SCAN(xorstr_("8D 43 80 48 8B 9C 24 ? ? ? ? 3B F0 0F 8E ? ? ? ?"));
						if (Offset::UserCMDNumberAAB) {
							ZydisDecodedInstruction instruction{};
							ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
							DECODE(Offset::UserCMDNumberAAB, &instruction, operands);

							// typeshit
							DECODE(Offset::UserCMDNumberAAB + instruction.length, &instruction, operands);

							if (operands[1].mem.disp.has_displacement)
								Offset::UserCMDNumberAAB = operands[1].mem.disp.value;

							sigcount++;

						}
					}
				}
				Log_To_Notepad("Offset::UserCMDNumberAAB = 0x%p", Offset::UserCMDNumberAAB);

				Offset::UserCMDNumber = SCAN(xorstr_("8D 47 44 33 87 ?? ?? ?? ?? 8D 58 02"));
				if (Offset::UserCMDNumber) {
					ZydisDecodedInstruction instruction{};
					ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
					DECODE(Offset::UserCMDNumber, &instruction, operands);

					if (operands[1].mem.disp.has_displacement)
						Offset::UserCMDNumber = operands[1].mem.disp.value;
					sigcount++;

				}
				else {
					Offset::UserCMDNumber = SCAN(xorstr_("8D 87 ? ? ? ? 33 87 ? ? ? ? 8D 58 02 0F AF D8 33 9F ? ? ? ? 3B F3 7E 17 41 B8 ? ? ? ? 48 8D 15 ? ? ? ?"));
					if (Offset::UserCMDNumber) {
						ZydisDecodedInstruction instruction{};
						ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
						DECODE(Offset::UserCMDNumber, &instruction, operands);

						if (operands[1].mem.disp.has_displacement)
							Offset::UserCMDNumber = operands[1].mem.disp.value;
						sigcount++;

					}
					else {
						Offset::UserCMDNumber = SCAN(xorstr_("8D 43 80 48 8B 9C 24 ? ? ? ? 3B F0 0F 8E ? ? ? ?"));
						if (Offset::UserCMDNumber) {
							ZydisDecodedInstruction instruction{};
							ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
							DECODE(Offset::UserCMDNumber, &instruction, operands);

							if (operands[1].mem.disp.has_displacement)
								Offset::UserCMDNumber = operands[1].mem.disp.value;
							sigcount++;

						}
					}
				}
				Log_To_Notepad("Offset::UserCMDNumber = 0x%p", Offset::UserCMDNumber);

				Offset::UserCMD = SCAN(xorstr_("0F 8E ?? ?? ?? ?? 85 F6 0F 8E ?? ?? ?? ?? 48 ?? C7"));
				if (Offset::UserCMD) {
					ZydisDecodedInstruction instruction{};
					ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
					DECODE(Offset::UserCMD + 14, &instruction, operands);
					if (instruction.mnemonic == ZYDIS_MNEMONIC_ADD)
						Offset::UserCMD = operands[1].imm.value.u;
					sigcount++;

				}
				Log_To_Notepad("Offset::UserCMD = 0x%p", Offset::UserCMD);

				Offset::UserCMDPackAngle = Memory::find_ida_sig(NULL, xorstr_("E8 ? ? ? ? C5 FA 10 0D ? ? ? ? C5 FA 10 44 24 ? 41 B8 ? ? ? ? 89 45 A4 E8")).self_jmp(1);
				if (Offset::UserCMDPackAngle)
					sigcount++;
				Log_To_Notepad("Offset::UserCMDPackAngle = 0x%p", Offset::UserCMDPackAngle);

				Offset::A_CL_Input_ClearAutoForwardFlag = SCAN(xorstr_("8B CD E8 ?? ?? ?? FF 8B CD E8 ?? ?? ?? FF 8B CD E8 ?? ?? ?? FF 8B CD E8"));
				if (Offset::A_CL_Input_ClearAutoForwardFlag) {
					Offset::A_CL_Input_ClearAutoForwardFlag = RESOLVE(Offset::A_CL_Input_ClearAutoForwardFlag + 2, 1, 5);
					sigcount++;

				}
				Log_To_Notepad("Offset::A_CL_Input_ClearAutoForwardFlag = 0x%p", Offset::A_CL_Input_ClearAutoForwardFlag);
			
				Offset::GetPlayerFOV = SCAN(xorstr_("C5 FA 11 ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? C5 FA 58 54 24 ?? C5 FA 11 54 24"));
				if (Offset::GetPlayerFOV) {
					ZydisDecodedInstruction instruction{};
					ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
					DECODE(Offset::GetPlayerFOV, &instruction, operands);

					if (instruction.mnemonic == ZYDIS_MNEMONIC_VMOVSS && operands[0].mem.disp.has_displacement)
						Offset::GetPlayerFOV = operands[0].mem.disp.value;

					sigcount++;

				}
				Log_To_Notepad("Offset::GetPlayerFOV = 0x%p", Offset::GetPlayerFOV);

				Offset::Lobby_GetPartyData = SCAN(xorstr_("E8 ?? ?? ?? ?? 48 69 CB ?? ?? ?? ?? 48 03 88 ?? ?? ?? ?? 0F B6 81 ?? ?? ?? ?? 2C 03 3C 01"));
				if (Offset::Lobby_GetPartyData) {
					Offset::Lobby_GetPartyData = RESOLVE(Offset::Lobby_GetPartyData, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::Lobby_GetPartyData = 0x%p", Offset::Lobby_GetPartyData);

				Offset::getPlatform = SCAN(xorstr_("E8 ?? ?? ?? ?? 8B D6 44 0F BE F0 48 8B CD"));
				if (Offset::getPlatform) {
					Offset::getPlatform = RESOLVE(Offset::getPlatform, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::getPlatform = 0x%p", Offset::getPlatform);

				Offset::getName = SCAN(xorstr_("E8 ?? ?? ?? ?? 4C 8B C0 49 8B D4 49 8B CE"));
				if (Offset::getName) {
					Offset::getName = RESOLVE(Offset::getName, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::getName = 0x%p", Offset::getName);

				Offset::usingGamepad = SCAN(xorstr_("48 8B C8 E8 ? ? ? ? 83 F8 01 0F 94 C2 EB 02"));
				if (Offset::usingGamepad) {
					Offset::usingGamepad = RESOLVE(Offset::usingGamepad + 3, 1, 5);
					sigcount++;

				}
				Log_To_Notepad("Offset::usingGamepad = 0x%p", Offset::usingGamepad);

				Offset::getXUID = SCAN(xorstr_("E8 ?? ?? ?? ?? 48 8D 55 B0 48 8D 4C 24 ?? E8 ?? ?? ?? ?? 84 C0 0F 85 ?? ?? ?? ?? FF C3"));
				if (Offset::getXUID) {
					Offset::getXUID = RESOLVE(Offset::getXUID, 1, 5);
					sigcount++;

				}
				Log_To_Notepad("Offset::getXUID = 0x%p", Offset::getXUID);

				Offset::CL_IsPlayerTalking = SCAN(xorstr_("E8 ?? ?? ?? ?? E9 ?? ?? ?? ?? 0F B6 8E ?? ?? ?? ??"));
				if (Offset::CL_IsPlayerTalking) {
					Offset::CL_IsPlayerTalking = RESOLVE(Offset::CL_IsPlayerTalking, 1, 5);
					sigcount++;

				}		
				Log_To_Notepad("Offset::CL_IsPlayerTalking = 0x%p", Offset::CL_IsPlayerTalking);

				Offset::Party_GetMemberTeam = SCAN(xorstr_("E8 ? ? ? ? 48 63 D0 48 8D 0D ? ? ? ? 4C 8B C6"));
				if (Offset::Party_GetMemberTeam) {
					Offset::Party_GetMemberTeam = RESOLVE(Offset::Party_GetMemberTeam, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::Party_GetMemberTeam = 0x%p", Offset::Party_GetMemberTeam);

				Offset::Party_IsMemberDeafened = SCAN(xorstr_("E8 ?? ?? ?? ?? 84 C0 48 8D 0D ?? ?? ?? ?? 4C 8B C6 0F 94 C2"));
				if (Offset::Party_IsMemberDeafened) {
					Offset::Party_IsMemberDeafened = RESOLVE(Offset::Party_IsMemberDeafened, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::Party_IsMemberDeafened = 0x%p", Offset::Party_IsMemberDeafened);

				Offset::CG_EntityMP_CalcLerpPositions = SCAN(xorstr_("E8 ?? ?? ?? ?? E9 ?? ?? ?? ?? 0F BF 16 45 8B CF"));
				if (Offset::CG_EntityMP_CalcLerpPositions) {
					Offset::CG_EntityMP_CalcLerpPositions = RESOLVE(Offset::CG_EntityMP_CalcLerpPositions, 1, 5);
					sigcount++;
				}
				Log_To_Notepad("Offset::CG_EntityMP_CalcLerpPositions = 0x%p", Offset::CG_EntityMP_CalcLerpPositions);


				AllDone = true;
				Globals::ScanComplete = true;
				Beep(500, 500);
				MiscDone = true;
			}
		}
	}
	int Init_Scanners = 0;
}
