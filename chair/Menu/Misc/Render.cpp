#define STB_IMAGE_IMPLEMENTATION
#include "..\ImGui/imgui_settings.h"
#include "..\ImGui/imstb_image.h"
#include "Render.h"
#include "..\Fonts/Font.h"
#include "..\Fonts/Icons.h"
#include "image.h"

namespace OriginalFunction {
	tWndProc WndProc;
}

LRESULT HKWndProc(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp) {

	switch (Msg)
	{

	case 0x403:
	case WM_SIZE: {

		if (Msg == WM_SIZE && wp == SIZE_MINIMIZED)
			break;

		if (Renderer::IsReady()) {
			Renderer::Clear();

			ImGui_ImplDX12_InvalidateDeviceObjects();

			Renderer::ResetImGuiRequest();
		} break;
	}
	};

	ImGuiIO& io = ImGui::GetIO();

	io.WantCaptureMouse = !Globals::Open;

	ImGui_ImplWin32_WndProcHandler(hWnd, Msg, wp, lp);
	
	return OriginalFunction::WndProc(hWnd, Msg, wp, lp);
}

void WndProc_hk() {
	OriginalFunction::WndProc = (WNDPROC)SetWindowLongPtrW(Globals::Hwind, GWLP_WNDPROC, (LONG_PTR)HKWndProc);
}


namespace D3D12 {
	D3D12_CPU_DESCRIPTOR_HANDLE* RenderTargetDescriptorArray;
	ID3D12DescriptorHeap* SRVDescriptionHeap;
	ID3D12DescriptorHeap* RTVDescriptionHeap;
	ID3D12GraphicsCommandList* CommandList;
	ID3D12CommandQueue* CommandQueue;
	FrameContext* FrameContextArray;
	ID3D12Resource** ResourceArray;
	IDXGISwapChain3* SwapChain;
	HANDLE WaitableSwapChain;
	UINT NumberOfBackBuffers;
	UINT64 LastFenceValue;
	ID3D12Device* Device;
	UINT NumberOfFrames;
	ID3D12Fence* Fence;
	HANDLE FenceEvent;
	UINT FrameIndex;
}

namespace Renderer
{

