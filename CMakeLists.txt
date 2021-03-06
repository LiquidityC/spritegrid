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

macro(set_option option value)
	set(${option} ${value} CACHE INTERNAL "" FORCE)
endmacro()

set_option(ECS_TESTS_ENABLED off)
set_option(ECS_LINT_ENABLED off)
add_subdirectory(ECS)
set(ECS_INCLUDE_DIR "ECS/src")
set(ECS_LIBRARY "ecs")

configure_file(
	"${PROJECT_SOURCE_DIR}/src/Config.h.in"
	"${PROJECT_BINARY_DIR}/Config.h"
	)

include_directories(
	${PROJECT_BINARY_DIR}
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${ECS_INCLUDE_DIR}
	)

add_definitions(-std=c++17)
set(CMAKE_CXX_FLAGS_DEBUG
	"${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -fsanitize=address -fno-omit-frame-pointer -pedantic -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wconversion -Wno-sign-conversion"
	)

add_executable(spritegrid
	src/SpriteGrid
	src/StringUtil
	src/Texture
	src/Timer
	src/Grid
	src/Util
	src/Input
	src/Update
	src/Message
	src/GridComponent
	src/Image
	src/TextureComponent
	)

add_executable(testspritegrid
	test/catch
	src/StringUtil
	test/SpriteGridTest
	test/StringUtilTest
	)

target_link_libraries(spritegrid
	-lstdc++fs
	${SDL2_LIBRARY}
	${SDL2MAIN_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${ECS_LIBRARY}
	)

enable_testing()
add_test(NAME test
	COMMAND testspritegrid
	)

# LINT:
if (CPPCHECK_FOUND)
	add_custom_target(lint
		COMMAND ${CPPCHECK_EXECUTABLE} --force --language=c++ --template=gcc --error-exitcode=1 --quiet --enable=warning,style,performance,portability,information,missingInclude src/
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Run cppcheck"
		)
endif (CPPCHECK_FOUND)

install(TARGETS spritegrid DESTINATION bin)
