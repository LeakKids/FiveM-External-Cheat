#include "main.hpp"
#include "include.h"
#include "esp.hpp"
#include "aimbot.hpp"
#include "memory.h"
#include "offsets.h"
#include "exploit.h"
#include "xor.hpp"
#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "skStr.h"
#include <urlmon.h>
#include "color.hpp"
#include "user_interface.h"
#include "imgui/imgui_impl_win32.h"
#include "trigger.hpp"
#include "nav_elements.h"
#include <iostream>
#include "json.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "file_operations.h"
#include "console_title_animator.h"
#include <thread>
#include "AntiDebug.h"
#include <fstream>
#include <shellapi.h>

#pragma comment(lib, "urlmon.lib")

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);


std::string FPS;
std::string logg;
using namespace std;
bool visual = true;
bool aimbot = true;
enum heads {
	rage, antiaim, visuals, settings, skins, configs, scripts
};

enum sub_heads {
	general, accuracy, exploits, _general, advanced
};


void panel();


bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {

	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}

void FovAimbot() {
	int screen_x = GetSystemMetrics(SM_CXSCREEN);
	int screen_y = GetSystemMetrics(SM_CYSCREEN);
	auto draw = ImGui::GetOverlayDrawList();
	draw->AddCircle(ImVec2(screen_x / 2, screen_y / 2), aimbot_fov_value, IM_COL32(233, 232, 232, 255), fov_segments, 2.0f);
}

void GPlayerList() {
	uintptr_t PedReplayInterface = read_mem<uintptr_t>(ReplayInterface_ptr + 0x18);
	uintptr_t PedList = read_mem<uintptr_t>(PedReplayInterface + 0x100);
	for (int i = 0; i < 256; i++) {
		if (PedList) {
			uintptr_t Ped = read_mem<uintptr_t>(PedList + (i * 0x10));
			if (Ped) {
				if (localplayer != 0) {
					if (Ped != localplayer) {

						player_contry[i] = Ped;

					}
				}
			}
		}
	}
}

void PlayerList() {
	GPlayerList();
	for (int i = 0; i < 256; i++) {
		if (player_contry[i] != 0) {
			string layer = std::to_string(i);
			if (player_friend[i] == 0) {
				if (ImGui::Button(("Add Friend ID: " + layer).c_str(), { 199, 22 })) {
					player_friend[i] = player_contry[i];
				}
			}
			else {
				if (ImGui::Button(("Remove Friend ID: " + layer).c_str(), { 199, 22 })) {
					player_friend[i] = 0;
				}
			}
		}
	}
}

void OpenGithub() {
	ShellExecuteA(nullptr, "open", "https://github.com/chres0", nullptr, nullptr, SW_SHOWNORMAL);
}

//void OpenWebsiteCheats() {
//	ShellExecuteA(nullptr, "open", "https://example.com/", nullptr, nullptr, SW_SHOWNORMAL);
//}

void loginpanel();

int valueI;
bool the_bool;

bool god;
bool nspeed;
bool nrec;
bool nreload;
bool npread;
bool VehSp;
bool VehBrk;
bool VehGod;
int tabb = 0;

const char* menu_bind[] = { ("F4"), ("F8"), ("Delete"), ("Insert") };
const char* aimbot_bind[] = { ("Right Button") ,("Left Button") , ("Page Backward Button"), ("Page Forward Button"),("Shift"),("Menu"),("E") };
const char* trigger_bind[] = { ("Right Button") ,("Left Button"), ("Page Backward Button"), ("Page Forward Button"),("Shift"),("Menu"),("E") };
static int selected = 0;
static int sub_selected = 0;

static bool bullying = false;
static bool bullythosemfs = false;
static bool stopbullythemyoushitters = false;
static bool stop = false;
static bool niggas = false;
static bool hihihi = false;
static bool bro = false;
static int sliderinc = 0;
//static int combo = 0;
const char* hitbox_items[] = { "Head", "Neck", "Pelvis", "Right Hand", "Left Hand", "Right Foot", "Left Foot" };
static float color[5] = { 1.f, 1.f, 1.f, 1.f };


