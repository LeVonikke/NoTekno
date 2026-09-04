cmake_minimum_required(VERSION 3.10)
project(NoTeknoProxy)

set(CMAKE_CXX_STANDARD 17)

# Download and use MinHook via FetchContent
include(FetchContent)
FetchContent_Declare(
  minhook
  GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(minhook)

# Create a shared library (DLL)
add_library(dinput8 SHARED 
    src/main.cpp 
    src/dinput8.def
    src/hooks.cpp
    src/BanapassEmu.cpp
    src/IOEmu.cpp
    src/NetworkHook.cpp
)

target_include_directories(dinput8 PRIVATE src)

# Link with MinHook and Windows libraries
target_link_libraries(dinput8 minhook user32.lib shlwapi.lib ws2_32.lib)

# Output should be dinput8.dll
set_target_properties(dinput8 PROPERTIES PREFIX "")
