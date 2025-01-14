#pragma once
#include <windows.h>

namespace offset {
	bool detectv2802 = false;

	namespace b2802 {
		DWORD ReplayInterface_ptr = 0x1F5B820;
		DWORD world_ptr = 0x254D448;
		DWORD viewport_ptr = 0x1FBC100;
	}

	namespace b2699 {
		DWORD ReplayInterface_ptr = 0x20304C8;
		DWORD world_ptr = 0x26684D8;
		DWORD viewport_ptr = 0x20D8C90;
	}

	namespace b2612 {
		DWORD ReplayInterface_ptr = 0x1F77EF0;
		DWORD world_ptr = 0x2567DB0;
		DWORD viewport_ptr = 0x1FD8570;
	}

	namespace b2545 {
		DWORD ReplayInterface_ptr = 0x1F2E7A8;
		DWORD world_ptr = 0x25667E8;
		DWORD viewport_ptr = 0x1FD6F70;
	}

	namespace b2372 {
		DWORD ReplayInterface_ptr = 0x1F05208;
		DWORD world_ptr = 0x252DCD8;
		DWORD viewport_ptr = 0x1F9E9F0;
	}

	namespace b2189 {
		DWORD ReplayInterface_ptr = 0x1EE18A8;
		DWORD world_ptr = 0x24E6D90;
		DWORD viewport_ptr = 0x1F888C0;
	}

	namespace b2060 {
		DWORD ReplayInterface_ptr = 0x1EC3828;
		DWORD world_ptr = 0x24C8858;
		DWORD viewport_ptr = 0x1F6A7E0;
	}

	namespace b1604 {
		DWORD ReplayInterface_ptr = 0x1EFD4C8;
		DWORD world_ptr = 0x247F840;
		DWORD viewport_ptr = 0x2087780;
	}

}

/*
uintptr_t GWorldPattern = 48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81
uintptr_t GWorld = *(uint64_t*)(GWorldPattern + *(int*)(GWorldPattern + 0x3) + 0x7);

uintptr_t ReplayInterfacePattern = 48 8D 0D ?? ?? ?? ?? 89 44 24 30 E8 ?? ?? ?? ?? 48 83 C4 28 C3 48 8B 05
uintptr_t ReplayInterface = *(uint64_t*)(ReplayInterfacePattern + *(int*)(ReplayInterfacePattern + 0x3) + 0x7);

uintptr_t BonePattern = 48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC 60 48 8B 01 41 8B E8 48 8B F2 48 8B F9 33 DB

uintptr_t World2Pattern = 48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25

uintptr_t ViewportPattern = 48 8B 15 ?? ?? ?? ?? 48 8D 2D ?? ?? ?? ?? 48 8B CD
uintptr_t Viewport = *(uint64_t*)(ViewportPattern + *(int*)(ViewportPattern + 0x3) + 0x7);
*/