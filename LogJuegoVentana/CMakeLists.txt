cmake_minimum_required(VERSION 2.8)

project(sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(~/TpFinalTaller/logJuegoVentana/include)

add_executable(sdldemo
            src/pruebaSDLmain.cpp
            src/juego.cpp
)

target_link_libraries(sdldemo SDL2 SDL2_image)

