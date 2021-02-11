#include "../include/jugadorLua.h"

JugadorLua::JugadorLua(Modelo& modelo) : modelo(modelo), esta_vivo(true){
    this->lua = ManejadorLua();
}

void JugadorLua::run() {
   // lua.crearMapa(modelo.obtenerMapa(),"mapa");
}