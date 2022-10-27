cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME untitled)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(SDL/include/SDL_keysym.h)
set(SDL2_INCLUDE_DIR C:/Users/HP/Downloads/libs/SDL/include)
set(SDL2_LIB_DIR C:/Users/HP/Downloads/libs/SDL/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)