#pragma once
#include "memory.h"
#include "vector.h"
#include "../include/imgui/imgui.h"

uintptr_t ReplayInterface_ptr;
uintptr_t world_ptr;
uintptr_t viewport_ptr;
uintptr_t localplayer;


uintptr_t player_contry[256];
uintptr_t player_friend[256];

//aimbot
uintptr_t aimbot_locked[247];
bool aimbot_on;
bool aimbot_fov;
bool aimbot_showtarget;
bool aimbot_maxsensi;
float aimbot_fov_value = 40;
float aimbot_smooth = 0.1;
float aimbot_max_distance = 80;
int aimbot_bone;
bool TargetNpcs = false;
int aimbot_currbone = 0;
int fov_segments = 40;
bool weapons = false;
bool invisibility = false;
bool infinitestamina = false;

//trigger
uintptr_t trigger_locked[255];
bool trigger_on;
bool trigger_fov;
bool trigger_showtarget;
float trigger_fov_value = 40;
float trigger_max_distance = 80;
int trigger_type;

//esp
bool esp_on = true;
bool esp_box;
bool esp_corner;
bool filled_box;
bool esp_skeletons;
bool esp_drawnpcs = false;
bool esp_skeletons2;
bool esp_showdistance;
bool esp_hptext;
bool esp_lines;
bool esp_head;
bool esp_hpbar;
bool esp_showid;
float esp_max_distance = 500;

//binds
int bind_menu;
int bind_menuVK;
int bind_aimbot;
int bind_trigger;
int bind_silent;

//exploits
bool ex_godmode;
bool ex_norecoil;
bool ex_semigodmode;
bool ex_vehiclegodmode;
bool ex_nospread;
bool ex_noreaload;
bool ex_runspeed_on;
float ex_runspeed_value = 1;
bool ex_vehicleaceleration;
float ex_vehicleaceleration_value;
bool ex_vehiclebreak;
float ex_vehiclebreak_value;

namespace Colors {
	ImColor ESPCorner = ImColor(149, 10, 255, 255);
	ImColor ESPLines = ImColor(149, 10, 255, 255);
	ImColor ESPBox = ImColor(149, 10, 255, 255);
	ImColor ESPName = ImColor(149, 10, 255, 255);
	ImColor ESPSkeleton = ImColor(149, 10, 255, 255);
	ImColor ESP_Skeleton_test = ImColor(149, 10, 255, 255);
	ImColor ESPDistance = ImColor(149, 10, 255, 255);
	ImColor ESPHpText = ImColor(149, 10, 255, 255);
}
namespace Temp {
	static float Corner[5] = { 1.f, 1.f, 1.f, 255 };
	static float Box[5] = { 1.f, 1.f, 1.f, 255 };
	static float Distance[5] = { 1.f, 1.f, 1.f, 255 };
	static float HpText[5] = { 1.f, 1.f, 1.f , 255 };
	static float Lines[5] = { 1.0f, 1.0f, 1.0f, 255 };
	static float Skeleton[5] = { 1.f, 1.f, 1.f , 255 };
	static float VehicleColor[5] = { 1.f, 1.f, 1.f , 255 };
}