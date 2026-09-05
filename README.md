# NoTekno

![C++](https://img.shields.io/badge/C%2B%2B-blue) ![Status](https://img.shields.io/badge/status-ativo-brightgreen) ![Privado](https://img.shields.io/badge/-privado-grey) ![Platform](https://img.shields.io/badge/platform-Windows-lightgrey)

Proxy `dinput8.dll` para **Wangan Midnight Maximum Tune 6RR** (arcade, Bandai Namco).
Carrega a `dinput8.dll` original do sistema (o jogo continua funcionando normalmente),
encadeia o carregamento do [OpenParrot](https://github.com/djhackersdev/openparrot) e do
OpenBanapass (Asakura), e redireciona por DNS os domínios de servidor da Bandai Namco
para `127.0.0.1` — para rodar o jogo contra um servidor local/privado.

## Estrutura

| arquivo | conteúdo |
|---|---|
| `src/main.cpp` | ponto de entrada da DLL — carrega o `dinput8.dll` real do sistema e injeta `OpenParrot64.dll` (path relativo à pasta do jogo, `tpui/OpenParrotx64/`) |
| `src/hooks.cpp` / `src/hooks.h` | instala os hooks (MinHook) |
| `src/NetworkHook.cpp` | intercepta `getaddrinfo` e redireciona `bandainamco.net`/`banapass.net`/`mucha.jp` para `127.0.0.1` |
| `src/BanapassEmu.cpp` | carrega `OpenBanapass64.dll` se presente na pasta |
| `src/IOEmu.cpp` | reservado — `OpenParrot64.dll` já cobre isso hoje |
| `src/dinput8.def` | exports da DLL, precisa bater com os do `dinput8.dll` real |

## Build

```bash
cmake -B build
cmake --build build
```

Gera `dinput8.dll` (via `add_library(... SHARED)` com `PREFIX ""`). Baixa o
[MinHook](https://github.com/TsudaKageyu/minhook) automaticamente via `FetchContent`.

## Instalação

Copiar o `dinput8.dll` gerado para a pasta do executável do jogo (mesmo nível de
`tpui/OpenParrotx64/`), junto com `OpenParrot64.dll` e, se usado, `OpenBanapass64.dll`.

## O que NÃO está aqui

O jogo em si, o `OpenParrot64.dll` e o `OpenBanapass64.dll` — são binários de outros
projetos/da Bandai Namco, não redistribuídos aqui.
