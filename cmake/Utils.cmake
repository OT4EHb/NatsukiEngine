function(natsuki_target target_name)
    if(WIN32)
        set_target_properties(${target_name} PROPERTIES WIN32_EXECUTABLE TRUE)
    elseif(APPLE)
        set_target_properties(${target_name} PROPERTIES MACOSX_BUNDLE TRUE)
    endif()
    
    target_compile_features(${target_name} PRIVATE cxx_std_20)
    
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/"
    )
    
    target_link_libraries(${target_name} PRIVATE NatsukiEngine)
endfunction()

function(natsuki_assets target_name src_dir)
    get_filename_component(folder_name ${src_dir} NAME)
    set(asset_target "${target_name}_assets")
    file(GLOB_RECURSE ASSET_FILES "${src_dir}/*")
    
    get_target_property(ASSET_DIR ${target_name} RUNTIME_OUTPUT_DIRECTORY)
    
    add_custom_target(${asset_target}
        DEPENDS ${ASSET_FILES}
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${src_dir}" "${ASSET_DIR}/${folder_name}"
        COMMENT "Copying assets from ${src_dir} to ${ASSET_DIR}"
    )
    
    add_dependencies(${target_name} ${asset_target})
endfunction()