cmake_minimum_required(VERSION 3.28)
project(NatsukiEngine)

include(cmake/SDL.cmake)
include(cmake/Utils.cmake) 

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_CXX_SCAN_FOR_MODULES ON)


option(USE_SYSTEM_SDL "Use system SDL" ON)
option(FORCE_VENDORED_SDL "Force rebuild vendored SDL" OFF)


add_library(NatsukiModules STATIC)
target_compile_features(NatsukiModules PRIVATE cxx_std_20)
target_include_directories(NatsukiModules PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_ttf/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_image/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_mixer/include"
)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE MODULES_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/modules/*.ixx")

target_sources(NatsukiModules
    PUBLIC FILE_SET CXX_MODULES TYPE CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/modules"
    FILES ${MODULES_FILES}
)
target_sources(NatsukiModules PRIVATE ${SRC_FILES})

target_link_libraries(NatsukiModules PRIVATE 
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
)

add_library(NatsukiEngine INTERFACE)
target_include_directories(NatsukiEngine INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(NatsukiEngine INTERFACE NatsukiModules)