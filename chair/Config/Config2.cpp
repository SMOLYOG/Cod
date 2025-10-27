#pragma once
#include "config2.h"
#include "..\Globals\Globals.h"

using json = nlohmann::json;

int boolToInt(bool btoi)
{
	if (btoi == true)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IntTobool(int btoi)
{
	if (btoi == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<std::string> GetList()
{
	std::vector<std::string> configs;
	WIN32_FIND_DATA ffd;
	LPCSTR directory = (xorstr_("C:\\MWIII\\Config\\*"));
	auto hFind = FindFirstFile(directory, &ffd);
	while (FindNextFile(hFind, &ffd))
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			std::string file_name = ffd.cFileName;
			if (file_name.size() < 4) // .cfg
				continue;
			std::string end = file_name;
			end.erase(end.begin(), end.end() - 4);
			if (end != (xorstr_(".json")))
				continue;
			file_name.erase(file_name.end() - 4, file_name.end());
			configs.push_back(file_name);
		}
	}
	return configs;
}


void Auto_Load()
{
	if (GetList().empty())
	{
		CreateDirectoryA((xorstr_("C:\\BO6")), NULL);
		CreateDirectoryA((xorstr_("C:\\BO6\\config")), NULL);
	}


}

void saveConfig(int configNumber) {
	char file_path[MAX_PATH];
	sprintf_s(file_path, (xorstr_("C:\\BO6\\config\\%s%s")), std::to_string(configNumber), (xorstr_(".json")));
	remove(file_path);

	std::ofstream log(file_path, std::ofstream::app | std::ofstream::out);

	json j;
	j["1"] = { {"0", KeyBinds::Aimbot}, {"1", KeyBinds::Aimbot2}, {"2", KeyBinds::Overide}, {"3", KeyBinds::NightVision},{"4", KeyBinds::AirStuck},{"5", KeyBinds::DynamicThirdPerson}};
	j["2"] = { {"0", boolToInt(Aimbot::Enable)},{"1", boolToInt(Aimbot::Silent)},{"2", boolToInt(Aimbot::Enable_MissChance)} , {"3", Aimbot::Miss_Chance}, {"4", Aimbot::Strength}, {"5", boolToInt(cfg::Aimbot::Targeting::BoneScan)}, { "6", Aimbot::Bone } };
	j["3"] = { {"0", Aimbot::switch_delay},{"1", boolToInt(Aimbot::Disable_on_kill)},{"2", Aimbot::Smoothingx} , {"3", Aimbot::Smoothingy}, {"4", Aimbot::Smoothingz}, {"5",cfg::Aimbot::Targeting::Type}, { "6", boolToInt(Aimbot::DynamicFOV)},  { "7", Aimbot::FOV} , { "8", Aimbot::Checks::Distance } ,{ "9", boolToInt(Aimbot::Targeting::Teamates) },  { "10", boolToInt(Aimbot::Targeting::Visible) },  { "11", boolToInt(Aimbot::Targeting::Downed) },  { "12", boolToInt(Aimbot::Targeting::RiotShield) } };	
	j["4"] = { {"0", boolToInt(Aimbot::Overide::Enable)},{"1",Aimbot::Overide::Smoothing},{"2",Aimbot::Overide::Bone}};
	j["5"] = { {"0", boolToInt(cfg::Aimbot::Health_Override::Enable)},{"1",cfg::Aimbot::Health_Override::Health_Trigger},{"2",cfg::Aimbot::Health_Override::Bone} };
	j["6"] = { {"0", boolToInt(Aimbot::Accuracy::NoRecoil)},{"1",Aimbot::Accuracy::Strength},{"2", boolToInt(Aimbot::Ignore_While_Spectated)},{"3",Aimbot::Spectator_Count},{"4",boolToInt(Aimbot::RapidFire)},{"5",cfg::Exploits::Rapid_fire::Shot_Delay}, {"6",boolToInt(Aimbot::AutoShoot)}, {"7",boolToInt(cfg::Aimbot::Extras::Auto_Ads)} };
	j["7"] = { {"0", boolToInt(cfg::Exploits::Auto_Reload::Enable)},{"1",boolToInt(cfg::Exploits::Auto_Reload::Stop_When_In_View)},{"2", boolToInt(cfg::Exploits::Auto_Reload::Stop_When_Targeting)},{"3",boolToInt(cfg::Exploits::Auto_Reload::Enable_AR)},{"4",cfg::Exploits::Auto_Reload::Bullet_Count_AR},{"5",boolToInt(cfg::Exploits::Auto_Reload::Enable_Sniper)}, {"6",cfg::Exploits::Auto_Reload::Bullet_Count_Sniper}, {"7",boolToInt(cfg::Exploits::Auto_Reload::Enable_LMG)} ,{"8",cfg::Exploits::Auto_Reload::Bullet_Count_LMG }, {"9",boolToInt(cfg::Exploits::Auto_Reload::Enable_SMG)} ,{"10",cfg::Exploits::Auto_Reload::Bullet_Count_SMG },{"11",boolToInt(cfg::Exploits::Auto_Reload::Enable_Pistol)} ,{"12",cfg::Exploits::Auto_Reload::Bullet_Count_Pistol } };
	j["8"] = { {"0", boolToInt(Visuals::Main::Enable)},{"1", boolToInt(Visuals::Main::filled)} ,{"2", boolToInt(Visuals::Main::Enable)} ,{"3", boolToInt(Visuals::Main::Draw_Box)} ,{"4", boolToInt(Visuals::Main::DrawPlayerSkeleton)} ,{"5", boolToInt(Visuals::Main::DrawPlayerHealth)} ,{"6", boolToInt(Visuals::Main::DrawPlayerName)} ,{"7", boolToInt(Visuals::Main::DrawPlayerWeapon)} ,{"8", boolToInt(Visuals::Main::DrawPlayerTeamID)} ,{"9", boolToInt(Visuals::Main::DrawPlayerSnaplines)},{"10", boolToInt(Visuals::Main::DrawPlayerDistance)} };
	j["9"] = { {"0", boolToInt(Globals::rainbowesp)},{"1",cfg::Esp::Drawing_Settings::box_Type},{"2",Visuals::Main::Drawing::Bonethicness},{"3",Visuals::Main::Drawing::all},{"4", boolToInt(Visuals::Main::Drawing::Teamates)},{"5", boolToInt(Visuals::Main::Drawing::Visible)},{"6", boolToInt(Visuals::Main::Drawing::Downed)},{"7",cfg::Esp::Drawing_Settings::Snapline_Pos} };
	j["10"] = { {"0", boolToInt(loot_esp::enable)},{"1", boolToInt(loot_esp::weapons)} ,{"2", boolToInt(loot_esp::weapon_crates)} ,{"3", boolToInt(loot_esp::lootboxes)} ,{"4", boolToInt(loot_esp::ammo)} ,{"5", boolToInt(loot_esp::money)} ,{"6", boolToInt(loot_esp::armour)} ,{"7", boolToInt(loot_esp::lethals)} ,{"8", boolToInt(loot_esp::tacticals)} ,{"9", boolToInt(loot_esp::equipment)},{"10", boolToInt(loot_esp::misc)} };
	j["11"] = { {"0", loot_esp::max_distance},{"1",boolToInt(loot_esp::show_dist)},{"2",boolToInt(loot_esp::ignoreinvis)}};
	j["12"] = { {"0", boolToInt(Visuals::Miscellaneous::DynamicRadar::Enable)},{"1",Visuals::Miscellaneous::DynamicRadar::RadarType},{"2",boolToInt(Visuals::Miscellaneous::DynamicRadar::filled)},{"3",Visuals::Miscellaneous::DynamicRadar::blipsize} };
	j["13"] = { {"0", Visuals::Miscellaneous::DynamicRadar::Distance},{"1",boolToInt(Visuals::Miscellaneous::DynamicRadar::Drawing::Teamates)},{"2",boolToInt(Visuals::Miscellaneous::DynamicRadar::Drawing::Visible)},{"3",boolToInt(Visuals::Miscellaneous::DynamicRadar::Drawing::Downed)}};
	j["14"] = { {"0", boolToInt(Visuals::Miscellaneous::Compass::Enable)},{"1",boolToInt(Visuals::Miscellaneous::Compass::Fill)},{"2",Visuals::Miscellaneous::Compass::Size},{"3",Visuals::Miscellaneous::Compass::Distance},{"4",Visuals::Miscellaneous::Compass::PosistionType} ,{"5",boolToInt(Visuals::Miscellaneous::Compass::Drawing::Teamates)} ,{"6",boolToInt(Visuals::Miscellaneous::Compass::Drawing::Visible)}};
	j["15"] = { {"0", boolToInt(Visuals::Miscellaneous::Tracers::Enable)},{"1",boolToInt(Visuals::Miscellaneous::Tracers::PlayerTracers)},{"2",boolToInt(Visuals::Miscellaneous::Tracers::Objects)},{"3",boolToInt(Visuals::Miscellaneous::Tracers::Players)},{"4",Visuals::Miscellaneous::Tracers::FadeInTime} ,{"5",Visuals::Miscellaneous::Tracers::TracerThickness} ,{"6",ImGui::ColorConvertFloat4ToU32(ImVec4(Visuals::Miscellaneous::Tracers::Tracer_Col[0],Visuals::Miscellaneous::Tracers::Tracer_Col[1],Visuals::Miscellaneous::Tracers::Tracer_Col[2],Visuals::Miscellaneous::Tracers::Tracer_Col[3]))}};
	j["16"] = { {"0", boolToInt(Visuals::Outlines::Player::Enable)},{"1",boolToInt(Visuals::Outlines::Player::Fill)},{"2",Visuals::Outlines::Player::Type},{"3",Visuals::Outlines::Player::Width},{"4",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::ChamsVec4[0][0],Color::ChamsVec4[0][1],Color::ChamsVec4[0][2],Color::ChamsVec4[0][3]))} };
	j["17"] = { {"0", boolToInt(Visuals::Outlines::Self::Enable)},{"1",boolToInt(Visuals::Outlines::Self::Fill)},{"2",Visuals::Outlines::Self::Type},{"3",Visuals::Outlines::Self::Width},{"4",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::ChamsVec4[1][0],Color::ChamsVec4[1][1],Color::ChamsVec4[1][2],Color::ChamsVec4[1][3]))} };
	j["18"] = { {"0", boolToInt(Visuals::Main::DrawCrosshair)},{"1",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::crosshair[0],Color::crosshair[1],Color::crosshair[2],Color::crosshair[3]))}, {"2",Visuals::Main::crosshair_thickness}, {"3", Visuals::Main::crosshair_size} };
	j["19"] = { {"0", boolToInt(Visuals::Main::DrawFOV)},{"1",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::FOV[0],Color::FOV[1],Color::FOV[2],Color::FOV[3]))}};
	j["20"] = { {"0", boolToInt(cfg::Aim_Target::Target_SnapLine)},{"1",ImGui::ColorConvertFloat4ToU32(ImVec4(cfg::Aim_Target::Color::Target_Esp[0],cfg::Aim_Target::Color::Target_Esp[1],cfg::Aim_Target::Color::Target_Esp[2],cfg::Aim_Target::Color::Target_Esp[3]))},{"2",ImGui::ColorConvertFloat4ToU32(ImVec4(cfg::Aim_Target::Color::Target_Crosshair[0],cfg::Aim_Target::Color::Target_Crosshair[1],cfg::Aim_Target::Color::Target_Crosshair[2],cfg::Aim_Target::Color::Target_Crosshair[3]))} };
	j["21"] = { {"0", boolToInt(Aim_Warning::Looking_At_You)},{"1",Aim_Warning::Looking_Max_Distance},{"2",ImGui::ColorConvertFloat4ToU32(ImVec4(Aim_Warning::LookingAtYou[0],Aim_Warning::LookingAtYou[1],Aim_Warning::LookingAtYou[2],Aim_Warning::LookingAtYou[3]))},{"3",boolToInt(Aim_Warning::Aiming_At_You)},{"4",Aim_Warning::Aiming_Max_distance}, {"5",ImGui::ColorConvertFloat4ToU32(ImVec4(Aim_Warning::AimingAtYou[0],Aim_Warning::AimingAtYou[1],Aim_Warning::AimingAtYou[2],Aim_Warning::AimingAtYou[3]))} };
	j["22"] = { {"0",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Distance[1][0],Color::Distance[1][1],Color::Distance[1][2],Color::Distance[1][3]))},{"1",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Distance[3][0],Color::Distance[3][1],Color::Distance[3][2],Color::Distance[3][3]))},{"2",ImGui::ColorConvertFloat4ToU32(ImVec4(loot_esp::Loot_Color[0],loot_esp::Loot_Color[1],loot_esp::Loot_Color[2],loot_esp::Loot_Color[3]))},{"3",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::DynamicRadar[1][0],Color::DynamicRadar[1][1],Color::DynamicRadar[1][2],Color::DynamicRadar[1][3]))},{"4",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::DynamicRadar[3][0],Color::DynamicRadar[3][1],Color::DynamicRadar[3][2],Color::DynamicRadar[3][3]))} , { "5",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Compass[1][0],Color::Compass[1][1],Color::Compass[1][2],Color::Compass[1][3])) },{"6",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Compass[3][0],Color::Compass[3][1],Color::Compass[3][2],Color::Compass[3][3]))} };
	j["23"] = { {"0",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Distance[0][0],Color::Distance[0][1],Color::Distance[0][2],Color::Distance[0][3]))},{"1",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Distance[2][0],Color::Distance[2][1],Color::Distance[2][2],Color::Distance[2][3]))},{"2",ImGui::ColorConvertFloat4ToU32(ImVec4(loot_esp::Loot_Color_Non_Vis[0],loot_esp::Loot_Color_Non_Vis[1],loot_esp::Loot_Color_Non_Vis[2],loot_esp::Loot_Color_Non_Vis[3]))},{"3",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::DynamicRadar[0][0],Color::DynamicRadar[0][1],Color::DynamicRadar[0][2],Color::DynamicRadar[0][3]))},{"4",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::DynamicRadar[2][0],Color::DynamicRadar[2][1],Color::DynamicRadar[2][2],Color::DynamicRadar[2][3]))} , { "5",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Compass[0][0],Color::Compass[0][1],Color::Compass[0][2],Color::Compass[0][3])) },{"6",ImGui::ColorConvertFloat4ToU32(ImVec4(Color::Compass[2][0],Color::Compass[2][1],Color::Compass[2][2],Color::Compass[2][3]))} };
	j["24"] = { {"0", boolToInt(Exploits::ExtendedFOV)},{"1",Commands::FOV},{"2",Commands::Map},{"3",boolToInt(Exploits::NightVision)} ,{"4",boolToInt(Exploits::Airstuck)} ,{"5",boolToInt(Exploits::ThirdPerson)} ,{"6",boolToInt(Exploits::DynamicThirdPerson)} ,{"7",boolToInt(Exploits::NoShellShock)}};
	j["25"] = { {"0", boolToInt(cfg::Exploits::Melee_Lunge::Enable)},{"1",cfg::Exploits::Melee_Lunge::Type},{"2",cfg::Exploits::Melee_Lunge::Max_Distance},{"3",boolToInt(cfg::Exploits::Melee_Lunge::Ignore_Team)} ,{"4",boolToInt(cfg::Exploits::Melee_Lunge::Ignore_Knocked)} ,{"5",boolToInt(cfg::Exploits::Melee_Lunge::Ignore_Invis)}};
	j["26"] = { {"0", boolToInt(cfg::Exploits::Chat_Spam::Enable)},{"1",boolToInt(cfg::Exploits::Chat_Spam::Spam_Message)}};
	j["27"] = { {"0", boolToInt(Visuals::Miscellaneous::DynamicRadar::Drawing::Bots)},{"1",boolToInt(Visuals::Miscellaneous::Compass::Drawing::Bots)} ,{"2",boolToInt(Visuals::Main::Drawing::Bots)} };
	j["28"] = { {"0", IntTobool(cfg::Esp::Platform)},{"1",IntTobool(cfg::Esp::Device)} ,{"2",IntTobool(cfg::Esp::Talking)} };
	j["29"] = { {"0", IntTobool(Aimbot::Targeting::Bots)}, {"1", IntTobool(loot_esp::ZMEE)}, {"2", IntTobool(loot_esp::ZMMachines)}, {"3", IntTobool(loot_esp::Wallbuys)}, {"4", IntTobool(loot_esp::ZMTrap) }};
	j["30"] = { {"0", ImGui::ColorConvertFloat4ToU32(ImVec4(Color::HighlightColor[0],Color::HighlightColor[1],Color::HighlightColor[2],Color::HighlightColor[3]))} };

	log << j;
	log.close();
}

