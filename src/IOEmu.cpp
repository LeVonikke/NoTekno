#include <windows.h>
#include <MinHook.h>
#include "hooks.h"

void InstallIOHooks() {
    // OpenParrot64.dll is now loaded in DirectInput8Create (main.cpp)
    // to avoid loader lock and ensure correct paths.
}
