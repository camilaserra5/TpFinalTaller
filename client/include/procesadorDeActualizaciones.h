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
        ProcesadorDeActualizaciones(Modelo* modelo,Actualizacion* actualizacion):
                                  modelo(modelo),actualizacion(actualizacion){}
        void ejecutar();
        void procesarActualizacionEmpezoPartida();
        void procesarActualizacionAperturaDePuerta();
        void procesarActualizacionCambioDeArma();
        void procesarActualizacionAtaque();
        void procesarActualizacionMoverse();
        void procesarActualizacionAgarreItem();
        void procesarActualizacionAgregarItem();
        void procesarActualizacionTerminoPartida();

    private:
        Modelo* modelo;
        Actualizacion* actualizacion;
};

#endif
