#pragma once
#include "..\Globals\framework.h"
#include "..\Globals\Globals.h"
extern void Draw();

namespace ImGui {
	void ComboSearchBox(char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, std::vector<int> ID, ImVec2 size = ImVec2(180, 0), ImVec2 Pos = ImVec2(10, 35));
	void ComboSearchBox(char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, ImVec2 size = ImVec2(229, 0));
	void TextCenter(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, const char* text, const ImVec2& align);
	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
	void TextCentered(const char* text);
	void Header(const char* Name);
	float CaculateAlpha(float n);
	void FadeMenu();
	void Logo();
}

namespace Menu {
	extern ImGuiWindowFlags ChildDisabledFlags;
	extern ImGuiWindowFlags ChildEnabledFlags;
	extern ImGuiColorEditFlags ColorFlags;
	extern ImGuiWindowFlags WindowFlags;
	extern unsigned char Rainbow[4];
	extern const char* Name;
	extern ImVec2 Size;

	void TabAnimations(float& tab_alpha, float& tab_add, int& active_tab, int Tab);
	void UpdateRainbowColor();
}