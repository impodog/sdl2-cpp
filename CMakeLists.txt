cmake_minimum_required(VERSION 3.26)
project(sdl2_cpp)

set(PROJECT_VERSION 0.1.0)
add_definitions(-DSDL2_CPP_VERSION="${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 20)

add_executable(sdl2_cpp
        library.cpp
        include.h
        sdl2-cpp/utility.hpp
        sdl2-cpp/point.hpp
        sdl2-cpp/rect.hpp
        sdl2-cpp/sdl2-cpp.h
)

target_link_libraries(sdl2_cpp SDL2 SDL2main)
