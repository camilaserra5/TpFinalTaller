#include <iostream>
#include <math.h>
#include "map_translator.h"
#include "rayo.h"
#include "juego.h"
#include <thread>


int main() {
  Juego *juego = new Juego();
  Map mapa(20,20);
  std::string nombre = "Sol";
  int id = 1;
  float anguloJugador = 2 * acos(0.0) / 3;
  int pixelesX = 120, pixelesY = 100;
  Posicion posicion(pixelesX,pixelesY,anguloJugador);
  Jugador jugador(nombre,id);
  jugador.setPosicion(posicion);
  int i = 1;
  try {
      juego->inicializar("Wolfstein", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
      while (juego->estaCorriendo()) {
          juego->handleEvents();
          juego->actualizar();
          juego->renderizar();
          juego->raycasting(mapa,jugador);
          //std::chrono::milliseconds duration(20);
          //std::this_thread::sleep_for(duration);
      }
      juego->clean();
  } catch (...) {
      std::cout << "error";
  }
  delete juego;
    return 0;

}
