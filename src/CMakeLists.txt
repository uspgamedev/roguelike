
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include(src_list.cmake) # defines the GAME_SRCS macro


# ================
# = User options =
# ================

option(ROGUELIKE_DEBUG_TOOLS "Set to ON to enable debugging tools ingame (does nothing for now)." ON)


# ============
# = Platform =
# ============

# # Adding the icon to the windows executable
# if (WIN32) 
#     set(GAME_SRCS ${GAME_SRCS} ./src/roguelike.rc)
# endif()

# # Mac with SDL
# IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#     SET(GAME_SRCS ${GAME_SRCS} ./src/mac/SDLMain.h ./src/mac/SDLMain.m)
# ENDIF ()

# Compiler flags
if (UNIX OR MINGW)
    add_definitions(-Wall -ansi -U_FORTIFY_SOURCE -std=gnu++0x)
    if(NOT ANDROID)
        add_definitions(-msse2)
    endif()
endif ()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(
        -Wno-self-assign
        -Wno-deprecated-register
    )
endif ()
if (MSVC) 
    add_definitions(/D_CRT_SECURE_NO_WARNINGS /W4 /wd4100 /wd4127 /wd4201 /wd4211 /wd4250 /wd4706 /fp:fast /MP)
    IF(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
        add_definitions(/arch:SSE2)
    ENDIF()
endif ()


# ================
# = Source & Out =
# ================

# if(MSVC)
#     include_directories(externals/windows/include)
# endif(MSVC)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# # Lua and Python
# include_directories(${LUA_INCLUDE_DIR})
# 
# if(NOT ANDROID)
#     include_directories(${PYTHON_INCLUDE_DIR})
# endif()
# 
# include(module/module_list.cmake)
# if(ANDROID)
#     set(ROGUELIKE_LANGUAGES_LIST "lua")
# else()
#     set(ROGUELIKE_LANGUAGES_LIST "lua;python")
# endif()
# 
# set(GENERATED_PY_FILES)
# 
# # SWIG
# include(${CMAKE_SOURCE_DIR}/cmake/SWIG.cmake)
# include_directories("${ugdk_SOURCE_DIR}/src")

# Resources directory
if(ANDROID)
    set(roguelike_DATA_PATH "/sdcard/roguelike")
else()
    set(roguelike_DATA_PATH "${CMAKE_SOURCE_DIR}/data")
endif()


# Game executable
CONFIGURE_FILE( "game/config.h.in" "game/config.h" )
add_ugdk_executable(roguelike ${GAME_SRCS} ${GENERATED_SRC})


# ==============
# = Post build =
# ==============

# # Copy the generated .py files to the data/scripts
# foreach(it ${GENERATED_PY_FILES} )
#     get_filename_component(FILE_NAME ${it} NAME)
#     add_custom_command(TARGET roguelike POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${it} "${roguelike_DATA_PATH}/scripts/${FILE_NAME}" 
#     WORKING_DIRECTORY "../" COMMENT "Copying generated py scripts")
# endforeach()

# On windows, copy the .dll files to the executable's folder.
if(WIN32)
    file(GLOB dlls RELATIVE ${CMAKE_BINARY_DIR} *.dll)
    file(GLOB libs RELATIVE ${CMAKE_BINARY_DIR} *.lib)
    
    add_custom_command(TARGET roguelike POST_BUILD
        COMMAND 
        COMMENT "Removing all libs and dlls from the project's root directory.")
    
    foreach(it ${dlls} ${libs})
        add_custom_command(TARGET roguelike POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove -f "${CMAKE_BINARY_DIR}/${it}")
    endforeach(it ${dlls})

    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(LIBS_SOURCE "./lib64/")
    ELSE()
        set(LIBS_SOURCE "./lib/")
    ENDIF()
    add_custom_command(TARGET roguelike POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIBS_SOURCE} ${CMAKE_BINARY_DIR}
        COMMENT "Copying libs from ${LIBS_SOURCE} to the project's root directory, ${CMAKE_BINARY_DIR}.")
endif(WIN32)
