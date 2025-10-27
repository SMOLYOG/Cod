#pragma once
#include "Lobby_Info.h"

std::string getPlatformStr(__int8 platform) {
    switch (platform) {
    case 0:
        return "H"; // Steam
    case 1:
        return "B"; // Steam
    case 2:
        return "A"; // Bnet
    case 3:
    case 4:
        return "C"; // Xbox
    case 5:
    case 6:
        return "F"; // Playstation
    case 9:
        return "G"; // Android
    case 11:
    case 12:
        return "H"; // Gamepass
    default:
        return "H"; // Gamepass
    }

    return std::to_string(platform);
}

void Grab_Lobby_Info()
{

    DWORD64* PartyData = GameCall<DWORD64*>(Offset::Lobby_GetPartyData)();
    if (PartyData == NULL)
        return;

    if (!Globals::InGame2) {

        for (int i = 0; i < Globals::MaxPlayerCount; i++) 
        {
            Lobby[i].highlight = false;
        }

        Lobby[0].platform = 12;
        Lobby[0].platform_String = getPlatformStr(Lobby[0].platform);
        Lobby[0].gamertag = "NULL";
        Lobby[0].gamepad = false;
        Lobby[0].GPad_String = Lobby[0].gamepad ? "D" : "E";
        Lobby[0].IsTalking = false;
        Lobby[0].Talking_String = Lobby[0].IsTalking ? "I" : "J";
        Lobby[0].Team = 0;
        Lobby[0].Ping = 0;
        Lobby[0].Deaths = 0;
        Lobby[0].Kills = 0;
        Lobby[0].Score = 0;
        Lobby[0].Rank = 0;
        Lobby[0].xuid = 123456789;
    }
    else {
        for (int i = 0; i < Globals::MaxPlayerCount; i++) {

            Lobby[i].Can_Draw = false;

            Lobby[i].client_Number = i;

            Lobby[i].platform = GameCall<__int8>(Offset::getPlatform)(PartyData, i);

            Lobby[i].platform_String = getPlatformStr(Lobby[i].platform);

            Lobby[i].gamertag = GameCall<const char*>(Offset::getName)(PartyData, i);

            Lobby[i].gamepad = GameCall<bool>(Offset::usingGamepad)(PartyData, i);

            Lobby[i].GPad_String = Lobby[i].gamepad ? "D" : "E";

            Lobby[i].IsTalking = GameCall<bool>(Offset::CL_IsPlayerTalking)(PartyData, i);

            Lobby[i].Talking_String = Lobby[i].IsTalking ? "I" : "J";

            Lobby[i].IsMuted = GameCall<int>(Offset::Party_IsMemberDeafened)(PartyData, 0, i);

            Lobby[i].Team = VariadicCall<int>(Offset::JmpRbx, Offset::Party_GetMemberTeam, PartyData, 0, i);

            if (!GlobalPlayerData::Score(i)) {
                Lobby[i].Ping = 0;
                Lobby[i].Deaths = 0;
                Lobby[i].Kills = 0;
                Lobby[i].Score = 0;
                Lobby[i].Rank = 0;
            }
            else {
                Lobby[i].Ping = GlobalPlayerData::Score(i)->ping;
                Lobby[i].Deaths = GlobalPlayerData::Score(i)->deaths;
                Lobby[i].Kills = GlobalPlayerData::Score(i)->kills;
                Lobby[i].Score = GlobalPlayerData::Score(i)->score;
                Lobby[i].Rank = GlobalPlayerData::Score(i)->Rank;

            }

            GameCall<unsigned __int64>(Offset::getXUID)(&Lobby[i].xuid, PartyData, i);

            Lobby[i].Can_Draw = true;

        }
    }  
}

