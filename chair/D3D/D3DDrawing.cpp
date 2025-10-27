#pragma once 
#include "D3DDrawing.h"

ImColor getDistanceBasedColorVec4(ImVec4 baseColor, float distance, float minDistance, float maxDistance) {
	// Clamp the distance to the specified range using conditional checks
	if (distance < minDistance) {
		distance = minDistance;
	}
	else if (distance > maxDistance) {
		distance = maxDistance;
	}

	// Use the base color's alpha channel as the maximum alpha
	float baseAlpha = baseColor.w;

	// Calculate alpha based on distance and base alpha
	float alpha = baseAlpha * (1.0f - (distance - minDistance) / (maxDistance - minDistance));

	// Ensure alpha is within 0.0-1.0 using conditional checks
	if (alpha < 0.0f) {
		alpha = 0.0f;
	}
	else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	// Return the color with the adjusted alpha
	return ImColor(baseColor.x, baseColor.y, baseColor.z, alpha);
}

ImColor getDistanceBasedColorImColor(ImColor baseColor, float distance, float minDistance, float maxDistance) {
	// Extract the RGBA components from the ImColor
	float baseRed = baseColor.Value.x;
	float baseGreen = baseColor.Value.y;
	float baseBlue = baseColor.Value.z;
	float baseAlpha = baseColor.Value.w;

	// Clamp the distance to the specified range using conditional checks
	if (distance < minDistance) {
		distance = minDistance;
	}
	else if (distance > maxDistance) {
		distance = maxDistance;
	}

	// Calculate alpha based on distance and base alpha
	float alpha = baseAlpha * (1.0f - (distance - minDistance) / (maxDistance - minDistance));

	// Ensure alpha is within 0.0-1.0 using conditional checks
	if (alpha < 0.0f) {
		alpha = 0.0f;
	}
	else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	// Return the color with the adjusted alpha
	return ImColor(baseRed, baseGreen, baseBlue, alpha);
}

void D3D_Draw_String1(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i)
{

	ImVec2 strSize = ImGui::CalcTextSize(string);
	ImVec2 calc = { position.x + strSize.x + 4.f, position.y + strSize.y };

	ImGui::SetWindowFontScale(0.5f);

	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(position.x, position.y - 2.f), calc, getDistanceBasedColorImColor(colorBG, loot_t[i].distance, 20.f, Visuals::Main::Drawing::all)
	);
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(position.x, position.y + strSize.y / 1.1f), ImVec2(calc.x, calc.y), getDistanceBasedColorImColor(colorUnderLine, loot_t[i].distance, 20.f, Visuals::Main::Drawing::all));
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x + 2.5f, position.y - 2.2f), getDistanceBasedColorImColor(colorText, loot_t[i].distance, 20.f, Visuals::Main::Drawing::all), string);
}

void D3D_Draw_String(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i)
{

	ImVec2 strSize = ImGui::CalcTextSize(string);
	ImVec2 calc = { position.x + strSize.x + 4.f, position.y + strSize.y };

	ImGui::SetWindowFontScale(0.5f);			
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x + 2.5f, position.y - 2.2f), getDistanceBasedColorImColor(colorText, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), string);
}

void D3D_Draw_Line(ImVec2 Point1, ImVec2 Point2, ImColor Color, float Thickness) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Point1.x, Point1.y), ImVec2(Point2.x, Point2.y), Color, Thickness);
}

