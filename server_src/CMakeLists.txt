cmake_minimum_required(VERSION 2.8)

project(server)
find_package(Threads REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}../common_src/include/thread.h)

add_executable (server
        src/server_main.cpp
        src/servidor.cpp
        src/cliente.cpp
        ${UIS_HEADERS})

file(GLOB common RELATIVE ${CMAKE_SOURCE_DIR} "common_src/src*.cpp" "common_src/include*.h")

target_link_libraries(server commons SDL2 SDL2_image Threads::Threads)

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
