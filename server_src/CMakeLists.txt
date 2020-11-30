cmake_minimum_required(VERSION 2.8)

project(server)
find_package(Threads REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(commons
        common_src/Area.cpp
        common_src/SdlException.cpp
        common_src/SdlTexture.cpp
        common_src/SdlWindow.cpp
        common_src/socket.cpp
        common_src/tcp_protocol.cpp
        common_src/thread.cpp
        )

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (server
        server_src/server_main.cpp
        server_src/server.cpp
        server_src/client_manager.cpp
        )


target_link_libraries(server commons SDL2 SDL2_image Threads::Threads)

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})