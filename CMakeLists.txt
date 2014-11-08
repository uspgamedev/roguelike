
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


# ===========
# = Project =
# ===========

PROJECT(roguelike CXX C)

# Version
set(roguelike_VERSION_MAJOR 0)
set(roguelike_VERSION_MINOR 0)
set(roguelike_VERSION_PATCH 0)
SET(roguelike_FULL_VERSION "${roguelike_VERSION_MAJOR}.${roguelike_VERSION_MINOR}.${roguelike_VERSION_PATCH}")
MESSAGE("== Roguelike -- version ${roguelike_FULL_VERSION} ==")


# ============
# = Platform =
# ============

# Windows
IF(MSVC AND (CMAKE_SIZEOF_VOID_P EQUAL 8))
    set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
ENDIF()

# # Mac Universal
# IF(UNIVERSAL)
#     SET (CMAKE_OSX_ARCHITECTURES ppc;i386;x86_64)
#     SET (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
#     SET (MACOSX_DEPLOYMENT_TARGET 10.5)
# ENDIF(UNIVERSAL)
# IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND UNIVERSAL)
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.5")
# ENDIF()

# Android
if(ANDROID)
    if(${ANDROID_NATIVE_API_LEVEL} LESS 9)
        message(FATAL_ERROR "ANDROID_NATIVE_API_LEVEL must be at least 9")
    endif()
else()
    macro(find_host_package)
        find_package(${ARGN})
    endmacro(find_host_package)
endif()


# =========================
# = Libraries & Resources =
# =========================

# General Libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# Git
find_host_package(Git)
if(GIT_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --always
                            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                            OUTPUT_VARIABLE roguelike_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE
                            RESULT_VARIABLE GIT_DESCRIBE_SUCCESS)
    if(NOT ${GIT_DESCRIBE_SUCCESS} EQUAL 0)
        # Source is not in a git repository
        set(roguelike_VERSION "Unknown version")
    endif()
else(GIT_FOUND)
    set(roguelike_VERSION "Unknown version")
endif(GIT_FOUND)

# # Resources repository
# set(RESOURCES_VERSION jsonmetadata)
# if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/resources-${RESOURCES_VERSION}.tar.gz)
#     if(GIT_FOUND)
#         message("= Downloading resources file version '${RESOURCES_VERSION}'...")
#         execute_process(COMMAND ${GIT_EXECUTABLE} archive --remote=git://uspgamedev.org/roguelike-resources.git
#                             -o ${CMAKE_CURRENT_BINARY_DIR}/resources-${RESOURCES_VERSION}.tar.gz ${RESOURCES_VERSION} resources/ )
#         execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_CURRENT_BINARY_DIR}/resources-${RESOURCES_VERSION}.tar.gz
#                         WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data")
#     else(GIT_FOUND)
#         message("-- WARNING: Git not found, unable to download resources.")
#     endif(GIT_FOUND)    
# endif()


# UGDK
option(ROGUELIKE_INTERNAL_UGDK   "Set to ON to use an internal UGDK instead of the system one." ON)
option(ROGUELIKE_FORCE_SUBMODULE "Set to ON to force git submodule update whenever cmake is ran." ON)
if(NOT ROGUELIKE_INTERNAL_UGDK)
    find_package(UGDK)
    if(NOT UGDK_FOUND)
        set(ROGUELIKE_INTERNAL_UGDK ON CACHE BOOL "Set to ON to use an internal UGDK instead of the system one." FORCE)
        message(FATAL_ERROR "Unable to find UGDK, forcing internal. Please, re-run CMake.")
    endif(NOT UGDK_FOUND)
    include_directories(${UGDK_INCLUDE_DIRS})
    set(UGDK_EXTERNAL_LIBRARIES ${UGDK_LIBRARIES})
    
else(NOT ROGUELIKE_INTERNAL_UGDK)
    if(ROGUELIKE_FORCE_SUBMODULE OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/externals/ugdk/CMakeLists.txt")
        if(GIT_FOUND)
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
                            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
        else(GIT_FOUND)
            message(FATAL_ERROR "Git submodule 'externals/ugdk' not initialized and git not found.")
        endif(GIT_FOUND)
    endif()
    
    set(UGDK_BUILD_TESTS    OFF CACHE BOOL "Set to ON to enable building tests.")
    set(UGDK_BUILD_EXAMPLES OFF CACHE BOOL "Set to ON to enable building examples.")

    add_definitions(-DEMBBEDED_UGDK="${CMAKE_CURRENT_BINARY_DIR}/externals/ugdk")
    add_subdirectory(externals/ugdk EXCLUDE_FROM_ALL)
    include_directories(${UGDK_EXTERNAL_INCLUDE_DIRS})
    set(UGDK_EXTERNAL_LIBRARIES libugdk)
endif(NOT ROGUELIKE_INTERNAL_UGDK)


# =========
# = Build =
# =========

add_subdirectory(src)

add_ugdk_android_project(roguelike "Roguelike" "org.uspgamedev.roguelike")
