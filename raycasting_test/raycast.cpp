#include <iostream>
#include <math.h>
#include "map_translator.h"
#include "juego.h"
#include <thread>

int main() {
  std::string nombre = "Sol";
  int id = 1;
  float anguloJugador =  3.0 * acos(0.0) + acos(0.0) ;
  int pixelesX = 80, pixelesY = 80;
  Posicion posicion(pixelesX,pixelesY,anguloJugador);
  Jugador jugador(nombre,id);
  jugador.setPosicion(posicion);
  int i = 1;
  Juego *juego = new Juego("Wolfstein", ANCHO_CANVAS, ALTURA_CANVAS, false,id,jugador);
  try {
      while (juego->estaCorriendo()) {
          juego->run();
          std::chrono::milliseconds duration(30);
          std::this_thread::sleep_for(duration);
      }
      juego->clean();
  } catch (...) {
      std::cout << "error";
  }
  delete juego;
    return 0;

}