static heads tab{ rage };
static sub_heads subtab{ general };

const char* tab_name = tab == rage ? "Ragebot" : tab == antiaim ? "Anti-aim" : tab == visuals ? "Visuals" : tab == settings ? "Settings" : tab == skins ? "Skins" : tab == configs ? "Configs" : tab == scripts ? "Scripts" : 0;
const char* tab_icon = tab == rage ? "B" : tab == antiaim ? "C" : tab == visuals ? "D" : tab == settings ? "E" : tab == skins ? "F" : tab == configs ? "G" : tab == scripts ? "H" : 0;


bool loadConfigRequested = false;  // Flag to indicate whether to load config

void LoadSettings(const char* filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error opening file for reading: " << filename << std::endl;
		return;
	}

	file.read(reinterpret_cast<char*>(&ex_noreaload), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_norecoil), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_nospread), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_vehicleaceleration), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_runspeed_on), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_runspeed_value), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_vehiclebreak), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_vehiclebreak_value), sizeof(bool));
	file.read(reinterpret_cast<char*>(&ex_vehiclegodmode), sizeof(bool));
	file.read(reinterpret_cast<char*>(&aimbot_on), sizeof(bool));
	file.read(reinterpret_cast<char*>(&aimbot_bone), sizeof(bool));
	file.read(reinterpret_cast<char*>(&aimbot_fov), sizeof(bool));
	file.read(reinterpret_cast<char*>(&aimbot_fov_value), sizeof(bool));
	file.read(reinterpret_cast<char*>(&TargetNpcs), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_box), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_corner), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_drawnpcs), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_head), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_hpbar), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_lines), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_max_distance), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_showdistance), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_showid), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_skeletons), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_skeletons2), sizeof(bool));
	file.read(reinterpret_cast<char*>(&trigger_fov), sizeof(bool));
	file.read(reinterpret_cast<char*>(&trigger_fov_value), sizeof(bool));
	file.read(reinterpret_cast<char*>(&trigger_on), sizeof(bool));
	file.read(reinterpret_cast<char*>(&esp_hptext), sizeof(bool));
	file.read(reinterpret_cast<char*>(&filled_box), sizeof(bool));

	file.close();
}

void SaveSettings(const char* filename) {
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error opening file for writing: " << filename << std::endl;
		return;
	}

	file.write(reinterpret_cast<char*>(&ex_noreaload), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_norecoil), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_nospread), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_vehicleaceleration), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_runspeed_on), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_runspeed_value), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_vehiclebreak), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_vehiclebreak_value), sizeof(bool));
	file.write(reinterpret_cast<char*>(&ex_vehiclegodmode), sizeof(bool));
	file.write(reinterpret_cast<char*>(&aimbot_on), sizeof(bool));
	file.write(reinterpret_cast<char*>(&aimbot_bone), sizeof(bool));
	file.write(reinterpret_cast<char*>(&aimbot_fov), sizeof(bool));
	file.write(reinterpret_cast<char*>(&aimbot_fov_value), sizeof(bool));
	file.write(reinterpret_cast<char*>(&TargetNpcs), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_box), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_corner), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_drawnpcs), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_head), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_hpbar), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_lines), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_max_distance), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_showdistance), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_showid), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_skeletons), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_skeletons2), sizeof(bool));
	file.write(reinterpret_cast<char*>(&trigger_fov), sizeof(bool));
	file.write(reinterpret_cast<char*>(&trigger_fov_value), sizeof(bool));
	file.write(reinterpret_cast<char*>(&trigger_on), sizeof(bool));
	file.write(reinterpret_cast<char*>(&esp_hptext), sizeof(bool));
	file.write(reinterpret_cast<char*>(&filled_box), sizeof(bool));


	file.close();
}

