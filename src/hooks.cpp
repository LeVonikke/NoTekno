#include <windows.h>
#include <MinHook.h>
#include "hooks.h"

void InitializeHooks() {
    if (MH_Initialize() != MH_OK) {
        return;
    }

    InstallNetworkHooks();
    InstallBanapassHooks();
    InstallIOHooks();

    MH_EnableHook(MH_ALL_HOOKS);
}
