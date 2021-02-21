#include "../include/jugadorLua.h"

JugadorLua::JugadorLua(EstadoJuego &estadoJuego, int id, std::string &ruta) :
        esta_vivo(true),
        estadoJuego(estadoJuego),
        lua(ruta),
        id(id) {}

void JugadorLua::instanciarJugador(std::string &nombre) {
    this->estadoJuego.agregarJugador(nombre, this->id);
    lua.crearMapa(this->estadoJuego.GetMapanumerico());
}

char JugadorLua::procesar() {
    std::vector<int> posicion = estadoJuego.getPosicionJugador(777);
    std::string retorno(lua.generarEvento(posicion.front(), posicion.back()));
    char teclaComando = retorno.at(0);
    std::cerr << "======RETORNO DE PROCESAR: "<< teclaComando << std::endl;
    return teclaComando;
}

JugadorLua::~JugadorLua() {
    esta_vivo = false;
    estadoJuego.desconectarJugador(this->id);
    std::cerr << "=== DESTRUYENDO JUGADOR LUA==== " << std::endl;
}
