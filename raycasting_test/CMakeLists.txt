cmake_minimum_required(VERSION 2.8)

project(raycasting_test)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -lm")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})
find_package(yaml-cpp)

set(PROJECT_LINK_LIBS libcommons.a)
link_directories(~/TpFinalTaller/common/build)
include_directories(~/TpFinalTaller/common/include)

add_executable(raycasting_test
        raycast.cpp
        rayo.cpp
        juego.cpp
        lienzo.cpp
        ../client/src/modelo.cpp
        ../client/src/textura.cpp
        ../client/src/ventana.cpp
        ../client/src/sprite.cpp
        ../client/src/player.cpp
        ../client/src/objetoJuego.cpp
        ../client/src/label.cpp
        ../client/src/fonts.cpp
        ../client/src/scene.cpp


        ${UIS_HEADERS})

target_link_libraries(raycasting_test ${PROJECT_LINK_LIBS} SDL2 SDL2_image SDL2_ttf Threads::Threads ${YAML_CPP_LIBRARIES})