struct Animator {
	float alpha;
	bool tick;
	float speed;
};

inline void AnimateContent(Animator& animator) {
	const int limit = 255;
	if (animator.tick || animator.alpha == limit) {
		animator.tick = true;
		if (!(animator.alpha <= 0))
			animator.alpha -= animator.speed;
		else if (animator.alpha <= 0)
			animator.tick ^= 1;
	}

	else if (!animator.tick || animator.alpha != limit)
	{
		animator.tick = false;
		if (!(animator.alpha >= limit))
			animator.alpha += animator.speed;
		else if (animator.alpha >= limit)
			animator.tick ^= 1;
	}
}

void Render() {

	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();



	if (bind_menu == 0) { bind_menuVK = VK_F4; }
	else if (bind_menu == 1) { bind_menuVK = VK_F8; }
	else if (bind_menu == 2) { bind_menuVK = VK_DELETE; }
	else if (bind_menu == 3) { bind_menuVK = VK_INSERT; }

	__try {
		if (aimbot_fov) { FovAimbot(); }

		if (esp_on) { DrawEsp(); }

		if (aimbot_on) { bindaimbot(); Aimbot(); }

		if (trigger_on) {
			bindtrigger();
			if (trigger_type == 0 || trigger_type == 1) {
				RageTriggerbot();
			}
			else if (trigger_type == 2) {
				LegitTriggerbot();
			}
		}

		if (ex_runspeed_on) { Player::SpeedWalk(true, ex_runspeed_value); nspeed = true; }
		else { if (nspeed) { Player::SpeedWalk(false, 0); }nspeed = false; }

		if (ex_runspeed_on) { Player::SpeedWalk(true, ex_runspeed_value); nspeed = true; }
		else { if (nspeed) { Player::SpeedWalk(false, 0); }nspeed = false; }

		if (ex_norecoil) { Weapons::NoRecoil(true); nrec = true; }
		else { if (nrec) { Weapons::NoRecoil(false); }nrec = false; }


		if (ex_noreaload) { Weapons::NoReaload(true); nreload = true; }
		else { if (nreload) { Weapons::NoReaload(false); }nreload = false; }

		if (ex_nospread) { Weapons::NoSpread(true); npread = true; }
		else { if (npread) { Weapons::NoSpread(false); }npread = false; }

		if (ex_godmode) { Player::Godmode(true); god = true; }
		else { if (god) { Player::Godmode(false); }god = false; }

		if (ex_semigodmode) {
			if (Player::GetHealth() <= 200) {
				Player::SetHealth(Player::GetMaxHealth());
			}
		}

		if (ex_vehicleaceleration) { Vehicle::VehicleAceleration(true, ex_vehicleaceleration_value); VehSp = true; }
		else { if (VehSp) { Vehicle::VehicleAceleration(false, ex_vehicleaceleration_value); }VehSp = false; }

		if (ex_vehiclebreak) { Vehicle::VehicleBrakeForce(true, ex_vehiclebreak_value); VehBrk = true; }
		else { if (VehBrk) { Vehicle::VehicleBrakeForce(false, ex_vehiclebreak_value); }VehBrk = false; }


		if (ex_vehiclegodmode) { Vehicle::GodModeVehicle(true); VehGod = true; }
		else { if (VehGod) { Vehicle::GodModeVehicle(false); }VehGod = false; }

	}
	__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}

	if (menu_visible) {

		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowSize(ImVec2(750, 500));

		ImGui::Begin("FiveM External Main", nullptr, ImGuiWindowFlags_NoDecoration);

		auto draw = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetWindowPos();
		ImVec2 size = ImGui::GetWindowSize();


		draw->AddRectFilled(ImVec2(0, 0), ImVec2(1920, 1080), ImColor(0, 0, 0, 255), 0.2f);


		draw->AddLine(ImVec2(pos.x + 55, pos.y + 35), ImVec2(pos.x + size.x, pos.y + 35), ImColor(0, 0, 0, 15)); // upper line
		draw->AddLine(ImVec2(pos.x + 55, pos.y), ImVec2(pos.x + 55, pos.y + size.y), ImColor(255, 255, 255, 15)); // left line

		ImGui::SetCursorPos(ImVec2(13, 11));
		ImGui::BeginGroup();
		if (elements::tab("B", tab == rage)) {
			tab = rage; sub_selected = 0;
		}
		if (elements::tab("D", tab == antiaim)) {
			tab = antiaim; sub_selected = 2;
		}
		if (elements::tab("C", tab == visuals)) {
			tab = visuals; sub_selected = 184;
		}
		if (elements::tab("E", tab == settings)) {
			tab = settings; sub_selected = 456;
		}
		ImGui::EndGroup();

		ImVec2 window_pos{ ImGui::GetWindowPos() };
		ImVec2 window_size{ ImGui::GetWindowSize() };

		static Animator animator{ 255, false, 1.1f };
		AnimateContent(animator);

		ImDrawList* draw_list = ImGui::GetForegroundDrawList();
		draw_list->AddRect({ window_pos.x - 1, window_pos.y - 1 }, { window_pos.x + window_size.x + 1, window_pos.y + window_size.y + 1 },
			ImColor(255, 0, 0, (int)animator.alpha), 4.0, 0, 1.5f);



		if (tab == rage) {
			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Aimbot", 0 == sub_selected)) {
				sub_selected = 0;
			}
			ImGui::SameLine();
			if (custom_interface::subtab("TriggerBot", 16 == sub_selected)) {
				sub_selected = 16;
			}
			ImGui::SameLine();
			if (custom_interface::subtab("Extra", 87 == sub_selected)) {
				sub_selected = 87;
			}
			ImGui::EndGroup();

			if (sub_selected == 0) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Aim Assistance", ImVec2(219, 382));
				{
					ImGui::Checkbox("Aimbot", &aimbot_on);
					ImGui::Checkbox("Show FOV", &aimbot_fov);
					ImGui::Checkbox("Target Peds/NPCs", &TargetNpcs);
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(291, 44));
				ImGui::BeginChild("Config", ImVec2(219, 382));
				{
					ImGui::Combo("Aimbot Bone", &aimbot_bone, hitbox_items, IM_ARRAYSIZE(hitbox_items));
					ImGui::SliderFloat("Aimbot Smoothing", &aimbot_smooth, 0.f, 50.f, "% .2f");
					ImGui::SliderFloat("Aimbot Distance", &aimbot_max_distance, 20.f, 500.f, "% .2f");
					ImGui::SliderFloat("Aimbot FOV", &aimbot_fov_value, 20.f, 400.f, "% .2f");
				}
				ImGui::EndChild();

			}

			if (sub_selected == 16) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("TriggerBot", ImVec2(219, 382));
				{
					ImGui::Checkbox("TriggerBot", &trigger_on);
					ImGui::Checkbox("TriggerBot FOV", &trigger_fov);

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(291, 44));
				ImGui::BeginChild("Config", ImVec2(219, 382));
				{
					//ImGui::Combo("Aimbot Bone", &combo, combo_items, 4);
					ImGui::SliderFloat("TriggerBot FOV Value", &trigger_fov_value, 0.f, 50.f, "% .2f");
					ImGui::SliderFloat("TriggerBot Distance", &aimbot_max_distance, 20.f, 500.f, "% .2f");
				}
				ImGui::EndChild();
			}

			if (sub_selected == 87) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Friend List", ImVec2(219, 382));
				{
					PlayerList();
				}
				ImGui::EndChild();
			}
		}

		if (tab == antiaim) {
			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Visuals", 2 == sub_selected)) {
				sub_selected = 2;
			}
			ImGui::EndGroup();

			if (sub_selected == 2) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Visuals", ImVec2(219, 382));
				{

					ImGui::Checkbox(XorStr("Box").c_str(), &esp_box);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Box Color").c_str(), Temp::Box, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPBox.Value.x = Temp::Box[0]; Colors::ESPBox.Value.y = Temp::Box[1]; Colors::ESPBox.Value.z = Temp::Box[2]; Colors::ESPBox.Value.w = Temp::Box[3];

					ImGui::Checkbox(XorStr("Box Corner").c_str(), &esp_corner);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Box Corner Color").c_str(), Temp::Corner, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPCorner.Value.x = Temp::Corner[0]; Colors::ESPCorner.Value.y = Temp::Corner[1]; Colors::ESPCorner.Value.z = Temp::Corner[2]; Colors::ESPCorner.Value.w = Temp::Corner[3];

					ImGui::Checkbox(XorStr("Skeleton").c_str(), &esp_skeletons);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Skeleton Color").c_str(), Temp::Skeleton, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPSkeleton.Value.x = Temp::Skeleton[0]; Colors::ESPSkeleton.Value.y = Temp::Skeleton[1]; Colors::ESPSkeleton.Value.z = Temp::Skeleton[2]; Colors::ESPSkeleton.Value.w = Temp::Skeleton[3];

					ImGui::Checkbox(XorStr("Show Distance").c_str(), &esp_showdistance);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Text Distance Color").c_str(), Temp::Distance, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPDistance.Value.x = Temp::Distance[0]; Colors::ESPDistance.Value.y = Temp::Distance[1]; Colors::ESPDistance.Value.z = Temp::Distance[2]; Colors::ESPDistance.Value.w = Temp::Distance[3];

					ImGui::Checkbox(XorStr("Health Text").c_str(), &esp_hptext);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Text Health Color").c_str(), Temp::HpText, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPHpText.Value.x = Temp::HpText[0]; Colors::ESPHpText.Value.y = Temp::HpText[1]; Colors::ESPHpText.Value.z = Temp::HpText[2]; Colors::ESPHpText.Value.w = Temp::HpText[3];

					ImGui::Checkbox(XorStr("Lines").c_str(), &esp_lines);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Lines Color").c_str(), Temp::Lines, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPLines.Value.x = Temp::Lines[0]; Colors::ESPLines.Value.y = Temp::Lines[1]; Colors::ESPLines.Value.z = Temp::Lines[2]; Colors::ESPLines.Value.w = Temp::Lines[3];


					ImGui::Checkbox(XorStr("Draw NPCS").c_str(), &esp_drawnpcs);

					ImGui::Checkbox(XorStr("Filled Box").c_str(), &filled_box);

					ImGui::Checkbox(XorStr("Health Bar").c_str(), &esp_hpbar);

					ImGui::Checkbox(XorStr("Head ESP").c_str(), &esp_head);
					
					ImGui::Checkbox(XorStr("Weapon ESP").c_str(), &weapons);

					ImGui::Checkbox(XorStr("Show Menu IDs").c_str(), &esp_showid);

					ImGui::SliderFloat(XorStr("ESP Distance").c_str(), &esp_max_distance, 20, 500, "% .2f");
				}
				ImGui::EndChild();


			}
		}
		int selectedHeal = 200;
		int selectedArmor = 100;
		if (tab == visuals) {
			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Self", 184 == sub_selected)) {
				sub_selected = 184;
			}
			ImGui::SameLine();
			if (custom_interface::subtab("Misc", 145 == sub_selected)) {
				sub_selected = 145;
			}
			ImGui::EndGroup();


			if (sub_selected == 184) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Player", ImVec2(219, 382));
				{
					ImGui::Checkbox("GodMode", &ex_godmode);
					ImGui::Checkbox("Semi-GodMode", &ex_semigodmode);
					ImGui::Checkbox("Infinite Stamina", &infinitestamina);
					ImGui::Checkbox("Invisibility (CS)", &invisibility);
					ImGui::Checkbox("Change Run Speed", &ex_runspeed_on);
					ImGui::SliderFloat(XorStr("Run Speed").c_str(), &ex_runspeed_value, 0.f, 1000.f, "% .1f");

					ImGui::Spacing();
					if (ImGui::Button("Max Health")) {
						write_mem<float>(localplayer + 0x280, selectedHeal);
						write_mem<float>(localplayer + 0x2A0, selectedHeal);
					}

					ImGui::SameLine();

					if (ImGui::Button("Max Armor")) {
						uintptr_t armadura = armoroffset;
						write_mem<float>(localplayer + armadura, static_cast<float>(selectedArmor));
					}
				}
				ImGui::EndChild();
			}
			else if (sub_selected == 145) {

				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Vehicle", ImVec2(219, 382));
				{
					ImGui::Checkbox("Vehicle Acceleration", &ex_vehicleaceleration);
					ImGui::Checkbox("Vehicle GodMode", &ex_vehiclegodmode);
					ImGui::Checkbox("Fix Engine", &the_bool);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));  // Set text color to white
					if (ImGui::Button("Fix Engine", ImVec2(192, 22))) {
						Vehicle::FixEngine(1000.f);
					}
					ImGui::PopStyleColor();  // Revert text color back to default
					ImGui::SliderFloat(XorStr("Vehicle Acceleration").c_str(), &ex_vehicleaceleration_value, 0.f, 20000.f, "% .2f");
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(291, 44));
				ImGui::BeginChild("Weapons", ImVec2(219, 382));
				{
					ImGui::Checkbox("No Recoil", &ex_norecoil);
					ImGui::Checkbox("No Reload", &ex_noreaload);
					ImGui::Checkbox("No Spread", &ex_nospread);
				}
				ImGui::EndChild();

			}
		}

		if (tab == settings) {

			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Extra", 456 == sub_selected)) {
				sub_selected = 456; //esta la pones aqui tmb
			}
			ImGui::EndGroup();

			if (sub_selected == 456) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Binds", ImVec2(219, 382));
				{
					ImGui::Combo("Menu Key", &bind_menu, menu_bind, IM_ARRAYSIZE(menu_bind));
					ImGui::Combo("Aimbot Key", &bind_aimbot, aimbot_bind, IM_ARRAYSIZE(aimbot_bind));
					ImGui::Combo("TriggerBot Key", &bind_trigger, trigger_bind, IM_ARRAYSIZE(trigger_bind));

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(291, 44));
				ImGui::BeginChild("Information", ImVec2(219, 382));
				{
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Set text color to white
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::PushFont(bold);
					ImGui::Text("Configs");
					ImGui::PopFont();
					ImGui::Separator();
					if (ImGui::Button("Load Config")) {
						loadConfigRequested = true;
					}

					// Save Config
					ImGui::SameLine();
					if (ImGui::Button("Save Config")) {
						SaveSettings("config.dat");
					}

					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::PushFont(bold);
					ImGui::Text("Copyright: 2024");
					ImGui::PopFont();
					ImGui::Separator();
					ImGui::Spacing();
					//if (ImGui::Button("Discord")) {
					//	OpenWebsiteCheats();
					//}
					if (ImGui::Button("GitHub")) {
						OpenGithub();
					}
					ImGui::PopStyleColor();
				}
				ImGui::EndChild();
			}
		}
		ImGui::End();
	}

	if (loadConfigRequested) {
		LoadSettings("config.dat");
		loadConfigRequested = false;
	}

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(menu_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(menu_window);
}

