cmake_minimum_required(VERSION 2.8)

project(client_src)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

set(PROJECT_LINK_LIBS libcommons.a)
link_directories(~/TpFinalTaller/common/build)
include_directories(~/TpFinalTaller/common/include)

add_executable(client_src
        src/client_main.cpp
        src/cliente.cpp
        src/juego.cpp
        src/lienzo.cpp
        src/textura.cpp
        src/objetoJuego.cpp)

target_link_libraries(client_src ${PROJECT_LINK_LIBS} SDL2 SDL2_image Threads::Threads)

install(FILES ../resources/images/ParteInferior.png  ../resources/images/Guard.png DESTINATION ${CMAKE_BINARY_DIR})
