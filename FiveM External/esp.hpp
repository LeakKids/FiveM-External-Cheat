#pragma once 
#include "../vector.h"
#include <Windows.h>
#include <iostream>
#include <string> 
#include "../include/imgui/imgui.h"
#include "Render.hpp"
#include "include.h"
#include "include.h"
#include "offsets.h"
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

static std::string get_weapon_name(DWORD hash)
{
    static auto dagger = std::string("Dagger");
    static auto bat = std::string("Bat");
    static auto bottle = std::string("Bottle");
    static auto crowbar = std::string("Crowbar");
    static auto unarmed = std::string("Unarmed");
    static auto flashlight = std::string("Flashlight");
    static auto golfclub = std::string("Golf Club");
    static auto hammer = std::string("Hammer");
    static auto hatchet = std::string("Hatchet");
    static auto knuckle = std::string("Knuckle");
    static auto knife = std::string("Knife");
    static auto machete = std::string("Machete");
    static auto switchblade = std::string("Switch Blade");
    static auto nightstick = std::string("nightstick");
    static auto wrench = std::string("Wrench");
    static auto battleaxe = std::string("Battle Axe");
    static auto poolcue = std::string("Pool Cue");
    static auto pistol = std::string("Pistol");
    static auto pistolmk2 = std::string("Pistol MK2");
    static auto combatpistol = std::string("Combat Pistol");
    static auto appistol = std::string("AP Pistol");
    static auto stungun = std::string("Stungun");
    static auto pistol50 = std::string("Pistol .50");
    static auto snspistol = std::string("SNS Pistol");
    static auto snspistolmk2 = std::string("SNS Pistol MK2");
    static auto heavypistol = std::string("Heavy Pistol");
    static auto vintagepistol = std::string("Vintage Pistol");
    static auto flaregun = std::string("Flaregun");
    static auto marksmanpistol = std::string("Marksman Pistol");
    static auto revolver = std::string("Revolver");
    static auto revolvermk2 = std::string("Revolver MK2");
    static auto doubleaction = std::string("Double Action");
    static auto microsmg = std::string("Micro SMG");
    static auto smg = std::string("SMG");
    static auto smgmk2 = std::string("SMG MK2");
    static auto assaultsmg = std::string("Assault MG");
    static auto combatpdw = std::string("Combat PDW");
    static auto machinepistol = std::string("Machine Pistol");
    static auto minismg = std::string("Mini SMG");
    static auto pumpshotgun = std::string("Pump Shotgun");
    static auto pumpshotgun_mk2 = std::string("Pump Shotgun MK2");
    static auto sawnoffshotgun = std::string("Sawnoff Shotgun");
    static auto assaultshotgun = std::string("Assault Shotgun");
    static auto bullpupshotgun = std::string("Bullpup Shotgun");
    static auto musket = std::string("Musket");
    static auto heavyshotgun = std::string("Heavy Shotgun");
    static auto dbshotgun = std::string("DB Shotgun");
    static auto autoshotgun = std::string("Auto Shotgun");
    static auto assaultrifle = std::string("Assault Rifle");
    static auto assaultrifle_mk2 = std::string("Assault Rifle MK2");
    static auto carbinerifle = std::string("Carbine Rifle");
    static auto carbinerifle_mk2 = std::string("Carbine Rifle MK2");
    static auto advancedrifle = std::string("Advanced Rifle");
    static auto specialcarbine = std::string("Special Carbine");
    static auto specialcarbine_mk2 = std::string("Special Carbine MK2");
    static auto bullpuprifle = std::string("Bullpup Rifle");
    static auto bullpuprifle_mk2 = std::string("Bullpup Rifle MK2");
    static auto compactrifle = std::string("Compact Rifle");
    static auto machine_gun = std::string("Machine Gun");
    static auto combatmg = std::string("Combat MG");
    static auto combatmg_mk2 = std::string("Combat MG MK2");
    static auto gusenberg = std::string("Gusenberg");
    static auto sniperrifle = std::string("Sniper Rifle");
    static auto heavysniper = std::string("Heavy Sniper");
    static auto heavysniper_mk2 = std::string("Heavy Sniper MK2");
    static auto marksmanrifle = std::string("Marksman Rifle");
    static auto marksmanrifle_mk2 = std::string("Marksman Rifle MK2");
    static auto rpg = std::string("RPG");
    static auto grenadelauncher = std::string("Grenade Launcher");
    static auto grenadelauncher_smoke = std::string("Smoke Grenade Launcher");
    static auto minigun = std::string("Minigun");
    static auto firework = std::string("Firework");
    static auto railgun = std::string("Railgun");
    static auto hominglauncher = std::string("Homing Launcher");
    static auto compactlauncher = std::string("Compact Launcher");
    static auto grenade = std::string("Grenade");
    static auto bzgas = std::string("BZ Gas");
    static auto smokegrenade = std::string("Smoke Grenade");
    static auto flare = std::string("Flare");
    static auto molotov = std::string("Molotov");
    static auto stickybomb = std::string("Sticky Bomb");
    static auto proxmine = std::string("Proxmine");
    static auto snowball = std::string("Snowball");
    static auto pipebomb = std::string("Pipe Bomb");
    static auto ball = std::string("Ball");
    static auto petrolcan = std::string("Petrol Can");
    static auto fireextinguisher = std::string("Fire Extinguisher");
    static auto parachute = std::string("Parachute");
    switch (hash)
    {
    case 0x92A27487:
        return dagger; break;
    case 0x958A4A8F:
        return bat; break;
    case 0xF9E6AA4B:
        return bottle; break;
    case 0x84BD7BFD:
        return crowbar; break;
    case 0xA2719263:
        return unarmed; break;
    case 0x8BB05FD7:
        return flashlight; break;
    case 0x440E4788:
        return golfclub; break;
    case 0x4E875F73:
        return hammer; break;
    case 0xF9DCBF2D:
        return hatchet; break;
    case 0xD8DF3C3C:
        return knuckle; break;
    case 0x99B507EA:
        return knife; break;
    case 0xDD5DF8D9:
        return machete; break;
    case 0xDFE37640:
        return switchblade; break;
    case 0x678B81B1:
        return nightstick; break;
    case 0x19044EE0:
        return wrench; break;
    case 0xCD274149:
        return battleaxe; break;
    case 0x94117305:
        return poolcue; break;
    case 0x1B06D571:
        return pistol; break;
    case 0xBFE256D4:
        return pistolmk2; break;
    case 0x5EF9FEC4:
        return combatpistol; break;
    case 0x22D8FE39:
        return appistol; break;
    case 0x3656C8C1:
        return stungun; break;
    case 0x99AEEB3B:
        return pistol50; break;
    case 0xBFD21232:
        return snspistol; break;
    case 0x88374054:
        return snspistolmk2; break;
    case 0xD205520E:
        return heavypistol; break;
    case 0x83839C4:
        return vintagepistol; break;
    case 0x47757124:
        return flaregun; break;
    case 0xDC4DB296:
        return marksmanpistol; break;
    case 0xC1B3C3D1:
        return revolver; break;
    case 0xCB96392F:
        return revolvermk2; break;
    case 0x97EA20B8:
        return doubleaction; break;
    case 0x13532244:
        return microsmg; break;
    case 0x2BE6766B:
        return smg; break;
    case 0x78A97CD0:
        return smgmk2; break;
    case 0xEFE7E2DF:
        return assaultsmg; break;
    case 0xA3D4D34:
        return combatpdw; break;
    case 0xDB1AA450:
        return machinepistol; break;
    case 0xBD248B55:
        return minismg; break;
    case 0x1D073A89:
        return pumpshotgun; break;
    case 0x555AF99A:
        return pumpshotgun_mk2; break;
    case 0x7846A318:
        return sawnoffshotgun; break;
    case 0xE284C527:
        return assaultshotgun; break;
    case 0x9D61E50F:
        return bullpupshotgun; break;
    case 0xA89CB99E:
        return musket; break;
    case 0x3AABBBAA:
        return heavyshotgun; break;
    case 0xEF951FBB:
        return dbshotgun; break;
    case 0x12E82D3D:
        return autoshotgun; break;
    case 0xBFEFFF6D:
        return assaultrifle; break;
    case 0x394F415C:
        return assaultrifle_mk2; break;
    case 0x83BF0278:
        return carbinerifle; break;
    case 0xFAD1F1C9:
        return carbinerifle_mk2; break;
    case 0xAF113F99:
        return advancedrifle; break;
    case 0xC0A3098D:
        return specialcarbine; break;
    case 0x969C3D67:
        return specialcarbine_mk2; break;
    case 0x7F229F94:
        return bullpuprifle; break;
    case 0x84D6FAFD:
        return bullpuprifle_mk2; break;
    case 0x624FE830:
        return compactrifle; break;
    case 0x9D07F764:
        return machine_gun; break;
    case 0x7FD62962:
        return combatmg; break;
    case 0xDBBD7280:
        return combatmg_mk2; break;
    case 0x61012683:
        return gusenberg; break;
    case 0x5FC3C11:
        return sniperrifle; break;
    case 0xC472FE2:
        return heavysniper; break;
    case 0xA914799:
        return heavysniper_mk2; break;
    case 0xC734385A:
        return marksmanrifle; break;
    case 0x6A6C02E0:
        return marksmanrifle_mk2; break;
    case 0xB1CA77B1:
        return rpg; break;
    case 0xA284510B:
        return grenadelauncher; break;
    case 0x4DD2DC56:
        return grenadelauncher_smoke; break;
    case 0x42BF8A85:
        return minigun; break;
    case 0x7F7497E5:
        return firework; break;
    case 0x6D544C99:
        return railgun; break;
    case 0x63AB0442:
        return hominglauncher; break;
    case 0x781FE4A:
        return compactlauncher; break;
    case 0x93E220BD:
        return grenade; break;
    case 0xA0973D5E:
        return bzgas; break;
    case 0xFDBC8A50:
        return smokegrenade; break;
    case 0x497FACC3:
        return flare; break;
    case 0x24B17070:
        return molotov; break;
    case 0x2C3731D9:
        return stickybomb; break;
    case 0xAB564B93:
        return proxmine; break;
    case 0x787F0BB:
        return snowball; break;
    case 0xBA45E8B8:
        return pipebomb; break;
    case 0x23C9F95C:
        return ball; break;
    case 0x34A67B97:
        return petrolcan; break;
    case 0x60EC506:
        return fireextinguisher; break;
    case 0xFBAB5776:
        return parachute; break;
    default:
        return unarmed; break;
    }
}

