cmake_minimum_required(VERSION 2.8)

project(client)
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

file(GLOB SOURCES src/animacion.cpp src/anunciador.cpp src/armaAnimada.cpp src/audio.cpp src/background.cpp src/client_event_receiver.cpp src/client_event_sender.cpp src/client_main.cpp src/cliente.cpp src/enemigo.cpp src/fonts.cpp src/highscoreWindow.cpp src/informacionJugador.cpp src/juego.cpp src/label.cpp src/logInWindow.cpp src/manejador_eventos.cpp src/modelo.cpp src/musica.cpp src/objetoDibujable.cpp src/objetoJuego.cpp src/player.cpp src/rayo.cpp src/sonido.cpp src/scene.cpp src/sprite.cpp src/textura.cpp src/ventana.cpp)
add_executable(client ${SOURCES} src/sprite.cpp src/player.cpp include/spriteAnimado.h include/audio.h src/audio.cpp include/sonido.h src/sonido.cpp include/musica.h src/musica.cpp ../server/src/LUA/manejadorlua.cpp ../server/src/LUA/manejadorlua.h ../server/src/jugadorLua.cpp ../server/include/jugadorLua.h)

target_link_libraries(client ${PROJECT_LINK_LIBS} SDL2 SDL2_image SDL2_ttf SDL2_mixer Threads::Threads -Llib -llua5.3 ${YAML_CPP_LIBRARIES})

install(FILES ../resources/images/ParteInferior.png ../resources/images/Guard.png ../resources/sonidos/musiquita.wav ../resources/sonidos/Knife.wav ../resources/sonidos/Pistol.wav DESTINATION ${CMAKE_BINARY_DIR})

install(TARGETS client COMPONENT client RUNTIME DESTINATION "/usr/local/bin" LIBRARY DESTINATION "/usr/local/bin" DESTINATION "/usr/local/bin")