	bool ResetImGui;
	bool Ready;
	bool LoadTextureFromMemory(unsigned char* buffer, unsigned int bufferLen, ID3D12Device* d3d_device, D3D12_CPU_DESCRIPTOR_HANDLE srv_cpu_handle, ID3D12Resource** out_tex_resource, int* out_width, int* out_height) {
		// Load from disk into a raw RGBA Buffer
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load_from_memory(buffer, bufferLen, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create Texture resource
		D3D12_HEAP_PROPERTIES props;
		memset(&props, 0, sizeof(D3D12_HEAP_PROPERTIES));
		props.Type = D3D12_HEAP_TYPE_DEFAULT;
		props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		desc.Alignment = 0;
		desc.Width = image_width;
		desc.Height = image_height;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		ID3D12Resource* pTexture = NULL;
		d3d_device->CreateCommittedResource(&props, D3D12_HEAP_FLAG_NONE, &desc,
			D3D12_RESOURCE_STATE_COPY_DEST, NULL, IID_PPV_ARGS(&pTexture));

		// Create a temporary upload resource to move the data in
		UINT uploadPitch = (image_width * 4 + D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1u) & ~(D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1u);
		UINT uploadSize = image_height * uploadPitch;
		desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment = 0;
		desc.Width = uploadSize;
		desc.Height = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		props.Type = D3D12_HEAP_TYPE_UPLOAD;
		props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		ID3D12Resource* uploadBuffer = NULL;
		HRESULT hr = d3d_device->CreateCommittedResource(&props, D3D12_HEAP_FLAG_NONE, &desc,
			D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&uploadBuffer));
		IM_ASSERT(SUCCEEDED(hr));

		// Write pixels into the upload resource
		void* mapped = NULL;
		D3D12_RANGE range = { 0, uploadSize };
		hr = uploadBuffer->Map(0, &range, &mapped);
		IM_ASSERT(SUCCEEDED(hr));
		for (int y = 0; y < image_height; y++)
			memcpy((void*)((uintptr_t)mapped + y * uploadPitch), image_data + y * image_width * 4, image_width * 4);
		uploadBuffer->Unmap(0, &range);

		// Copy the upload resource content into the real resource
		D3D12_TEXTURE_COPY_LOCATION srcLocation = {};
		srcLocation.pResource = uploadBuffer;
		srcLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		srcLocation.PlacedFootprint.Footprint.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srcLocation.PlacedFootprint.Footprint.Width = image_width;
		srcLocation.PlacedFootprint.Footprint.Height = image_height;
		srcLocation.PlacedFootprint.Footprint.Depth = 1;
		srcLocation.PlacedFootprint.Footprint.RowPitch = uploadPitch;

		D3D12_TEXTURE_COPY_LOCATION dstLocation = {};
		dstLocation.pResource = pTexture;
		dstLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dstLocation.SubresourceIndex = 0;

		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = pTexture;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

		// Create a temporary command queue to do the copy with
		ID3D12Fence* fence = NULL;
		hr = d3d_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
		IM_ASSERT(SUCCEEDED(hr));

		HANDLE event = CreateEvent(0, 0, 0, 0);
		IM_ASSERT(event != NULL);

		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 1;

		ID3D12CommandQueue* cmdQueue = NULL;
		hr = d3d_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&cmdQueue));
		IM_ASSERT(SUCCEEDED(hr));

		ID3D12CommandAllocator* cmdAlloc = NULL;
		hr = d3d_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAlloc));
		IM_ASSERT(SUCCEEDED(hr));

		ID3D12GraphicsCommandList* cmdList = NULL;
		hr = d3d_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAlloc, NULL, IID_PPV_ARGS(&cmdList));
		IM_ASSERT(SUCCEEDED(hr));

		cmdList->CopyTextureRegion(&dstLocation, 0, 0, 0, &srcLocation, NULL);
		cmdList->ResourceBarrier(1, &barrier);

		hr = cmdList->Close();
		IM_ASSERT(SUCCEEDED(hr));

		// Execute the copy
		cmdQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&cmdList);
		hr = cmdQueue->Signal(fence, 1);
		IM_ASSERT(SUCCEEDED(hr));

		// Wait for everything to complete
		fence->SetEventOnCompletion(1, event);
		WaitForSingleObject(event, INFINITE);

		// Tear down our temporary command queue and release the upload resource
		cmdList->Release();
		cmdAlloc->Release();
		cmdQueue->Release();
		CloseHandle(event);
		fence->Release();
		uploadBuffer->Release();

		// Create a shader resource view for the Texture
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		d3d_device->CreateShaderResourceView(pTexture, &srvDesc, srv_cpu_handle);

		// Return results
		*out_tex_resource = pTexture;
		*out_width = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}
	bool Start(IDXGISwapChain3* SwapChain, ID3D12CommandQueue* CommandQueue, Type::tImguiStyle StyleFunction, float FontSize, ImFont** font)
	{

		if (Ready && ImGuiNeedReset())
		{
			ReInit(SwapChain, CommandQueue);
			ResetImGui = false;
		}

		if (Ready)
			return true;

		if (!InitD3D12(SwapChain, CommandQueue))
			return false;

		ImGui::CreateContext();
		ImGui::GetIO().WantSaveIniSettings = false;

		if (StyleFunction == nullptr)
			ImGui::StyleColorsDark();
		else
			StyleFunction();

		ImGui_ImplWin32_Init(Globals::Hwind);
		ImGui_ImplDX12_Init(
			D3D12::Device,
			D3D12::NumberOfFrames,
			DXGI_FORMAT_R8G8B8A8_UNORM, D3D12::SRVDescriptionHeap,
			D3D12::SRVDescriptionHeap->GetCPUDescriptorHandleForHeapStart(),
			D3D12::SRVDescriptionHeap->GetGPUDescriptorHandleForHeapStart());

		ImFontConfig FontConfig;
		FontConfig.PixelSnapH = false;
		FontConfig.OversampleH = 5;
		FontConfig.OversampleV = 5;
		FontConfig.RasterizerMultiply = 1.2f;

		static const ImWchar Ranges[] = { 0x0020, 0x00FF, 0x0400, 0x052F, 0x2DE0, 0x2DFF, 0xA640, 0xA69F, 0xE000, 0xE226, 0, };


		Font::mainfont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 16, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		Font::mainfont_smaller = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 14, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		Font::mainfont_bigger = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 20, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		Font::functionfont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 18, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		Font::icons = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&iconshxd, sizeof iconshxd, 20, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());


		Font::IconFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&Icons_Font, sizeof Icons_Font, 20, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

		if (Font::mainfont == nullptr) return false;

		*font = Font::mainfont;
		WndProc_hk();

		Ready = true;

		return true;
	}
	char InitD3D12(IDXGISwapChain3* SwapChain, ID3D12CommandQueue* CommandQueue)
	{
		D3D12::CommandQueue = CommandQueue;
		D3D12::SwapChain = SwapChain;

		if (!SUCCEEDED(D3D12::SwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&D3D12::Device)))
			return 0;

		{
			DXGI_SWAP_CHAIN_DESC1 desc;

			if (!SUCCEEDED(D3D12::SwapChain->GetDesc1(&desc)))
				return 0;

			D3D12::NumberOfBackBuffers = desc.BufferCount;
			D3D12::NumberOfFrames = desc.BufferCount;
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			desc.NumDescriptors = D3D12::NumberOfBackBuffers;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			desc.NodeMask = 1;

			if (!SUCCEEDED(D3D12::Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&D3D12::RTVDescriptionHeap)))) return 0;
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			desc.NumDescriptors = 6;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			desc.NodeMask = 0;

			if (!SUCCEEDED(D3D12::Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&D3D12::SRVDescriptionHeap)))) return 0;
		}

		if (!SUCCEEDED(D3D12::Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&D3D12::Fence)))) return 0;

		D3D12::FrameContextArray = new FrameContext[D3D12::NumberOfFrames];
		D3D12::ResourceArray = new ID3D12Resource * [D3D12::NumberOfBackBuffers];
		D3D12::RenderTargetDescriptorArray = new D3D12_CPU_DESCRIPTOR_HANDLE[D3D12::NumberOfBackBuffers];

		for (UINT i = 0; i < D3D12::NumberOfFrames; ++i)
			if (!SUCCEEDED(D3D12::Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&D3D12::FrameContextArray[i].CommandAllocator)))) return 0;

		SIZE_T nDescriptorSize = D3D12::Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = D3D12::RTVDescriptionHeap->GetCPUDescriptorHandleForHeapStart();

		for (UINT i = 0; i < D3D12::NumberOfBackBuffers; ++i) {
			D3D12::RenderTargetDescriptorArray[i] = rtvHandle;
			rtvHandle.ptr += nDescriptorSize;
		}

		if (!SUCCEEDED(D3D12::Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12::FrameContextArray[0].CommandAllocator, NULL, IID_PPV_ARGS(&D3D12::CommandList))) || !SUCCEEDED(D3D12::CommandList->Close())) return 0;

		D3D12::WaitableSwapChain = D3D12::SwapChain->GetFrameLatencyWaitableObject();

		D3D12::FenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		if (D3D12::FenceEvent == NULL) return 0;

		ID3D12Resource* pBackBuffer;
		for (UINT i = 0; i < D3D12::NumberOfBackBuffers; ++i) {
			if (!SUCCEEDED(D3D12::SwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer)))) return 0;

			D3D12::Device->CreateRenderTargetView(pBackBuffer, NULL, D3D12::RenderTargetDescriptorArray[i]);
			D3D12::ResourceArray[i] = pBackBuffer;
		}
	}
	void ReInit(IDXGISwapChain3* SwapChain, ID3D12CommandQueue* CommandQueue)
	{
		InitD3D12(SwapChain, CommandQueue);
		ImGui_ImplDX12_CreateDeviceObjects();
	}
	void RemoveBoarder(Type::tESP esp_function, ImFont* font) {
		ImGuiStyle& style = ImGui::GetStyle();
		const float bor_size = style.WindowBorderSize;
		style.WindowBorderSize = 0.0f;
		esp_function(font);
		style.WindowBorderSize = bor_size;
	}
	__forceinline bool ImGuiNeedReset() {
		return ResetImGui;
	}
	FrameContext* WaitForNextFrame() {
		UINT nextFrameIndex = D3D12::FrameIndex + 1;
		D3D12::FrameIndex = nextFrameIndex;

		HANDLE waitableObjects[] = { D3D12::WaitableSwapChain, NULL };
		constexpr DWORD numWaitableObjects = 1;

		FrameContext* frameCtxt = &D3D12::FrameContextArray[nextFrameIndex % D3D12::NumberOfFrames];

		WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

		return frameCtxt;
	}
	void ResetImGuiRequest() {
		ResetImGui = true;
	}
	void HeaderFrame() {
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	void EndFrame() {
		FrameContext* frameCtxt = WaitForNextFrame();
		UINT backBufferIdx = D3D12::SwapChain->GetCurrentBackBufferIndex();

		{
			frameCtxt->CommandAllocator->Reset();
			static D3D12_RESOURCE_BARRIER barrier = {};
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
			barrier.Transition.pResource = D3D12::ResourceArray[backBufferIdx];
			D3D12::CommandList->Reset(frameCtxt->CommandAllocator, NULL);
			D3D12::CommandList->ResourceBarrier(1, &barrier);
			D3D12::CommandList->OMSetRenderTargets(1, &D3D12::RenderTargetDescriptorArray[backBufferIdx], FALSE, NULL);
			D3D12::CommandList->SetDescriptorHeaps(1, &D3D12::SRVDescriptionHeap);
		}

		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), D3D12::CommandList);

		static D3D12_RESOURCE_BARRIER barrier = { };
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.pResource = D3D12::ResourceArray[backBufferIdx];

		D3D12::CommandList->ResourceBarrier(1, &barrier);
		D3D12::CommandList->Close();

		D3D12::CommandQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&D3D12::CommandList);

		//HRESULT results = OriginalPresent(SwapChain, SyncInterval, Flags);

		UINT64 fenceValue = D3D12::LastFenceValue + 1;
		D3D12::CommandQueue->Signal(D3D12::Fence, fenceValue);
		D3D12::LastFenceValue = fenceValue;
		frameCtxt->FenceValue = fenceValue;
	}
	bool IsReady() {
		return Ready;
	}
	void Release()
	{
		D3D12::CommandQueue = nullptr;
		D3D12::SwapChain = nullptr;
		D3D12::Device = nullptr;

		if (D3D12::Fence) {
			D3D12::Fence->Release();
			D3D12::Fence = nullptr;
		}

		if (D3D12::SRVDescriptionHeap) {
			D3D12::SRVDescriptionHeap->Release();
			D3D12::SRVDescriptionHeap = nullptr;
		}

		if (D3D12::RTVDescriptionHeap) {
			D3D12::RTVDescriptionHeap->Release();
			D3D12::RTVDescriptionHeap = nullptr;
		}

		if (D3D12::CommandList) {
			D3D12::CommandList->Release();
			D3D12::CommandList = nullptr;
		}

		if (D3D12::FrameContextArray) {
			for (UINT i = 0; i < D3D12::NumberOfFrames; ++i) {
				if (D3D12::FrameContextArray[i].CommandAllocator) {
					D3D12::FrameContextArray[i].CommandAllocator->Release();
					D3D12::FrameContextArray[i].CommandAllocator = nullptr;
				}
			}

			delete[] D3D12::FrameContextArray;
			D3D12::FrameContextArray = NULL;
		}

		if (D3D12::ResourceArray) {
			for (UINT i = 0; i < D3D12::NumberOfBackBuffers; ++i) {
				if (D3D12::ResourceArray[i]) {
					D3D12::ResourceArray[i]->Release();
					D3D12::ResourceArray[i] = nullptr;
				}
			}

			delete[] D3D12::ResourceArray;
			D3D12::ResourceArray = NULL;
		}

		if (D3D12::RenderTargetDescriptorArray) {
			delete[] D3D12::RenderTargetDescriptorArray;
			D3D12::RenderTargetDescriptorArray = NULL;
		}

		if (D3D12::WaitableSwapChain) {
			D3D12::WaitableSwapChain = nullptr;
		}

		if (D3D12::FenceEvent) {
			CloseHandle(D3D12::FenceEvent);
			D3D12::FenceEvent = nullptr;
		}

		D3D12::NumberOfFrames = 0;
		D3D12::NumberOfBackBuffers = 0;

		D3D12::FrameIndex = 0;
	}
	void Clear() {
		if (D3D12::FrameContextArray) {
			FrameContext* frameCtxt = &D3D12::FrameContextArray[D3D12::FrameIndex % D3D12::NumberOfFrames];

			if (frameCtxt->FenceValue == 0)
				return;

			frameCtxt->FenceValue = 0;

			if (!(D3D12::Fence->GetCompletedValue() >= frameCtxt->FenceValue)) {
				D3D12::Fence->SetEventOnCompletion(frameCtxt->FenceValue, D3D12::FenceEvent);
				WaitForSingleObject(D3D12::FenceEvent, INFINITE);
			}

			Release();
		}
	}
}

