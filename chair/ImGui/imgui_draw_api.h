#pragma once
#include "..\Globals\framework.h"

struct FrameContext
{
	ID3D12CommandAllocator* CommandAllocator;
	UINT64                  FenceValue;
};

namespace Type
{
	typedef void(CALLBACK* tImguiStyle)();
	typedef void(CALLBACK* tESP)(ImFont*);
}

namespace Renderer
{
	bool Start(IDXGISwapChain3* SwapChain, ID3D12CommandQueue* CommandQueue, Type::tImguiStyle SetStyleFunction, float font_size, ImFont**);
	void RemoveBoarder(Type::tESP esp_function, ImFont* font);
	void ResetImGuiRequest();
	bool ImGuiNeedReset();
	void HeaderFrame();
	bool IsReady();
	void Clear();
}