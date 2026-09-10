# Source-Code-Of-Major-Steel-And-Flesh-2-multiplayer-methods

This repository contains decompiled C++ source code for major multiplayer methods from a Steel and Flesh 2 multiplayer game, extracted using IL2CPP reverse engineering. Each file follows the IDA Pro / Hex-Rays decompilation format with method signatures, offsets, and RVA addresses.

## Repository Overview

This repo contains 9 methods related to Photon networking and game management, collected through multiple commits. The methods cover core multiplayer functionality including connection management, player info, spawning, master client operations, room joining, and main menu operations.

## Current Files in Repository

| File | Method | Signature | Offset | RVA | First Added |
|------|--------|-----------|--------|-----|-------------|
| `Assembly-CSharp/PhotonNetwork__CloseConnection.cpp` | PhotonNetwork::CloseConnection | `void __fastcall PhotonNetwork__CloseConnection(const MethodInfo *method)` | `0x156E5D8` | `0x15725D8` | Initial commit |
| `Assembly-CSharp/sc_game__FindPlayerInfo.cpp` | sc_game::FindPlayerInfo | `void __fastcall sc_game__FindPlayerInfo(const MethodInfo *method)` | `0x156E620` | `0x1572620` | Initial commit |
| `Assembly-CSharp/sc_game__SpawnHorse.cpp` | sc_game::SpawnHorse | `void __fastcall sc_game__SpawnHorse(const MethodInfo *method)` | `0x156E678` | `0x1572678` | Initial commit |
| `Assembly-CSharp/sc_game__SpawnSiege.cpp` | sc_game::SpawnSiege | `void __fastcall sc_game__SpawnSiege(const MethodInfo *method)` | `0x156E6E0` | `0x15726E0` | Initial commit |
| `Assembly-CSharp/NetworkingPeer__DestroyAll.cpp` | NetworkingPeer::DestroyAll | `void __fastcall NetworkingPeer__DestroyAll(const MethodInfo *method)` | `0x156ED58` | `0x1572D58` | v1 (ae0e3ab) |
| `Assembly-CSharp/NetworkingPeer__SetMasterClient.cpp` | NetworkingPeer::SetMasterClient | `bool PhotonNetwork::SetMasterClient(PhotonPlayer* masterClientPlayer, const MethodInfo* method)` | `0x156DED4` | `0x1571ED4` | v2 (2ab23ff) |
| `Assembly-CSharp/sc_main_menu__Join.cpp` | sc_main_menu::Join | `void __fastcall sc_main_menu__Join(const MethodInfo *method)` | `0x156F218` | `0x1573218` | Current HEAD |
| `Assembly-CSharp/PhotonNetwork__JoinRoom.cpp` | PhotonNetwork::JoinRoom | `bool __fastcall PhotonNetwork__JoinRoom(System_String_o *roomName, const MethodInfo *method)` | `0x156EAF4` | `0x1572AF4` | Current HEAD |
| `Assembly-CSharp/sc_main_menu__UnBan.cpp` | sc_main_menu::UnBan | `void __fastcall sc_main_menu__UnBan(sc_main_menu_o *this, const MethodInfo *method)` | `0x1208E50` | `0x1248E50` | Current HEAD |

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
- **Game room:** Creates Hashtable with MasterClientId (key 0xF8), sends via OpSetPropertiesOfRoom
- **Non-game room:** Checks IsMasterClient, sets directly via peer->SetMasterClient()

### 7. sc_main_menu::Join
**Purpose:** Join a multiplayer game session from the main menu.
- Triggers the UI flow for joining a game
- Supports multiple join modes: QuickMatch, CustomGame, FriendsOnly, Default
- Validates join configuration before attempting connection
- Navigates to appropriate join screen based on game mode

### 8. PhotonNetwork::JoinRoom
**Purpose:** Join a room by name.
- Static initialization guard (byte_2D5A000+0x901)
- Validates roomName not null/empty
- Checks connection readiness via internal state
- Delegates to internal JoinRoom overload with default parameters

### 9. sc_main_menu::UnBan
**Purpose:** Unban a player or reset ban state.
- Static initialization guard (byte_2D5A000+0x1E3)
- Preference key validation (from `this + 0x30`)
- Sets preference integer to 0 via `UnityEngine.PlayerPrefs::SetInt`
- Saves profile via `sc_info_simple::SaveProfile` if key exists
- Error logging if key is missing/null

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

## commit History

| Commit | Author | Description |
|--------|--------|-------------|
| `108d971` | Researcher | Added sc_main_menu__UnBan IL2CPP source |
| `33e5076` | Researcher | Added PhotonNetwork::JoinRoom IL2CPP source |
| `e1d2557` | Researcher | Updated sc_main_menu::Join with real IL2CPP code |
| `da14d57` | Researcher | Added sc_main_menu::Join IL2CPP source and update README |
| `a0a6a7e` | Researcher | Fix readme.md // remove ai slop |
| `03572c5` | Researcher | Added NetworkingPeer::SetMasterClient IL2CPP source |
| `b7729ab` | halal101 | Added readme |
| `bc32107` | halal101 | test |
| `52db8d8` | halal101 | fix file name |
| `80273aa` | halal101 | fix file name |
| `cb6bbeb` | halal101 | Delete invalid ifle |
| `51b6f4a` | halal101 | add multiple source files |
| `f5a510d` | halal101 | fix file extension |
| `ae0e3ab` | halal101 | Add DestroyAll Code |
| `4308219` | halal101 | delete a file |
| `2ab23ff` | halal101 | Add SetMasterClient Code |
| `b6f67ff` | halal101 | Add SetMasterClient Code |
| `9ce77c3` | halal101 | Created PhotonNetwork::CloseConnection.cpp |
| `7fd1014` | Initial | Repository creation with LICENSE and README |

## Usage

These source files are intended for:
- Research into multiplayer networking implementation
- Understanding IL2CPP code generation patterns
- Game server/client development reference
- Educational purposes in reverse engineering

## License

MIT license (as per original repository)