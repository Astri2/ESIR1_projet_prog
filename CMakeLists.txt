cmake_minimum_required(VERSION 3.27)
project(projet_programmation)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-c -Wall -ggdb)

include_directories(${PROJECT_SOURCE_DIR}/libs/SDL2/x86_64-w64-mingw32/include/)

add_executable(projet_programmation src/main.cpp
)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/SDL2/x86_64-w64-mingw32/bin/SDL2.dll)