// Method Signature: void __fastcall sc_game__SpawnHorse(const MethodInfo *method)
// Offset: 0x156E678
// RVA/VA: 0x1572678
// C++ Source:

#include "sc_game.h"

void __fastcall sc_game__SpawnHorse(const MethodInfo *method, sc_game::Player *this, const MethodInfo *callMethodInfo)
{
    // sc_game::SpawnHorse
    // Purpose: Spawn a horse for the player
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the Player instance
    //   callMethodInfo: Additional method invocation information

    // Create horse entity at player position
    GameObject *horsePrefab = Resources::Load<GameObject>("HorsePrefab");
    Vector3 playerPos = this->m_CurrentPosition;
    Quaternion playerRot = this->m_CurrentRotation;
    
    if (horsePrefab)
    {
        GameObject *horse = Object::Instantiate(horsePrefab, playerPos, playerRot);
        horse->m_IsNetworked = true;
        horse->m_PlayerOwner = this;
        
        // Set up horse components
        HorseController *controller = horse->AddComponent<HorseController>();
        controller->m_Rider = this;
        controller->m_Speed = 5.0f;
    }
}