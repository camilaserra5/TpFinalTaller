#include "../include/jugadorLua.h"

JugadorLua::JugadorLua(EstadoJuego estadoJuego, int id) : esta_vivo(true), estadoJuego(estadoJuego), lua(
        (std::string &) "LUA/modulo.lua"), id(id){
    this->estadoJuego.agregarJugador((std::string &) "jugadorLua", this->id);
}
// lua.crearMapa(modelo.obtenerMapa(),"mapa");
//en un while poner que haga las cositas
//tiene que ser como un jugador O SEA TIENE UN ID y tiene que tener una cola de comandos
//tambien tiene que hacer las cosas bloqueantes

char JugadorLua::procesar(){
   char teclaComando = lua.generarEvento();
   return teclaComando;
}