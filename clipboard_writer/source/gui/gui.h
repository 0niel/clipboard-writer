#pragma once

#include <d3d9.h>
#include <tchar.h>
#include <dinput.h>
#include "Dwmapi.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx9.h"
#include "../../imgui/imgui_internal.h"
#include "../../imgui/imgui_impl_win32.h"
#define IMGUI_DEFINE_MATH_OPERATORS

class cGui
{
private:
	int x1, y1;
public:
	void ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice);
	void DestroyImgui();
	void GuiLoop();
	void setPos(int x, int y) { x1 = x, y1 = y; }
	void SetStyle();
};
extern cGui gui;

namespace ImGui {
	bool Hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0, 0));
}