uintptr_t WeaponManager = read_mem<uintptr_t>(localplayer + weaponmanager);
uintptr_t weaponinfo = read_mem<uintptr_t>(WeaponManager + 0x20);

D3DXVECTOR2 world_to_screen(D3DXVECTOR3 world_pos) {
    auto viewmatrix = read_mem<D3DXMATRIX>(viewport_ptr + 0x24C);

    D3DXMatrixTranspose(&viewmatrix, &viewmatrix);
    auto vec_x = D3DXVECTOR4(viewmatrix._21, viewmatrix._22, viewmatrix._23, viewmatrix._24),
        vec_y = D3DXVECTOR4(viewmatrix._31, viewmatrix._32, viewmatrix._33, viewmatrix._34),
        vec_z = D3DXVECTOR4(viewmatrix._41, viewmatrix._42, viewmatrix._43, viewmatrix._44);

    auto screen_pos = D3DXVECTOR3((vec_x.x * world_pos.x) + (vec_x.y * world_pos.y) + (vec_x.z * world_pos.z) + vec_x.w,
        (vec_y.x * world_pos.x) + (vec_y.y * world_pos.y) + (vec_y.z * world_pos.z) + vec_y.w,
        (vec_z.x * world_pos.x) + (vec_z.y * world_pos.y) + (vec_z.z * world_pos.z) + vec_z.w);

    if (screen_pos.z <= 0.1f)
        return D3DXVECTOR2(0, 0);

    screen_pos.z = 1.0f / screen_pos.z;
    screen_pos.x *= screen_pos.z;
    screen_pos.y *= screen_pos.z;

    auto width = GetSystemMetrics(SM_CXSCREEN);
    auto height = GetSystemMetrics(SM_CYSCREEN);
    float x_temp = width / 2;
    float y_temp = height / 2;

    screen_pos.x += x_temp + float(0.5f * screen_pos.x * width + 0.5f);
    screen_pos.y = y_temp - float(0.5f * screen_pos.y * height + 0.5f);
    return D3DXVECTOR2(screen_pos.x, screen_pos.y);
}

