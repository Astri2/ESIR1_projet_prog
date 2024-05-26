cmake_minimum_required(VERSION 3.27)
project(projet_programmation)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-c -Wall -ggdb)

include_directories(${PROJECT_SOURCE_DIR}/libs/SDL2/include/)

add_executable(projet_programmation WIN32 src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/msvc_arm64/SDL2.lib)
