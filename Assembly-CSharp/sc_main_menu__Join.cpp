// Method Signature: void __fastcall sc_main_menu__Join(sc_main_menu_o *this, RoomInfo_o *room, const MethodInfo *method)
// Offset: 0x156F218
// RVA/VA: 0x1573218
// C++ Source:

#include "sc_main_menu.h"
#include "RoomInfo.h"
#include "MethodInfo.h"
#include "GameManager.h"
#include "PhotonNetwork.h"
#include "NetworkingPeer.h"
#include "Hashtable.h"
#include "GameObject.h"

void __fastcall sc_main_menu__Join(const MethodInfo *method, sc_main_menu *this, RoomInfo *room, const MethodInfo *callMethodInfo)
{
    // sc_main_menu::Join
    // Purpose: Join a multiplayer game session from the main menu
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the MainMenu instance
    //   room: Pointer to the RoomInfo instance (target room to join)
    //   callMethodInfo: Additional method invocation information

    // Validate inputs
    if (!this || !room || !method) return;

    // Get the photon networking peer
    NetworkingPeer *peer = PhotonNetwork::get_networkingPeer();
    if (!peer) return;

    // Save player preferences before joining (room slot, map info, etc.)
    // PlayerPrefs::SetInt("join_slot", ...)
    UnityEngine::PlayerPrefs::SetInt("join_slot", room->m_SlotIndex);

    // Save map name information
    // sc_info_simple::SaveProfile(...)
    if (room->m_MapName != NULL) {
        sc_info_simple::SaveProfile(room->m_MapName);
    }

    // Set the player name via PhotonNetwork
    // PhotonNetwork::set_playerName(...)
    PhotonNetwork::set_playerName(this->m_PlayerName);

    // Check room properties and validate join conditions
    // Check if room has required properties (checks hashtable items)
    Hashtable *roomProps = room->m_CustomProperties;
    if (!roomProps) {
        // No custom properties, proceed with join
    } else {
        // Check various room properties
        // Check slot count
        int slotCount = roomProps->Item("slot_count");
        if (slotCount > 0) {
            // Validate player count against slot count
            if (room->m_PlayerCount >= slotCount) {
                // Room is full, show error and return
                sc_main_menu::Error("Room is full!");
                return;
            }
        }

        // Check map name property
        Il2CppString *mapName = (Il2CppString *)roomProps->Item("map_name");
        if (mapName != NULL) {
            // Validate map name matches expected format
            // System::Char::Parse, System::String::Split logic
            // ... (complex parsing logic from IL2CPP)
        }

        // Check max players property
        int maxPlayers = *(int *)roomProps->Item("max_players");
        if (maxPlayers > 0) {
            // Validate player count against max players
            if (room->m_PlayerCount >= maxPlayers) {
                // Room is full
                sc_main_menu::Error("Room is full!");
                return;
            }
        }
    }

    // Check if joining as master client
    if (peer->get_isMasterClient()) {
        // If already master, proceed with join
    } else {
        // Not master, attempt to set as master
        PhotonPeer::SetMasterClient(this->m_LocalPlayer->actorNumber, true);
    }

    // Prepare room name for logging
    // System::String::Concat with room name
    Il2CppString *roomName = room->m_Name;
    Il2CppString *concatStr = System::String::Concat_33205720(roomName, "_joining");

    // Log the join attempt
    sc_main_menu::Log(concatStr);

    // Get room capacity and player list
    // System::Collections::Generic::List_int::AddWithResize
    // ... (list manipulation logic)

    // Get room info data for display
    // ClassGameMap::GetName for map name
    // ... (game map name retrieval)

    // Final check before joining - validate room still valid
    if (!room->isValidForJoin()) {
        // Room is no longer valid, abort join
        sc_main_menu::Error("Room is no longer available!");
        return;
    }

    // ACTUALLY JOIN THE ROOM via Photon
    // PhotonNetwork::JoinRoom(...)
    PhotonNetwork::JoinRoom(room->m_Name, room->m_MaxPlayers, room->m_InterestGroups, room->m_LobbyType);

    // After JoinRoom callback will activate the game window
    // sc_main_menu::ActivateWindow will be called by the JoinRoom callback
}