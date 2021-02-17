#include "../include/jugadorLua.h"

JugadorLua::JugadorLua(EstadoJuego estadoJuego, int id) : esta_vivo(true), estadoJuego(estadoJuego), lua(
        (std::string &) "LUA/modulo.lua"), id(id){
    this->estadoJuego.agregarJugador((std::string &) "jugadorLua", this->id);
    lua.crearMapa(this->estadoJuego.GetMapanumerico());
}

char JugadorLua::procesar(){
    std::vector<int> posicion = estadoJuego.getPosicionJugador(id);

    std::string retorno(lua.generarEvento(posicion.front(), posicion.back()));
    char teclaComando = retorno.at(0);

    return teclaComando;
}

JugadorLua::~JugadorLua() {}
