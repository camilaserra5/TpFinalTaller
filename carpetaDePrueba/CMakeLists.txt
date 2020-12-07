cmake_minimum_required(VERSION 2.8)

project(sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdldemo
  pruebaSDLmain.cpp
)

target_link_libraries(sdldemo SDL2 SDL2_image)

