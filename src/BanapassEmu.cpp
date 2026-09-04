#include <windows.h>
#include "hooks.h"

void InstallBanapassHooks() {
    // Attempt to load Asakura OpenBanapass directly if present in the folder
    LoadLibraryA("OpenBanapass64.dll");
}
