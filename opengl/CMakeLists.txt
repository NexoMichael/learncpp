cmake_minimum_required(VERSION 3.12)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Weffc++ -Wextra -Wsign-conversion")

project(main)

set(SOURCE main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})