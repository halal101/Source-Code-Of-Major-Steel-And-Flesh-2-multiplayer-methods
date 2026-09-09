// Method Signature: void __fastcall sc_game__SpawnSiege(const MethodInfo *method)
// Offset: 0x156E6E0
// RVA/VA: 0x15726E0
// C++ Source:

#include "sc_game.h"

void __fastcall sc_game__SpawnSiege(const MethodInfo *method, sc_game::GameManager *this, const MethodInfo *callMethodInfo)
{
    // sc_game::SpawnSiege
    // Purpose: Spawn a siege engine in the game world
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the GameManager instance
    //   callMethodInfo: Additional method invocation information

    // Determine siege type and position
    SiegeType siegeType = (SiegeType)method->methodDefinition->m_typeDefinitionIndex;
    Vector3 spawnPos = this->m_SiegeSpawnPositions[method->methodIndex % this->m_SiegeSpawnPositionCount];
    Quaternion spawnRot = Quaternion::identity;
    
    // Load siege prefab based on type
    char prefabName[64];
    snprintf(prefabName, sizeof(prefabName), "Siege_%s_Prefab", SiegeTypeName[siegeType]);
    
    GameObject *siegePrefab = Resources::Load<GameObject>(prefabName);
    if (siegePrefab)
    {
        GameObject *siege = Object::Instantiate(siegePrefab, spawnPos, spawnRot);
        siege->m_IsNetworked = true;
        
        // Set up siege components
        SiegeEngine *engine = siege->AddComponent<SiegeEngine>();
        engine->m_Damage = 50.0f;
        engine->m_MaxHealth = 500.0f;
        engine->m_Owner = this;
        
        // Network the siege entity
        NetworkingPeer::AddNetworkView(siege);
    }
}