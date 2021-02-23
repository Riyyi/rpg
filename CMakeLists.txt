# User config between these lines
# ------------------------------------------

# Set engine name
set(ENGINE "unnamed")
# Set project name
set(GAME "rpg")
# Set debugging, ON/OFF
set(DEBUG "ON")

# ------------------------------------------

# Add 'make run' target
add_custom_target(run
    COMMAND ${GAME}
)

# ------------------------------------------

cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Check if the build should include debugging symbols
option(DEBUG "" ${DEBUG})
if(DEBUG)
	# cmake -DDEBUG=on .. && make
	message("--- Debug ---")
	set(CMAKE_BUILD_TYPE "Debug")

	# -Og     = Optimizations that do not interfere with debugging
	# -Wall   = All warnings about contructions that are easily avoidable
	# -Wextra = Extra warning flags not covered by -Wall
	# -g      = Produce debugging information in OS's native format
	# -pg     = Generate profile information for analysis with gprof
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall -Wextra -g -pg")
	# gprof <GAME> gmon.out > profile-data.txt
else()
	# cmake -DDEBUG=off .. && make
	message("--- Release ---")
	set(CMAKE_BUILD_TYPE "Release")

	# -O3     = Optimizations that increases compilation time and performance
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# Include all headers
include_directories(
	"src"
	"deps/rapidjson/include"
	"deps/SFML/include"
)

# file(GLOB_RECURSE SFML "deps/SFML/src/*.cpp")
# set(ENGINE_SOURCES ${SFML})

# Define game source files
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
set(GAME_SOURCES ${GAME_SOURCES})

# ------------------------------------------

project(${GAME})
set(CMAKE_CXX_STANDARD 11)

# SFML options
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "" FORCE)

# Add SFML target to project
add_subdirectory(deps/SFML)

# set (SFML_DIR "${CMAKE_SOURCE_DIR}/deps/SFML")
# set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/SFML/cmake")
# find_package (SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${GAME} ${GAME_SOURCES})
target_link_libraries(${GAME} sfml-system sfml-window sfml-network sfml-graphics sfml-audio)

# ------------------------------------------------------------------------

# file(GLOB_RECURSE SFML "deps/SFML/src/*.cpp")
# set(ENGINE_SOURCES ${SFML})

# # Define game source files
# file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
# set(GAME_SOURCES ${GAME_SOURCES})

# # ------------------------------------------

# project(${ENGINE})
# set(CMAKE_CXX_STANDARD 11)

# # SFML options
# set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
# set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
# set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "" FORCE)

# # Add SFML target to project
# add_subdirectory(deps/SFML)

# # set (SFML_DIR "${CMAKE_SOURCE_DIR}/deps/SFML")
# # set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/SFML/cmake")
# # find_package (SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)


# add_library(${ENGINE} STATIC ${ENGINE_SOURCES})
# target_link_libraries(${ENGINE} sfml-system sfml-window sfml-network sfml-graphics sfml-audio)

# # ------------------------------------------

# project(${GAME})
# set(CMAKE_CXX_STANDARD 11)

# add_executable(${GAME} ${GAME_SOURCES})
# target_link_libraries(${GAME} ${ENGINE})