void setVars(int configNumber)
{
	char file_path[MAX_PATH];
	sprintf_s(file_path, (xorstr_("C:\\BO6\\config\\%s%s")), std::to_string(configNumber), (xorstr_(".json")));
	if (!std::filesystem::exists(file_path))
	{
		MessageBoxA(NULL, "Config file does not exist. Save one before trying to apply it!", "Error!", MB_ICONERROR);
		return;
	}
	std::ifstream f(file_path);
	json data = json::parse(f);

	if (data.contains("1"))
	{
		KeyBinds::Aimbot = data["1"]["0"];
		KeyBinds::Aimbot2 = data["1"]["1"];
		KeyBinds::Overide = data["1"]["2"];
		KeyBinds::NightVision = data["1"]["3"];
		KeyBinds::AirStuck = data["1"]["4"];
		KeyBinds::DynamicThirdPerson = data["1"]["5"];
	}

	if (data.contains("2"))
	{
		Aimbot::Enable = IntTobool(data["2"]["0"]);
		Aimbot::Silent = IntTobool(data["2"]["1"]);
		Aimbot::Enable_MissChance = IntTobool(data["2"]["2"]);
		Aimbot::Miss_Chance = data["2"]["3"];
		Aimbot::Strength = data["2"]["4"];
		cfg::Aimbot::Targeting::BoneScan = IntTobool(data["2"]["5"]);
		Aimbot::Bone = IntTobool(data["2"]["6"]);
	}

	if (data.contains("3"))
	{
		Aimbot::switch_delay = data["3"]["0"];
		Aimbot::Disable_on_kill = IntTobool(data["3"]["1"]);
		Aimbot::Smoothingx = data["3"]["2"];
		Aimbot::Smoothingy = data["3"]["3"];
		Aimbot::Smoothingz = data["3"]["4"];
		cfg::Aimbot::Targeting::Type = data["3"]["5"];
		Aimbot::DynamicFOV = IntTobool(data["3"]["6"]);
		Aimbot::FOV = data["3"]["7"];
		Aimbot::Checks::Distance = data["3"]["8"];
		Aimbot::Targeting::Teamates = IntTobool(data["3"]["9"]);
		Aimbot::Targeting::Visible = IntTobool(data["3"]["10"]);
		Aimbot::Targeting::Downed = IntTobool(data["3"]["11"]);
		Aimbot::Targeting::RiotShield = IntTobool(data["3"]["12"]);
	}
	
	if (data.contains("4"))
	{
		Aimbot::Overide::Enable = IntTobool(data["4"]["0"]);
		Aimbot::Overide::Smoothing = data["4"]["1"];
		Aimbot::Overide::Bone = data["4"]["2"];
	}

	if (data.contains("5"))
	{
		cfg::Aimbot::Health_Override::Enable = IntTobool(data["5"]["0"]);
		cfg::Aimbot::Health_Override::Health_Trigger = data["5"]["1"];
		cfg::Aimbot::Health_Override::Bone = data["5"]["2"];
	}

	if (data.contains("6"))
	{
		Aimbot::Accuracy::NoRecoil = IntTobool(data["6"]["0"]);
		Aimbot::Accuracy::Strength = data["6"]["1"];
		Aimbot::Ignore_While_Spectated = IntTobool(data["6"]["2"]);
		Aimbot::Spectator_Count = data["6"]["3"];
		Aimbot::RapidFire = IntTobool(data["6"]["4"]);
		cfg::Exploits::Rapid_fire::Shot_Delay = data["6"]["5"];
		Aimbot::AutoShoot = IntTobool(data["6"]["6"]);
		cfg::Aimbot::Extras::Auto_Ads = IntTobool(data["6"]["7"]);
	}

	if (data.contains("7"))
	{
		cfg::Exploits::Auto_Reload::Enable = IntTobool(data["7"]["0"]);
		cfg::Exploits::Auto_Reload::Stop_When_In_View = IntTobool(data["7"]["1"]);
		cfg::Exploits::Auto_Reload::Stop_When_Targeting = IntTobool(data["7"]["2"]);
		cfg::Exploits::Auto_Reload::Enable_AR = IntTobool(data["7"]["3"]);
		cfg::Exploits::Auto_Reload::Bullet_Count_AR = data["7"]["4"];
		cfg::Exploits::Auto_Reload::Enable_Sniper = IntTobool(data["7"]["5"]);
		cfg::Exploits::Auto_Reload::Bullet_Count_Sniper = data["7"]["6"];
		cfg::Exploits::Auto_Reload::Enable_LMG = IntTobool(data["7"]["7"]);
		cfg::Exploits::Auto_Reload::Bullet_Count_LMG = data["7"]["8"];
		cfg::Exploits::Auto_Reload::Enable_SMG = IntTobool(data["7"]["9"]);
		cfg::Exploits::Auto_Reload::Bullet_Count_SMG = data["7"]["10"];
		cfg::Exploits::Auto_Reload::Enable_Pistol = IntTobool(data["7"]["11"]);
		cfg::Exploits::Auto_Reload::Bullet_Count_Pistol = data["7"]["12"];
	}

	if (data.contains("8"))
	{
		Visuals::Main::Enable = IntTobool(data["8"]["0"]);
		Visuals::Main::filled = IntTobool(data["8"]["1"]);
		Visuals::Main::Enable = IntTobool(data["8"]["2"]);
		Visuals::Main::Draw_Box = IntTobool(data["8"]["3"]);
		Visuals::Main::DrawPlayerSkeleton = IntTobool(data["8"]["4"]);
		Visuals::Main::DrawPlayerHealth = IntTobool(data["8"]["5"]);
		Visuals::Main::DrawPlayerName = IntTobool(data["8"]["6"]);
		Visuals::Main::DrawPlayerWeapon = IntTobool(data["8"]["7"]);
		Visuals::Main::DrawPlayerTeamID = IntTobool(data["8"]["8"]);
		Visuals::Main::DrawPlayerSnaplines = IntTobool(data["8"]["9"]);
		Visuals::Main::DrawPlayerDistance = IntTobool(data["8"]["10"]);
	}

	if (data.contains("9"))
	{
		Globals::rainbowesp = IntTobool(data["9"]["0"]);
		cfg::Esp::Drawing_Settings::box_Type = IntTobool(data["9"]["1"]);
		Visuals::Main::Drawing::Bonethicness = data["9"]["2"];
		Visuals::Main::Drawing::all = data["9"]["3"];
		Visuals::Main::Drawing::Teamates = IntTobool(data["9"]["4"]);
		Visuals::Main::Drawing::Visible = IntTobool(data["9"]["5"]);
		Visuals::Main::Drawing::Downed = IntTobool(data["9"]["6"]);
		cfg::Esp::Drawing_Settings::Snapline_Pos = data["9"]["7"];
	}

	if (data.contains("10"))
	{
		loot_esp::enable = IntTobool(data["10"]["0"]);
		loot_esp::weapons = IntTobool(data["10"]["1"]);
		loot_esp::weapon_crates = IntTobool(data["10"]["2"]);
		loot_esp::lootboxes = IntTobool(data["10"]["3"]);
		loot_esp::ammo = IntTobool(data["10"]["4"]);
		loot_esp::money = IntTobool(data["10"]["5"]);
		loot_esp::armour = IntTobool(data["10"]["6"]);
		loot_esp::lethals = IntTobool(data["10"]["7"]);
		loot_esp::tacticals = IntTobool(data["10"]["8"]);
		loot_esp::equipment = IntTobool(data["10"]["9"]);
		loot_esp::misc = IntTobool(data["10"]["10"]);
	}

	if (data.contains("11"))
	{
		loot_esp::max_distance = data["11"]["0"];
		loot_esp::show_dist = IntTobool(data["11"]["1"]);
		loot_esp::ignoreinvis = IntTobool(data["11"]["2"]);
	}

	if (data.contains("12"))
	{
		Visuals::Miscellaneous::DynamicRadar::Enable = IntTobool(data["12"]["0"]);
		Visuals::Miscellaneous::DynamicRadar::RadarType = data["12"]["1"];
		Visuals::Miscellaneous::DynamicRadar::filled = IntTobool(data["12"]["2"]);
		Visuals::Miscellaneous::DynamicRadar::blipsize = data["12"]["3"];
	}

	if (data.contains("13"))
	{
		Visuals::Miscellaneous::DynamicRadar::Distance = data["13"]["0"];
		Visuals::Miscellaneous::DynamicRadar::Drawing::Teamates = IntTobool(data["13"]["1"]);
		Visuals::Miscellaneous::DynamicRadar::Drawing::Visible = IntTobool(data["13"]["2"]);
		Visuals::Miscellaneous::DynamicRadar::Drawing::Downed = IntTobool(data["13"]["3"]);
	}

	if (data.contains("14"))
	{
		Visuals::Miscellaneous::Compass::Enable = IntTobool(data["14"]["0"]);
		Visuals::Miscellaneous::Compass::Fill = IntTobool(data["14"]["1"]);
		Visuals::Miscellaneous::Compass::Size = data["14"]["2"];
		Visuals::Miscellaneous::Compass::Distance = data["14"]["3"];
		Visuals::Miscellaneous::Compass::PosistionType = data["14"]["4"];
		Visuals::Miscellaneous::Compass::Drawing::Teamates = IntTobool(data["14"]["5"]);
		Visuals::Miscellaneous::Compass::Drawing::Visible = IntTobool(data["14"]["6"]);
	}

	if (data.contains("15"))
	{
		Visuals::Miscellaneous::Tracers::Enable = IntTobool(data["15"]["0"]);
		Visuals::Miscellaneous::Tracers::PlayerTracers = IntTobool(data["15"]["1"]);
		Visuals::Miscellaneous::Tracers::Objects = IntTobool(data["15"]["2"]);
		Visuals::Miscellaneous::Tracers::Players = IntTobool(data["15"]["3"]);
		Visuals::Miscellaneous::Tracers::FadeInTime = data["15"]["4"];
		Visuals::Miscellaneous::Tracers::TracerThickness = data["15"]["5"];
		ImVec4 Tracer_Col = ImGui::ColorConvertU32ToFloat4(data["15"]["6"]);
		Visuals::Miscellaneous::Tracers::Tracer_Col[0] = Tracer_Col.x;
		Visuals::Miscellaneous::Tracers::Tracer_Col[1] = Tracer_Col.y;
		Visuals::Miscellaneous::Tracers::Tracer_Col[2] = Tracer_Col.z;
		Visuals::Miscellaneous::Tracers::Tracer_Col[3] = Tracer_Col.w;
	}

	if (data.contains("16"))
	{
		Visuals::Outlines::Player::Enable = IntTobool(data["16"]["0"]);
		Visuals::Outlines::Player::Fill = IntTobool(data["16"]["1"]);
		Visuals::Outlines::Player::Type = data["16"]["2"];
		Visuals::Outlines::Player::Width = data["16"]["3"];
		ImVec4 Player_Chams = ImGui::ColorConvertU32ToFloat4(data["16"]["4"]);
		Color::ChamsVec4[0][0] = Player_Chams.x;
		Color::ChamsVec4[0][1] = Player_Chams.y;
		Color::ChamsVec4[0][2] = Player_Chams.z;
		Color::ChamsVec4[0][3] = Player_Chams.w;
	}

	if (data.contains("17"))
	{
		Visuals::Outlines::Self::Enable = IntTobool(data["17"]["0"]);
		Visuals::Outlines::Self::Fill = IntTobool(data["17"]["1"]);
		Visuals::Outlines::Self::Type = data["17"]["2"];
		Visuals::Outlines::Self::Width = data["17"]["3"];
		ImVec4 Self_Chams = ImGui::ColorConvertU32ToFloat4(data["17"]["4"]);
		Color::ChamsVec4[1][0] = Self_Chams.x;
		Color::ChamsVec4[1][1] = Self_Chams.y;
		Color::ChamsVec4[1][2] = Self_Chams.z;
		Color::ChamsVec4[1][3] = Self_Chams.w;
	}

	if (data.contains("18"))
	{
		Visuals::Main::DrawCrosshair = IntTobool(data["18"]["0"]);
		ImVec4 crosshair = ImGui::ColorConvertU32ToFloat4(data["18"]["1"]);
		Color::crosshair[0] = crosshair.x;
		Color::crosshair[1] = crosshair.y;
		Color::crosshair[2] = crosshair.z;
		Color::crosshair[3] = crosshair.w;
		Visuals::Main::crosshair_thickness = data["18"]["2"];
		Visuals::Main::crosshair_size = data["18"]["3"];
	}

	if (data.contains("19"))
	{
		Visuals::Main::DrawFOV = IntTobool(data["19"]["0"]);
		ImVec4 FOV_Circle = ImGui::ColorConvertU32ToFloat4(data["19"]["1"]);
		Color::FOV[0] = FOV_Circle.x;
		Color::FOV[1] = FOV_Circle.y;
		Color::FOV[2] = FOV_Circle.z;
		Color::FOV[3] = FOV_Circle.w;
	}

	if (data.contains("20"))
	{
		cfg::Aim_Target::Target_SnapLine = IntTobool(data["20"]["0"]);
		ImVec4 Target_Esp = ImGui::ColorConvertU32ToFloat4(data["20"]["1"]);
		cfg::Aim_Target::Color::Target_Esp[0] = Target_Esp.x;
		cfg::Aim_Target::Color::Target_Esp[1] = Target_Esp.y;
		cfg::Aim_Target::Color::Target_Esp[2] = Target_Esp.z;
		cfg::Aim_Target::Color::Target_Esp[3] = Target_Esp.w;
		ImVec4 Target_Cross = ImGui::ColorConvertU32ToFloat4(data["20"]["2"]);
		cfg::Aim_Target::Color::Target_Crosshair[0] = Target_Cross.x;
		cfg::Aim_Target::Color::Target_Crosshair[1] = Target_Cross.y;
		cfg::Aim_Target::Color::Target_Crosshair[2] = Target_Cross.z;
		cfg::Aim_Target::Color::Target_Crosshair[3] = Target_Cross.w;
	}


	if (data.contains("21"))
	{
		Aim_Warning::Looking_At_You = IntTobool(data["21"]["0"]);
		Aim_Warning::Looking_Max_Distance = data["21"]["1"];
		ImVec4 LookingAtYou = ImGui::ColorConvertU32ToFloat4(data["21"]["2"]);
		Aim_Warning::LookingAtYou[0] = LookingAtYou.x;
		Aim_Warning::LookingAtYou[1] = LookingAtYou.y;
		Aim_Warning::LookingAtYou[2] = LookingAtYou.z;
		Aim_Warning::LookingAtYou[3] = LookingAtYou.w;
		Aim_Warning::Aiming_At_You = IntTobool(data["21"]["3"]);
		Aim_Warning::Aiming_Max_distance = data["21"]["4"];
		ImVec4 Aiming_At_You = ImGui::ColorConvertU32ToFloat4(data["21"]["5"]);
		Aim_Warning::AimingAtYou[0] = Aiming_At_You.x;
		Aim_Warning::AimingAtYou[1] = Aiming_At_You.y;
		Aim_Warning::AimingAtYou[2] = Aiming_At_You.z;
		Aim_Warning::AimingAtYou[3] = Aiming_At_You.w;
	}

	if (data.contains("22"))
	{
		ImVec4 Dist1 = ImGui::ColorConvertU32ToFloat4(data["22"]["0"]);
		Color::Distance[1][0] = Dist1.x;
		Color::Distance[1][1] = Dist1.y;
		Color::Distance[1][2] = Dist1.z;
		Color::Distance[1][3] = Dist1.w;
		ImVec4 dist3 = ImGui::ColorConvertU32ToFloat4(data["22"]["1"]);
		Color::Distance[3][0] = dist3.x;
		Color::Distance[3][1] = dist3.y;
		Color::Distance[3][2] = dist3.z;
		Color::Distance[3][3] = dist3.w;
		ImVec4 Lootvis = ImGui::ColorConvertU32ToFloat4(data["22"]["2"]);
		loot_esp::Loot_Color[0] = Lootvis.x;
		loot_esp::Loot_Color[1] = Lootvis.y;
		loot_esp::Loot_Color[2] = Lootvis.z;
		loot_esp::Loot_Color[3] = Lootvis.w;
		ImVec4 DynamicRadar1 = ImGui::ColorConvertU32ToFloat4(data["22"]["3"]);
		Color::DynamicRadar[1][0] = DynamicRadar1.x;
		Color::DynamicRadar[1][1] = DynamicRadar1.y;
		Color::DynamicRadar[1][2] = DynamicRadar1.z;
		Color::DynamicRadar[1][3] = DynamicRadar1.w;
		ImVec4 DynamicRadar3 = ImGui::ColorConvertU32ToFloat4(data["22"]["4"]);
		Color::DynamicRadar[3][0] = DynamicRadar3.x;
		Color::DynamicRadar[3][1] = DynamicRadar3.y;
		Color::DynamicRadar[3][2] = DynamicRadar3.z;
		Color::DynamicRadar[3][3] = DynamicRadar3.w;
		ImVec4 Compass1 = ImGui::ColorConvertU32ToFloat4(data["22"]["5"]);
		Color::Compass[1][0] = Compass1.x;
		Color::Compass[1][1] = Compass1.y;
		Color::Compass[1][2] = Compass1.z;
		Color::Compass[1][3] = Compass1.w;
		ImVec4 Compass3 = ImGui::ColorConvertU32ToFloat4(data["22"]["6"]);
		Color::Compass[3][0] = Compass3.x;
		Color::Compass[3][1] = Compass3.y;
		Color::Compass[3][2] = Compass3.z;
		Color::Compass[3][3] = Compass3.w;
	}

	if (data.contains("23"))
	{
		ImVec4 Dist0 = ImGui::ColorConvertU32ToFloat4(data["23"]["0"]);
		Color::Distance[0][0] = Dist0.x;
		Color::Distance[0][1] = Dist0.y;
		Color::Distance[0][2] = Dist0.z;
		Color::Distance[0][3] = Dist0.w;
		ImVec4 dist2 = ImGui::ColorConvertU32ToFloat4(data["23"]["1"]);
		Color::Distance[2][0] = dist2.x;
		Color::Distance[2][1] = dist2.y;
		Color::Distance[2][2] = dist2.z;
		Color::Distance[2][3] = dist2.w;
		ImVec4 Lootnonvis = ImGui::ColorConvertU32ToFloat4(data["23"]["2"]);
		loot_esp::Loot_Color_Non_Vis[0] = Lootnonvis.x;
		loot_esp::Loot_Color_Non_Vis[1] = Lootnonvis.y;
		loot_esp::Loot_Color_Non_Vis[2] = Lootnonvis.z;
		loot_esp::Loot_Color_Non_Vis[3] = Lootnonvis.w;
		ImVec4 DynamicRadar0 = ImGui::ColorConvertU32ToFloat4(data["23"]["3"]);
		Color::DynamicRadar[0][0] = DynamicRadar0.x;
		Color::DynamicRadar[0][1] = DynamicRadar0.y;
		Color::DynamicRadar[0][2] = DynamicRadar0.z;
		Color::DynamicRadar[0][3] = DynamicRadar0.w;
		ImVec4 DynamicRadar2 = ImGui::ColorConvertU32ToFloat4(data["23"]["4"]);
		Color::DynamicRadar[2][0] = DynamicRadar2.x;
		Color::DynamicRadar[2][1] = DynamicRadar2.y;
		Color::DynamicRadar[2][2] = DynamicRadar2.z;
		Color::DynamicRadar[2][3] = DynamicRadar2.w;
		ImVec4 Compass0 = ImGui::ColorConvertU32ToFloat4(data["23"]["5"]);
		Color::Compass[0][0] = Compass0.x;
		Color::Compass[0][1] = Compass0.y;
		Color::Compass[0][2] = Compass0.z;
		Color::Compass[0][3] = Compass0.w;
		ImVec4 Compass2 = ImGui::ColorConvertU32ToFloat4(data["23"]["6"]);
		Color::Compass[2][0] = Compass2.x;
		Color::Compass[2][1] = Compass2.y;
		Color::Compass[2][2] = Compass2.z;
		Color::Compass[2][3] = Compass2.w;
	}

	if (data.contains("24"))
	{
		Exploits::ExtendedFOV = IntTobool(data["24"]["0"]);
		Commands::FOV = data["24"]["1"];
		Commands::Map = data["24"]["2"];
		Exploits::NightVision = IntTobool(data["24"]["3"]);
		Exploits::Airstuck = IntTobool(data["24"]["4"]);
		Exploits::ThirdPerson = IntTobool(data["24"]["5"]);
		Exploits::DynamicThirdPerson = IntTobool(data["24"]["6"]);
		Exploits::NoShellShock = IntTobool(data["24"]["7"]);
	}

	if (data.contains("25"))
	{
		cfg::Exploits::Melee_Lunge::Enable = IntTobool(data["25"]["0"]);
		cfg::Exploits::Melee_Lunge::Type = data["25"]["1"];
		cfg::Exploits::Melee_Lunge::Max_Distance = data["25"]["2"];
		cfg::Exploits::Melee_Lunge::Ignore_Team = IntTobool(data["25"]["3"]);
		cfg::Exploits::Melee_Lunge::Ignore_Knocked = IntTobool(data["25"]["4"]);
		cfg::Exploits::Melee_Lunge::Ignore_Invis = IntTobool(data["25"]["5"]);
	}

	if (data.contains("26"))
	{
		cfg::Exploits::Chat_Spam::Enable = IntTobool(data["26"]["0"]);
		cfg::Exploits::Chat_Spam::Spam_Message = IntTobool(data["26"]["1"]);
	}

	if (data.contains("27"))
	{
		Visuals::Miscellaneous::DynamicRadar::Drawing::Bots = IntTobool(data["27"]["0"]);
		Visuals::Miscellaneous::Compass::Drawing::Bots = IntTobool(data["27"]["1"]);
		Visuals::Main::Drawing::Bots = IntTobool(data["27"]["2"]);
	}

	if (data.contains("28"))
	{
		cfg::Esp::Platform = IntTobool(data["28"]["0"]);
		cfg::Esp::Device = IntTobool(data["28"]["1"]);
		cfg::Esp::Talking = IntTobool(data["28"]["2"]);

	}

	if (data.contains("29")) {
		Aimbot::Targeting::Bots = IntTobool(data["29"]["0"]);
		loot_esp::ZMEE = IntTobool(data["29"]["1"]);
		loot_esp::ZMMachines = IntTobool(data["29"]["2"]);
		loot_esp::Wallbuys = IntTobool(data["29"]["3"]);
		loot_esp::ZMTrap = IntTobool(data["29"]["4"]);
	}

	if (data.contains("30")) {
		ImVec4 Highlight = ImGui::ColorConvertU32ToFloat4(data["30"]["0"]);
		Color::HighlightColor[0] = Highlight.x;
		Color::HighlightColor[1] = Highlight.y;
		Color::HighlightColor[2] = Highlight.z;
		Color::HighlightColor[3] = Highlight.w;
	}

	f.close();
}