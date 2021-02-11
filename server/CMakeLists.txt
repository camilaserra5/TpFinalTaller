cmake_minimum_required(VERSION 2.8)

project(server)
find_package(Threads REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

set(PROJECT_LINK_LIBS libcommons.a)
link_directories(${PROJECT_SOURCE_DIR}/common/build)
include_directories(${PROJECT_SOURCE_DIR}/common/include)
find_package(yaml-cpp)
file(GLOB SOURCES src/thclient.cpp src/manejadorPartidas.cpp src/aceptador.cpp src/server_main.cpp src/cliente.cpp src/server_event_receiver.cpp src/servidor.cpp src/server_event_sender.cpp )
add_executable(server
        ${SOURCES})

target_link_libraries(server ${PROJECT_LINK_LIBS} SDL2 SDL2_image Threads::Threads ${YAML_CPP_LIBRARIES})

install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
