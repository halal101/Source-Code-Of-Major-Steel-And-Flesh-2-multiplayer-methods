// Method Signature: void __fastcall PhotonNetwork__CloseConnection(const MethodInfo *method)
// Offset: 0x156E5D8
// RVA/VA: 0x15725D8
// C++ Source:

#include "PhotonNetwork.h"

void __fastcall PhotonNetwork__CloseConnection(const MethodInfo *method, PhotonNetwork *this, const MethodInfo *callMethodInfo)
{
    // PhotonNetwork::CloseConnection
    // Purpose: Close a connection to the Photon server
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the PhotonNetwork instance
    //   callMethodInfo: Additional method invocation information

    // Verify we have a valid connection before closing
    if (this->m_CurrentState == ConnectionState::Connected)
    {
        // Force disconnect from the Photon server
        PhotonSocket::Disconnect(this->m_PhotonSocket);
        
        // Reset connection state
        this->m_CurrentState = ConnectionState::Disconnected;
        
        // Clean up any related objects
        PhotonView::RemoveAll();
    }
}