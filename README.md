# NoTekno

![C++](https://img.shields.io/badge/C%2B%2B-blue) ![Status](https://img.shields.io/badge/status-active-brightgreen) ![Private](https://img.shields.io/badge/-private-grey) ![Platform](https://img.shields.io/badge/platform-Windows-lightgrey)

`dinput8.dll` proxy for **Wangan Midnight Maximum Tune 6RR** (arcade, Bandai Namco).
Loads the system's real `dinput8.dll` (the game keeps working normally), chains the
loading of [OpenParrot](https://github.com/djhackersdev/openparrot) and OpenBanapass
(Asakura), and DNS-redirects Bandai Namco's server domains to `127.0.0.1` — to run the
game against a local/private server.

## Structure

| file | content |
|---|---|
| `src/main.cpp` | DLL entry point — loads the system's real `dinput8.dll` and injects `OpenParrot64.dll` (path relative to the game folder, `tpui/OpenParrotx64/`) |
| `src/hooks.cpp` / `src/hooks.h` | installs the hooks (MinHook) |
| `src/NetworkHook.cpp` | intercepts `getaddrinfo` and redirects `bandainamco.net`/`banapass.net`/`mucha.jp` to `127.0.0.1` |
| `src/BanapassEmu.cpp` | loads `OpenBanapass64.dll` if present in the folder |
| `src/IOEmu.cpp` | reserved — `OpenParrot64.dll` already covers this today |
| `src/dinput8.def` | DLL exports, must match the real `dinput8.dll`'s |

## Build

```bash
cmake -B build
cmake --build build
```

Produces `dinput8.dll` (via `add_library(... SHARED)` with `PREFIX ""`). Downloads
[MinHook](https://github.com/TsudaKageyu/minhook) automatically via `FetchContent`.

## Install

Copy the generated `dinput8.dll` into the game's executable folder (same level as
`tpui/OpenParrotx64/`), together with `OpenParrot64.dll` and, if used,
`OpenBanapass64.dll`.

## What's NOT here

The game itself, `OpenParrot64.dll`, and `OpenBanapass64.dll` — binaries from other
projects/from Bandai Namco, not redistributed here.
