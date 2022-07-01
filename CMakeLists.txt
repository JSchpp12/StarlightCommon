cmake_minimum_required (VERSION 3.8)
find_package(Git)
SET(SC_INSTALL OFF)
project("StarlightCommon" VERSION 1.0.0
    DESCRIPTION "Header only library for common classes used by the Starlight Engine" 
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MACOSX_RPATH 1)
cmake_policy(SET CMP0076 NEW)

SET(${PROJECT_NAME}_HEDERS
    "include/Enums.h" 
    "include/Shader.h" 
    "include/ResourceContainer.hpp" 
    "include/Media.h" 
    "include/ConfigFile.h" 
    "include/FileHelpers.h" 
    "include/Stage.h"
    "include/RenderObject.hpp"
    "include/Handle.hpp"
)

#check for needed includes 
if(DEFINED GLFW_SOURCE_DIR)
    set(GLFW_INCLUDE_DIR ${GLFW_SOURCE_DIR}/include)
endif()
if(NOT IS_DIRECTORY ${GLFW_INCLUDE_DIR})
    message(FATAL_ERROR "GLFW is needed for common includes. Ensure it is available.")
endif()

add_library(${PROJECT_NAME} INTERFACE)
#provide alias for subdirectory
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

#add_library(${PROJECT_NAME} INTERFACE ${${PROJECT_NAME}_HEADERS})
target_include_directories(${PROJECT_NAME} 
    INTERFACE
        ${glm_SOURCE_DIR}
        ${GLFW_INCLUDE_DIR}
        # ${CMAKE_CURRENT_SOURCE_DIR}/include
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

#for future use 
if (SC_INSTALL)
    message("Installing StarlightCommon")
    #install
    set(config_install_dir "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}")
    set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
    set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
    set(namespace "${PROJECT_NAME}::")

    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
    )

    install(
        EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
    )

    install(
        FILES 
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
    )

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/SC DESTINATION include)
else()
    message("Skipping install of StarlightCommon")
endif()