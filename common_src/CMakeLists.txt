cmake_minimum_required(VERSION 2.8)

project(server)
find_package(Threads REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_library(commons
        ../common_src/src/Area.cpp
        ../common_src/src/SdlException.cpp
        ../common_src/src/SdlTexture.cpp
        ../common_src/src/SdlWindow.cpp
        ../common_src/src/socket.cpp
        ../common_src/src/tcp_protocol.cpp
        ../common_src/src/thread.cpp
        ../common_src/src/protected_queue.cpp
        ../common_src/src/comando.cpp
        ../common_src/src/movimiento.cpp
        ../common_src/src/ataque.cpp
        ../common_src/src/item_catch.cpp
        )
