// Method Signature: PhotonNetwork__SetMasterClient(PhotonPlayer_o *masterClientPlayer, const MethodInfo *method)
// Offset: 0x156DED4
// RVA/VA: 0x1571ED4
// C++ Source:

#include "PhotonNetwork.h"
#include "PhotonPlayer.h"
#include "NetworkingPeer.h"
#include "Hashtable.h"
#include "Room"

bool __fastcall PhotonNetwork__SetMasterClient(const MethodInfo *method, PhotonNetwork *this, PhotonPlayer *masterClientPlayer, const MethodInfo *callMethodInfo)
{
    // PhotonNetwork::SetMasterClient
    // Purpose: Set the master client for the room
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the PhotonNetwork instance
    //   masterClientPlayer: The PhotonPlayer to set as master client
    //   callMethodInfo: Additional method invocation information

    // Static initialization guard (byte_2D5A000+0x91F)
    static bool initialized = false;
    if (!initialized)
    {
        // Initialize static fields (resolved at runtime by Il2Cpp)
        initialized = true;
    }

    // Get the singleton instance (photonNetwork)
    PhotonNetwork* photonNetwork = GetPhotonNetworkInstance();
    if (!photonNetwork) return false;

    // Check if we're in a room
    if (!PhotonNetwork::get_inRoom()) return false;

    // Verify network can be used
    if (!PhotonNetwork::VerifyCanUseNetwork()) return false;

    // Get the NetworkingPeer
    NetworkingPeer* peer = photonNetwork->networkingPeer;
    if (!peer || !peer->IsConnected) return false;

    // Check if we're already the master client
    // At offset 0x2C in NetworkingPeer, there's a field that indicates if we're master
    if (peer->isMasterClient == 1)
    {
        // Already master client
        return false;
    }

    // Get the room
    Room* room = PhotonNetwork::get_room();
    if (!room) return false;

    // Check if the room is a "game room" (has players)
    if (room->isGameRoom)
    {
        // Game room: Create Hashtable with MasterClientId property
        // Key 0xF8 is the MasterClientId property code
        Hashtable* gameProperties = new Hashtable();
        
        // Add the "MasterClientId" property to the hashtable
        // The value is the player's actor number
        gameProperties->Add(0xF8, masterClientPlayer->actorNumber);
        
        // Create another Hashtable for expected properties (empty)
        Hashtable* expectedProperties = new Hashtable();
        
        // Add the current master client ID to expected properties
        int currentMasterId = peer->GetMasterClientId();
        expectedProperties->Add(0xF8, currentMasterId);
        
        // Send the properties to the room via OpSetPropertiesOfRoom
        peer->OpSetPropertiesOfRoom(gameProperties, expectedProperties, 0, nullptr);
        
        return true;
    }
    else
    {
        // Not a game room: check if we're the master client
        if (PhotonNetwork::get_isMasterClient())
        {
            // We are the master client, so we can set the master directly
            if (masterClientPlayer != nullptr)
            {
                // Set the master client via the NetworkingPeer
                peer->SetMasterClient(masterClientPlayer->actorNumber, true);
                return true;
            }
        }
        return false;
    }
}