D3DXVECTOR3 get_bone_position(uintptr_t ped_ptr, int bone_id) {
    auto matrix = read_mem<D3DXMATRIX>(ped_ptr + 0x60);
    D3DXVECTOR3 bone;
    if (offset::detectv2802) {
        bone = read_mem<D3DXVECTOR3>(ped_ptr + (0x410 + 0x10 * bone_id));
    }
    else {
        bone = read_mem<D3DXVECTOR3>(ped_ptr + (0x430 + bone_id * 0x10));
    }
    D3DXVECTOR4 transform;
    D3DXVec3Transform(&transform, &bone, &matrix);
    return D3DXVECTOR3(transform.x, transform.y, transform.z);
}

D3DXVECTOR2 GetBonePosDX9(uintptr_t ped_base,int boneid) {
    D3DXVECTOR3 bonepos = get_bone_position(ped_base, boneid);
    return world_to_screen(bonepos);
}

ImVec2 GetBonePosImVec(uintptr_t ped_base, int boneid) {
    D3DXVECTOR3 bonepos = get_bone_position(ped_base, boneid);
    D3DXVECTOR2 world = world_to_screen(bonepos);
    return ImVec2(world.x, world.y);
}

ImVec2 ConvertVec2(D3DXVECTOR2 point) {
    return ImVec2(point.x, point.y);
}

