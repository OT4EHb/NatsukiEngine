cmake_minimum_required(VERSION 3.5)
project(NatsukiEngine)
set(EXECUTABLE_NAME ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if ((APPLE AND NOT CMAKE_SYSTEM_NAME MATCHES "Darwin") OR EMSCRIPTEN)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
    set(SDL_SHARED OFF)
else()
    set(SDL_SHARED ON)
endif()

if(MSVC)
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        add_definitions(/MP)
    endif()
endif()

add_executable(${EXECUTABLE_NAME})

file(GLOB_RECURSE SRC_FILES 
    CONFIGURE_DEPENDS
    #"${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/templates/*.cpp"
)

file(GLOB_RECURSE MODULES_FILES 
    CONFIGURE_DEPENDS
    #"${CMAKE_CURRENT_SOURCE_DIR}/test/*.ixx"
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/*.ixx"
    "${CMAKE_CURRENT_SOURCE_DIR}/templates/*.ixx"
)

target_sources(${EXECUTABLE_NAME}
    PRIVATE
        FILE_SET CXX_MODULES
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            ${MODULES_FILES}
)

target_sources(${EXECUTABLE_NAME}
    PRIVATE
        ${SRC_FILES}
)

target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_20)

if(EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

set(SDLTTF_VENDORED ON)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE 
	SDL3_ttf::SDL3_ttf
	SDL3_image::SDL3_image
    SDL3::SDL3
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_ttf/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_image/include"
)