cmake_minimum_required(VERSION 2.8)

project(client)
find_package(Threads REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(commonc
        common_src/src/Area.cpp
        common_src/src/SdlException.cpp
        common_src/src/SdlTexture.cpp
        common_src/src/SdlWindow.cpp
        common_src/src/socket.cpp
        common_src/src/tcp_protocol.cpp
        common_src/src/thread.cpp
        )

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (client
        src/client_main.cpp
        src/cliente.cpp
        ${UIS_HEADERS}
        )

target_link_libraries(client commonc SDL2 SDL2_image Threads::Threads)

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
