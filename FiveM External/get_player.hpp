#pragma once
#include "include.h"
#include "esp.hpp"
#include "render.hpp"
#include <Windows.h>
#include <iostream>

uintptr_t get_Player(int bone) {
	uintptr_t ClosestPlayer = 0;
	float closestdist = FLT_MAX;
	float dist;

	uintptr_t PedReplayInterface = read_mem<uintptr_t>(ReplayInterface_ptr + 0x18);
	uintptr_t PedList = read_mem<uintptr_t>(PedReplayInterface + 0x100);

	for (int i = 0; i < 256; i++) {

		if (!PedList) continue;

		uintptr_t Ped = read_mem<uintptr_t>(PedList + (i * 0x10));
		auto pedType = read_mem<int>(Ped + 0x10b8) << 11 >> 25;

		if (!Ped) continue;

		if (!TargetNpcs) {
			if (pedType != 2)
				continue;
		}

		if (Ped != localplayer) {

			if (player_friend[i] != Ped) {

				ImVec2 Head = GetBonePosImVec(Ped, bone);

				float Health = read_mem<float>(Ped + 0x280);

				if (Health <= 110) continue;

				ImVec2 middle = GetWindowMiddle();
				dist = pythag(middle, Head);

				if (dist < closestdist) {
					closestdist = dist;
					ClosestPlayer = Ped;
				}
			}
		}
	}
	return ClosestPlayer;
}
