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
    int& id;
public:
    JugadorLua(EstadoJuego estadoJuego, int id);
    char procesar();
    ~JugadorLua(){};
};


#endif //WOLFSTEIN_JUGADORLUA_H
