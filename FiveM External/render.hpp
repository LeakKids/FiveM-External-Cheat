#pragma once
#include <Windows.h>
#include <wincrypt.h>
#include <iostream>
#include "../include/imgui/imgui.h"

ImVec2 GetWindowSize();
ImDrawList* GetDrawList();
ImVec2 GetWindowMiddle();

// GetSystemMetrics(SM_CXSCREEN)
// if (coords.x < 0.1f || coords.y < 0.1 || coords.x > GetSystemMetrics(SM_CXSCREEN) || coords.y > GetSystemMetrics(SM_CYSCREEN))
bool OnScreen(ImVec2 coords) {
    if (coords.x < 0.1f || coords.y < 0.1 || coords.x >(GetWindowSize().x - 10) || coords.y >(GetWindowSize().y) - 10)
    {
        return false;
    }
    else {
        return true;
    }
}


void DrawCornerBox(ImVec2 pos, ImVec2 dim, ImColor col, int thickness) {
    if (OnScreen(pos)) {
        float cornersizex = dim.x / 4;
        float cornersizey = dim.y / 10;

        ImDrawList* drawlist = GetDrawList();

        drawlist->AddLine(ImVec2(pos), ImVec2(pos.x - cornersizex, pos.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2((pos.x - dim.x) + cornersizex, pos.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2(pos.x - dim.x, pos.y - cornersizey), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, (pos.y - dim.y)), ImVec2(pos.x - dim.x, (pos.y - dim.y) + cornersizey), col, thickness);

        drawlist->AddLine(ImVec2(pos.x - dim.x, (pos.y - dim.y)), ImVec2((pos.x - dim.x) + cornersizex, pos.y - dim.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x, (pos.y - dim.y)), ImVec2(pos.x - cornersizex, pos.y - dim.y), col, thickness);

        drawlist->AddLine(ImVec2(pos.x, (pos.y - dim.y)), ImVec2(pos.x, (pos.y - dim.y) + cornersizey), col, thickness);

        drawlist->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y - cornersizey), col, thickness);

    }
}

void DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center) {
    std::string line = text;
    int index = 0;

    ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

    if (center) {
        ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * index) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
        ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * index) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
        ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
    }
    else {
        ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * index) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
        ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * index) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
        ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
    }
}

void FilledBox(ImVec2 pos, ImVec2 dim, ImColor color) {
    if (OnScreen(pos)) {
        ImDrawList* drawlist = GetDrawList();
        drawlist->AddRectFilled(pos, dim, ImColor(0, 0, 0, 90), 1, 1);
        drawlist->AddRect(pos, dim, color, 1, 1, 1.7);
    }
}

void MakeCircle(ImVec2 pos, int dim, ImColor color) {
    if (OnScreen(pos)) {
        ImDrawList* drawlist = GetDrawList();
        drawlist->AddCircle(ImVec2(pos.x, pos.y), dim, color, 100, 1.0f);
    }
}

void DrawBox(ImVec2 pos, ImVec2 dim, ImColor color, int thickness) {
    if (OnScreen(pos))
    {
        GetDrawList()->AddLine(pos, ImVec2(pos.x - dim.x, pos.y), color, thickness);
        GetDrawList()->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2(pos.x - dim.x, pos.y + dim.y), color, thickness);
        GetDrawList()->AddLine(ImVec2(pos.x - dim.x, pos.y + dim.y), ImVec2(pos.x, pos.y + dim.y), color, thickness);
        GetDrawList()->AddLine(ImVec2(pos.x, pos.y + dim.y), ImVec2(pos.x, pos.y), color, thickness);
    }
}

void DrawLine(ImVec2 dst, ImVec2 src, ImColor col, int thickness) {
    if (OnScreen(dst) && OnScreen(src))
    {
        GetDrawList()->AddLine(src, dst, col, thickness);
    }
}

void DrawText2d(ImVec2 pos, ImColor col, const char* text) {
    if (OnScreen(pos)) {

        GetDrawList()->AddText(pos, col, text, 0);
    }
}

void DrawHealthBar(ImVec2 pos, ImVec2 dim, ImColor col, int sso) {
    if (OnScreen(pos))
    {
        GetDrawList()->AddLine(pos, ImVec2(pos.x - 0.5, pos.y - dim.y), col, sso);
    }
}

void DrawFilledCircle(ImVec2 pos, float radius, float segments, ImColor col) {
    GetDrawList()->AddCircleFilled(pos, radius, col, segments);
}

ImDrawList* GetDrawList() {
    return ImGui::GetOverlayDrawList();
}

bool IsFullscreen(HWND windowHandle) {
    MONITORINFO monitorInfo = { 0 };
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);

    RECT windowRect;
    GetWindowRect(windowHandle, &windowRect);

    return windowRect.left == monitorInfo.rcMonitor.left &&
        windowRect.right == monitorInfo.rcMonitor.right &&
        windowRect.top == monitorInfo.rcMonitor.top &&
        windowRect.bottom == monitorInfo.rcMonitor.bottom;
}

ImVec2 GetWindowSize() {
    RECT rect;
    HWND hwnd = GetActiveWindow();
    if (GetWindowRect(hwnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        if (IsFullscreen(hwnd))
        {
            return ImVec2(width, height);
        }
        return ImVec2((width - 17), (height - 35));
    }
    return ImVec2(0, 0);
}

ImVec2 GetWindowMiddle() {
    RECT rect;
    HWND hwnd = GetActiveWindow();
    if (GetWindowRect(hwnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        if (IsFullscreen(hwnd))
        {
            return ImVec2(width / 2, height / 2);
        }
        return ImVec2((width - 17) / 2, (height - 35) / 2);
    }
    return ImVec2(0, 0);
}
