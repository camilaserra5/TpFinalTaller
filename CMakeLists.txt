cmake_minimum_required(VERSION 2.8.11)

project(wolfstein)

set(PROJECT_BASE_DIR ${PROJECT_SOURCE_DIR})
configure_file(config.h.in config.h)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(common/include)

add_subdirectory(common)
add_subdirectory(editor)
add_subdirectory(server)
add_subdirectory(client)
