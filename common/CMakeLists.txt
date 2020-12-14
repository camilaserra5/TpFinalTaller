cmake_minimum_required(VERSION 2.8)
project(common)
set(CMAKE_BUILD_TYPE Release)

find_package(Threads REQUIRED)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_library(commons STATIC ${SOURCES})
install(TARGETS commons DESTINATION /usr/lib)
