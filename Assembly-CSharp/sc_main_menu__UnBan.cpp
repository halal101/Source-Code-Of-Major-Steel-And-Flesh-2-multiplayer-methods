// Method Signature: void __fastcall sc_main_menu__UnBan(sc_main_menu_o *this, const MethodInfo *method)
// Offset: 0x1208E50
// RVA/VA: 0x1248E50
// C++ Source:

#include "sc_main_menu.h"
#include "MethodInfo.h"
#include "UnityEngine/PlayerPrefs.h"
#include "sc_info_simple.h"

void __fastcall sc_main_menu__UnBan(const MethodInfo *method, sc_main_menu *this, const MethodInfo *callMethodInfo)
{
    // sc_main_menu::UnBan
    // Purpose: Unban a player or reset ban state
    // Parameters:
    //   method: MethodInfo structure containing method metadata
    //   this: Pointer to the MainMenu instance
    //   callMethodInfo: Additional method invocation information

    // Static initialization guard (byte_2D5A000+0x1E3)
    static bool initialized = false;
    if (!initialized)
    {
        // Initialize static fields (resolved at runtime by Il2Cpp)
        initialized = true;
    }

    // Reset some pref related to ban or graphics? 
    // The code stores 1 into byte_2D5A000+0x1E3 if not set.
    // Then it loads from X21 which is from [X21,#0x148] (some global settings)
    // Then it calls UnityEngine.PlayerPrefs::SetInt with key from X19+0x30 and value 0.
    // Then if that key/value exists, it calls sc_info_simple::SaveProfile with that string.
    // Otherwise it calls loc_1069180 (error logging?).

    // Get the key string from this + 0x30 (likely a pref key)
    Il2CppString* prefKey = this->m_PrefKey; // assuming offset 0x30
    if (prefKey != nullptr && prefKey->m_stringLength > 0)
    {
        // Set the preference integer to 0 (unban or reset)
        UnityEngine::PlayerPrefs::SetInt(prefKey, 0);

        // Save the profile using the key as profile name?
        sc_info_simple::SaveProfile(prefKey);
    }
    else
    {
        // If key is empty or null, log error or show message
        // The code jumps to loc_1069180 which likely logs an error.
        // We'll call a generic error log.
        sc_main_menu::Log("UnBan failed: missing preference key");
    }
}