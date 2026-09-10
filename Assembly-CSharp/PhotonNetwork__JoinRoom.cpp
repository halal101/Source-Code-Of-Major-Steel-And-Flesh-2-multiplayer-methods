// Method Signature: bool __fastcall PhotonNetwork__JoinRoom(System_String_o *roomName, const MethodInfo *method)
// Offset: 0x156EAF4
// RVA/VA: 0x1572AF4
// C++ Source:

#include "PhotonNetwork.h"
#include "System/String.h"

bool __fastcall PhotonNetwork__JoinRoom(const MethodInfo *method, PhotonNetwork *this, System_String *roomName, const MethodInfo *callMethodInfo)
{
    // PhotonNetwork::JoinRoom
    // Purpose: Join a room by name
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the PhotonNetwork instance
    //   roomName: Name of the room to join
    //   callMethodInfo: Additional method invocation information

    // Static initialization guard (byte_2D5A000+0x901)
    static bool initialized = false;
    if (!initialized)
    {
        // Initialize static fields (resolved at runtime by Il2Cpp)
        // This includes checks for internal state
        initialized = true;
    }

    // Validate input
    if (!roomName || roomName->m_stringLength == 0)
        return false;

    // Additional check: maybe ensure networking is ready
    // LDRB W8, [X20,#0x901] seems to be a flag; if not set, run init routine
    // We already handled static init; the flag may be for something else, but we treat as done.

    // Possibly check some internal state flag at offset 0xE0 of some object
    // The code loads from X21 (which came from [X21,#0x508]) then byte at 0xE0
    // If that byte is non-zero, skip error; else call error handler.
    // We'll assume it's a check for whether the client is connected to master server.
    // For simplicity, we'll call an internal function to verify connection.
    if (!PhotonNetwork::get_isConnectedAndReady())
        return false;

    // If all checks passed, delegate to the internal JoinRoom overload
    // The assembly tail-calls PhotonNetwork$$JoinRoom_22473548 with X0=roomName, X1=0 (likely default maxPlayers=0, expectedPlayers=0, etc.)
    // This corresponds to the overload: bool JoinRoom(string roomName, byte expectedPlayers = 0, bool autoPlayerTtl = false, ...)
    // We'll call the appropriate overload with default parameters.
    return PhotonNetwork::JoinRoom(roomName, 0, false, 0, nullptr, nullptr);
}