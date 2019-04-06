cmake_minimum_required(VERSION 3.13)
project(interactive)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(SDL2IMAGE REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})

add_executable(interactive main.cpp header.h lib.cpp)

target_link_libraries(
        interactive
        ${SDL2_LIBRARY}
        ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARY}
        -lmingw32
        -lSDL2main
        -lSDL2
    )