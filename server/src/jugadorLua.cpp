#include "../include/jugadorLua.h"

JugadorLua::JugadorLua(EstadoJuego estadoJuego, int id) : esta_vivo(true), estadoJuego(estadoJuego), lua(
        (std::string &) "LUA/modulo.lua"), id(id){
    this->estadoJuego.agregarJugador((std::string &) "jugadorLua", this->id);
    lua.crearMapa(this->estadoJuego.GetMapanumerico(), "mapa");
}

char JugadorLua::procesar(){
    std::vector<int> posicion = estadoJuego.getPosicionJugador(id);
   char teclaComando = lua.generarEvento(posicion.front(), posicion.back());
   return teclaComando;
}