void D3D_Draw_PlayerNames(int i, ImColor color)
{
	ImVec2 vStringSize, vPosition, center;

	if (Visuals::Main::DrawPlayerTeamID && Visuals::Main::DrawPlayerName) {
		auto formatted_str = std::format("{} [ {} ]", Entity_t[i].Name.c_str(), Entity_t[i].team);
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		center = ImVec2(Entity_t[i].tag_origin_2D.x, Entity_t[i].tag_origin_2D.y - Entity_t[i].Dimentions.y);
		vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
		D3D_Draw_String(vPosition, formatted_str.c_str(), color, ImColor(50, 50, 50, 155), color, i);
	}
	if (!Visuals::Main::DrawPlayerTeamID && Visuals::Main::DrawPlayerName) {
		auto formatted_str = std::format("{}", Entity_t[i].Name.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		center = ImVec2(Entity_t[i].tag_origin_2D.x, Entity_t[i].tag_origin_2D.y - Entity_t[i].Dimentions.y);
		vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
		D3D_Draw_String(vPosition, formatted_str.c_str(), color, ImColor(50, 50, 50, 155), color, i);
	}
	if (Visuals::Main::DrawPlayerTeamID && !Visuals::Main::DrawPlayerName) {
		auto formatted_str = std::format("Team ID : {}", Entity_t[i].team);
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		center = ImVec2(Entity_t[i].tag_origin_2D.x, Entity_t[i].tag_origin_2D.y - Entity_t[i].Dimentions.y);
		vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
		D3D_Draw_String(vPosition, formatted_str.c_str(), color, ImColor(50, 50, 50, 155), color, i);
	}
	if (!Visuals::Main::DrawPlayerTeamID && !Visuals::Main::DrawPlayerName)
		return;
}

void D3D_Draw_Distance(int i, ImColor color)
{
	ImVec2 vStringSize, vPosition, center;
	bool skipDistance = false;
	std::string distance;
	int editedPos = 6;

	if (Visuals::Main::DrawPlayerWeapon && Visuals::Main::DrawPlayerDistance) {
		auto formatted_str = std::format("{} [{}.m]", Entity_t[i].Weapon.c_str(), Math::RoundFloat(Entity_t[i].distance));
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		center = ImVec2(Entity_t[i].tag_origin_2D.x, Entity_t[i].tag_origin_2D.y + 15.f);
		vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
		D3D_Draw_String(vPosition, formatted_str.c_str(), color, ImColor(50, 50, 50, 155), color, i);
	}
	else if (!Visuals::Main::DrawPlayerWeapon && Visuals::Main::DrawPlayerDistance) {
		auto formatted_str = std::format("[{}.m]", Math::RoundFloat(Entity_t[i].distance));
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		center = ImVec2(Entity_t[i].tag_origin_2D.x, Entity_t[i].tag_origin_2D.y + 15.f);
		vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
		D3D_Draw_String(vPosition, formatted_str.c_str(), color, ImColor(50, 50, 50, 155), color, i);
	}
	else if (Visuals::Main::DrawPlayerWeapon && !Visuals::Main::DrawPlayerDistance) {
		auto formatted_str = std::format("{}", Entity_t[i].Weapon.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		center = ImVec2(Entity_t[i].tag_origin_2D.x, Entity_t[i].tag_origin_2D.y + 15.f);
		vPosition = ImVec2(center.x - (vStringSize.x / 2.0f), (center.y - vStringSize.y) - 2);
		D3D_Draw_String(vPosition, formatted_str.c_str(), color, ImColor(50, 50, 50, 155), color, i);
	}
	else if (!Visuals::Main::DrawPlayerWeapon && !Visuals::Main::DrawPlayerDistance)
		return;
}

void D3D_Draw_Health(int i) {

	float Resize = fabsf(Entity_t[i].tag_origin_2D.y - (Entity_t[i].tag_origin_2D.y + Entity_t[i].Dimentions.y)) - (((fabsf(Entity_t[i].tag_origin_2D.y - (Entity_t[i].tag_origin_2D.y + Entity_t[i].Dimentions.y)) * Entity_t[i].health) / 127));
	ImVec2 Size;

	int health = Entity_t[i].health;
	int maxHealth = 127;

	float height, x, y, resize;

	height = Entity_t[i].Dimentions.y;

	x = Entity_t[i].tag_origin_2D.x + (Entity_t[i].Dimentions.x / 2);
	y = Entity_t[i].tag_origin_2D.y - height;
	resize = fabsf(Entity_t[i].tag_origin_2D.y - (Entity_t[i].tag_origin_2D.y + Entity_t[i].Dimentions.y)) - (((fabsf(Entity_t[i].tag_origin_2D.y - (Entity_t[i].tag_origin_2D.y + Entity_t[i].Dimentions.y)) * health) / maxHealth));

	float w = 5;
	ImColor fill = getDistanceBasedColorImColor(ImColor(static_cast<int> ((130.0f - health * 1.3f)), static_cast<int> ((health * 2.55f)), 10, 255), Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all);
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 3, y - 1), ImVec2(x + w, y + height + 1), getDistanceBasedColorImColor(ImColor(1, 1, 1), Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), 0, 0);
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 3, y + resize), ImVec2(x + w, y + height), fill, 0, 0);
}
void D3D_Draw_Platform(int i, ImColor Color) {
	ImVec2 vStringSize, vPosition, center;
	bool skipDistance = false;
	std::string distance;
	int editedPos = 15;

	if (cfg::Esp::Platform && !cfg::Esp::Device && !cfg::Esp::Talking) {
		auto formatted_str = std::format("{}", Lobby[i].platform_String.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		vPosition = ImVec2(Entity_t[i].tag_origin_2D.x - (vStringSize.x / 2.0f), Entity_t[i].tag_origin_2D.y + editedPos);
		ImGui::SetWindowFontScale(0.5f);
		ImGui::PushFont(Font::IconFont);
		ImGui::GetBackgroundDrawList()->AddText(vPosition, ImColor(Color), formatted_str.c_str());
		ImGui::PopFont();
	}
	else if (cfg::Esp::Device && !cfg::Esp::Platform && !cfg::Esp::Talking) {
		auto formatted_str = std::format("{}", Lobby[i].GPad_String.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		vPosition = ImVec2(Entity_t[i].tag_origin_2D.x - (vStringSize.x / 2.0f), Entity_t[i].tag_origin_2D.y + editedPos);
		ImGui::SetWindowFontScale(0.5f);
		ImGui::PushFont(Font::IconFont);
		ImGui::GetBackgroundDrawList()->AddText(vPosition, ImColor(Color), formatted_str.c_str());
		ImGui::PopFont();
	}
	else if (cfg::Esp::Device && cfg::Esp::Platform && !cfg::Esp::Talking) {
		auto formatted_str = std::format("{} {}", Lobby[i].GPad_String.c_str(), Lobby[i].platform_String.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		vPosition = ImVec2(Entity_t[i].tag_origin_2D.x - (vStringSize.x / 2.0f), Entity_t[i].tag_origin_2D.y + editedPos);
		ImGui::SetWindowFontScale(0.5f);
		ImGui::PushFont(Font::IconFont);
		ImGui::GetBackgroundDrawList()->AddText(vPosition, ImColor(Color), formatted_str.c_str());
		ImGui::PopFont();
	}
	else if (cfg::Esp::Device && !cfg::Esp::Platform && cfg::Esp::Talking) {
		auto formatted_str = std::format("{} {}", Lobby[i].GPad_String.c_str(), Lobby[i].Talking_String.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		vPosition = ImVec2(Entity_t[i].tag_origin_2D.x - (vStringSize.x / 2.0f), Entity_t[i].tag_origin_2D.y + editedPos);
		ImGui::SetWindowFontScale(0.5f);
		ImGui::PushFont(Font::IconFont);
		ImGui::GetBackgroundDrawList()->AddText(vPosition, ImColor(Color), formatted_str.c_str());
		ImGui::PopFont();
	}
	else if (!cfg::Esp::Device && cfg::Esp::Platform && cfg::Esp::Talking) {
		auto formatted_str = std::format("{} {}", Lobby[i].platform_String.c_str(), Lobby[i].Talking_String.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		vPosition = ImVec2(Entity_t[i].tag_origin_2D.x - (vStringSize.x / 2.0f), Entity_t[i].tag_origin_2D.y + editedPos);
		ImGui::SetWindowFontScale(0.5f);
		ImGui::PushFont(Font::IconFont);
		ImGui::GetBackgroundDrawList()->AddText(vPosition, ImColor(Color), formatted_str.c_str());
		ImGui::PopFont();
	}
	else if (cfg::Esp::Device && cfg::Esp::Platform && cfg::Esp::Talking) {
		auto formatted_str = std::format("{} {} {}", Lobby[i].GPad_String.c_str(), Lobby[i].platform_String.c_str(), Lobby[i].Talking_String.c_str());
		vStringSize = ImVec2(ImGui::CalcTextSize(formatted_str.c_str()).x + 4, ImGui::CalcTextSize(formatted_str.c_str()).y);
		vPosition = ImVec2(Entity_t[i].tag_origin_2D.x - (vStringSize.x / 2.0f), Entity_t[i].tag_origin_2D.y + editedPos);
		ImGui::SetWindowFontScale(0.5f);
		ImGui::PushFont(Font::IconFont);
		ImGui::GetBackgroundDrawList()->AddText(vPosition, ImColor(Color), formatted_str.c_str());
		ImGui::PopFont();
	}

}

void D3D_Draw_FOV_Circle(float AimbotFOV, ImColor Color) {
	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), tan(Math::Deg2Rad(AimbotFOV) / 2.f) / tan(Math::Deg2Rad(130) / 2.f) * ImGui::GetIO().DisplaySize.x, Color, 360);
}

void RenderSpinningCrosshair(float rotationSpeed, float lineLength, float lineGap, float dotRadius, float lineThickness, ImColor Color) {
	// Get the current window size
	ImVec2 windowSize = ImGui::GetIO().DisplaySize;
	ImVec2 center = ImVec2(windowSize.x / 2, windowSize.y / 2); // Calculate the center of the screen

	// Rotation angle based on time and speed
	float rotationAngle = ImGui::GetTime() * rotationSpeed;

	// Calculate rotation matrix components
	float cosTheta = cosf(rotationAngle);
	float sinTheta = sinf(rotationAngle);

	// Function to rotate a point around the center
	auto RotatePoint = [&](float x, float y) {
		return ImVec2(center.x + x * cosTheta - y * sinTheta, center.y + x * sinTheta + y * cosTheta);
		};

	if (Visuals::Main::DrawCrosshair) {

		// Calculate the start and end points of the crosshair lines, ensuring a gap
		// Top line
		ImVec2 startTop = RotatePoint(0.0f, -(lineGap + dotRadius));  // Start with gap + dot size
		ImVec2 endTop = RotatePoint(0.0f, -(lineGap + dotRadius + lineLength));  // End after the line length
		D3D_Draw_Line(startTop, endTop, Color, lineThickness);

		// Bottom line
		ImVec2 startBottom = RotatePoint(0.0f, (lineGap + dotRadius));  // Start with gap + dot size
		ImVec2 endBottom = RotatePoint(0.0f, (lineGap + dotRadius + lineLength));  // End after the line length
		D3D_Draw_Line(startBottom, endBottom, Color, lineThickness);

		// Left line
		ImVec2 startLeft = RotatePoint(-(lineGap + dotRadius), 0.0f);  // Start with gap + dot size
		ImVec2 endLeft = RotatePoint(-(lineGap + dotRadius + lineLength), 0.0f);  // End after the line length
		D3D_Draw_Line(startLeft, endLeft, Color, lineThickness);

		// Right line
		ImVec2 startRight = RotatePoint((lineGap + dotRadius), 0.0f);  // Start with gap + dot size
		ImVec2 endRight = RotatePoint((lineGap + dotRadius + lineLength), 0.0f);  // End after the line length
		D3D_Draw_Line(startRight, endRight, Color, lineThickness);
	}
	// Draw the dot in the middle (small circle)
	if (cfg::Crosshair::enabledot)
		ImGui::GetBackgroundDrawList()->AddCircleFilled(center, dotRadius, Color);  // Dot color (white)

}

void RenderStaticCrosshair(float lineLength, float lineGap, float dotRadius, float lineThickness,ImColor Color) {
	// Get the current window size
	ImVec2 windowSize = ImGui::GetIO().DisplaySize;
	ImVec2 center = ImVec2(windowSize.x / 2, windowSize.y / 2); // Calculate the center of the screen

	if (Visuals::Main::DrawCrosshair) { 
		// Draw the top line (static, not rotating)
		ImVec2 startTop = ImVec2(center.x - 0.0f, center.y - (lineGap + dotRadius));  // Start with gap + dot size
		ImVec2 endTop = ImVec2(center.x - 0.0f, center.y - (lineGap + dotRadius + lineLength));  // End after the line length
		D3D_Draw_Line(startTop, endTop, Color, lineThickness);

		// Draw the bottom line (static, not rotating)
		ImVec2 startBottom = ImVec2(center.x - 0.0f, center.y + (lineGap + dotRadius));  // Start with gap + dot size
		ImVec2 endBottom = ImVec2(center.x - 0.0f, center.y + (lineGap + dotRadius + lineLength));  // End after the line length
		D3D_Draw_Line(startBottom, endBottom, Color, lineThickness);

		// Draw the left line (static, not rotating)
		ImVec2 startLeft = ImVec2(center.x - (lineGap + dotRadius), center.y - 0.0f);  // Start with gap + dot size
		ImVec2 endLeft = ImVec2(center.x - (lineGap + dotRadius + lineLength), center.y - 0.0f);  // End after the line length
		D3D_Draw_Line(startLeft, endLeft, Color, lineThickness);

		// Draw the right line (static, not rotating)
		ImVec2 startRight = ImVec2(center.x + (lineGap + dotRadius), center.y - 0.0f);  // Start with gap + dot size
		ImVec2 endRight = ImVec2(center.x + (lineGap + dotRadius + lineLength), center.y - 0.0f);  // End after the line length
		D3D_Draw_Line(startRight, endRight, Color, lineThickness);
	}
	// Draw the dot in the middle (static)
	if (cfg::Crosshair::enabledot)
		ImGui::GetBackgroundDrawList()->AddCircleFilled(center, dotRadius, Color);  // Dot color (white)
}

void D3D_Draw_Crosshair(ImColor Color) {

	if (cfg::Crosshair::spin)
		RenderSpinningCrosshair(cfg::Crosshair::speed, cfg::Crosshair::linelength, cfg::Crosshair::linegap, Visuals::Main::crosshair_thickness, Visuals::Main::crosshair_thickness, Color);
	else
		RenderStaticCrosshair(cfg::Crosshair::linelength, cfg::Crosshair::linegap, Visuals::Main::crosshair_thickness, Visuals::Main::crosshair_thickness, Color);
}

void D3D_Draw_SnapLines(int i, ImColor Color) {
	Vector2 Pos;

	switch (cfg::Esp::Drawing_Settings::Snapline_Pos)
	{
	case 0:
		Pos = Vector2(Screen.x / 2, 0);
		break;
	case 1:
		Pos = Vector2(Screen.x / 2, Screen.y);
		break;
	case 2:
		Pos = Vector2(Screen.x / 2, Screen.y / 2);
		break;
	case 3:
		Pos = Vector2(Screen.x, Screen.y / 2);
		break;
	case 4:
		Pos = Vector2(0, Screen.y / 2);
		break;
	case 5:
		Pos = Vector2(Screen.x, 0);
		break;
	case 6:
		Pos = Vector2(0, 0);
		break;
	case 7:
		Pos = Vector2(Screen.x, Screen.y);
		break;
	case 8:
		Pos = Vector2(0, Screen.y);
		break;
	default:
		Pos = Vector2(Screen.x / 2, Screen.y / 2);
		break;
	}

	D3D_Draw_Line(ImVec2(Pos.x,Pos.y), ImVec2(Entity_t[i].tag_origin_2D.x, Entity_t[i].tag_origin_2D.y), getDistanceBasedColorImColor(Color, Entity_t[i].distance,20.f, Visuals::Main::Drawing::all), 1.0f);
}

void D3D_Draw_Bones(int i, ImColor Color) {
	for (int j = 0; j < 4; j++) {
		D3D_Draw_Line(ImVec2(Entity_t[i].LeftArm[j].x, Entity_t[i].LeftArm[j].y), ImVec2(Entity_t[i].LeftArm[j + 1].x, Entity_t[i].LeftArm[j + 1].y), getDistanceBasedColorImColor(Color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), Visuals::Main::Drawing::Bonethicness);

		D3D_Draw_Line(ImVec2(Entity_t[i].RightArm[j].x, Entity_t[i].RightArm[j].y), ImVec2(Entity_t[i].RightArm[j + 1].x, Entity_t[i].RightArm[j + 1].y), getDistanceBasedColorImColor(Color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), Visuals::Main::Drawing::Bonethicness);

		D3D_Draw_Line(ImVec2(Entity_t[i].LeftLeg[j].x, Entity_t[i].LeftLeg[j].y), ImVec2(Entity_t[i].LeftLeg[j + 1].x, Entity_t[i].LeftLeg[j + 1].y), getDistanceBasedColorImColor(Color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), Visuals::Main::Drawing::Bonethicness);

		D3D_Draw_Line(ImVec2(Entity_t[i].RightLeg[j].x, Entity_t[i].RightLeg[j].y), ImVec2(Entity_t[i].RightLeg[j + 1].x, Entity_t[i].RightLeg[j + 1].y), getDistanceBasedColorImColor(Color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), Visuals::Main::Drawing::Bonethicness);

	}
	for (int j = 1; j < 5; j++)
		D3D_Draw_Line(ImVec2(Entity_t[i].Body[j].x, Entity_t[i].Body[j].y), ImVec2(Entity_t[i].Body[j + 1].x, Entity_t[i].Body[j + 1].y), getDistanceBasedColorImColor(Color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), Visuals::Main::Drawing::Bonethicness);
}

void D3D_Draw_Cornered_Box(const ImVec2& rect, const ImVec2& size, ImColor color)
{
	float cornerSize = size.x / 4;
	const float lineW = (size.x / 5);
	const float lineH = (size.y / 6);
	const float lineT = 1;

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x - lineT, rect.y - lineT), ImVec2(rect.x + lineW, rect.y - lineT), color, 1.0f); //top left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x - lineT, rect.y - lineT), ImVec2(rect.x - lineT, rect.y + lineH), color, 1.0f);

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x - lineT, rect.y + size.y - lineH), ImVec2(rect.x - lineT, rect.y + size.y + lineT), color, 1.0f); //bot left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x - lineT, rect.y + size.y + lineT), ImVec2(rect.x + lineW, rect.y + size.y + lineT), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x - lineT, rect.y + size.y - lineH), ImVec2(rect.x - lineT, rect.y + size.y + lineT), color, 1.0f); //bot left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x + size.x - lineW, rect.y - lineT), ImVec2(rect.x + size.x + lineT, rect.y - lineT), color, 1.0f); // top right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x + size.x + lineT, rect.y - lineT), ImVec2(rect.x + size.x + lineT, rect.y + lineH), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x + size.x + lineT, rect.y + size.y - lineH), ImVec2(rect.x + size.x + lineT, rect.y + size.y + lineT), color, 1.0f); // bot right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rect.x + size.x - lineW, rect.y + size.y + lineT), ImVec2(rect.x + size.x + lineT, rect.y + size.y + lineT), color, 1.0f);
}

