#include "..\ImGui/imgui_draw_api.h"
#include "..\Menu\Menu.h"
#include "..\SDK\Sdk.h"

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef LRESULT(CALLBACK* tWndProc)(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp);
extern LRESULT HKWndProc(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp);
typedef long(__fastcall* Present)(IDXGISwapChain*, UINT, UINT);
static Present OriginalPresent = NULL;

extern void WndProc_hk();

namespace OriginalFunction {
	extern tWndProc WndProc;
}

namespace Renderer
{
	extern bool ResetImGui;
	extern bool Ready;
	extern bool LoadTextureFromMemory(unsigned char* buffer, unsigned int bufferLen, ID3D12Device* d3d_device, D3D12_CPU_DESCRIPTOR_HANDLE srv_cpu_handle, ID3D12Resource** out_tex_resource, int* out_width, int* out_height);
	bool Start(IDXGISwapChain3* SwapChain, ID3D12CommandQueue* CommandQueue, Type::tImguiStyle StyleFunction, float FontSize, ImFont**);
	char InitD3D12(IDXGISwapChain3* SwapChain, ID3D12CommandQueue* CommandQueue);
	void ReInit(IDXGISwapChain3* SwapChain, ID3D12CommandQueue* CommandQueue);
	void RemoveBoarder(Type::tESP esp_function, ImFont* font);
	__forceinline bool ImGuiNeedReset();
	FrameContext* WaitForNextFrame();
	void ResetImGuiRequest();
	void HeaderFrame();
	void EndFrame();
	bool IsReady();
	void Release();
	void Clear();
}


namespace D3D12 {
	extern D3D12_CPU_DESCRIPTOR_HANDLE* RenderTargetDescriptorArray;
	extern ID3D12DescriptorHeap* SRVDescriptionHeap;
	extern ID3D12DescriptorHeap* RTVDescriptionHeap;
	extern ID3D12GraphicsCommandList* CommandList;
	extern ID3D12CommandQueue* CommandQueue;
	extern FrameContext* FrameContextArray;
	extern ID3D12Resource** ResourceArray;
	extern IDXGISwapChain3* SwapChain;
	extern HANDLE WaitableSwapChain;
	extern UINT NumberOfBackBuffers;
	extern UINT64 LastFenceValue;
	extern ID3D12Device* Device;
	extern UINT NumberOfFrames;
	extern ID3D12Fence* Fence;
	extern HANDLE FenceEvent;
	extern UINT FrameIndex;
}

