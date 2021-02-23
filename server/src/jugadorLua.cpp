#include "../include/jugadorLua.h"

JugadorLua::JugadorLua(EstadoJuego &estadoJuego, int id, std::string &ruta) :
        esta_vivo(true),
        estadoJuego(estadoJuego),
        lua(ruta),
        id(id) {}

void JugadorLua::instanciarJugador(std::string &nombre) {
    std::cerr << "======ID ES: "<< this->id << std::endl;
    this->estadoJuego.agregarJugador(nombre, this->id );
    lua.crearMapa(this->estadoJuego.GetMapanumerico());
}

char JugadorLua::procesar() {
    std::cerr << "======PROCESAR, ID ES: "<< this->id << std::endl;
    std::vector<int> posicionMapa = estadoJuego.getPosicionEspecificaJugador(this->id);
    std::vector<int> posicionesJugadores = estadoJuego.getPosicionesEnemigos(this->id);
    std::vector<int> posicionPixels = estadoJuego.getPosicionPixels(this->id);
    int cantidadJugadores = posicionesJugadores.size()/2;
    std::string retorno(lua.generarEvento(posicionMapa.front(), posicionMapa.back(),
                posicionesJugadores, cantidadJugadores, posicionPixels.front(), posicionPixels.back()));
    char teclaComando = retorno.at(0);
      std::cerr << "======RETORNO DE PROCESAR: "<< retorno << std::endl;
    return teclaComando;
}

JugadorLua::~JugadorLua() {
    esta_vivo = false;
    estadoJuego.desconectarJugador(this->id);
//    std::cerr << "=== DESTRUYENDO JUGADOR LUA==== " << std::endl;
}
