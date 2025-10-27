#pragma once

namespace Process
{
	BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam);
	HWND get_process_window();
	extern HWND hwnd;
}

namespace Main {
	void MainLoop(ImFont* font);
	void Init(ImFont* font);
	void Begin();
	void End();

	inline std::recursive_mutex Mutex = {};
}
