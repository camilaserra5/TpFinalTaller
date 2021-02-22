#ifndef PROCESADOR_DE_ACTUALIZACIONES_H
#define PROCESADOR_DE_ACTUALIZACIONES_H

#include "map.h"
#include <actualizaciones/actualizacionTerminoPartida.h>
#include <actualizaciones/actualizacionInicioPartida.h>
#include <actualizaciones/actualizacionMovimiento.h>
#include <actualizaciones/actualizacionAtaque.h>
#include <actualizaciones/actualizacionCambioArma.h>
#include <actualizaciones/actualizacionAperturaPuerta.h>
#include <actualizaciones/actualizacionAgarroItem.h>
#include <actualizaciones/actualizacionAgregarItem.h>
#include "objetoJuego.h"
class Modelo;

class ProcesadorDeActualizaciones{

    public:
        /*
          * Creara el procesador de actualizaciones dejandolo valido para uso
          * el modelo, y la actualizacion deben estar inicializados
        */
        ProcesadorDeActualizaciones(Modelo* modelo,Actualizacion* actualizacion):
                                  modelo(modelo),actualizacion(actualizacion){}
        /*
          * se encarga de verificar el tipo de actualizacion y ejecurtarla
        */
        void ejecutar();
        /*
          * procesa la actualizacion de emepzar partida
        */
        void procesarActualizacionEmpezoPartida();
        /*
          * procesar actualizaciones de apertura de puerta
        */
        void procesarActualizacionAperturaDePuerta();
        /*
          * peocesar actualizacion de cambio de arma
        */
        void procesarActualizacionCambioDeArma();
        /*
          * procesar actualizacion de ataque
        */
        void procesarActualizacionAtaque();
        /*
          * procesa actualiazcion de moverse
        */
        void procesarActualizacionMoverse();
        /*
          * procesa actualizacion de agarrrar item
        */
        void procesarActualizacionAgarreItem();
        /*
          * procesa actualizacion de agregar item
        */
        void procesarActualizacionAgregarItem();
        /*
          * procesa actualizaciones de terminar partida
        */   
        void procesarActualizacionTerminoPartida();

    private:
        Modelo* modelo;
        Actualizacion* actualizacion;
};

#endif
