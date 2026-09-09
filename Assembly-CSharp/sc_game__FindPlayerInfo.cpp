// Method Signature: void __fastcall sc_game__FindPlayerInfo(const MethodInfo *method)
// Offset: 0x156E620
// RVA/VA: 0x1572620
// C++ Source:

#include "sc_game.h"

void __fastcall sc_game__FindPlayerInfo(const MethodInfo *method, sc_game::GameManager *this, const MethodInfo *callMethodInfo)
{
    // sc_game::FindPlayerInfo
    // Purpose: Find player information from the game state
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the GameManager instance
    //   callMethodInfo: Additional method invocation information

    // Search through the player list to find the requested player
    PlayerInfo *result = nullptr;
    Il2CppObject **players = this->m_PlayerList;
    int32_t playerCount = this->m_PlayerCount;
    
    for (int32_t i = 0; i < playerCount; i++)
    {
        if (players[i]->m_PlayerId == this->m_TargetPlayerId)
        {
            result = (PlayerInfo *)players[i];
            break;
        }
    }
    
    // Return the found player info or null
    method->methodReturnValue = result;
}