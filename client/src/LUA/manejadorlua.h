#ifndef WOLFSTEIN_MANEJADORLUA_H
#define WOLFSTEIN_MANEJADORLUA_H

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}
#include <vector>
#include <string>

class ManejadorLua {
    lua_State *interprete;
    int mapaAncho;
    int mapaLargo;

    void crearTabla(std::vector<std::vector<int>> table, std::string nombremapa);
public:
    ManejadorLua();
    ~ManejadorLua();
    /*
     * Recibe mapa de la partida actual para guardar y usarla para poder moverse.
     */
    void  crearMapa(std::vector<std::vector<int>> mapa, std::string nombremapa);
    void vaciarStack();
};


#endif //WOLFSTEIN_MANEJADORLUA_H