void D3D_Draw_Border(int i, ImVec2 position, ImVec2 dimentions, bool border, ImColor color)
{
	ImVec2 calc = { position.x + dimentions.x, position.y + dimentions.y };

	if (cfg::Esp::Drawing_Settings::box_Type == 0) {
		if (!border)
		{
			ImGui::GetBackgroundDrawList()->AddRect(position, calc, getDistanceBasedColorImColor(color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all));
		}
		else {

			ImGui::GetBackgroundDrawList()->AddRectFilled(position, calc, getDistanceBasedColorImColor(ImColor(50, 50, 50, 100), Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all) );
			ImGui::GetBackgroundDrawList()->AddRect(position, calc, getDistanceBasedColorImColor(color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all));
		}
	}
	else if (cfg::Esp::Drawing_Settings::box_Type == 1) {

		D3D_Draw_Cornered_Box(position, dimentions, getDistanceBasedColorImColor(color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all));
	}
}

void D3D_Draw_Tracers() {
	if (Tracer_V.empty() || !Visuals::Miscellaneous::Tracers::Enable || IncorrectOffset::Tracers) return;
	if (!Offset::CGArray || !Globals::InGame2) return;

	ImVec4 col = ImVec4(Visuals::Miscellaneous::Tracers::Tracer_Col[0], Visuals::Miscellaneous::Tracers::Tracer_Col[1], Visuals::Miscellaneous::Tracers::Tracer_Col[2], Visuals::Miscellaneous::Tracers::Tracer_Col[3]);

	for (auto& Tracer : Tracer_V)
	{
		if (Tracer.W2SSuccess)
		{
			D3D_Draw_Line(ImVec2(Tracer.StartPos2D.x, Tracer.StartPos2D.y), ImVec2(Tracer.HitPos2D.x, Tracer.HitPos2D.y), Color::Rainbow::FOV ? ImColor(Color::Rainbow::Rainbow) : ImColor(col), Visuals::Miscellaneous::Tracers::TracerThickness);
		}
	}
}

