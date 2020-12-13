cmake_minimum_required(VERSION 2.8)

project(server)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

set(PROJECT_LINK_LIBS libcommons.a)
link_directories(~/TpFinalTaller/common/build)
include_directories(~/TpFinalTaller/common/include)

add_executable(server
        src/servidor.cpp
        src/cliente.cpp
        src/server_main.cpp
        ${UIS_HEADERS})

target_link_libraries(server ${PROJECT_LINK_LIBS} SDL2 SDL2_image Threads::Threads)

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
