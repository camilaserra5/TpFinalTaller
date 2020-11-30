cmake_minimum_required(VERSION 2.8)

project(server)
find_package(Threads REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(commons
        ../common_src/src/Area.cpp
        ../common_src/src/SdlException.cpp
        ../common_src/src/SdlTexture.cpp
        ../common_src/src/SdlWindow.cpp
        ../common_src/src/socket.cpp
        ../common_src/src/tcp_protocol.cpp
        ../common_src/src/thread.cpp
        ../common_src/src/protected_queue.cpp
        )

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (server
        src/server_main.cpp
        src/servidor.cpp
        src/cliente.cpp
        ${UIS_HEADERS})

file(GLOB common RELATIVE ${CMAKE_SOURCE_DIR} "common_src/src*.cpp" "common_src/include*.h")

target_link_libraries(server commons SDL2 SDL2_image Threads::Threads)

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