void D3D_Draw_Compass(int i, float Size, ImColor Color) {
	ImVec2 vScreen, ScreenCenter;
	Vector3 AngleArc;

	ScreenCenter.x = Screen.x / 2.f;
	ScreenCenter.y = Screen.y / 2.f;

	WorldToCompass(MyClient.Position, MyClient.View_Angles, Entity_t[i].tag_origin, ScreenCenter, Screen.y / 2.f, vScreen);
	Math::VectorAngles(Vector3(ScreenCenter.x - vScreen.x, ScreenCenter.y - vScreen.y, 0), AngleArc);
	AngleArc = Vector3(AngleArc.x * -1.f, AngleArc.y * -1.f, AngleArc.z * -1.f);

	float Yaw = DegreesToRadians(AngleArc.y);
	float NewPointX = ScreenCenter.x + Size * cosf(Yaw);
	float NewPointY = ScreenCenter.y + Size * sinf(Yaw);

	std::array<ImVec2, 3>Points{ ImVec2(NewPointX - Visuals::Miscellaneous::Compass::TriangleSize, NewPointY - Visuals::Miscellaneous::Compass::TriangleSize), ImVec2(NewPointX + (Visuals::Miscellaneous::Compass::TriangleSize + 2), NewPointY), ImVec2(NewPointX - Visuals::Miscellaneous::Compass::TriangleSize, NewPointY + Visuals::Miscellaneous::Compass::TriangleSize) };

	Math::RotateTriangle(Points, AngleArc.y);

	if (Visuals::Miscellaneous::Compass::Fill)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(Points[0], Points[1], Points[2], getDistanceBasedColorImColor(Color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all));
	else
		ImGui::GetBackgroundDrawList()->AddTriangle(Points[0], Points[1], Points[2], getDistanceBasedColorImColor(Color, Entity_t[i].distance, 20.f, Visuals::Main::Drawing::all), 2.f);

}


