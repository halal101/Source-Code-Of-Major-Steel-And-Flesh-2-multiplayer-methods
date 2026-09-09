// Method Signature: PhotonNetwork__SetMasterClient(PhotonPlayer_o *masterClientPlayer, const MethodInfo *method)
// Offset: 0x156DED4
// RVA/VA: 0x1571ED4
// C++ Source:

bool PhotonNetwork::SetMasterClient(PhotonPlayer* masterClientPlayer, const MethodInfo* method)
{
    // Static initialization guard (byte_2D5A000+0x91F)
    static bool initialized = false;
    if (!initialized) {
        // Initialize static fields (all those ADRP/LDR/BL calls)
        // These are the various static field initializations
        // I've simplified this section since the actual values are resolved at runtime
        initialized = true;
    }

    // Get the singleton instance (photonNetwork)
    PhotonNetwork* photonNetwork = GetPhotonNetworkInstance();
    if (!photonNetwork) return false;

    // Check if we're in a room
    if (!PhotonNetwork::get_inRoom()) {
        return false;
    }

    // Verify network can be used
    if (!PhotonNetwork::VerifyCanUseNetwork()) {
        return false;
    }

    // Check if the network is connected (byte_2D5A000+0x87B is a network state flag)
    // This appears to be a "network ready" check
    // If not ready, we log and return false

    // Get the NetworkingPeer
    NetworkingPeer* peer = photonNetwork->networkingPeer;

    // Check if the peer is connected
    if (!peer || !peer->IsConnected) {
        return false;
    }

    // Check if we're already the master client
    // At offset 0x2C in NetworkingPeer, there's a field that indicates if we're master
    if (peer->isMasterClient == 1) {
        // Log: "Called SetMasterClient, but we are already master"
        return false;
    }

    // Get the room
    Room* room = PhotonNetwork::get_room();
    if (!room) {
        return false;
    }

    // Check if the room is a "game room" (has players)
    if (room->isGameRoom) {
        // This appears to be the "make master client" functionality
        // Creating a Hashtable with properties to update the room
        
        // Create a new Hashtable for properties
        Hashtable* gameProperties = new Hashtable();
        
        // Add the "MasterClientId" property to the hashtable
        // The key is "0xF8" (MasterClientId property code)
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
    } else {
        // If not in a game room, check if we're the master client
        if (PhotonNetwork::get_isMasterClient()) {
            // We are the master client, so we can set the master directly
            if (masterClientPlayer != nullptr) {
                // Set the master client via the NetworkingPeer
                peer->SetMasterClient(masterClientPlayer->actorNumber, true);
                return true;
            }
        }
        return false;
    }
}