D3DXVECTOR3 ConvertDxVec(Vec3 point) {
    return D3DXVECTOR3(point.x, point.y, point.z);
}

void draw_skeleton(uintptr_t ped_base,ImColor Cor) {
    int bone_positions[][2] = {
        { 0, 7 },
        { 7, 6 },
        { 7, 5 },
        { 7, 8 },
        { 8, 3 },
        { 8, 4 }
    };
    for (int i = 0; i < 6; ++i) {
        auto bone_1 = get_bone_position(ped_base, bone_positions[i][0]);
        auto bone_2 = get_bone_position(ped_base, bone_positions[i][1]);
        D3DXVECTOR2 screen_1 = world_to_screen(bone_1);
        D3DXVECTOR2 screen_2 = world_to_screen(bone_2);
        DrawLine(ImVec2(screen_1.x, screen_1.y), ImVec2(screen_2.x, screen_2.y), Cor, 1);
    }
}

float pythag(ImVec2 src, ImVec2 dst) {
    return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
}

auto get_distance = [](double x1, double y1, double x2, double y2) {
    return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
};

void DrawEsp() {

    auto center_y = (GetSystemMetrics(SM_CYSCREEN));
    auto center_x = (GetSystemMetrics(SM_CXSCREEN));

    uintptr_t PedReplayInterface = read_mem<uintptr_t>(ReplayInterface_ptr + 0x18);
    uintptr_t PedList = read_mem<uintptr_t>(PedReplayInterface + 0x100);

    for (int i = 0; i < 256; i++) {

        if (!PedList) continue;

        uintptr_t Ped = read_mem<uintptr_t>(PedList + (i * 0x10));
        auto pedType = read_mem<int>(Ped + 0x10b8) << 11 >> 25;

        if (!Ped) continue;

        if (esp_drawnpcs) {
            if (pedType != 2)
                continue;
        }

        if (localplayer != Ped) {



            ImColor SkelColor = Colors::ESPSkeleton;

            if (player_friend[i] == Ped) {
                SkelColor = ImColor(10, 10, 255, 255);
            }

            Vec3 EntPos = read_mem<Vec3>(Ped + 0x90);

            Vec3 LocPos = read_mem<Vec3>(localplayer + 0x90);

            float Health = read_mem<float>(Ped + 0x280);

            Vec3 DistanceCalculation = (LocPos - EntPos);

            double distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

            if (distance <= esp_max_distance) {

                ImVec2 Head = GetBonePosImVec(Ped, 0);
                ImVec2 Pelvis = GetBonePosImVec(Ped, 8);

                ImVec2 LeftFootpls = GetBonePosImVec(Ped, 1);
                ImVec2 RightFootpls = GetBonePosImVec(Ped, 2);

                float FootAdv = (LeftFootpls.y + RightFootpls.y) / 2;
                float height = fabs(Head.y - FootAdv) * 1.2;
                float width = height / 2.5;

                ImVec2 Ent2DPos = ConvertVec2(world_to_screen(ConvertDxVec(EntPos)));



                if (esp_corner) {
                    DrawCornerBox(ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y + height / 1.9), ImVec2(width, height), Colors::ESPCorner, 1);
                }

                if (esp_box) {
                    DrawBox(ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y - height / 2.11), ImVec2(width, height), Colors::ESPBox, 1);
                }

                if (filled_box) {
                    if (OnScreen(ImVec2(Ent2DPos.x - width / 2, Ent2DPos.y - height / 2))) {
                        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Ent2DPos.x - width / 2, Ent2DPos.y - height / 2.11), ImVec2(Ent2DPos.x + width / 2, Ent2DPos.y + height / 1.9), ImColor(0, 0, 0, 50));

                    }
                }

                if (esp_skeletons) {
                    draw_skeleton(Ped, SkelColor);
                }
                
                if (esp_head) {
                    ImVec2 Heads = GetBonePosImVec(Ped, 0);
                    int CircleValue = height / 10;
                    if (CircleValue <= 10) { height / 15; }
                    MakeCircle(ImVec2(Heads.x, Heads.y), CircleValue, Colors::ESPSkeleton);
                }

                if (esp_lines) {
                    auto center_y = (GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYSCREEN)) + 15;
                    auto center_x = ((GetSystemMetrics(SM_CXSCREEN) / 2));
                    ImVec2 ss = GetBonePosImVec(localplayer, 8);
                    DrawLine(ImVec2(ss), ImVec2(Pelvis), Colors::ESPLines, 1);
                }

                if (invisibility) {
                    write_mem<BYTE>(localplayer + 0x2C, 0x1);
                }

                if (infinitestamina) {
                    uintptr_t Playerinfo = read_mem<uintptr_t>(localplayer + 0x10C8);
                    write_mem<float>(Playerinfo + 0x0CF4, 100);


                }

                if (weapons)
                {
                    auto weapon_mgr = read_mem<uintptr_t>(Ped + weaponmanager);
                    if (weapon_mgr) {
                        auto weapon_current = read_mem<uintptr_t>(weapon_mgr + 0x20);
                        if (weapon_current) {
                            auto weapon_hash = read_mem<uintptr_t>(weapon_current + 0x10);
                            ImFont* font = ImGui::GetFont();
                            float yOffset = -5.0f;

                            DrawOutlinedText(font, get_weapon_name(weapon_hash), ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2 + 1 + yOffset), 8.0f, ImColor(255, 255, 255), true);
                            DrawOutlinedText(font, get_weapon_name(weapon_hash), ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2 + 1 + yOffset), 8.0f, ImColor(255, 255, 255), true);
                        }
                    }
                }

                if (esp_showid) {
                    std::string text = "ID: " + std::to_string(static_cast<int>(i));
                    float font_size = 18 * text.size() / 2;
                    DrawText2d(ImVec2(Head), Colors::ESPDistance, text.c_str());
                    //FilledBox(ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height), ImVec2((Ent2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ent2DPos.y + height / 4),ImColor(255,255,255));
                }


                if (esp_hpbar) {
                    float HealthPercentage = height / 100 * (Health);
                    float fixedhealth = Health - 100;
                    ImColor col;
                    if (fixedhealth >= 320 && fixedhealth <= 410) {
                        col = ImColor(81, 252, 141, 255);
                    }
                    else if (fixedhealth <= 320 && fixedhealth >= 240) {
                        col = ImColor(191, 245, 64, 255);
                    }
                    else if (fixedhealth <= 240 && fixedhealth >= 150) {
                        col = ImColor(221, 245, 64, 255);
                    }
                    else if (fixedhealth <= 150 && fixedhealth >= 60) {
                        col = ImColor(245, 79, 64, 255);
                    }
                    else if (fixedhealth <= 60 && fixedhealth >= 0) {
                        col = ImColor(81, 252, 141, 255);
                    }
                    else {
                        col = ImColor(81, 252, 141, 255);
                    }
                    DrawHealthBar(ImVec2(Ent2DPos.x + (width / 1.87), Ent2DPos.y + height / 1.9), ImVec2(4, (height / 100 * (100))), ImColor(10, 10, 10, 255), 2);
                    DrawHealthBar(ImVec2(Ent2DPos.x + (width / 1.87), Ent2DPos.y + height / 1.9), ImVec2(4, (HealthPercentage / 4)), col, 1.5);
                }



                if (esp_hptext) {
                    std::string text = "" + std::to_string(static_cast<int>(Health)) + " Hp ";
                    float font_size = 18 * text.size() / 2;
                    if (distance <= 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 14.0f, Colors::ESPHpText, true);
                    }
                    else if (distance <= 50 && distance > 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 13.0f, Colors::ESPHpText, true);
                    }
                    else if (distance <= 75 && distance > 50)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 12.0f, Colors::ESPHpText, true);
                    }
                    else if (distance <= 100 && distance > 75)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 11.0f, Colors::ESPHpText, true);
                    }
                    else
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y - height / 2), 10.0f, Colors::ESPHpText, true);
                    }
                }

                if (esp_showdistance) {
                    std::string text = "" + std::to_string(static_cast<int>(distance)) + " m ";
                    float font_size = 18 * text.size() / 2;
                    if (distance <= 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 14.0f, Colors::ESPDistance, true);
                    }
                    else if (distance <= 50 && distance > 25)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 13.0f, Colors::ESPDistance, true);
                    }
                    else if (distance <= 75 && distance > 50)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 12.0f, Colors::ESPDistance, true);
                    }
                    else if (distance <= 100 && distance > 75)
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 11.0f, Colors::ESPDistance, true);
                    }
                    else
                    {
                        DrawOutlinedText(ImGui::GetFont(), text, ImVec2(Ent2DPos.x, Ent2DPos.y + height / 2), 10.0f, Colors::ESPDistance, true);
                    }
                }
            }
        }
    }
}