void ReallockLocalPlayer() {
	while (true) {

		localplayer = read_mem<uintptr_t>(world_ptr + (0x8));
	}
}

string procname = "";


int initialize() {
	attach_window = FindWindowA("grcWindow", 0);
	DWORD off_world, off_replay, off_view;
	if (isProcRunning(skCrypt("FiveM_GTAProcess.exe").decrypt())) {
		off_world = offset::b1604::world_ptr;
		off_replay = offset::b1604::ReplayInterface_ptr;
		off_view = offset::b1604::viewport_ptr;
		procname = skCrypt("FiveM_GTAProcess.exe");
		weaponmanager = 0x10D8;
		armoroffset = 0x14B8;
	}
	else if (isProcRunning(skCrypt("FiveM_b2060_GTAProcess.exe").decrypt())) {
		off_world = offset::b2060::world_ptr;
		off_replay = offset::b2060::ReplayInterface_ptr;
		off_view = offset::b2060::viewport_ptr;
		procname = skCrypt("FiveM_b2060_GTAProcess.exe");
		weaponmanager = 0x10D8;
		i_camera = 0x20D9868;
		armoroffset = 0x14E0;
	}
	else if (isProcRunning(skCrypt("FiveM_b2189_GTAProcess.exe").decrypt())) {
		off_world = offset::b2189::world_ptr;
		off_replay = offset::b2189::ReplayInterface_ptr;
		off_view = offset::b2189::viewport_ptr;
		procname = skCrypt("FiveM_b2189_GTAProcess.exe");
		weaponmanager = 0x10D8;
		i_camera = read_mem<DWORD64>(base_address.modBaseAddr + 0x0);
		armoroffset = 0x14E0;
	}
	else if (isProcRunning(skCrypt("FiveM_b2372_GTAProcess.exe").decrypt())) {
		off_world = offset::b2372::world_ptr;
		off_replay = offset::b2372::ReplayInterface_ptr;
		off_view = offset::b2372::viewport_ptr;
		weaponmanager = 0x10D8;
		procname = skCrypt("FiveM_b2372_GTAProcess.exe");
		armoroffset = 0x14E0;
		i_camera = 0x1FD8570;
	}
	else if (isProcRunning(skCrypt("FiveM_b2545_GTAProcess.exe").decrypt())) {
		off_world = offset::b2545::world_ptr;
		off_replay = offset::b2545::ReplayInterface_ptr;
		off_view = offset::b2545::viewport_ptr;
		procname = skCrypt("FiveM_b2545_GTAProcess.exe");
		weaponmanager = 0x10D8;
		i_camera = 0x1FD7B48;
		armoroffset = 0x1530;
	}
	else if (isProcRunning(skCrypt("FiveM_b2612_GTAProcess.exe").decrypt())) {
		off_world = offset::b2612::world_ptr;
		off_replay = offset::b2612::ReplayInterface_ptr;
		off_view = offset::b2612::viewport_ptr;
		weaponmanager = 0x10D8;
		procname = skCrypt("FiveM_b2612_GTAProcess.exe");
		i_camera = read_mem<DWORD64>(base_address.modBaseAddr + 0x20D9868);
		armoroffset = 0x1530;
	}
	else if (isProcRunning(skCrypt("FiveM_b2699_GTAProcess.exe").decrypt())) {
		off_world = offset::b2699::world_ptr;
		off_replay = offset::b2699::ReplayInterface_ptr;
		off_view = offset::b2699::viewport_ptr;
		weaponmanager = 0x10D8;
		procname = skCrypt("FiveM_b2699_GTAProcess.exe");
		i_camera = 0x20D9868;
		armoroffset = 0x1530;
	}
	else if (isProcRunning(skCrypt("FiveM_b2802_GTAProcess.exe").decrypt())) {
		offset::detectv2802 = true;
		weaponmanager = 0x10B8;
		i_camera = read_mem<DWORD64>(base_address.modBaseAddr + 0x0);
		off_world = offset::b2802::world_ptr;
		off_replay = offset::b2802::ReplayInterface_ptr;
		off_view = offset::b2802::viewport_ptr;
		procname = skCrypt("FiveM_b2802_GTAProcess.exe");
		armoroffset = 0x150C;
	}
	if (!attach_window) {
		LPCWSTR message = L"Could not find FiveM process.";
		LPCWSTR title = L"FiveM Cheats";
		MessageBox(NULL, message, title, MB_ICONERROR);
		ExitProcess(0);
	}

	DWORD pid;
	GetWindowThreadProcessId(attach_window, &pid);

	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	base_address = get_module_base64(pid, std::wstring(procname.begin(), procname.end()).c_str());

	ReplayInterface_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_replay));

	world_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_world));

	viewport_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_view));

	localplayer = read_mem<uintptr_t>(world_ptr + (0x8));


	setupWindow();
	if (!menu_window) { return 1; }

	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ReallockLocalPlayer, nullptr, NULL, nullptr);
	tema();
	while (!glfwWindowShouldClose(menu_window)) {
		handleKeyPresses();
		Render();
	}

	cleanupWindow();
}

