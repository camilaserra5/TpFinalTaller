cmake_minimum_required(VERSION 2.8)

project(sdl)
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(~/TpFinalTaller/logJuegoVentana/include)

add_executable(sdldemo
        src/pruebaSDLmain.cpp
        src/juego.cpp
        src/textura.cpp src/lienzo.cpp include/lienzo.h)

target_link_libraries(sdldemo SDL2 SDL2_image)

install(FILES ../resources/images/ParteInferior.png DESTINATION ${CMAKE_BINARY_DIR})
