cmake_minimum_required(VERSION 3.22)
project(sfmlTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(sfmlTest polynom.cpp common.cpp ooptool.cpp ooptoolg.cpp common.h ooptool.h ooptoolg.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(sfmlTest sfml-system sfml-window sfml-graphics)
