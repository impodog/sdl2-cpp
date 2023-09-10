cmake_minimum_required(VERSION 3.26)
project(sdl2_cpp)

set(PROJECT_VERSION 0.1.0)
add_definitions(-DSDL2_CPP_VERSION="${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 20)

add_library(sdl2_cpp
        library.cpp
        include.h
        sdl2-cpp/utility.hpp
        sdl2-cpp/point.hpp
        sdl2-cpp/rect.hpp
        sdl2-cpp/sdl2-cpp.h
        sdl2-cpp/window.hpp
        sdl2-cpp/color.hpp
        sdl2-cpp/except.hpp
        sdl2-cpp/texture.hpp
        sdl2-cpp/renderer.hpp
        sdl2-cpp/surface.hpp
        sdl2-cpp/event.hpp
        sdl2-cpp/keyboard.hpp
        image-cpp/image.hpp
        ttf-cpp/font.hpp
        ttf-cpp/ttf-cpp.h
        image-cpp/image-cpp.h
)

target_link_libraries(sdl2_cpp SDL2 SDL2main SDL2_image SDL2_ttf)

project(sdl2_cpp_test)

add_executable(sdl2_cpp_test test.cpp
        test.cpp)
target_link_libraries(sdl2_cpp_test sdl2_cpp)
