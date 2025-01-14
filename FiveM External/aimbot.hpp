#pragma once
#include "get_player.hpp"
#include <Windows.h>
#include <iostream>
using namespace std;

namespace aim {
	int bone;
	int bind;
	int Fd_Key;
}


class Vector3 final
{
public:

	float x, y, z;

	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrt(x * x + y * y + z * z); }
	Vector3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
	void Invert() { *this *= -1; }
	static Vector3 FromM128(__m128 in) { return Vector3(in.m128_f32[0], in.m128_f32[1], in.m128_f32[2]); }
};

void Aimbot() {

	if (aimbot_bone == 0) {
		aimbot_currbone = 0;
	}
	
	else if (aimbot_bone == 1)
	{
		aimbot_currbone = 7; 
	}
	else if (aimbot_bone == 2)
	{
		aimbot_currbone = 6;
	}
	else if (aimbot_bone == 3)
	{
		aimbot_currbone = 5;
	}
	else if (aimbot_bone == 4)
	{
		aimbot_currbone = 3;
	}
	else if (aimbot_bone == 5)
	{
		aimbot_currbone = 4;
	}

	uintptr_t Aimbot_get = get_Player(aimbot_currbone);
	
	//std::cout << Aimbot_get << std::endl;

	//std::cout << aimbot_currbone << std::endl;


	if (Aimbot_get) {

		auto bone_pos = GetBonePosImVec(Aimbot_get, aimbot_currbone);
		//DrawOutlinedText(ImGui::GetFont(), "Bone", bone_pos, 50, ImColor(120,120,120,255), true);


		float MaxSensi;

		if (aimbot_maxsensi) {
			MaxSensi = aimbot_smooth + 0.10;
		}
		else {
			MaxSensi = aimbot_smooth + 1.5;
		}

		float AimbSmt = MaxSensi;

		ImVec2 screen = bone_pos;

		auto center_x = (GetSystemMetrics(SM_CXSCREEN)) / 2;
		auto center_y = (GetSystemMetrics(SM_CYSCREEN)) / 2;
		auto fov = get_distance(center_x, center_y, screen.x, screen.y);
		float TargetX = 0;
		float TargetY = 0;

		if (screen.x != 0) {
			if (screen.x > center_x) {
				TargetX = -(center_x - screen.x);
				TargetX /= AimbSmt;
				if (TargetX + center_x > center_x * 2) TargetX = 0;
			}

			if (screen.x < center_x) {
				TargetX = screen.x - center_x;
				TargetX /= AimbSmt;
				if (TargetX + center_x < 0) TargetX = 0;
			}
		}

		if (screen.y != 0) {
			if (screen.y > center_y) {
				TargetY = -(center_y - screen.y);
				TargetY /= AimbSmt;
				if (TargetY + center_y > center_y * 2) TargetY = 0;
			}

			if (screen.y < center_y) {
				TargetY = screen.y - center_y;
				TargetY /= AimbSmt;
				if (TargetY + center_y < 0) TargetY = 0;
			}
		}

		Vec3 EntPos = read_mem<Vec3>(Aimbot_get + 0x90);

		Vec3 LocPos = read_mem<Vec3>(localplayer + 0x90);

		double distance = sqrt(pow(LocPos.x - EntPos.x, 2) + pow(LocPos.y - EntPos.y, 2) + pow(LocPos.y - EntPos.y, 2)) * 0.625;

		if (fov <= aimbot_fov_value + 0.10) {

			if (distance <= aimbot_max_distance) {

				if (GetKeyState(aim::bind) & 0x8000) {
					//cout << aim::bind << endl;
					mouse_event(MOUSEEVENTF_MOVE, float(TargetX), float(TargetY / 1), 0, 0);
				}

			}
		}
	}
}

void bindaimbot() {
	if (bind_aimbot == 0) { aim::bind = VK_RBUTTON; }
	else if (bind_aimbot == 1) { aim::bind = VK_LBUTTON; }
	else if (bind_aimbot == 2) { aim::bind = VK_XBUTTON1; }
	else if (bind_aimbot == 3) { aim::bind = VK_XBUTTON2; }
	else if (bind_aimbot == 4) { aim::bind = VK_SHIFT; }
	else if (bind_aimbot == 5) { aim::bind = VK_MENU; }
	else if (bind_aimbot == 6) { aim::bind = 0x45; }
}
