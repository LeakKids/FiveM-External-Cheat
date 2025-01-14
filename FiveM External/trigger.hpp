#pragma once
#include "get_player.hpp"

namespace trig {
	int boneeee;
	int keyyyy;
	int Fd_Key;
}

bool trigactive;

uintptr_t bGetPlayer() {
	uintptr_t ClosestPlayer = 0;
	float closestdist = FLT_MAX;
	float dist;

	//int MaxPeds = *(int*)(cfg::OffPlay::PedReplayInterface + 0x108);
	for (int i = 0; i < 256; i++) {

		uintptr_t PedReplayInterface = read_mem<uintptr_t>(ReplayInterface_ptr + 0x18);
		uintptr_t PedList = read_mem<uintptr_t>(PedReplayInterface + 0x100);

		if (!PedList) continue;

		if (localplayer != 0) {

			uintptr_t Ped = read_mem<uintptr_t>(PedList + (i * 0x10));

			if (!Ped) continue;

			//if (PedList < 10000)continue;

			if (Ped != localplayer) {

				float Health = read_mem<float>(Ped + 0x280);

				if (Health <= 110) continue;

				ImVec2 Head = GetBonePosImVec(Ped, 0);
				// ImVec2 middle = ImVec2(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
				ImVec2 middle = GetWindowMiddle();
				dist = pythag(middle, Head);

				if (dist < closestdist)
				{
					closestdist = dist;
					ClosestPlayer = Ped;
				}
			}
		}
	}
	return ClosestPlayer;
}

void RageTriggerbot() {

	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
	};

	uintptr_t RespCPed = bGetPlayer();

	auto bone_pos = GetBonePosImVec(RespCPed, 0);


	ImVec2 screen = bone_pos;

	auto center_x = (GetSystemMetrics(SM_CXSCREEN) - 5) / 2;
	auto center_y = (GetSystemMetrics(SM_CYSCREEN) - 5) / 2;
	auto fov = get_distance(center_x, center_y, screen.x, screen.y);
	float TargetX = 0;
	float TargetY = 0;

	Vec3 EntPos = read_mem<Vec3>(RespCPed + 0x90);

	Vec3 LocPos = read_mem<Vec3>(localplayer + 0x90);

	double distance = sqrt(pow(LocPos.x - EntPos.x, 2) + pow(LocPos.y - EntPos.y, 2) + pow(LocPos.y - EntPos.y, 2)) * 0.625;

	if (fov <= trigger_fov_value + 0.10) {
		if (distance <= trigger_max_distance) {
			if (GetKeyState(trig::keyyyy) & 0x8000) {
				trigactive = true;
				trigger_locked[0] = RespCPed;
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				trigactive = true;
			}
		}
	}
	else if (trigactive) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		trigger_locked[0] = 0;
		trigactive = false;
	}
}


void LegitTriggerbot() {

	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
	};

	uintptr_t RespCPed = bGetPlayer();

	auto bone_pos = GetBonePosImVec(RespCPed, 0);


	ImVec2 screen = bone_pos;

	auto center_x = (GetSystemMetrics(SM_CXSCREEN) - 5) / 2;
	auto center_y = (GetSystemMetrics(SM_CYSCREEN) - 5) / 2;
	auto fov = get_distance(center_x, center_y, screen.x, screen.y);
	float TargetX = 0;
	float TargetY = 0;

	Vec3 EntPos = read_mem<Vec3>(RespCPed + 0x90);

	Vec3 LocPos = read_mem<Vec3>(localplayer + 0x90);

	double distance = sqrt(pow(LocPos.x - EntPos.x, 2) + pow(LocPos.y - EntPos.y, 2) + pow(LocPos.y - EntPos.y, 2)) * 0.625;

	if (trigactive) {
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		trigger_locked[0] = 0;
		trigactive = false;
	}

	if (fov <= trigger_fov_value + 0.10) {
		if (distance <= trigger_max_distance) {
			if (GetKeyState(trig::keyyyy) & 0x8000) {
				trigactive = true;
				trigger_locked[0] = RespCPed;
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				trigactive = true;
			}
		}
		else {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
}


void bindtrigger() {
	if (bind_trigger == 0) { trig::keyyyy = VK_RBUTTON; }
	else if (bind_trigger == 1) { trig::keyyyy = VK_LBUTTON; }
	else if (bind_trigger == 2) { trig::keyyyy = VK_XBUTTON1; }
	else if (bind_trigger == 3) { trig::keyyyy = VK_XBUTTON2; }
	else if (bind_trigger == 4) { trig::keyyyy = VK_SHIFT; }
	else if (bind_trigger == 5) { trig::keyyyy = VK_MENU; }
	else if (bind_trigger == 6) { trig::keyyyy = 0x45; }
}
