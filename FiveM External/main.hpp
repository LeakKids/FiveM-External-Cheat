#include <iostream>
#include "GL/glew.h"
#include "imgui/imgui.h"
#include "include.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <tchar.h>
#include <intrin.h>
#include "byte_array.h"
#define STB_IMAGE_IMPLEMENTATION
#include "image.h"
RECT ProcessRect = { NULL };

HWND attach_window;
HWND fuck_hwnd;

uintptr_t i_world;
uintptr_t i_replay;
uintptr_t i_viewport;
uintptr_t i_localplayer;
uintptr_t i_waypointx;
uintptr_t i_waypointy;

uintptr_t i_veh;
uintptr_t i_enginehealth;
uintptr_t armoroffset;
uintptr_t weaponmanager;
uintptr_t i_handling;
uintptr_t playerinfo;
DWORD64 i_camera;
uintptr_t i_base;
GLFWwindow* menu_window;

int menu_width = 155;
int menu_height = 155;

bool menu_visible = true;
static void CallBackError(int error, const char* description) {}

int my_image_width;
int my_image_height;
GLuint my_image_texture;
bool Result;

//namespace fonts
ImFont* medium;
ImFont* bold;
ImFont* tab_icons;
ImFont* logo;
ImFont* tab_title;
ImFont* tab_title_icon;
ImFont* subtab_title;
ImFont* combo_arrow;

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

void tema() {
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	
	ImGui::StyleColorsLight();


	// Load Fonts
	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;

	medium = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 15.0f, &font_config, ranges);
	bold = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

	tab_icons = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 15.0f, &font_config, ranges);
	logo = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 21.0f, &font_config, ranges);

	tab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 19.0f, &font_config, ranges);
	tab_title_icon = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 18.0f, &font_config, ranges);

	subtab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

	combo_arrow = io.Fonts->AddFontFromMemoryTTF(combo, sizeof(combo), 9.0f, &font_config, ranges);

	// Our state
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	style.Colors[ImGuiCol_Border] = ImColor(149, 10, 255,255);	
	//style.Colors[ImGuiCol_TitleBg] = ImColor(149, 10, 255, 255);
	//style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(149, 10, 255, 255);
	//style.Colors[ImGuiCol_TitleBgActive] = ImColor(149, 10, 255, 255);
	//style.Colors[ImGuiCol_SliderGrab] = ImColor(149, 10, 255, 255);
	//style.Colors[ImGuiCol_SliderGrabActive] = ImColor(149, 10, 255, 255);
	//style.Colors[ImGuiCol_CheckMark] = ImColor(149, 10, 255, 255);
}

static void HelpMarker(const char* desc) {
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

static HWND get_process_wnd(uint32_t pid) {
	std::pair<HWND, uint32_t> params = { 0, pid };

	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
		auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
		uint32_t processId = 0;

		if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
			SetLastError((uint32_t)-1);
			pParams->first = hwnd;
			return FALSE;
		}

		return TRUE;

		}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
		return params.first;

	return NULL;
}

void setupWindow() {

	glfwSetErrorCallback(CallBackError);
	if (!glfwInit()) {
		return;
	}

	//GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	//if (!monitor) {
	//	return;
	//}

	if (attach_window) {
		GetClientRect(attach_window, &ProcessRect);
		POINT xy;
		ClientToScreen(attach_window, &xy);
		ProcessRect.left = xy.x;
		ProcessRect.top = xy.y;

		menu_width = ProcessRect.right;
		menu_height = ProcessRect.bottom;
	}

	//menu_width = glfwGetVideoMode(monitor)->width;
	//menu_height = glfwGetVideoMode(monitor)->height;

	glfwWindowHint(GLFW_FLOATING, true);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_MAXIMIZED, true);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

	menu_window = glfwCreateWindow(menu_width, menu_height, "FiveM External", NULL, NULL);
	if (menu_window == NULL) {
		return;
	}
	fuck_hwnd = glfwGetWin32Window(menu_window);
	//ShowWindow(fuck_hwnd, SW_HIDE);
	SetWindowLong(fuck_hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	glfwSetWindowAttrib(menu_window, GLFW_DECORATED, false);
	glfwSetWindowAttrib(menu_window, GLFW_MOUSE_PASSTHROUGH, true);
	glfwSetWindowMonitor(menu_window, NULL, 0, 0, menu_width, menu_height + 1, 0);

	glfwMakeContextCurrent(menu_window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		return;
	}

	my_image_texture = 0;
	Result = LoadTextureFromFile("C:\\logo.png", &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(Result);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplGlfw_InitForOpenGL(menu_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void cleanupWindow() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(menu_window);
	glfwTerminate();
}

void handleKeyPresses() {
	HWND hwnd_active = GetForegroundWindow();

	if (hwnd_active != attach_window && hwnd_active != fuck_hwnd) {
		ShowWindow(fuck_hwnd, SW_HIDE);
	}
	else {
		ShowWindow(fuck_hwnd, SW_SHOW);
		if (GetAsyncKeyState(bind_menuVK) & 1) {
			menu_visible = !menu_visible;
			glfwSetWindowAttrib(menu_window, GLFW_MOUSE_PASSTHROUGH, !menu_visible);
		}
	}
}