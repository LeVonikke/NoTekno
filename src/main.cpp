#include <windows.h>
#include <stdio.h>

// Original dinput8.dll handle
HMODULE hOriginalDinput8 = NULL;
typedef HRESULT(WINAPI* DirectInput8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
DirectInput8Create_t OriginalDirectInput8Create = nullptr;

extern void InitializeHooks();

bool parrotLoaded = false;

extern "C" HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter) {
    if (!OriginalDirectInput8Create) {
        return E_FAIL;
    }
    
    if (!parrotLoaded) {
        parrotLoaded = true;
        char path[MAX_PATH];
        GetModuleFileNameA(NULL, path, MAX_PATH);
        char* lastSlash = strrchr(path, '\\');
        if (lastSlash) {
            *lastSlash = '\0'; // now points to bin
            lastSlash = strrchr(path, '\\'); // now points to Wangan Midnight Maximum Tune 6RR
            if (lastSlash) {
                *lastSlash = '\0';
                strcat_s(path, MAX_PATH, "\\tpui\\OpenParrotx64\\OpenParrot64.dll");
                HMODULE hParrot = LoadLibraryA(path);
                if (!hParrot) {
                    MessageBoxA(NULL, "Não foi possível carregar OpenParrot64.dll! Verifique a pasta tpui.", "Erro Loader", MB_OK);
                }
            }
        }
    }
    
    return OriginalDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

void LoadOriginalDinput8() {
    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    strcat_s(path, MAX_PATH, "\\dinput8.dll");
    hOriginalDinput8 = LoadLibraryA(path);
    if (hOriginalDinput8) {
        OriginalDirectInput8Create = (DirectInput8Create_t)GetProcAddress(hOriginalDinput8, "DirectInput8Create");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        LoadOriginalDinput8();
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitializeHooks, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        if (hOriginalDinput8) FreeLibrary(hOriginalDinput8);
        break;
    }
    return TRUE;
}
