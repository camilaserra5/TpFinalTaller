#ifndef WOLFSTEIN_JUGADORLUA_H
#define WOLFSTEIN_JUGADORLUA_H

#include "thread.h"
#include "../../common/include/estadoJuego.h"
#include "../src/LUA/manejadorlua.h"
#include <string>

class JugadorLua {
private:
    bool esta_vivo;
    EstadoJuego &estadoJuego;
    ManejadorLua lua;

public:
    int id;
    /*
      * Creara el juagdor lua dejandolo valido para uso 
    */
    JugadorLua(EstadoJuego &estadoJuego, int id, std::string &ruta);

    /*
     * Agrega un Jugador al estadoJuego y se le pasa el mapa numerico al manejador de Lua.
     */
    void instanciarJugador(std::string &nombre);

    /*
     * Se le pide al modulo lua la proxima accion a hacer (puede moverse o disparar)
     */
    char procesar();

    ~JugadorLua();
};


#endif //WOLFSTEIN_JUGADORLUA_H
