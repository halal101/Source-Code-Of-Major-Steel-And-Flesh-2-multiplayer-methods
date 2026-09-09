// Method Signature: void __fastcall NetworkingPeer__DestroyAll(const MethodInfo *method)
// Offset: 0x156ED58
// RVA/VA: 0x1572D58
// C++ Source:

#include "NetworkingPeer.h"

void __fastcall NetworkingPeer__DestroyAll(const MethodInfo *method, NetworkingPeer *this, const MethodInfo *callMethodInfo)
{
    // NetworkingPeer::DestroyAll
    // Purpose: Destroy all networked objects and views
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the NetworkingPeer instance
    //   callMethodInfo: Additional method invocation information

    // Iterate through all instantiated objects and destroy them
    Dictionary_2_2 * instantiatedObjects = this->m_CachedRpcInfos;
    int32_t count = instantiatedObjects->m_size;
    
    for (int32_t i = 0; i < count; i++)
    {
        Il2CppObject *key = nullptr;
        Il2CppObject *value = nullptr;
        Dictionary_2_2_get_Item(instantiatedObjects, i, &key, &value);
        
        // Get the PhotonView from the instantiated object
        PhotonView *view = (PhotonView *)value;
        
        // Destroy the PhotonView and its associated game object
        if (view)
        {
            PhotonView::Destroy(view);
        }
    }
    
    // Clear the cached RPC information
    instantiatedObjects->m_size = 0;
    instantiatedObjects->m_version = 0;
}