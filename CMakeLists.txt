cmake_minimum_required(VERSION 3.5)
project(NatsukiEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
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

find_package(SDL3 QUIET CONFIG
    PATHS ${CMAKE_CURRENT_BINARY_DIR}/vendored/SDL
    NO_DEFAULT_PATH
)
if(WIN32)
    set(SDL3_LOCATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/SDL3.dll")
else()
    set(SDL3_LOCATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libSDL3.so")
endif()
if(NOT SDL3_FOUND OR NOT EXISTS SDL3_LOCATION)
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
endif()

set(SDL3_ttf_FOUND OFF)
set(SDL3_TTF_LIB "${CMAKE_CURRENT_BINARY_DIR}/vendored/SDL_ttf/SDL3_ttf.lib")
if (${SDL_SHARED} AND EXISTS ${SDL3_TTF_LIB})
    if(WIN32)
        set(SDL3_TTF_LOCATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/SDL3_ttf.dll")
    else()
        set(SDL3_TTF_LOCATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libSDL3_ttf.so")
    endif()
    if(EXISTS ${SDL3_TTF_LOCATION})
        add_library(SDL3_ttf::SDL3_ttf SHARED IMPORTED)
        set_target_properties(SDL3_ttf::SDL3_ttf PROPERTIES
            IMPORTED_LOCATION ${SDL3_TTF_LOCATION}
            IMPORTED_IMPLIB ${SDL3_TTF_LIB}
            INTERFACE_LINK_LIBRARIES SDL3::SDL3
        )
        set(SDL3_ttf_FOUND ON)
        message("Found SDL_ttf")
    endif()
endif()
if(NOT SDL3_ttf_FOUND)
    set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)

    add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)
endif() 

set(SDL3_image_FOUND OFF)
set(SDL3_IMAGE_LIB "${CMAKE_CURRENT_BINARY_DIR}/vendored/SDL_image/SDL3_image.lib")
if (${SDL_SHARED} AND EXISTS ${SDL3_IMAGE_LIB})
    if(WIN32)
        set(SDL3_IMAGE_LOCATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/SDL3_image.dll")
    else()
        set(SDL3_IMAGE_LOCATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libSDL3_image.so")
    endif()
    if (EXISTS ${SDL3_IMAGE_LOCATION})
        add_library(SDL3_image::SDL3_image SHARED IMPORTED)
        set_target_properties(SDL3_image::SDL3_image PROPERTIES
            IMPORTED_LOCATION ${SDL3_IMAGE_LOCATION}
            IMPORTED_IMPLIB ${SDL3_IMAGE_LIB}
            INTERFACE_LINK_LIBRARIES SDL3::SDL3
        )
        set(SDL3_image_FOUND ON)
        message("Found SDL_image")
    endif()
endif()
if(NOT SDL3_image_FOUND)
    set(SDLIMAGE_VENDORED ON CACHE BOOL "" FORCE)
    set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)

    add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
endif()

function(configure_target target_name)
    message("\nConfiguring ${target_name}")

    set(cxx_std cxx_std_20)
    if(ARGC GREATER 1)
        set(cxx_std ${ARGV1})
    endif()
    message("Used ${cxx_std}")

    if(WIN32)
        set_target_properties(${target_name} PROPERTIES WIN32_EXECUTABLE TRUE)
    elseif(APPLE)
        set_target_properties(${target_name} PROPERTIES MACOSX_BUNDLE TRUE)
    endif()
    
    target_compile_features(${target_name} PRIVATE ${cxx_std})

    file(GLOB_RECURSE SRC_FILES 
        CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
    )

    file(GLOB_RECURSE MODULES_FILES 
        CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/modules/*.ixx"
    )

    target_sources(${target_name}
        PRIVATE
            FILE_SET CXX_MODULES
            TYPE CXX_MODULES
            BASE_DIRS ${CMAKE_SOURCE_DIR}
            FILES
                ${MODULES_FILES}
    )

    target_sources(${target_name}
        PRIVATE
            ${SRC_FILES}
    )

    if(EMSCRIPTEN)
	    set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
    endif()

    target_link_libraries(${target_name} PRIVATE 
        SDL3::SDL3
	    SDL3_ttf::SDL3_ttf
	    SDL3_image::SDL3_image
    )

    target_include_directories(${target_name} PRIVATE
        "${CMAKE_SOURCE_DIR}/vendored/SDL/include"
        "${CMAKE_SOURCE_DIR}/vendored/SDL_ttf/include"
        "${CMAKE_SOURCE_DIR}/vendored/SDL_image/include"
    )
endfunction()

function(added_src target_name src_dir)
    file(GLOB_RECURSE SRC_FILES 
        CONFIGURE_DEPENDS
        "${src_dir}/*.cpp"
    )

    file(GLOB_RECURSE MODULES_FILES 
        CONFIGURE_DEPENDS
        "${src_dir}/*.ixx"
        "${src_dir}/*.cppm"
    )

    target_sources(${target_name}
        PRIVATE
            FILE_SET test_MODULES
            TYPE CXX_MODULES
            BASE_DIRS ${src_dir}
            FILES
                ${MODULES_FILES}
    )

    target_sources(${target_name}
        PRIVATE
            ${SRC_FILES}
    )
endfunction()

function(added_assets target_name src_dir)
    file(COPY ${src_dir} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endfunction()

include(config.cmake)
add_subdirectory(${APP_DIR})
