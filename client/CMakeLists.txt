cmake_minimum_required(VERSION 2.8)

project(client)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

set(PROJECT_LINK_LIBS libcommons.a)
link_directories(~/TpFinalTaller/common/build)
include_directories(~/TpFinalTaller/common/include)

file(GLOB SOURCES src/*.cpp)
add_executable(client ${SOURCES} src/sprite.cpp src/player.cpp)

target_link_libraries(client ${PROJECT_LINK_LIBS} SDL2 SDL2_image SDL2_ttf Threads::Threads)

install(FILES ../resources/images/ParteInferior.png ../resources/images/Guard.png DESTINATION ${CMAKE_BINARY_DIR})
