#ifndef WOLFSTEIN_JUGADORLUA_H
#define WOLFSTEIN_JUGADORLUA_H

#include "thread.h"
#include "../../common/include/estadoJuego.h"
#include "../src/LUA/manejadorlua.h"
#include <string>

class JugadorLua{
private:
    bool esta_vivo;
    EstadoJuego& estadoJuego;
    ManejadorLua lua;

public:
    JugadorLua(EstadoJuego& estadoJuego, int id, std::string& ruta);
    void instanciarJugador(std::string & nombre);
    char procesar();
    int& id;
    ~JugadorLua();
};


#endif //WOLFSTEIN_JUGADORLUA_H
