#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "..\ImGui/imgui_settings.h"
#include "..\GameSDK\GameSDK.h"
#include "..\Menu\Misc\Render.h"
#include "Menu.h"
#include "..\Third Party\xor.h"
#include "..\Config/Config2.h"
#include "../Exploits/Exploits.h"
using namespace ImGui;

int number;

int confignum;
int rebrandcol = 0; 
int subtabss = 0;
int subtabsss = 0;

bool ua = false;

static bool rainbow = false;
int tabs = 1;

inline ImVec2 center_text(ImVec2 min, ImVec2 max, const char* text)
{
    return min + (max - min) / 2 - ImGui::CalcTextSize(text) / 2;
}
ImDrawList* drawlist;
ImVec2 pos;
static float animation = 0.f;
static bool shouldmove = true;

int lang = 0;

DWORD imgui_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static bool checkbox[50];
static int sliderscalar[100], combo = 0;
float col[4] = { 118 / 255.f, 187 / 255.f, 117 / 255.f, 0.5f };
int key = 0;
int k;

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

int tabb;
    
void Draw()
{
    if (GetAsyncKeyState(VK_F1) & 1)
        setVars(1);

    if (GetAsyncKeyState(VK_F2) & 1)
        setVars(2);

    if (GetAsyncKeyState(VK_F3) & 1)
        setVars(3);

    if (GetAsyncKeyState(VK_F4) & 1)
        setVars(4);

    if (GetAsyncKeyState(VK_F5) & 1)
        setVars(5);

    if (!Globals::Open)
        return;

    std::string label;

  
    label = xorstr_("Menu");



        ImGuiIO& IO = ImGui::GetIO();

        Menu::UpdateRainbowColor();
        if (rainbow)
            main_color = { Menu::Rainbow[0], Menu::Rainbow[1] ,Menu::Rainbow[2], 255 };

        if (ImGui::Begin(xorstr_("erdgergdtgd"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground)) {
            ImGui::StyleColorsDark();
            animation = 140.f;  /*ImLerp(animation, shouldmove ? 0.f : 140.f, g.IO.DeltaTime * 6.f);*/
            ImGui::SetWindowSize(ImVec2(1110.f + animation, 620.f));
            ImGuiContext& g = *GImGui;
            drawlist = ImGui::GetWindowDrawList();
            pos = ImGui::GetWindowPos() + ImVec2(5, 5);
            

            drawlist->AddRectFilled(pos, ImVec2(pos.x + 750.f + animation, pos.y + 610.f), ImColor(17, 17, 17, 255), 4.f, ImDrawFlags_RoundCornersAll);
            //subtabs & actual tab title
            drawlist->AddRectFilled(pos, ImVec2(pos.x + 50.f + animation, pos.y + 50.f), ImColor(23, 23, 23, 255), 4.f, ImDrawFlags_RoundCornersTop); //bg

            drawlist->AddRectFilled(ImVec2(pos.x + 800.f + animation , pos.y + 100.f), ImVec2(pos.x + 800.f + animation, pos.y + 200.f), ImColor(17, 17, 17, 255), 4.f, ImDrawFlags_RoundCornersAll);


            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.f, 0.f, 0.f, 0.f));
            ImGui::SetCursorPos(ImVec2(5, 5));
            ImGui::BeginChild(xorstr_("Tabs"), ImVec2(50.f + animation, 610.f));
            {
                if (ImGui::Tabs(label.c_str(), xorstr_("Black Ops 6"), xorstr_("A"), ImVec2(50.f + animation, 50.f), shouldmove == true)) shouldmove = true;
                if (ImGui::Tabs(xorstr_("Aimbot"), xorstr_("Lock On To Entitys"), xorstr_("B"), ImVec2(50.f + animation, 50.f), tabs == 1)) { tabs = 1; shouldmove = true; };
                if (ImGui::Tabs(xorstr_("ESP"), xorstr_("Visualise Entitys"), xorstr_("C"), ImVec2(50.f + animation, 50.f), tabs == 2)) { tabs = 2; shouldmove = true; };             
                if (ImGui::Tabs(xorstr_("Colors"), xorstr_("Change Visuals Colors"), xorstr_("E"), ImVec2(50.f + animation, 50.f), tabs == 4)) { tabs = 4; shouldmove = true; };
                if (ImGui::Tabs(xorstr_("Lobby Info"), xorstr_("View Info On Players"), xorstr_("D"), ImVec2(50.f + animation, 50.f), tabs == 5)) { tabs = 5; shouldmove = true; };
                if (ImGui::Tabs(xorstr_("Miscellaneous"), xorstr_("Game / Lobby Exploits"), xorstr_("J"), ImVec2(50.f + animation, 50.f), tabs == 6)) { tabs = 6; shouldmove = true; };
                if (ImGui::Tabs(xorstr_("Settings"), xorstr_("Save / Load Configs"), xorstr_("H"), ImVec2(50.f + animation, 50.f), tabs == 7)) { tabs = 7; shouldmove = true; };
             //  if (ImGui::Tabs(xorstr_("Loot"), xorstr_("fgdfgv"), xorstr_("H"), ImVec2(50.f + animation, 50.f), tabs == 8)) { tabs = 8; shouldmove = true; };

            }
            ImGui::EndChild();
            ImGui::PopStyleVar();

            //Sub Tabs Drawing
            if (tabs == 1)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
                ImGui::SetCursorPos(ImVec2(50.f + animation, 5.f));
                ImGui::BeginGroup();
                {
                    if (ImGui::Subtabs("Aimbot", ImVec2(233.3333333f, 50.f), subtabss == 0)) subtabss = 0;
                    if (ImGui::Subtabs("Override", ImVec2(233.3333333f, 50.f), subtabss == 1)) subtabss = 1;
                    if (ImGui::Subtabs("Miscellaneous", ImVec2(233.3333333f, 50.f), subtabss == 2)) subtabss = 2;
                }
                ImGui::EndGroup();
                ImGui::PopStyleVar();
            }

            if (tabs == 2)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
                ImGui::SetCursorPos(ImVec2(50.f + animation, 5.f));
                ImGui::BeginGroup();
                {
                    if (ImGui::Subtabs("Entitys", ImVec2(116.f, 50.f), subtabsss == 0)) subtabsss = 0;
                    if (ImGui::Subtabs("Uav / Compass", ImVec2(116.f, 50.f), subtabsss == 1)) subtabsss = 1;
                    if (ImGui::Subtabs("Chams", ImVec2(116.f, 50.f), subtabsss == 2)) subtabsss = 2;
                    if (ImGui::Subtabs("Miscellaneous", ImVec2(116.f, 50.f), subtabsss == 3)) subtabsss = 3;
                    if (ImGui::Subtabs("Screen", ImVec2(116.f, 50.f), subtabsss == 4)) subtabsss = 4;
                    if (ImGui::Subtabs("Loot", ImVec2(116.f, 50.f), subtabsss == 5)) subtabsss = 5;

                }
                ImGui::EndGroup();
                ImGui::PopStyleVar();

            }

            ImGui::SetCursorPos(ImVec2(55.f + animation, 20.f));
            ImGui::BeginChild(xorstr_("fgtf4reftrdrfg"), ImVec2(750.f + animation, 610.f));
            {
                ImGui::PushFont(Font::functionfont);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(23, 23, 23, 255)));
                std::vector<std::vector<std::string>> Auto = {
                    //////////////////////////
                    /////////Targating////////
                    //////////////////////////
                    { xorstr_("Visible Only"), xorstr_("In Gulag"), xorstr_("Teammates"), xorstr_("Self Reviving"), xorstr_("Riot Shielders"), xorstr_("Being Revived"), xorstr_("Enemy Players"), xorstr_("In Gulag Match"), xorstr_("Downed Players"), },

                    //////////////////////////
                    ///////General ESP////////
                    //////////////////////////
                    { xorstr_("Enable"), xorstr_("Draw KD"), xorstr_("Draw FOV"), xorstr_("Draw Ping"), xorstr_("Draw Kills"), xorstr_("Draw Rank"), xorstr_("Draw Score"), xorstr_("Draw Name"), xorstr_("Draw Health"), xorstr_("Draw Assists"), xorstr_("Draw Deaths"), xorstr_("Draw TeamID"), xorstr_("Draw Weapon"), xorstr_("Draw Damage"), xorstr_("Draw Distance"), xorstr_("Draw Skeleton"), xorstr_("Draw Snap Lines"),},
                    { xorstr_("Enable Visuals"), xorstr_("Draw Players KD"), xorstr_("Draw FOV Circle"), xorstr_("Draw Players Ping"), xorstr_("Draw Players Kills"), xorstr_("Draw Players Rank"), xorstr_("Draw Players Score"), xorstr_("Draw Players Name"), xorstr_("Draw Players Health"), xorstr_("Draw Players Assists"), xorstr_("Draw Players Deaths"), xorstr_("Draw Players TeamID"), xorstr_("Draw Players Weapon"), xorstr_("Draw Players Damage"), xorstr_("Draw Players Distance"), xorstr_("Draw Players Skeleton"), xorstr_("Draw Player Snap Line") },

                    //////////////////////////
                    ///////Visual Checks//////
                    //////////////////////////
                    { xorstr_("Player KD"), xorstr_("Player Box"), xorstr_("Player Ping"), xorstr_("Player Kills"), xorstr_("Player Rank"), xorstr_("Player Score"), xorstr_("Player Name"), xorstr_("Player Health"), xorstr_("Player Assists"), xorstr_("Player Deaths"), xorstr_("Player TeamID"), xorstr_("Player Weapon"), xorstr_("Player Damage"), xorstr_("Player Distance"), xorstr_("Player Skeleton"), xorstr_("Player Snap Lines"), xorstr_("Players Spectating"), },
                    { xorstr_("Max Drawing Distance For KD"), xorstr_("Max Drawing Distance For Box"), xorstr_("Max Drawing Distance For Ping"), xorstr_("Max Drawing Distance For Kills"), xorstr_("Max Drawing Distance For Rank"), xorstr_("Max Drawing Distance For Score"), xorstr_("Max Drawing Distance For Name"), xorstr_("Max Drawing Distance For Health"), xorstr_("Max Drawing Distance For Assists"), xorstr_("Max Drawing Distance For Deaths"), xorstr_("Max Drawing Distance For TeamID"), xorstr_("Max Drawing Distance For Weapon"), xorstr_("Max Drawing Distance For Damage"), xorstr_("Max Drawing Distance For Distance"), xorstr_("Max Drawing Distance For Skeleton"), xorstr_("Max Drawing Distance For Snaplines"), xorstr_("Disable Visuals While Being Spectated"), },

                    //////////////////////////
                    //////Bullet Tracers//////
                    //////////////////////////
                    {  xorstr_("Hit Objects"), xorstr_("Hit Players"), xorstr_("Player Tracers") },
                    {  xorstr_("Draw Tracers When You Hit Objects"), xorstr_("Draw Tracers When You Hit Players"), xorstr_("Draw Only Your Tracers") },

                    //////////////////////////
                    /////////Outlines/////////
                    //////////////////////////
                    { xorstr_("Enable"), xorstr_("Render Type"), xorstr_("Outline Width"), xorstr_("Fill Outlines"), xorstr_("Visible Outlines"), xorstr_("Invisible Outlines"), },
                    { xorstr_("Activate Player Outlines"), xorstr_("Change How Outlines Are Rendered"), xorstr_("Change How Thick Outliines Are"), xorstr_("Fill Player Outlines"), xorstr_("Outline Players Who Are Visible"), xorstr_("Outline Players Who Are Invisible"),},

                    //////////////////////////
                    /////////Exploits/////////
                    //////////////////////////
                    { xorstr_("Third Person"), xorstr_("Night Vision"), xorstr_("No ShellShock"), xorstr_("Dynamic Third Person"),},
                    { xorstr_("Sets Your Players Camera In Third Person"), xorstr_("Puts Night Vision Goggles On"), xorstr_("Removes Stun, Flash, And Gas Gernade Effects"), xorstr_("Third Person But, Allows You To ADS Normally"), },

                    //////////////////////////
                    /////////Commands/////////
                    //////////////////////////
                    { xorstr_("No Fog"), xorstr_("Draw FPS"), xorstr_("Break Camera"), xorstr_("Swap Loadouts"), xorstr_("No Shield Shake"), xorstr_("Developer Playlist"), xorstr_("In Game Crosshair"), xorstr_("Profanity Name Bypass"), xorstr_("Bypass Private Matches"), },
                    { xorstr_("Removes Any Fog In The Game, Not Smoke"), xorstr_("Draw A More Accurate FPS In The Top Right"), xorstr_("Breaks Your Player Camera"), xorstr_("Swap Warzone And Multi Player Loadouts"), xorstr_("Removes Shaking Effect When Using A Riot Shield"), xorstr_("Enable The Games Developer Playlist"), xorstr_("Disable The In Game Crosshair"), xorstr_("Allows You To Set Your Name To Profanity"), xorstr_("Bypass Private Match Player Count"), },

                    //////////////////////////
                    /////////Drawing//////////
                    //////////////////////////
                    { xorstr_("Visible Only"), xorstr_("In Gulag"), xorstr_("Teammates"), xorstr_("Self Reviving"), xorstr_("Riot Shielders"), xorstr_("Being Revived"), xorstr_("Enemy Players"),  xorstr_("In Gulag Match"), xorstr_("Downed Players"), },
                };

                if (tabs == 1) //aimbot
                {
                    const char* Bone[14] = { xorstr_("Head"), xorstr_("Neck"),xorstr_("Spine"), xorstr_("Left Shoulder"), xorstr_("Right Shoulder"), xorstr_("Left Elbow"), xorstr_("Right Elbow"), xorstr_("Left Wrist"), xorstr_("Right Wrist"), xorstr_("Hips"), xorstr_("Left Knee"), xorstr_("Right Knee"), xorstr_("Left Ankle"), xorstr_("Right Ankle") };
                    const char* AimType[4] = { xorstr_("Smart"), xorstr_("Health"), xorstr_("Distance"), xorstr_("FOV") };
                    const char* FovStyle[2] = { xorstr_("Static"), xorstr_("Dynamic") };
                    const char* Targeting[3] = { xorstr_("Closest Distance"), xorstr_("In Fov") , xorstr_("Smart Check") };
                   
                    if (subtabss == 0) {

                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                        ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("General"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable Aimbot"), &Aimbot::Enable);
                                ImGui::Keybind(xorstr_("Aimbot Key"), &KeyBinds::Aimbot);
                                ImGui::Checkbox(xorstr_("Silent Aim"), &Aimbot::Silent);
                                if (!Aimbot::Silent) {
                                    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                                }
                                ImGui::Checkbox(xorstr_("Enable Miss Chance"), &Aimbot::Enable_MissChance);
                                if (!Aimbot::Silent) {
                                    ImGui::PopItemFlag();
                                    ImGui::PopStyleVar();
                                }
                                if (!Aimbot::Enable_MissChance) {
                                    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                                }
                                ImGui::SliderInt(xorstr_("Miss Chance"), &Aimbot::Miss_Chance, 1, 100, "%d Percent");
                                if (!Aimbot::Enable_MissChance) {
                                    ImGui::PopItemFlag();
                                    ImGui::PopStyleVar();
                                }
                                ImGui::SliderFloat(xorstr_("Prediction Strength"), &Aimbot::Strength, 0.0f, 2.0f, xorstr_("%.01f"));
                     
                                if (ImGui::SliderFloat(xorstr_("Smoothing"), &Aimbot::Smoothingx, 0.0f, 100.0f, xorstr_("%1.0f")))
                                {
                                    Aimbot::Smoothingy = Aimbot::Smoothingx;
                                    Aimbot::Smoothingz = Aimbot::Smoothingx;
                                }
                                ImGui::SliderFloat(xorstr_("Field of View"), &Aimbot::FOV, 0.0f, 180.0f, xorstr_("%1.0f"));
                                ImGui::Checkbox(xorstr_("Bone Scan"), &cfg::Aimbot::Targeting::BoneScan);
                                if (!cfg::Aimbot::Targeting::BoneScan)                           
                                    ImGui::Combo(xorstr_("Aimbot Bone"), &Aimbot::Bone, Bone, IM_ARRAYSIZE(Bone));
                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360.f, 50.f));

                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            //title
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Targeting"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                            ImGui::BeginGroup();
                            {
                                ImGui::Combo(xorstr_("Priority Type"), &cfg::Aimbot::Targeting::Type, Targeting, IM_ARRAYSIZE(Targeting));
                                ImGui::SliderInt(xorstr_("Target Switch Delay"), &Aimbot::switch_delay, 0, 1000, "%d Ms");
                                ImGui::Checkbox(xorstr_("Disable On Kill"), &Aimbot::Disable_on_kill);

           

                                ImGui::Checkbox(xorstr_("Dynamic FOV Circle"), &Aimbot::DynamicFOV);

                                ImGui::SliderInt(xorstr_("Max Distance"), &Aimbot::Checks::Distance, 1, 400, "%d Metres");
                                ImGui::Checkbox(xorstr_("Ignore Team"), &Aimbot::Targeting::Teamates);
                                ImGui::Checkbox(xorstr_("Ignore Invis"), &Aimbot::Targeting::Visible);
                                ImGui::Checkbox(xorstr_("Ignore Downed"), &Aimbot::Targeting::Downed);
                                ImGui::Checkbox(xorstr_("Ignore Bots / Zombies"), &Aimbot::Targeting::Bots);

                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();
                    }
                   
                    if (subtabss == 1) {
                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                        ImGui::BeginChild(xorstr_("Child2"), ImVec2(320.f, 530.f));
                        {
                            //title
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Aimbot Overide"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable Override"), &Aimbot::Overide::Enable);               
                                ImGui::Keybind(xorstr_("Overide Aimbot Key"), &KeyBinds::Overide);
                                ImGui::SliderFloat(xorstr_("Override Smoothing"), &Aimbot::Overide::Smoothing, 0.0f, 100.0f, xorstr_("%1.0f"));
                                ImGui::Combo(xorstr_("Override Target Bone"), &Aimbot::Overide::Bone, Bone, IM_ARRAYSIZE(Bone));
                           
                                  
                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360.f, 50.f));

                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            //title
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Health Override"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable Health Override"), &cfg::Aimbot::Health_Override::Enable);
                                ImGui::SliderInt(xorstr_("Health Amount Trigger"), &cfg::Aimbot::Health_Override::Health_Trigger, 1, 127, xorstr_("%d"));
                                ImGui::Combo(xorstr_("Override Bone"), &cfg::Aimbot::Health_Override::Bone, Bone, IM_ARRAYSIZE(Bone));
                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                    }
                    
                    if (subtabss == 2) {
                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                        ImGui::BeginChild(xorstr_("Child2"), ImVec2(320.f, 530.f));
                        {
                            //title
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Misc"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Reduce Recoil"), &Aimbot::Accuracy::NoRecoil);
                                ImGui::SliderFloat(xorstr_("Recoil Reduction"), &Aimbot::Accuracy::Strength, 0.0f, 99.0f, xorstr_("%.0f%%"));
                                ImGui::Checkbox(xorstr_("Rapid Fire"), &Aimbot::RapidFire);
                                ImGui::SliderInt(xorstr_("Rapid Fire Shot Delay"), &cfg::Exploits::Rapid_fire::Shot_Delay, 0, 1000, "%dMs");
                                ImGui::Checkbox(xorstr_("Auto Shoot"), &Aimbot::AutoShoot);
                                ImGui::Checkbox(xorstr_("Disable While Spectated"), &Aimbot::Ignore_While_Spectated);
                                ImGui::SliderInt(xorstr_("Min Spectators"), &Aimbot::Spectator_Count, 1, 15, "%d+ Spectators");
                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360.f, 50.f));

                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            //title
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Auto Reload"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable Auto Reload"), &cfg::Exploits::Auto_Reload::Enable);
                                ImGui::Checkbox(xorstr_("Disable When Looked At"), &cfg::Exploits::Auto_Reload::Stop_When_In_View);
                                ImGui::Checkbox(xorstr_("Disable When Targeting"), &cfg::Exploits::Auto_Reload::Stop_When_Targeting);
                                ImGui::SliderInt(xorstr_("Reload AR At"), &cfg::Exploits::Auto_Reload::Bullet_Count_AR, 0, 30, "%d Bullets");
                                ImGui::SliderInt(xorstr_("Reload Sniper At"), &cfg::Exploits::Auto_Reload::Bullet_Count_Sniper, 0, 5, "%d Bullets");
                                ImGui::SliderInt(xorstr_("Reload LMG At"), &cfg::Exploits::Auto_Reload::Bullet_Count_LMG, 0, 30, "%d Bullets");
                                ImGui::SliderInt(xorstr_("Reload SMG At"), &cfg::Exploits::Auto_Reload::Bullet_Count_SMG, 0, 30, "%d Bullets");
                                ImGui::SliderInt(xorstr_("Reload Pistol At"), &cfg::Exploits::Auto_Reload::Bullet_Count_Pistol, 0, 15, "%d Bullets");
                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                    }
                 
                }

                if (tabs == 2) //PLayer Esp
                {
                    const char* snaplinepos[9] = { xorstr_("Top Middle"), xorstr_("Bottom Middle") , xorstr_("Centre Screen"), xorstr_("Centre Right") , xorstr_("Centre Left"), xorstr_("Top Right") , xorstr_("Top Left") , xorstr_("Bottom Right"), xorstr_("Bottom Left") };
                    const char* BoxType[2] = { xorstr_("Full"), xorstr_("Cornered") };
                    const char* healthtype[2] = { xorstr_("Left Side"), xorstr_("Right Side") };
                    const char* b_crosshairswitch[5] = { xorstr_("Cross"), xorstr_("dot"), xorstr_("Circle"), xorstr_("Smiley Face"), xorstr_("diamond") };
                    const char* type[2] = { xorstr_("Directional"), xorstr_("Non Directional") };
                    const char* Posistion[2] = { xorstr_("Lock With FOV Circle"), xorstr_("Use Custom Size") };

                    if (subtabsss == 0) {

                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                        ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("General"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                              
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable Visuals"), &Visuals::Main::Enable);                       
                                ImGui::Checkbox(xorstr_("Box"), &Visuals::Main::Draw_Box);
                                ImGui::Checkbox(xorstr_("Bones"), &Visuals::Main::DrawPlayerSkeleton);
                                ImGui::Checkbox(xorstr_("Health"), &Visuals::Main::DrawPlayerHealth);
                                ImGui::Checkbox(xorstr_("Name"), &Visuals::Main::DrawPlayerName);
                                ImGui::Checkbox(xorstr_("Weapon"), &Visuals::Main::DrawPlayerWeapon);
                                ImGui::Checkbox(xorstr_("Team ID"), &Visuals::Main::DrawPlayerTeamID);
                                ImGui::Checkbox(xorstr_("Snap Lines"), &Visuals::Main::DrawPlayerSnaplines);
                                ImGui::Checkbox(xorstr_("Distance"), &Visuals::Main::DrawPlayerDistance);
                                ImGui::Checkbox(xorstr_("Platform"), &cfg::Esp::Platform);
                                ImGui::Checkbox(xorstr_("Input Device"), &cfg::Esp::Device);
                                ImGui::Checkbox(xorstr_("Is Talking"), &cfg::Esp::Talking);
                            }
                                
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360.f, 50.f));

                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Settings"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));

                            ImGui::BeginGroup();
                            {

                                ImGui::Checkbox(xorstr_("ESP Filled"), &Visuals::Main::filled);
                                ImGui::SliderFloat(xorstr_("Bone Thickness"), &Visuals::Main::Drawing::Bonethicness, 0.0f, 5.0f, xorstr_("%0.1f Pixels"));
                                ImGui::SliderFloat(xorstr_("Max Distance"), &Visuals::Main::Drawing::all, 0.0f, 400.0f, xorstr_("%1.0f Metres"));
                                ImGui::Combo(xorstr_("Snapline POS"), &cfg::Esp::Drawing_Settings::Snapline_Pos, snaplinepos, IM_ARRAYSIZE(snaplinepos), 9);
                                ImGui::Combo(xorstr_("Box Type"), &cfg::Esp::Drawing_Settings::box_Type, BoxType, IM_ARRAYSIZE(BoxType));
                                ImGui::Checkbox(xorstr_("Ignore Team"), &Visuals::Main::Drawing::Teamates);
                                ImGui::Checkbox(xorstr_("Ignore Invis"), &Visuals::Main::Drawing::Visible);
                                ImGui::Checkbox(xorstr_("Ignore Downed"), &Visuals::Main::Drawing::Downed);
                                ImGui::Checkbox(xorstr_("Ignore Bots / Zombies"), &Visuals::Main::Drawing::Bots);

                            }
                            ImGui::EndGroup();

                        }
                        ImGui::EndChild();
                    }
                    if (subtabsss == 1) {

                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                       
                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Compass"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));

                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable Compass"), &Visuals::Miscellaneous::Compass::Enable);
                                ImGui::Checkbox(xorstr_("Compass Fill"), &Visuals::Miscellaneous::Compass::Fill);
                                ImGui::SliderInt(xorstr_("Compass Size"), &Visuals::Miscellaneous::Compass::Size, 0, 180);
                                ImGui::SliderInt(xorstr_("Triangle Size"), &Visuals::Miscellaneous::Compass::TriangleSize, 0, 100);
                                ImGui::Combo(xorstr_("Compass Posistion"), &Visuals::Miscellaneous::Compass::PosistionType, Posistion, IM_ARRAYSIZE(Posistion), 2);
                                ImGui::SliderFloat(xorstr_("Compass Max Distance"), &Visuals::Miscellaneous::Compass::Distance, 0.0f, 400.0f, xorstr_("%1.0fM"));
                                ImGui::Checkbox(xorstr_("Ignore Team"), &Visuals::Miscellaneous::Compass::Drawing::Teamates);
                                ImGui::Checkbox(xorstr_("Ignore Invis"), &Visuals::Miscellaneous::Compass::Drawing::Visible);
                                ImGui::Checkbox(xorstr_("Ignore Downed"), &Visuals::Miscellaneous::Compass::Drawing::Downed);
                                ImGui::Checkbox(xorstr_("Ignore Bots / Zombies"), &Visuals::Miscellaneous::Compass::Drawing::Bots);

                            }

                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();
                    }
                    if (subtabsss == 2) {

                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                        ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Player Chams"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));

                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable"), &Visuals::Outlines::Player::Enable);
                                ImGui::Checkbox(xorstr_("Fill"), &Visuals::Outlines::Player::Fill);
                                ImGui::SliderInt(xorstr_("Render Type"), &Visuals::Outlines::Player::Type, 0, 25, xorstr_("%d"));
                                ImGui::SliderInt(xorstr_("Outline Width"), &Visuals::Outlines::Player::Width, 0, 25, xorstr_("%d"));
                                ImGui::ColorEdit4(xorstr_("Player chams Color"), Color::ChamsVec4[0], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            }

                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360.f, 50.f));

                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Self Chams"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15, 60));

                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable"), &Visuals::Outlines::Self::Enable);
                                ImGui::Checkbox(xorstr_("Fill"), &Visuals::Outlines::Self::Fill);
                                ImGui::SliderInt(xorstr_("Render Type"), &Visuals::Outlines::Self::Type, 0, 25, xorstr_("%d"));
                                ImGui::SliderInt(xorstr_("Outline Width"), &Visuals::Outlines::Self::Width, 0, 25, xorstr_("%d"));
                                ImGui::ColorEdit4(xorstr_("Self chams Color"), Color::ChamsVec4[1], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);

                            }

                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();
                    }
                    if (subtabsss == 3) {

                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                        ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("FOV Circle / Crosshair"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));

                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("FOV Circle"), &Visuals::Main::DrawFOV);
                                ImGui::ColorEdit4(xorstr_("FOV Circle Color"), Color::FOV, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                                ImGui::Checkbox(xorstr_("Crosshair Cross"), &Visuals::Main::DrawCrosshair);
                                ImGui::Checkbox(xorstr_("Crosshair Dot"), &cfg::Crosshair::enabledot);
                                ImGui::Checkbox(xorstr_("Rotating Crosshair"), &cfg::Crosshair::spin);
                                ImGui::SliderFloat(xorstr_("Rotation Speed"), &cfg::Crosshair::speed, 0.1f, 10.0f, xorstr_("%0.1f"));
                                ImGui::SliderFloat(xorstr_("Crosshair Thickness"), &Visuals::Main::crosshair_thickness, 0.1f, 10.0f, xorstr_("%0.1f Pixels"));
                                ImGui::SliderFloat(xorstr_("Line Length"), &cfg::Crosshair::linelength, 0.0f, 50.0f, xorstr_("%0.1f Pixels"));
                                ImGui::SliderFloat(xorstr_("Line Gap"), &cfg::Crosshair::linegap, 2.0f, 50.0f, xorstr_("%0.1f Pixels"));
                                ImGui::ColorEdit4(xorstr_("Crosshair Color"), Color::crosshair, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            }

                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360.f, 50.f));

                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Target"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));

                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Target Snap Lines"), &cfg::Aim_Target::Target_SnapLine);
                                ImGui::ColorEdit4(xorstr_("Target ESP Color"), cfg::Aim_Target::Color::Target_Esp, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
                                ImGui::ColorEdit4(xorstr_("Target Crosshair Color"), cfg::Aim_Target::Color::Target_Crosshair, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
                                ImGui::ColorEdit4(xorstr_("Target FOV Color"), cfg::Aim_Target::Color::Target_FOV, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
                            }

                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                    }
                    if (subtabsss == 4) {

                        ImGui::SetCursorPos(ImVec2(20.f, 50.f));
                        ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Tracers"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));

                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable"), &Visuals::Miscellaneous::Tracers::Enable);
                                for (int i = 0; i < Auto[6].size(); ++i) {
                                    ImGui::Checkbox(Auto[6][i].c_str(), Visuals::Miscellaneous::Tracers::Array[i]);
                                }

                                ImGui::SliderInt(xorstr_("Tracer Fade Time"), &Visuals::Miscellaneous::Tracers::FadeInTime, 1, 5000, "%d Ms");
                                ImGui::SliderFloat(xorstr_("Tracer Thickness"), &Visuals::Miscellaneous::Tracers::TracerThickness, 0.0f, 5.0f, "%.1f");
                                ImGui::ColorEdit4(xorstr_("Tracer Color"), Visuals::Miscellaneous::Tracers::Tracer_Col, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);

                            }

                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360.f, 50.f));

                        ImGui::BeginChild(xorstr_("Child4"), ImVec2(320.f, 530.f));
                        {
                            ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                            ImGui::Text(xorstr_("Aim Warnings"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15.f, 60.f));

                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enemy Looking At You"), &Aim_Warning::Looking_At_You);
                                ImGui::SliderInt(xorstr_("Looking At You Max Distance"), &Aim_Warning::Looking_Max_Distance, 5, 400, "%d Metres");
                                ImGui::ColorEdit4(xorstr_("Looking At You"), Aim_Warning::LookingAtYou, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                                ImGui::Checkbox(xorstr_("Enemy Aiming At You"), &Aim_Warning::Aiming_At_You);
                                ImGui::SliderInt(xorstr_("Aiming At You Max Distance"), &Aim_Warning::Aiming_Max_distance, 5, 400, "%d Metres");
                                ImGui::ColorEdit4(xorstr_("Looking At You"), Aim_Warning::AimingAtYou, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            }

                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();
                    }
                    if (subtabsss == 5) //MISC
                    {
                        ImGui::SetCursorPos(ImVec2(20, 50));
                        ImGui::BeginChild(xorstr_("Child0"), ImVec2(320, 530));
                        {

                            ImGui::SetCursorPos(ImVec2(15, 15));
                            ImGui::Text(xorstr_("Loot Esp"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15, 60));
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Enable Loot ESP"), &loot_esp::enable);

                                ImGui::Checkbox(xorstr_("Weapons"), &loot_esp::weapons);
                                ImGui::Checkbox(xorstr_("Weapon Crates"), &loot_esp::weapon_crates);
                                ImGui::Checkbox(xorstr_("Loot Boxes"), &loot_esp::lootboxes);
                                ImGui::Checkbox(xorstr_("Ammo"), &loot_esp::ammo);
                                ImGui::Checkbox(xorstr_("Money"), &loot_esp::money);
                                ImGui::Checkbox(xorstr_("Armour"), &loot_esp::armour);
                                ImGui::Checkbox(xorstr_("Lethals"), &loot_esp::lethals);
                                ImGui::Checkbox(xorstr_("Tacticals"), &loot_esp::tacticals);
                                ImGui::Checkbox(xorstr_("Equipment"), &loot_esp::equipment);
                                ImGui::Checkbox(xorstr_("Misc"), &loot_esp::misc);
                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPos(ImVec2(360, 50));
                        ImGui::BeginChild(xorstr_("Child111"), ImVec2(320, 530));
                        {
                            //title
                            ImGui::SetCursorPos(ImVec2(15, 15));
                            ImGui::Text(xorstr_("Loot Esp 2"));
                            ImGui::Separator();

                            ImGui::SetCursorPos(ImVec2(15, 60));
                            ImGui::BeginGroup();
                            {
                                ImGui::Checkbox(xorstr_("Zombies EE"), &loot_esp::ZMEE);
                                ImGui::Checkbox(xorstr_("Zombies Machines"), &loot_esp::ZMMachines);
                                ImGui::Checkbox(xorstr_("Zombies Traps"), &loot_esp::ZMTrap);
                                ImGui::Checkbox(xorstr_("Zombies Wallbuys"), &loot_esp::Wallbuys);

                                ImGui::SliderInt(xorstr_("Max Distance"), &loot_esp::max_distance, 1, 1000, xorstr_("%d Metres"));
                                ImGui::Checkbox(xorstr_("Show Distance"), &loot_esp::show_dist);
                                ImGui::Checkbox(xorstr_("Ignore Non Visible"), &loot_esp::ignoreinvis);

                            }
                            ImGui::EndGroup();
                        }
                        ImGui::EndChild();


                    }

                }
                    
                if (tabs == 3) //MISC
                {
                    ImGui::SetCursorPos(ImVec2(20.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 530.f));
                    {

                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Loot Esp"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            ImGui::Checkbox(xorstr_("Enable Loot ESP"), &loot_esp::enable);

                            ImGui::Checkbox(xorstr_("Weapons"), &loot_esp::weapons);
                            ImGui::Checkbox(xorstr_("Weapon Crates"), &loot_esp::weapon_crates);
                            ImGui::Checkbox(xorstr_("Loot Boxes"), &loot_esp::lootboxes);
                            ImGui::Checkbox(xorstr_("Ammo"), &loot_esp::ammo);
                            ImGui::Checkbox(xorstr_("Money"), &loot_esp::money);
                            ImGui::Checkbox(xorstr_("Armour"), &loot_esp::armour);
                            ImGui::Checkbox(xorstr_("Lethals"), &loot_esp::lethals);
                            ImGui::Checkbox(xorstr_("Tacticals"), &loot_esp::tacticals);
                            ImGui::Checkbox(xorstr_("Equipment"), &loot_esp::equipment);
                            ImGui::Checkbox(xorstr_("Misc"), &loot_esp::misc);
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(360.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child111"), ImVec2(320.f, 530.f));
                    {
                        //title
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Settings"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            ImGui::SliderInt(xorstr_("Max Distance"), &loot_esp::max_distance, 1, 1000, xorstr_("%d Metres"));
                            ImGui::Checkbox(xorstr_("Show Distance"), &loot_esp::show_dist);
                            ImGui::Checkbox(xorstr_("Ignore Non Visible"), &loot_esp::ignoreinvis);
                            ImGui::ColorEdit4(xorstr_("Loot Esp Visible"), loot_esp::Loot_Color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Loot Esp Non Visible"), loot_esp::Loot_Color_Non_Vis, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);

                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPosY(570);

                }

                if (tabs == 4) //MISC
                {
                    ImGui::SetCursorPos(ImVec2(20.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 580.f));
                    {

                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Visible"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            ImGui::ColorEdit4(xorstr_("Visible Enemy ESP"), Color::Distance[1], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
                            ImGui::ColorEdit4(xorstr_("Visible Team ESP"), Color::Distance[3], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
                            ImGui::ColorEdit4(xorstr_("Visible Enemy UAV"), Color::DynamicRadar[1], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Visible Team UAV"), Color::DynamicRadar[3], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Visible Enemy Compass"), Color::Compass[1], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Visible Team Compass"), Color::Compass[3], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Visible Loot"), loot_esp::Loot_Color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);

                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(360.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child111"), ImVec2(320.f, 580.f));
                    {
                        //title
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Non Visible"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            ImGui::ColorEdit4(xorstr_("Non Visible Enemy ESP"), Color::Distance[0], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
                            ImGui::ColorEdit4(xorstr_("Non Visible Team ESP"), Color::Distance[2], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
                            ImGui::ColorEdit4(xorstr_("Non Visible Enemy UAV"), Color::DynamicRadar[0], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Non Visible Team UAV"), Color::DynamicRadar[2], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Non Visible Enemy Compass"), Color::Compass[0], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Non Visible Team Compass"), Color::Compass[2], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            ImGui::ColorEdit4(xorstr_("Non Visible Loot"), loot_esp::Loot_Color_Non_Vis, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);

                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPosY(570);

                }

                if (tabs == 5) //Lobby
                {
                    ImGui::SetCursorPos(ImVec2(20.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child0"), ImVec2(660.f, 580.f));
                    {
                        const char* ReportType[7] = { xorstr_("Cheating"), xorstr_("Exploiting") , xorstr_("Text Chat Spam"), xorstr_("Text Chat Offensive") , xorstr_("Voice Chat Offensive"), xorstr_("Username Offensive") , xorstr_("Clantag Offensive")};

                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Lobby Info"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            int COLUMNS_COUNT = 8;
                            auto& table = Lobby;

                            ImGuiTableFlags Flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_Reorderable;

                            static ImGuiTextFilter filter;
                            filter.Draw(xorstr_("Search By Name"), 100.f);

                       
                                if (ImGui::BeginTable(xorstr_("Player List"), COLUMNS_COUNT, Flags, ImVec2(630.f, 260.f)))
                                {

                                    ImGui::TableSetupColumn(xorstr_("#"), ImGuiTableColumnFlags_WidthFixed );
                                    ImGui::TableSetupColumn(xorstr_("Name"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Rank"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("K/D"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Score"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Ping"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Device"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("XUID"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableHeadersRow();

                                        for (int row = 0; row < Globals::MaxPlayerCount; row++) {

                                            if (!filter.PassFilter(table[row].gamertag))
                                                continue;

                                            if (table[row].xuid == 0)
                                                continue;

                                            if (table[row].highlight)
                                                continue;

                                            ImGui::TableNextRow();

                                            for (int column = 0; column < COLUMNS_COUNT; column++) {
                                                ImGui::TableSetColumnIndex(column);
                                                std::string Device = std::format("{} {} {}", table[row].platform_String, table[row].GPad_String, table[row].Talking_String);                                           
                                                std::string gamertag = std::format("[{}] {}", table[row].Team, table[row].gamertag);
                                                std::string KD = std::format("{}/{}", table[row].Kills, table[row].Deaths);

                                                switch (column) {
                                                case 0:
                                                    ImGui::Text(std::to_string(table[row].client_Number).c_str());
                                                    break;
                                                case 1:
                                                    ImGui::Text(gamertag.c_str());
                                                    break;
                                                case 2:
                                                    ImGui::Text(std::to_string(table[row].Rank).c_str());
                                                    break;
                                                case 3:
                                                    ImGui::Text(KD.c_str());
                                                    break;
                                                case 4:
                                                    ImGui::Text(std::to_string(table[row].Score).c_str());
                                                    break;
                                                case 5:
                                                    ImGui::Text(std::to_string(table[row].Ping).c_str());
                                                    break;
                                                case 6:
                                                    ImGui::PushFont(Font::IconFont);
                                                    ImGui::Text(Device.c_str());
                                                    ImGui::PopFont();
                                                    break;
                                                case 7:
                                                    ImGui::Text(std::to_string(table[row].xuid).c_str());
                                                    break;
                                                }

                                                ImGui::PushID(row * COLUMNS_COUNT + column);
                                                ImGui::SetNextItemWidth(200);

                                                if (ImGui::BeginPopupContextItem(std::to_string(row * COLUMNS_COUNT + column).c_str()))
                                                {
                                                    // ImGui::SetWindowFocus();

                                                    ImGui::Text(gamertag.c_str());
                                                    ImGui::Separator();

 
                                                    ImGui::Checkbox(xorstr_("Highlight Player"), &table[row].highlight);

                                                    ImGui::EndMenu();
                                                }
                                                ImGui::PopID();


                                            }
                                        }
                                 

                                    ImGui::EndTable();

                                }
                                ImGui::ColorEdit4(xorstr_("Highlighted ESP Color"), Color::HighlightColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                                if (ImGui::BeginTable(xorstr_("Highlighted Player List"), COLUMNS_COUNT, Flags, ImVec2(630.f, 150.f)))
                                {

                                    ImGui::TableSetupColumn(xorstr_("#"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Name"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Rank"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("K/D"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Score"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Ping"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("Device"), ImGuiTableColumnFlags_WidthFixed);
                                    ImGui::TableSetupColumn(xorstr_("XUID"), ImGuiTableColumnFlags_WidthFixed);

                                    ImGui::TableHeadersRow();
                       
                                        for (int row = 0; row < Globals::MaxPlayerCount; row++) {

                                            if (!table[row].highlight)
                                                continue;
                                            if (table[row].xuid == 0)
                                                continue;

                                            ImGui::TableNextRow();

                                            for (int column = 0; column < COLUMNS_COUNT; column++) {
                                                ImGui::TableSetColumnIndex(column);
                                                std::string Device = std::format("{} {} {}", table[row].platform_String, table[row].GPad_String, table[row].Talking_String);
                                                std::string gamertag = std::format("[{}] {}", table[row].Team, table[row].gamertag);
                                                std::string KD = std::format("{}/{}", table[row].Kills, table[row].Deaths);

                                                switch (column) {
                                                case 0:
                                                    ImGui::Text(std::to_string(table[row].client_Number).c_str());
                                                    break;
                                                case 1:
                                                    ImGui::Text(gamertag.c_str());
                                                    break;
                                                case 2:
                                                    ImGui::Text(std::to_string(table[row].Rank).c_str());
                                                    break;
                                                case 3:
                                                    ImGui::Text(KD.c_str());
                                                    break;
                                                case 4:
                                                    ImGui::Text(std::to_string(table[row].Score).c_str());
                                                    break;
                                                case 5:
                                                    ImGui::Text(std::to_string(table[row].Ping).c_str());
                                                    break;
                                                case 6:
                                                    ImGui::PushFont(Font::IconFont);
                                                    ImGui::Text(Device.c_str());
                                                    ImGui::PopFont();
                                                    break;
                                                case 7:
                                                    ImGui::Text(std::to_string(table[row].xuid).c_str());
                                                    break;
                                                }

                                                ImGui::PushID(row * COLUMNS_COUNT + column);
                                                ImGui::SetNextItemWidth(200);

                                                if (ImGui::BeginPopupContextItem(std::to_string(row * COLUMNS_COUNT + column).c_str()))
                                                {
                                                    // ImGui::SetWindowFocus();

                                                    ImGui::Text(gamertag.c_str());
                                                    ImGui::Separator();
                                                    
                                                    ImGui::Checkbox(xorstr_("Highlight Player"), &table[row].highlight);

                                                    ImGui::EndMenu();
                                                }
                                                ImGui::PopID();
                                            }
                                        }
                                  

                                    ImGui::EndTable();

                                }

                      
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();


                }

                if (tabs == 6) //MISC
                {

                    ImGui::SetCursorPos(ImVec2(20.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 580.f));
                    {
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Exploits"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                        
                    
                            ImGui::Text(xorstr_("We Do Not Advise Using UA On Main Acc"));
                            if (ImGui::Checkbox(xorstr_("Unlock All [RISKY]"), &Exploits::UnlockAll))
                                UA();

                    
                            ImGui::Checkbox(xorstr_("Enable Extended FOV"), &Exploits::ExtendedFOV);
                            ImGui::SliderFloat(xorstr_("FOV"), &Commands::FOV, 0.f, 170.f, xorstr_("%1.0f"));

                            for (int i = 0; i < Auto[9].size(); ++i) {
                                ImGui::Checkbox(Auto[9][i].c_str(), Exploits::Array[i]);
                            }
                            ImGui::Checkbox(xorstr_("Enable 3RD Person Spinbot"), &Exploits::SpinBot);
                            ImGui::Keybind(xorstr_("Night Vision Key"), &KeyBinds::NightVision);
                            ImGui::Keybind(xorstr_("Dynamic Third Person Key"), &KeyBinds::DynamicThirdPerson);
                            ImGui::Checkbox(xorstr_("Enable Air Stuck"), &Exploits::Airstuck);
                            ImGui::Keybind(xorstr_("Air Stuck Key"), &KeyBinds::AirStuck);

                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(360.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child111"), ImVec2(320.f, 580.f));
                    {
                        //title
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Exploits"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {

                            ImGui::Checkbox(xorstr_("Enable Chat Spam"), &cfg::Exploits::Chat_Spam::Spam_Message);
                            ImGui::InputTextEx(xorstr_(" "), xorstr_("Enter Chat Message"), cfg::Exploits::Chat_Spam::Chat_Message, 255, ImVec2(290.f, 35.f), NULL);
              
                            ImGui::SliderInt(xorstr_("Delay Time"), &cfg::Exploits::Chat_Spam::Delay_Time, 0, 30, xorstr_("%i Seconds"));

                            if (ImGui::Button(xorstr_("Send Single Message"), ImVec2(290.f, 30.f))) {
                                if (!std::string(cfg::Exploits::Chat_Spam::Chat_Message).empty()) {
                                    Send_Chat_Message(cfg::Exploits::Chat_Spam::Chat_Message);
                                }
                            }
                 
                            if (ImGui::SliderFloat(xorstr_("Map Size"), &Commands::Map, 0.1f, 10.f, xorstr_("%.1fx")))
                                JUP::SetCbuff(xorstr_("seta #x372DF48BFC3FB80C7 %.1f"), Commands::Map);

                            ImGui::Checkbox(xorstr_("Remove Loadout Checks"), &cfg::Exploits::Profanity_Checks::Enable);

 /*                           ImGui::InputTextEx(xorstr_(" "), xorstr_("Enter Cbuff Command"), Commands::Input, IM_ARRAYSIZE(Commands::Input), ImVec2(290, 35), NULL);

                            if (ImGui::Button(xorstr_("Send Command"), ImVec2(290, 30))) {
                                JUP::SetCbuff(Commands::Input);
                            }; */

     /*                       for (int i = 0; i < Auto[11].size(); ++i) {
                                bool Checked = ImGui::Checkbox(Auto[11][i].c_str(), Commands::Array[i]);

                                if (Checked && Commands::Array[i]) {
                                    switch (i) {
                                    case 0: JUP::SetCbuff(xorstr_("seta #x3DF200A089A3B3FEB %i;"), !Commands::NoFog); break;
                                    case 2: JUP::SetCbuff(xorstr_("seta #x34958E45561A1F918 %i;"), Commands::DrawFPS); break;
                                    case 3: JUP::SetCbuff(xorstr_("seta #x3D80B69DE4DA004BE %i;"), Commands::BreakCamera); break;
                                    case 4: JUP::SetCbuff(xorstr_("seta #x32F1C7266C0A91797 %i;"), Commands::SwapLoadouts); break;
                                    case 5: JUP::SetCbuff(xorstr_("seta #x35D474D39E096F8F1 %i;"), !Commands::NoShieldShake); break;
                                    case 6: JUP::SetCbuff(xorstr_("seta #x38BADBB201F2E8588 %i;"), Commands::DevPlayList); break;
                                    case 7: JUP::SetCbuff(xorstr_("seta #x31F94AB661347AF15 %i;"), !Commands::InGameCrosshair); break;
                                    case 8: JUP::SetCbuff(xorstr_("seta #x3BB203010F77299D4 %i;"), !Commands::ProfanityNameBypass); break;
                                    case 9: JUP::SetCbuff(xorstr_("seta #x3EBB1AD2F73337342 %i;"), !Commands::BypassPrivateMatches); break;
                                    default: break;
                                    }
                                }
                            }
                            ImGui::InputTextEx(xorstr_(" "), xorstr_("Enter Cbuff Command"), Commands::Input, IM_ARRAYSIZE(Commands::Input), ImVec2(290, 35), NULL);
                            if (ImGui::Button(xorstr_("Send Command"), ImVec2(290, 30))) {
                                JUP::SetCbuff(std::string(xorstr_("seta ") + std::string(Commands::Input)).c_str());
                            };*/
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();
                }

                if (tabs == 7) //MISC
                {
                    const char* cofnigs[10] = { xorstr_("Config 1"), xorstr_("Config 2"), xorstr_("Config 3"), xorstr_("Config 4"), xorstr_("Config 5"), xorstr_("Config 6"), xorstr_("Config 7"), xorstr_("Config 8"), xorstr_("Config 9"), xorstr_("Config 10") };

                    ImGui::SetCursorPos(ImVec2(20.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child0"), ImVec2(320.f, 240.f));
                    {
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Configs"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            ImGui::Combo(xorstr_("Select Config Slot"), &confignum, cofnigs, IM_ARRAYSIZE(cofnigs));
                            if (ImGui::Button(xorstr_("Save Config"), ImVec2(290.f, 30.f))) {

                                saveConfig(confignum + 1);
                            };

                            if (ImGui::Button(xorstr_("Load Config"), ImVec2(290.f, 30.f))) {
                                setVars(confignum + 1);
                            };

                            if (ImGui::Button(xorstr_("Delete"), ImVec2(290.f, 30.f))) {
                                char file_path[MAX_PATH];
                                sprintf_s(file_path, (xorstr_("C:\\BO6\\Configs\\%s%s")), std::to_string(confignum + 1), (xorstr_(".json")));
                                std::remove(file_path);
                            };
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(20.f, 260.f));
                    ImGui::BeginChild(xorstr_("Child02343"), ImVec2(320.f, 220.f));
                    {
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Menu Settings"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            ImGui::Keybind(xorstr_("Menu Open / Close"), &KeyBinds::Menu);
                            if (rainbow)
                                ImGui::Checkbox(xorstr_("Rainbow Mode"), &rainbow);
                            else
                            {
                                ImGui::Checkbox(xorstr_("Rainbow Mode"), &rainbow);
                                ImGui::ColorEdit4(xorstr_("Menu Accent"), (float*)&main_color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
                            }
                           
                            ImGui::Checkbox(xorstr_("Rainbow Visuals"), &Globals::rainbowesp);
                        }
                        ImGui::EndGroup();
                    }

                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(360.f, 0.f));
                    ImGui::BeginChild(xorstr_("Child111"), ImVec2(320.f, 190.f));
                    {
                        //title
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Preset Configs"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            if (ImGui::Button(xorstr_("Rage"), ImVec2(290.f, 30.f))) {
                              //  rage();
                            };

                            if (ImGui::Button(xorstr_("Semi Legit"), ImVec2(290.f, 30.f))) {
                                //SemiLegit();
                            };

                            if (ImGui::Button(xorstr_("Legit"), ImVec2(290.f, 30.f))) {
                              //  Legit();
                            };
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(360.f, 210.f));
                    ImGui::BeginChild(xorstr_("Chotkeys"), ImVec2(320.f, 230.f));
                    {
                        //title
                        ImGui::SetCursorPos(ImVec2(15.f, 15.f));
                        ImGui::Text(xorstr_("Config Hot Keys"));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(15.f, 60.f));
                        ImGui::BeginGroup();
                        {
                            ImGui::Text(xorstr_("[F1]- Load Config 1"));
                            ImGui::Text(xorstr_("[F2]- Load Config 2"));
                            ImGui::Text(xorstr_("[F3]- Load Config 3"));
                            ImGui::Text(xorstr_("[F4]- Load Config 4"));
                            ImGui::Text(xorstr_("[F5]- Load Config 5"));
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();

                }

              
                ImGui::PopFont();
                ImGui::PopStyleColor();
            }
            ImGui::EndChild();

            ImGui::PopStyleColor();

        }
        ImGui::End();
    
}