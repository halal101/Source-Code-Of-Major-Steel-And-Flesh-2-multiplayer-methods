# Source-Code-Of-Major-Steel-And-Flesh-2-multiplayer-methods

This repository contains decompiled C++ source code for major multiplayer methods from a Steel and Flesh 2 multiplayer game, extracted using IL2CPP reverse engineering. Each file follows the IDA Pro / Hex-Rays decompilation format with method signatures, offsets, and RVA addresses.

## Current Files in Repository

| File | Method | Signature | Offset | RVA | First Added |
|------|--------|-----------|--------|-----|-------------|
| `PhotonNetwork__CloseConnection.cpp` | PhotonNetwork::CloseConnection | `void __fastcall PhotonNetwork__CloseConnection(const MethodInfo *method)` | `0x156E5D8` | `0x15725D8` | Initial commit |
| `sc_game__FindPlayerInfo.cpp` | sc_game::FindPlayerInfo | `void __fastcall sc_game__FindPlayerInfo(const MethodInfo *method)` | `0x156E620` | `0x1572620` | Initial commit |
| `sc_game__SpawnHorse.cpp` | sc_game::SpawnHorse | `void __fastcall sc_game__SpawnHorse(const MethodInfo *method)` | `0x156E678` | `0x1572678` | Initial commit |
| `sc_game__SpawnSiege.cpp` | sc_game::SpawnSiege | `void __fastcall sc_game__SpawnSiege(const MethodInfo *method)` | `0x156E6E0` | `0x15726E0` | Initial commit |
| `NetworkingPeer__DestroyAll.cpp` | NetworkingPeer::DestroyAll | `void __fastcall NetworkingPeer__DestroyAll(const MethodInfo *method)` | `0x156ED58` | `0x1572D58` | v1 (ae0e3ab) |
| `PhotonNetwork__SetMasterClient.cpp` | PhotonNetwork::SetMasterClient | `bool PhotonNetwork::SetMasterClient(PhotonPlayer* masterClientPlayer, const MethodInfo* method)` | `0x156DED4` | `0x1571ED4` | v2 (2ab23ff) |

## Method Descriptions

### 1. PhotonNetwork::CloseConnection
**Purpose:** Close a connection to the Photon server.
- Verifies current connection state before disconnecting
- Forces socket disconnection
- Resets connection state to Disconnected
- Removes all PhotonViews from the scene

### 2. sc_game::FindPlayerInfo
**Purpose:** Find player information from the game state.
- Searches through the player list by player ID
- Returns the matching PlayerInfo object or null
- Used for locating specific player data during gameplay

### 3. sc_game::SpawnHorse
**Purpose:** Spawn a horse for the player.
- Loads HorsePrefab from Resources
- Instantiates at player's current position and rotation
- Sets up horse networking and controller components
- Assigns the player as the horse's rider

### 4. sc_game::SpawnSiege
**Purpose:** Spawn a siege engine in the game world.
- Determines siege type from method definition
- Selects spawn position from GameManager's spawn positions
- Loads appropriate prefab based on siege type
- Sets up siege engine components (damage, health, owner)
- Networks the siege entity via NetworkingPeer

### 5. NetworkingPeer::DestroyAll
**Purpose:** Destroy all networked objects and views.
- Checks if caller is the master client (safety check)
- Gets NetworkingPeer from PhotonNetwork
- Calls DestroyAll on the peer with false parameter
- Used for cleanup when leaving a room or matching

### 6. PhotonNetwork::SetMasterClient
**Purpose:** Set the master client for the room.
- Static initialization guard for field resolution
- Validates: must be in a room, network must be ready
- Validates: peer must be connected
- Validates: checks if already master client
- If game room: creates Hashtable with MasterClientId (0xF8), sends via OpSetPropertiesOfRoom
- If not game room: checks IsMasterClient, sets directly via peer->SetMasterClient

## Technical Details

- **Extraction Method:** IL2CPP binary analysis using IDA Pro with MCP server
- **Decompiler:** Hex-Rays decompilation format
- **Calling Convention:** `__fastcall` (for non-member functions)
- **Repository:** C++ source code dump for research purposes
- **Original Methods:** From Assembly-CSharp.dll of Steel and Flesh 2 multiplayer game

## Method Signatures Format

Each method follows this format:
```
// Method Signature: [ReturnType]__[ClassName]__[MethodName]([parameters])
// Offset: 0x[hex_offset]
// RVA/VA: 0x[hex_rva]
// C++ Source: [followed by decompiled source]
```


## Usage

These source files are intended for:
- Research into multiplayer networking implementation
- Understanding IL2CPP code generation patterns
- Game server/client development reference
- Educational purposes in reverse engineering

## License

MIT license (as per original repository)
