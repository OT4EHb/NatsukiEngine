cmake_minimum_required(VERSION 3.28)
project(Mineswaper)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
#disable NASM
set(SDLIMAGE_AVIF OFF)
get_filename_component(ENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
add_subdirectory(${ENGINE_ROOT} ${CMAKE_CURRENT_BINARY_DIR}/Natsuki)

add_executable(Mineswaper)
natsuki_target(Mineswaper)
target_sources(Mineswaper
    PRIVATE
        FILE_SET test_MODULES
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            "Area.cppm"
)

target_include_directories(Mineswaper PRIVATE "include")

target_sources(Mineswaper
    PRIVATE
        "src/Game.cpp"
        "src/MenuState.cpp"
        "src/GameState.cpp"
)
natsuki_assets(Mineswaper "${CMAKE_CURRENT_SOURCE_DIR}/res")