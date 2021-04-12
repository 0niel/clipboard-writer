#include "gui.h"
#include "../cvars/cvars.h"
#include "../defines.h"
#include <vector>
#include <sstream>

cGui gui;

struct fonts
{
	ImFont* title;
}font;

void cGui::ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice)
{

	ImGui::CreateContext();

    ImFontConfig font_config;
    font_config.OversampleH = 2; //or 2 is the same
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x044F, // Cyrillic
        0,
    };
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14.0f, &font_config, ranges);

	ImGui_ImplWin32_Init(h);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	auto& style = ImGui::GetStyle();
    SetStyle();
	style.WindowRounding = 0.0f;

}

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void cGui::SetStyle() {
    // cherry colors, 3 intensities
#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
// backgrounds (@todo: complete with BG_MED, BG_LOW)
#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
// text
#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

    auto& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = TEXT(0.78f);
    style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
    style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
    style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
    style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
    style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
    style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
    style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
    style.Colors[ImGuiCol_Header] = MED(0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
    style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);

    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
    style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
    style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
    // [...]
    style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

    style.WindowRounding = 0.0f;
    style.FrameRounding = 3.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;
    style.GrabMinSize = 20.0f;
    style.GrabRounding = 2.0f;

    style.WindowTitleAlign.x = 0.50f;

    style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
}

void cGui::DestroyImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}


const char* const KeyNames[] = {
   "Unknown",
   "VK_LBUTTON",
   "VK_RBUTTON",
   "VK_CANCEL",
   "VK_MBUTTON",
   "VK_XBUTTON1",
   "VK_XBUTTON2",
   "Unknown",
   "VK_BACK",
   "VK_TAB",
   "Unknown",
   "Unknown",
   "VK_CLEAR",
   "VK_RETURN",
   "Unknown",
   "Unknown",
   "VK_SHIFT",
   "VK_CONTROL",
   "VK_MENU",
   "VK_PAUSE",
   "VK_CAPITAL",
   "VK_KANA",
   "Unknown",
   "VK_JUNJA",
   "VK_FINAL",
   "VK_KANJI",
   "Unknown",
   "VK_ESCAPE",
   "VK_CONVERT",
   "VK_NONCONVERT",
   "VK_ACCEPT",
   "VK_MODECHANGE",
   "VK_SPACE",
   "VK_PRIOR",
   "VK_NEXT",
   "VK_END",
   "VK_HOME",
   "VK_LEFT",
   "VK_UP",
   "VK_RIGHT",
   "VK_DOWN",
   "VK_SELECT",
   "VK_PRINT",
   "VK_EXECUTE",
   "VK_SNAPSHOT",
   "VK_INSERT",
   "VK_DELETE",
   "VK_HELP",
   "0",
   "1",
   "2",
   "3",
   "4",
   "5",
   "6",
   "7",
   "8",
   "9",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "A",
   "B",
   "C",
   "D",
   "E",
   "F",
   "G",
   "H",
   "I",
   "J",
   "K",
   "L",
   "M",
   "N",
   "O",
   "P",
   "Q",
   "R",
   "S",
   "T",
   "U",
   "V",
   "W",
   "X",
   "Y",
   "Z",
   "VK_LWIN",
   "VK_RWIN",
   "VK_APPS",
   "Unknown",
   "VK_SLEEP",
   "VK_NUMPAD0",
   "VK_NUMPAD1",
   "VK_NUMPAD2",
   "VK_NUMPAD3",
   "VK_NUMPAD4",
   "VK_NUMPAD5",
   "VK_NUMPAD6",
   "VK_NUMPAD7",
   "VK_NUMPAD8",
   "VK_NUMPAD9",
   "VK_MULTIPLY",
   "VK_ADD",
   "VK_SEPARATOR",
   "VK_SUBTRACT",
   "VK_DECIMAL",
   "VK_DIVIDE",
   "VK_F1",
   "VK_F2",
   "VK_F3",
   "VK_F4",
   "VK_F5",
   "VK_F6",
   "VK_F7",
   "VK_F8",
   "VK_F9",
   "VK_F10",
   "VK_F11",
   "VK_F12",
   "VK_F13",
   "VK_F14",
   "VK_F15",
   "VK_F16",
   "VK_F17",
   "VK_F18",
   "VK_F19",
   "VK_F20",
   "VK_F21",
   "VK_F22",
   "VK_F23",
   "VK_F24",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "VK_NUMLOCK",
   "VK_SCROLL",
   "VK_OEM_NEC_EQUAL",
   "VK_OEM_FJ_MASSHOU",
   "VK_OEM_FJ_TOUROKU",
   "VK_OEM_FJ_LOYA",
   "VK_OEM_FJ_ROYA",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "Unknown",
   "VK_LSHIFT",
   "VK_RSHIFT",
   "VK_LCONTROL",
   "VK_RCONTROL",
   "VK_LMENU",
   "VK_RMENU"
};

void cGui::GuiLoop()
{

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImVec2 vecPrevirousPos;
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Always, ImVec2(0.f, 0.f));
	ImGuiWindowFlags WndFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize;

	ImGuiWindowFlags WndFlags1 = ImGuiWindowFlags_NoSavedSettings  | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    
	ImGuiID id = ImGui::Begin("Mirea Ninja", nullptr, ImVec2(WindowSizeX+16, WindowSizeY+20), 1.0f, WndFlags1);
    {
        ImGui::TextWrapped(u8"Данная программа имитирует нажатия клавиш для ввода содержимого буфера обмена в различные поля.");
        ImGui::SliderInt(u8"Задержка (ms)", &g_Cvars.delay, 0, 500);
        ImGui::Checkbox(u8"Использовать рандомную задержку?", &g_Cvars.userRandomDelay);
        ImGui::SameLine(); HelpMarker(u8"Рандомная задежрка будет прибавляться к обычной задержке.\nНапример, если обычная задержка у вас стоит на 100мс, то у \nвас задержка будет 100 + random.");
        if (g_Cvars.userRandomDelay) {
            ImGui::SliderInt(u8"Интервал (ms)", &g_Cvars.delayRandom, 0, 500);
        }
        ImGui::Checkbox(u8"Использовать умные задержки?", &g_Cvars.useSmartDelay);
        ImGui::SameLine(); HelpMarker(u8"Интервалы задержек будут имитировать человеческий ввод.");
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::Hotkey(u8"Кнопка, чтобы начать печатать", &g_Cvars.keyStartWrite, ImVec2{ 310, 25 });
        ImGui::Hotkey(u8"Кнопка, чтобы прекратить печатать", &g_Cvars.keyStopWrite, ImVec2{ 310, 25 });
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);

		if (ImGui::Button(u8"Закрыть", ImVec2(WindowSizeX, 20)))
			ExitProcess(0);

		ImGui::SameLine();
		ImGui::End();
		
	}
	ImGui::End();

	ImGui::EndFrame();
}