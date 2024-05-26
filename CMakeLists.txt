cmake_minimum_required(VERSION 3.27)
project(projet_programmation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

add_compile_options(-c -Wall -ggdb)

set(SDL2_PATH ${PROJECT_SOURCE_DIR}/libs/SDL2/x86_64-w64-mingw32)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(projet_programmation main.cpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})