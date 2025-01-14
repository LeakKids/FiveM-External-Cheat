#pragma once
#include <string.h>  
#include <stdio.h>  
#include <locale.h>  
#include <tchar.h>
#include <vector>
#include <dwmapi.h>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <codecvt>
#include <sstream>
#include "include.h"
HANDLE process_handle;


struct module_t
{
	DWORD64 modBaseAddr, hModule, modBaseSize;
};

module_t base_address;
template <class t>
t read_mem(uintptr_t address) {
	t read;
	ReadProcessMemory(process_handle, (LPVOID)address, &read, sizeof(t), NULL);
	return read;
}

template <class T>
void write_mem(uintptr_t address, T value) {
	WriteProcessMemory(process_handle, (LPVOID)address, &value, sizeof(T), NULL);
}

module_t get_module_base64(uintptr_t pid, const wchar_t* module_name) {
	module_t module_ = { 0, 0, 0 };
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	if (snapshot == INVALID_HANDLE_VALUE) {
		wchar_t str[0xff];
		swprintf(str, 0xff, L"Failed to get %s, invalid handle value", module_name);
		MessageBoxW(0, str, L"ERROR", MB_OK | MB_ICONERROR);
		return module_;
	}

	MODULEENTRY32W module_entry;
	module_entry.dwSize = sizeof(MODULEENTRY32W);
	if (Module32FirstW(snapshot, &module_entry)) {
		do {
			if (_wcsicmp(module_entry.szModule, module_name) == 0) {
				module_ = { (DWORD64)module_entry.modBaseAddr, (DWORD64)module_entry.hModule, module_entry.modBaseSize };
				break;
			}
		} while (Module32NextW(snapshot, &module_entry));
	}
	CloseHandle(snapshot);
	return module_;
}

int getProcID(const std::wstring& p_name) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W structprocsnapshot = { 0 };
	structprocsnapshot.dwSize = sizeof(PROCESSENTRY32W);
	if (snapshot == INVALID_HANDLE_VALUE)
		return 0;
	if (Process32FirstW(snapshot, &structprocsnapshot) == FALSE)
		return 0;
	while (Process32NextW(snapshot, &structprocsnapshot)) {
		if (!wcscmp(structprocsnapshot.szExeFile, p_name.c_str())) {
			CloseHandle(snapshot);
			return structprocsnapshot.th32ProcessID;
		}
	}
	CloseHandle(snapshot);
	return 0;
}


bool isProcRunning(std::string process) {
	if (getProcID(std::wstring(process.begin(), process.end())) == 0) {
		return false;
	}
	else {
		return true;
	}
}