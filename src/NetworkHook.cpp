#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <MinHook.h>
#include "hooks.h"

typedef int (WSAAPI *getaddrinfo_t)(PCSTR, PCSTR, const ADDRINFOA*, PADDRINFOA*);
getaddrinfo_t fpOriginalGetAddrInfo = NULL;

int WSAAPI HookedGetAddrInfo(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA *pHints, PADDRINFOA *ppResult) {
    if (pNodeName && (strstr(pNodeName, "bandainamco.net") || strstr(pNodeName, "banapass.net") || strstr(pNodeName, "mucha.jp"))) {
        return fpOriginalGetAddrInfo("127.0.0.1", pServiceName, pHints, ppResult);
    }
    return fpOriginalGetAddrInfo(pNodeName, pServiceName, pHints, ppResult);
}

void InstallNetworkHooks() {
    HMODULE hWs2 = GetModuleHandleA("ws2_32.dll");
    if (!hWs2) return;
    
    void* pGetAddrInfo = GetProcAddress(hWs2, "getaddrinfo");
    if (pGetAddrInfo) {
        MH_CreateHook(pGetAddrInfo, (LPVOID)HookedGetAddrInfo, (LPVOID*)&fpOriginalGetAddrInfo);
    }
}
