cmake_minimum_required (VERSION 3.2.0)

SET(CMAKE_COLOR_MAKEFILE ON)

project(spritegrid CXX)

set(spritegrid_TITLE "SpriteGrid")
set(spritegrid_MAJOR_VERSION 0)
set(spritegrid_MINOR_VERSION 0)
set(spritegrid_PATCH_VERSION 1)
set(spritegrid_RELEASE_TYPE "(alfa)")

include(mk/cmake/FindSDL2.cmake)
include(mk/cmake/FindSDL2_image.cmake)
include(mk/cmake/FindCCache.cmake)
include(mk/cmake/Findcppcheck.cmake)

configure_file(
	"${PROJECT_SOURCE_DIR}/src/Config.h.in"
	"${PROJECT_BINARY_DIR}/Config.h"
	)

include_directories(
	${PROJECT_BINARY_DIR}
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	)

add_definitions(-std=c++17)
set(CMAKE_CXX_FLAGS_DEBUG
	"${CMAKE_CXX_FLAGS_DEBUG} -pedantic -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wconversion -Wno-sign-conversion"
	)

add_executable(spritegrid
	src/SpriteGrid
	src/StringUtil
	)

add_executable(testspritegrid
	test/catch
	src/StringUtil
	test/SpriteGridTest
	test/StringUtilTest
	)

target_link_libraries(spritegrid
	${SDL2_LIBRARY}
	${SDL2MAIN_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	)

# LINT:
if (CPPCHECK_FOUND)
	add_custom_target(lint
		COMMAND ${CPPCHECK_EXECUTABLE} --force --language=c++ --template=gcc --error-exitcode=1 --quiet --enable=warning,style,performance,portability,information,missingInclude src/
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Run cppcheck"
		)
endif (CPPCHECK_FOUND)
