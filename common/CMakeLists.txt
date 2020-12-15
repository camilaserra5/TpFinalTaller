cmake_minimum_required(VERSION 2.8)
project(common)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lm -g")

find_package(Threads REQUIRED)

include_directories(include)
file(GLOB SOURCES src/*.cpp src/armas/*.cpp src/items/*.cpp src/comandos/*.cpp)
add_library(commons STATIC ${SOURCES})
install(TARGETS commons DESTINATION /usr/lib)
