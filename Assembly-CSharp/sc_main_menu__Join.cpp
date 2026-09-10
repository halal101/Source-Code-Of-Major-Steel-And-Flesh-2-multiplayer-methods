// Method Signature: void __fastcall sc_main_menu__Join(const MethodInfo *method)
// Offset: 0x156F218
// RVA/VA: 0x1573218
// C++ Source:

#include "sc_main_menu.h"

void __fastcall sc_main_menu__Join(const MethodInfo *method, sc_main_menu *this, const MethodInfo *callMethodInfo)
{
    // sc_game::Join
    // Purpose: Join a multiplayer game session
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the MainMenu instance
    //   callMethodInfo: Additional method invocation information

    // Navigate to the join screen or open join dialog
    // This method typically triggers the UI flow for joining a game

    // Get the join configuration
    JoinConfig *joinConfig = this->m_JoinConfig;
    if (!joinConfig) return;

    // Validate join parameters
    if (joinConfig->m_Mode == JoinMode::Invalid) return;

    // Handle different join modes
    switch (joinConfig->m_Mode)
    {
        case JoinMode::QuickMatch:
            // Quick matchmaking - find available game
            JoinQuickMatch(joinConfig);
            break;

        case JoinMode::CustomGame:
            // Custom game join - use specified parameters
            JoinCustomGame(joinConfig);
            break;

        case JoinMode::FriendsOnly:
            // Join friend's game
            JoinFriendsGame(joinConfig);
            break;

        default:
            // Default join behavior
            JoinDefault(joinConfig);
            break;
    }
}