#include <iostream>
#include <math.h>
#include "map.h"
#include "map_translator.h"
#include "rayo.h"
#include "juego.h"
#include <thread>


int main() {
  Juego *juego = new Juego();
  int i = 1;
  try {
      juego->inicializar("Wolfstein", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
      while (juego->estaCorriendo()) {
          juego->handleEvents();
          juego->actualizar();
          juego->renderizar();
          juego->raycasting();
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
