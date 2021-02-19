cmake_minimum_required(VERSION 2.8)

project(server)
find_package(Threads REQUIRED)
cmake_policy(SET CMP0015 NEW)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

set(PROJECT_LINK_LIBS commons)
link_directories(../common/build)
include_directories(../common/include)

find_package(yaml-cpp)
file(GLOB SOURCES src/LUA/manejadorlua.cpp src/jugadorLua.cpp src/thclient.cpp src/manejadorPartidas.cpp src/aceptador.cpp src/server_main.cpp src/cliente.cpp src/server_event_receiver.cpp src/servidor.cpp src/server_event_sender.cpp src/InvalidMapException.cpp)
add_executable(server
        ${SOURCES})

target_link_libraries(server ${PROJECT_LINK_LIBS} SDL2 SDL2_image Threads::Threads -Llib -llua5.3 ${YAML_CPP_LIBRARIES})

install(FILES src/LUA/modulo.lua DESTINATION ${CMAKE_BINARY_DIR})
install(FILES DESTINATION ${CMAKE_BINARY_DIR})

install(TARGETS server COMPONENT server RUNTIME DESTINATION "/usr/local/bin" LIBRARY DESTINATION "/usr/local/bin" DESTINATION "/usr/local/bin")
