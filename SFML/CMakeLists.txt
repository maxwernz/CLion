cmake_minimum_required(VERSION 3.22)
project(SFML)

set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include)

add_executable(SFML main.cpp ooptool.cpp ooptoolg.cpp ooptool.h ooptoolg.h)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SFML sfml-system sfml-window sfml-graphics)