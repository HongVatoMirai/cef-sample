cmake_minimum_required(VERSION 3.13)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

#
# Project configuration
#

project("MyApp")

# CEF configuration
set_property(GLOBAL PROPERTY OS_FOLDERS ON)
# set(CEF_VERSION "120.2.7+g4bc6a59+chromium-120.0.6099.234")

# set cache string cef_version
set(CEF_VERSION "120.2.7+g4bc6a59+chromium-120.0.6099.234" CACHE STRING "CEF version to download")
message(STATUS "CEF version: ${CEF_VERSION}")

# architecture
message(STATUS "arch: ${CMAKE_SYSTEM_PROCESSOR}")

# Determine the platform
if(NOT DEFINED CEF_PLATFORM)
  if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "arm64")
      set(CEF_PLATFORM "macosarm64")
    else()
      set(CEF_PLATFORM "macosx64")
    endif()
  elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    if(CMAKE_SIZEOF_VOID_P MATCHES 8)
      set(CEF_PLATFORM "linux64")
    else()
      set(CEF_PLATFORM "linux32")
    endif()
  elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    if(CMAKE_SIZEOF_VOID_P MATCHES 8)
      set(CEF_PLATFORM "windows64")
    else()
      set(CEF_PLATFORM "windows32")
    endif()
  endif()
endif()

# Add this project's cmake/ directory to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/app/cmake/cef")

# Download and extract the CEF binary distribution (executes DownloadCEF.cmake)
include(DownloadCEF)
downloadcef("${CEF_PLATFORM}" "${CEF_VERSION}" "${CMAKE_SOURCE_DIR}/temp/cef")

# Add the CEF binary distribution's cmake/ directory to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

# Load the CEF configuration (executes FindCEF.cmake)
find_package(CEF REQUIRED)

#
# Target configuration
#

# Include the libcef_dll_wrapper target (executes libcef_dll/CMakeLists.txt)
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

# Allow includes relative to the current source directory
include(${CMAKE_CURRENT_SOURCE_DIR}/app/cmake/shared/common.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app/cmake/shared)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app/cmake/main)

# Display configuration settings
print_cef_config()
