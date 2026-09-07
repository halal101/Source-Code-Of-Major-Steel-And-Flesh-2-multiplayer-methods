// Method Signature: void __fastcall PhotonNetwork__DestroyAll(const MethodInfo *method)
// Offset: 0x156E5D8
// RVA/VA: 0x15725D8
// C++ Source:

void PhotonNetwork::DestroyAll(const MethodInfo* method)
{
    // Static initialization guard (byte_2D5A000+0x924)
    static bool initialized = false;
    if (!initialized) {
        // Initialize static fields
        // These are the various static field initializations (ADRP/LDR/BL calls)
        // The actual values are resolved at runtime by Il2Cpp
        initialized = true;
    }

    // Get the singleton instance (photonNetwork)
    PhotonNetwork* photonNetwork = GetPhotonNetworkInstance();
    if (!photonNetwork) return;

    // Check if we are the master client
    if (!PhotonNetwork::get_isMasterClient()) {
        // Log error: "Only master client can call DestroyAll"
        Debug::LogError("Only the master client can call DestroyAll");
        return;
    }

    // Get the NetworkingPeer from photonNetwork
    NetworkingPeer* peer = photonNetwork->networkingPeer;
    if (!peer) {
        return; // Will go to error handler (loc_15726A0)
    }

    // Call NetworkingPeer::DestroyAll with parameter false
    // The second parameter (W1) is false (0)
    // The third parameter (X2) is null (0)
    peer->DestroyAll(false, nullptr);
}