void openLink(const std::string& url) {
    ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

#ifdef _WINDLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)initialize, nullptr, NULL, nullptr);
		return TRUE;

	}
	return TRUE;
}
#else

void logo3()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	SetConsoleTextAttribute(hConsole, 4);
	std::cout <<
		R"(
                        FiveM External (Version: 2.9)

  $$$$$$$$\ $$\                      $$\      $$\        $$$$$$\  $$\                            $$\               
  $$  _____|\__|                     $$$\    $$$ |      $$  __$$\ $$ |                           $$ |              
  $$ |      $$\ $$\    $$\  $$$$$$\  $$$$\  $$$$ |      $$ /  \__|$$$$$$$\   $$$$$$\   $$$$$$\ $$$$$$\    $$$$$$$\ 
  $$$$$\    $$ |\$$\  $$  |$$  __$$\ $$\$$\$$ $$ |      $$ |      $$  __$$\ $$  __$$\  \____$$\\_$$  _|  $$  _____|
  $$  __|   $$ | \$$\$$  / $$$$$$$$ |$$ \$$$  $$ |      $$ |      $$ |  $$ |$$$$$$$$ | $$$$$$$ | $$ |    \$$$$$$\  
  $$ |      $$ |  \$$$  /  $$   ____|$$ |\$  /$$ |      $$ |  $$\ $$ |  $$ |$$   ____|$$  __$$ | $$ |$$\  \____$$\ 
  $$ |      $$ |   \$  /   \$$$$$$$\ $$ | \_/ $$ |      \$$$$$$  |$$ |  $$ |\$$$$$$$\ \$$$$$$$ | \$$$$  |$$$$$$$  |
  \__|      \__|    \_/     \_______|\__|     \__|       \______/ \__|  \__| \_______| \_______|  \____/ \_______/ 
                                                                                                                 

        )";
}

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
	std::thread titleThread(animateConsoleTitle);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	logo3();

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "\n\n Connecting...\n";

	Sleep(2000);
	std::cout << " Successfully Connected.\n\n";

	SetConsoleTextAttribute(hConsole, 15);  // Reset color

	std::cout << "\n The cheat will launch automatically. Please make sure that FiveM is running before doing so.\n\n";
	Sleep(1000);

	std::cout << "\n [1] Login\n ";
	SetConsoleTextAttribute(hConsole, 7);
	SetConsoleTextAttribute(hConsole, 4);

	std::cout << "\n Selection: ";

	SetConsoleTextAttribute(hConsole, 7); //reset color

	int option;

	std::cin >> option;
	switch (option)
	{
	case 1:
		std::cout << "\n ";
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "\n Initializing...";
		Sleep(1500);
		std::cout << "\n Starting...";
		SetConsoleTextAttribute(hConsole, 7);
		Sleep(3000);
		initialize();
		titleThread.join();
		
		return 0; // Exit after initialization
	default:
		std::cout << "\n\n Status: Failure: Invalid Selection";
		Sleep(3000);
		exit(0);
	}
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
#endif}