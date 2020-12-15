#include <iostream>
#include <math.h>
#include "map.h"
#include "map_translator.h"
#include "rayo.h"

#define ANCHO_CANVAS 320
#define LARGO_CANVAS 320
#define TAMANIO_FILA 10
#define TAMANIO_COLUMNA 10
#define LARGO_PROYECTOR 320
#define ANCHO_PROYECTOR 20


int main() {

    int mapa[TAMANIO_FILA][TAMANIO_COLUMNA] = { {1,1,1,1,1,1,1,1,1,1},
                                                {1,0,0,0,0,0,0,0,0,1},
                                                {1,0,0,0,0,0,0,0,0,1},
                                                {1,0,0,1,0,0,0,0,0,1},
                                                {1,0,0,1,0,1,0,0,0,1},
                                                {1,0,0,0,0,1,0,0,0,1},
                                                {1,0,0,0,0,1,0,0,0,1},
                                                {1,0,0,0,0,0,0,0,0,1},
                                                {1,0,0,0,0,0,0,0,0,1},
                                                {1,1,1,1,1,1,1,1,1,1}
    };

    float posJugadorX, posJugadorY, alturaJugador;
    float anguloDeVista = 2 * acos(0.0) / 3;
    float anguloJugador = 2 * acos(0.0) / 3;
    int alturaParedProyectada = 0;
    int ladoCelda = ANCHO_CANVAS/TAMANIO_FILA;

    Rayo rayo(anguloDeVista, ladoCelda, /*TAMANIO_FILA*/ANCHO_CANVAS, LARGO_PROYECTOR);

    for (int i = ANCHO_CANVAS; i > 0; i--) {
      //como barremos antihorario, barremos de derecha a izquierda la pantalla, igual barre al revez
        float distancia = 0;
        if (rayo.verificarInterseccionHorizontal(mapa, distancia, anguloJugador)) {
            alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
            std::cout << "la altura es: " << alturaParedProyectada << "\n";
        } else if (rayo.verificarInterseccionVertical(mapa, distancia, anguloJugador)) {
            alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
            std::cout << "la altura es: " << alturaParedProyectada << "\n";
        }

        /*  if (distancia > 0){
            dibujarPared(alturaParedProyectada,i);
          }*/
        rayo.aumentarAnguloBarrido();
    }
    Juego *juego = new Juego();
    try {
        juego->inicializar("Wolfstein", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
        while (juego->estaCorriendo()) {
            juego->handleEvents();
            juego->actualizar();
            juego->renderizar();
        }
        juego->clean();
    } catch (...) {
        std::cout << "error";
    }
    return 0;

}
