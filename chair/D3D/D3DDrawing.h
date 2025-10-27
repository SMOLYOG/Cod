#pragma once
#include "..\Globals\FrameWork.h"
//preferably move
#include "../GameSDK/GameSDK.h"

extern void D3D_Draw_String1(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i);

extern void D3D_Draw_String(ImVec2 position, const char* string, ImColor colorText, ImColor colorBG, ImColor colorUnderLine, int i);

extern void D3D_Draw_Line(ImVec2 Point1, ImVec2 Point2, ImColor Color, float Thickness);

extern void D3D_Draw_PlayerNames(int i, ImColor color);

extern void D3D_Draw_Distance(int i, ImColor color);

extern void D3D_Draw_Health(int i);

extern void D3D_Draw_Platform(int i, ImColor Color);

extern void D3D_Draw_FOV_Circle(float AimbotFOV, ImColor Color);

extern void D3D_Draw_Crosshair(ImColor Color);

extern void D3D_Draw_SnapLines(int i, ImColor Color);

extern void D3D_Draw_Bones(int i, ImColor Color);

extern void D3D_Draw_Cornered_Box(const ImVec2& rect, const ImVec2& size, ImColor color);

extern void D3D_Draw_Border(int i, ImVec2 position, ImVec2 dimentions, bool border, ImColor color);

extern void D3D_Draw_Tracers();

extern void D3D_Draw_Compass(int i, float Size, ImColor Color);