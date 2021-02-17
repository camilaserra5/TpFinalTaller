#include "../include/jugadorLua.h"

JugadorLua::JugadorLua(EstadoJuego& estadoJuego, int id, std::string & ruta) :
 esta_vivo(true),
 estadoJuego(estadoJuego),
 lua(ruta),
 id(id){
    std::string nombre("jugadorLua");
    this->estadoJuego.agregarJugador(nombre, this->id);
    lua.crearMapa(this->estadoJuego.GetMapanumerico());
}

char JugadorLua::procesar(){
    std::vector<int> posicion = estadoJuego.getPosicionJugador(id);

    std::string retorno(lua.generarEvento(posicion.front(), posicion.back()));
    char teclaComando = retorno.at(0);

    return teclaComando;
}

JugadorLua::~JugadorLua() {}
