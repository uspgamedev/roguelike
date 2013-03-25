CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

### Project Specification ###

PROJECT(roguelike CXX C)
set(roguelike_VERSION_MAJOR 0)
set(roguelike_VERSION_MINOR 0)
set(roguelike_VERSION_PATCH 0)
SET(roguelike_FULL_VERSION "${roguelike_VERSION_MAJOR}.${roguelike_VERSION_MINOR}.${roguelike_VERSION_PATCH} Alpha")

MESSAGE("== Roguelike -- version ${roguelike_FULL_VERSION} ==")

IF(MSVC AND (CMAKE_SIZEOF_VOID_P EQUAL 8))
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
ENDIF()

#Necessary for a Mac Universal Binary
IF(UNIVERSAL)
  SET (CMAKE_OSX_ARCHITECTURES ppc;i386;x86_64)
  SET (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
  SET (MACOSX_DEPLOYMENT_TARGET 10.5)
ENDIF(UNIVERSAL)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND UNIVERSAL)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.5")
ENDIF()


### Find Libraries ###

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# FindUGDK
#option (USE_EMBBEDED_UGDK "" OFF)
find_package(UGDK REQUIRED)
include_directories(${UGDK_INCLUDE_DIRS})
set(UGDK_EXTERNAL_LIBRARIES ${UGDK_LIBRARIES})


### Build ###

include (src_list.cmake)

#Adding the icon to the windows executable
#if (WIN32) 
#	set(GAME_SRCS ${GAME_SRCS} ./src/roguelike.rc)
#endif()

#Necessary for Mac with SDL
IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(GAME_SRCS ${GAME_SRCS} ./src/mac/SDLMain.h ./src/mac/SDLMain.m)
ENDIF ()

#Compiler definitions
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
if (UNIX OR MINGW)
    # se for o g++ para *nix ou o MinGW para Windows:
    add_definitions(-Wall -ansi -U_FORTIFY_SOURCE -msse2 -std=c++0x)
elseif (MSVC) 
    add_definitions(/D_CRT_SECURE_NO_WARNINGS /W4 /wd4100 /wd4127 /wd4201 /wd4211 /wd4250 /wd4355 /wd4706 /arch:SSE2 /fp:fast /MP)
endif ()

#Source Directories
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/src/")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#Executable
add_executable(roguelike ${GAME_SRCS})
target_link_libraries(roguelike ${UGDK_EXTERNAL_LIBRARIES})

set(GAME_LOCAL_DIR "./data")

CONFIGURE_FILE(
    "src/game/config.h.in"
    "src/game/config.h"
)


### Post-Build Commands ###

#Manual copy of libs and dlls to the executable's root in Windows, for x86/x64 compatibility.
if(WIN32)
	file(GLOB dlls RELATIVE ${CMAKE_SOURCE_DIR} *.dll)
	file(GLOB libs RELATIVE ${CMAKE_SOURCE_DIR} *.lib)
	
	add_custom_command(TARGET roguelike POST_BUILD
		COMMAND 
		COMMENT "Removing all libs and dlls from the project's root directory.")
	
	foreach(it ${dlls} ${libs})
		add_custom_command(TARGET roguelike POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E remove -f "${CMAKE_SOURCE_DIR}/${it}")
	endforeach(it ${dlls})

	IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(LIBS_SOURCE "./lib64/")
	ELSE()
		set(LIBS_SOURCE "./lib/")
	ENDIF()
	add_custom_command(TARGET roguelike POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIBS_SOURCE} "./"
		COMMENT "Copying libs from ${LIBS_SOURCE} to the project's root directory.")
endif(WIN32)
