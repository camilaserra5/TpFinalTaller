cmake_minimum_required(VERSION 2.8.11)

project(wolfstein)
include_directories(common/include)
add_subdirectory(common)
add_subdirectory(editor)
add_subdirectory(server)
add_subdirectory(client)
#add_subdirectory(raycasting_test)
