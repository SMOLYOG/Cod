#define IMGUI_DEFINE_MATH_OPERATORS
#pragma warning(disable : 4996)
#include "Menu Helper.h"
#include "..\Third Party\xor.h"

namespace Font {
	ImFont* lexend_general_bold;
	ImFont* icomoon_widget2;
	ImFont* icomoon_widget;
	ImFont* lexend_regular;
	ImFont* lexend_bold;
	ImFont* icomoon;

	ImFont* mainfont;
	ImFont* mainfont_smaller;
	ImFont* mainfont_bigger;
	ImFont* functionfont;
	ImFont* icons;

	ImFont* interbi;
	ImFont* interbinoshift;
	ImFont* extreme_fontnoshift;
	ImFont* extreme_font;
	ImFont* IconFont;
}

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text) {
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
		};
	void ComboSearchBox(char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, std::vector<int> ID, ImVec2 size, ImVec2 Pos)
	{
		ImGui::SetCursorPos(Pos);
		ImGui::PushItemWidth(size.x);
		std::string str;
		str = input;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		std::string label = xorstr_("##input") + hint;

		bool Pressed = ImGui::InputTextWithHint(label.c_str(), hint.c_str(), input, sizeof(input), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
		bool Activated = ImGui::IsItemActivated();
        bool Active = ImGui::IsItemActive();

		if (Activated)
		{
			ImGui::OpenPopup(xorstr_("##popup"));
		}
		{
			ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y));
			ImGui::SetNextWindowSize(ImVec2(size.x, 70));
			if (ImGui::BeginPopup(xorstr_("##popup"), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ChildWindow))
			{
				for (int Search = 0; Search < list.size(); Search++)
				{
					if (strstr(listLower[Search].c_str(), str.c_str()) == NULL)
						continue;
					if (ImGui::Selectable(list[Search].c_str()))
					{
						ImGui::ClearActiveID();
						strcpy(input, list[Search].c_str());
						*index = ID[Search];
					}
				}

				if (!Active && !ImGui::IsWindowFocused())
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		ImGui::PopItemWidth();
	}
	void ComboSearchBox(char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, ImVec2 size)
	{
		ImGuiStyle* Style = &ImGui::GetStyle();
		std::string str;
		str = input;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		std::string label = xorstr_("##input") + hint;


		bool Pressed = ImGui::InputTextEx(xorstr_(" "), hint.c_str(), input, IM_ARRAYSIZE(input), ImVec2(290, 35), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
		bool Activated = ImGui::IsItemActivated();
		bool Active = ImGui::IsItemActive();

		if (Activated)
		{
			ImGui::OpenPopup(std::string(xorstr_("##popup") + hint).c_str());
		}
		{
			ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y + 5));
			ImGui::SetNextWindowSize(ImVec2(size.x, 200));
			if (ImGui::BeginPopup(std::string(xorstr_("##popup") + hint).c_str(), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ChildWindow))
			{
				for (int Search = 0; Search < list.size(); Search++)
				{
					if (strstr(listLower[Search].c_str(), str.c_str()) == NULL)
						continue;

					if (ImGui::Selectable(list[Search].c_str()))
					{
						ImGui::ClearActiveID();
						strcpy(input, list[Search].c_str());
						*index = Search;
					}
				}

				if (!Active && !ImGui::IsWindowFocused())
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
	}
	void TextCenter(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, const char* text, const ImVec2& align)
    {
        PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(col));
        RenderTextClipped(p_min, p_max, text, NULL, NULL, align, NULL);
        PopStyleColor();
    }
	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values) {
		if (values.empty()) { return false; }
		return ImGui::Comboa(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
	}
	float CaculateAlpha(float n)
	{
		n = (n > 0.0f) * n + !(n > 0.0f) * 0.0f;
		return (n < 1.0f) * n + !(n < 1.0f) * 1.0f;
	}
	void Header(const char* Name)
	{
		//PushFont(Font::HeaderFont);
		TextCentered(Name);
		Separator();
		//PopFont();
	}
	void TextCentered(const char* text) {
		float window_width = GetWindowWidth();
		float text_width = CalcTextSize(text).x;
		float center_x = window_width / 2.0f - text_width / 2.0f;
		SetCursorPosX(center_x);

		Text(text);
	}
	void FadeMenu()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGuiIO& io = ImGui::GetIO();
		static float Alpha;
		
		Alpha = ImLerp(Alpha, Globals::Open ? 1.0f : 0.0f, io.DeltaTime * 6.0f);

		style.Alpha = Alpha;

	}
}

namespace Menu
{
	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollWithMouse;
    ImGuiColorEditFlags ColorFlags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;
	ImGuiWindowFlags ChildDisabledFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMouseInputs;
    ImGuiWindowFlags ChildEnabledFlags = ImGuiWindowFlags_NoScrollbar;
	const char* Name = "";
	unsigned char Rainbow[4] = { 255, 0, 0, 0 };
	ImVec2 Size = ImVec2(795, 450);

	void TabAnimations(float& tab_alpha, float& AddTab, int& ActiveTab, int Tab) {
		tab_alpha = ImLerp(tab_alpha, (Tab == ActiveTab) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);

		if (tab_alpha < 0.01f && AddTab < 0.01f) ActiveTab = Tab; 
	}

	void UpdateRainbowColor()
	{
		int stage = Rainbow[3];
		switch (stage) {
		case 0:        Rainbow[2] += 3;        if (Rainbow[2] == 255)           Rainbow[3] = 1;        break;
		case 1:        Rainbow[0] -= 3;        if (Rainbow[0] == 0)             Rainbow[3] = 2;        break;
		case 2:        Rainbow[1] += 3;        if (Rainbow[1] == 255)           Rainbow[3] = 3;        break;
		case 3:        Rainbow[2] -= 3;        if (Rainbow[2] == 0)             Rainbow[3] = 4;        break;
		case 4:        Rainbow[0] += 3;        if (Rainbow[0] == 255)           Rainbow[3] = 5;        break;
		case 5:        Rainbow[1] -= 3;        if (Rainbow[1] == 0)             Rainbow[3] = 0;        break;
		}
	}
}