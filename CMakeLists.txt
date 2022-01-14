cmake_minimum_required(VERSION 3.10)

project(STGInputTest VERSION 1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(STGInputTest src/main.c)

target_link_libraries(STGInputTest PUBLIC STGInput ${SDL2_LIBRARIES})
target_include_directories(STGInputTest PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/STGInput"
)
add_library(
    STGInput
    SHARED
    src/STGInput/AxisState.c
    src/STGInput/ButtonState.c
    src/STGInput/Convenience.c
    src/STGInput/GamepadState.c
    src/STGInput/KeyboardState.c
    src/STGInput/MouseState.c
    src/STGInput/STGInput.c
)
