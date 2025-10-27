#pragma once
#include "DLL Init.h"
#include "../Pattern Scanners/PatternScanners.h"


namespace DLL_Init {

	std::string siggg;

	static ImFont* MainFont = nullptr;

	__declspec(dllexport)HRESULT present_hk(IDXGISwapChain3* SwapChain, UINT SyncInterval, UINT Flags) {
		if (!SwapChain)
			return OriginalPresent(SwapChain, SyncInterval, Flags);

		D3D12::CommandQueue = *reinterpret_cast<decltype(D3D12::CommandQueue)*>(Offset::commandqueue.casta());

		DXGI_SWAP_CHAIN_DESC sdesc;
		SwapChain->GetDesc(&sdesc);

		if (sdesc.OutputWindow == GetForegroundWindow())
		{

			if (!Renderer::Start(reinterpret_cast<IDXGISwapChain3*>(SwapChain), reinterpret_cast<ID3D12CommandQueue*>((D3D12::CommandQueue)), nullptr, 16.0f, &MainFont))
				return OriginalPresent(SwapChain, SyncInterval, Flags);

			Renderer::HeaderFrame();

			if (GetAsyncKeyState(KeyBinds::Menu) & 1 || KeyBinds::ControllerMenu) Globals::Open = !Globals::Open;
			if (GetAsyncKeyState(KeyBinds::Uninject) & 1 || KeyBinds::ControllerUninject) {
				Globals::Open = false;
				Kiero::ShutDown();
			}

			if (gotcmdq) {
				if (Globals::ScanComplete)
					Draw();
			}

			Renderer::RemoveBoarder(Main::Init, MainFont);

			Renderer::EndFrame();
		}

		return OriginalPresent(SwapChain, SyncInterval, Flags);
	}

	__forceinline DWORD WINAPI Init_Point(HMODULE hModule) {

		Globals::Hwind = Process::get_process_window();

		if (MH_Initialize() != MH_OK)
		{
			return 0;
		}

		Offset::JmpRbx = SCAN(xorstr_("FF 23"));
		Log_To_Notepad("Offset::JmpRbx = 0x%p", Offset::JmpRbx);

		Offset::CL_InputMP_ReadyToSendPacket = [&]() -> shared::address_t {
			shared::address_t address = Memory::find_ida_sig(NULL, xorstr_("C5 FA 5E CF C5 7A 2C C1 48 8D 94 24 ? ? ? ? 49 8B CF E8 ? ? ? ? 49 BF"));
			if (address == nullptr)
				return {};

			int counter = 0; // 3rd call mnemonic would be our desired function.
			while (counter < 3)
			{
				address.self_offset(0x1);

				ZydisDecodedInstruction instruction;
				ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
				DECODE(address, &instruction, operands);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_CALL)
					counter++;
			}

			return address.self_jmp();//

			}();
		Log_To_Notepad("Offset::CL_InputMP_ReadyToSendPacket = 0x%p", Offset::CL_InputMP_ReadyToSendPacket);

		if (Offset::CL_InputMP_ReadyToSendPacket.m_ptr <= 0)
			return false;

		Offset::commandqueue = Memory::find_ida_sig(NULL, StreamFileToMemString().c_str()).self_jmp(0x5);
		if (Offset::commandqueue) {
			gotcmdq = true;
		}
		Log_To_Notepad("Offset::commandqueue = 0x%p", Offset::commandqueue);

		if (Kiero::init(Kiero::RenderType::D3D12) == Kiero::Status::Success)
			Kiero::bind(140, (void**)&OriginalPresent, present_hk);
		else
			MessageBoxW(NULL, xorstr_(L"Could not hook to the game process. Try reinstalling DirectX, updating your graphics drivers, disabling any overlays, and restarting your PC."), xorstr_(L"Error!"), MB_ICONERROR);

	
		switch (ScanSigs::Init_Scanners) {
		case 0:

			ScanSigs::Miscellaneous::ScanSigs();
			Auto_Load();
			break;
		}
		if (ScanSigs::Init_Scanners != 2)
			ScanSigs::Init_Scanners++;


		auto CL_InputMP_ReadyToSendPacket = Offset::CL_InputMP_ReadyToSendPacket.casta<LPVOID>();

		if (MH_CreateHook(CL_InputMP_ReadyToSendPacket, &Main_Game::DetourCL_InputMP_ReadyToSendPacket,
			reinterpret_cast<LPVOID*>(&Main_Game::fpCL_InputMP_ReadyToSendPacket)) != MH_OK)
		{
			return 0;
		}

		if (MH_EnableHook(CL_InputMP_ReadyToSendPacket) != MH_OK)
		{
			return 0;
		}


		MH_CreateHook((LPVOID*)(Offset::BlockKeyboardInput), &Misc::BlockKeyboardHook, reinterpret_cast<LPVOID*>(&Misc::BlockKeyboardOrig));
		MH_CreateHook((LPVOID*)(Offset::BlockMouseInput), &Misc::BlockMouseHook, reinterpret_cast<LPVOID*>(&Misc::BlockMouseOrig));
		MH_CreateHook((LPVOID*)(Offset::BlackBoxIntalized), &Hooks::HookBlackBoxIntalized, reinterpret_cast<LPVOID*>(&Hooks::BlackBoxIntalized));
		MH_CreateHook((LPVOID*)(Offset::ThirdPerson), &Hooks::HookThirdPerson, reinterpret_cast<LPVOID*>(&Hooks::ThirdPerson));
		MH_CreateHook((LPVOID*)(Offset::ShellShock), &Hooks::HookShellShock, reinterpret_cast<LPVOID*>(&Hooks::ShellShock));
		MH_CreateHook((LPVOID*)(Offset::SelfChams), &Hooks::HookSelfChams, reinterpret_cast<LPVOID*>(&Hooks::SelfChams));
		MH_CreateHook((LPVOID*)(Offset::Tracers), &Hooks::HookTracers, reinterpret_cast<LPVOID*>(&Hooks::Tracers));
		MH_CreateHook((LPVOID*)(Offset::Chams), &Hooks::HookChams, reinterpret_cast<LPVOID*>(&Hooks::Chams));
		MH_CreateHook((LPVOID*)(Offset::FOV), &Hooks::HookFOV, reinterpret_cast<LPVOID*>(&Hooks::FOV));
		MH_CreateHook((LPVOID*)(Offset::CG_EntityMP_CalcLerpPositions), &Hooks::hkCG_EntityMP_CalcLerpPositions, reinterpret_cast<LPVOID*>(&Hooks::oCG_EntityMP_CalcLerpPositions));

		MH_EnableHook(MH_ALL_HOOKS);

		return 0;
	}


}