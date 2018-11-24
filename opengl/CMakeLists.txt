cmake_minimum_required(VERSION 3.12)

# setting OSX version
if(NOT DEFINED OSX_SYSTEM)
	execute_process(
			COMMAND xcodebuild -version -sdk macosx SDKVersion
			OUTPUT_VARIABLE OSX_SYSTEM
			OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

message(STATUS "Detected OS X ${OSX_SYSTEM}")

# see "cmake --help-policy CMP0003"
cmake_policy(SET CMP0003 NEW)

project(main)

set (CMAKE_CXX_STANDARD 17)

set(${CXX_WARNINGS} "-Werror -Wall -Weffc++ -Wextra -Wsign-conversion")
set(${PLATFORM_CFLAGS} "")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit  -framework CoreVideo")

set(CMAKE_CXX_FLAGS "${CXX_WARNINGS} ${CMAKE_CXX_FLAGS} ${PLATFORM_CFLAGS}")

include(ExternalProject)

set(GLFW3_SETTINGS "-DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF")

ExternalProject_Add(glfw3
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "master"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/installed ${GLFW3_SETTINGS}
)


link_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_INCLUDEDIR})

find_package(OpenGL REQUIRED)
include_directories(SYSTEM ${OPENGL_INCLUDE_DIR})

set(SOURCE main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
add_dependencies(${PROJECT_NAME} glfw3)
target_link_libraries(main ${CMAKE_BINARY_DIR}/lib/installed/lib/libglfw3.a)