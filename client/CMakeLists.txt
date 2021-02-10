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

file(GLOB SOURCES src/animacion.cpp src/anunciador.cpp src/armaAnimada.cpp src/audio.cpp src/background.cpp src/client_event_receiver.cpp src/client_event_sender.cpp src/client_main.cpp src/cliente.cpp src/enemigo.cpp src/fonts.cpp src/highscoreWindow.cpp src/informacionJugador.cpp src/juego.cpp src/label.cpp src/logInWindow.cpp src/manejador_eventos.cpp src/modelo.cpp src/musica.cpp src/objetoDibujable.cpp src/objetoJuego.cpp src/player.cpp src/rayo.cpp src/sonido.cpp src/scene.cpp src/sprite.cpp src/textura.cpp src/ventana.cpp)
add_executable(client ${SOURCES} src/sprite.cpp src/player.cpp include/spriteAnimado.h include/audio.h src/audio.cpp include/sonido.h src/sonido.cpp include/musica.h src/musica.cpp src/LUA/manejadorlua.cpp src/LUA/manejadorlua.h)

target_link_libraries(client ${PROJECT_LINK_LIBS} SDL2 SDL2_image SDL2_ttf SDL2_mixer Threads::Threads -Llib -llua5.3)

install(FILES ../resources/images/ParteInferior.png ../resources/images/Guard.png  ../resources/sonidos/musiquita.wav DESTINATION ${CMAKE_BINARY_DIR})
