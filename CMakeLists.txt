cmake_minimum_required(VERSION 3.10)

project(vulkan_test)

# Add path for local cmake scripts
list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/build_config)

# Precompiled header macro. Parameters are source file list and filename for pch cpp file.
macro(vulkan_samples_pch SRCS PCHCPP)
    if (MSVC AND CMAKE_GENERATOR MATCHES "^Visual Studio")
        set(PCH_NAME "$(IntDir)\\pch.pch")
        # make source files use/depend on PCH_NAME
        set_source_files_properties(${${SRCS}} PROPERTIES COMPILE_FLAGS "/Yupch.h /FIpch.h /Fp${PCH_NAME} /Zm300" OBJECT_DEPENDS "${PCH_NAME}")
        # make PCHCPP file compile and generate PCH_NAME
        set_source_files_properties(${PCHCPP} PROPERTIES COMPILE_FLAGS "/Ycpch.h /Fp${PCH_NAME} /Zm300" OBJECT_OUTPUTS "${PCH_NAME}")
        list(APPEND ${SRCS} "${PCHCPP}")
    endif ()
endmacro(vulkan_samples_pch)

include(global_options)

add_subdirectory(third_party)
add_subdirectory(framework)
add_subdirectory(src)

add_definitions(VKB_DEBUG)