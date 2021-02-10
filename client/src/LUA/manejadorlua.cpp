#include "manejadorlua.h"

ManejadorLua::ManejadorLua(){
    interprete = luaL_newstate();
}

void ManejadorLua::vaciarStack() {
    int stackSize = lua_gettop(interprete);
    while(stackSize != 0) {
        lua_pop(interprete, 1);
        stackSize = lua_gettop(interprete);
    }
}

ManejadorLua::~ManejadorLua() {
    vaciarStack();
    lua_close(interprete);
}

/* Crea una tabla en lua que es guardada en el stack
 * para ser usada por el script
 */
void ManejadorLua::crearTabla(std::vector<std::vector<int>> mapa, std::string nombremapa) {
    lua_newtable(interprete);
    for(int i = 0; i < mapa.size(); i++) {
        lua_pushnumber(interprete, i + 1);    // indice de la tabla
        lua_newtable(interprete);                    // tabla
        int size = mapa[i].size();
        for(int j = 0; j < size; j++) {
            lua_pushnumber(interprete, j + 1);       // indice del valor
            lua_pushnumber(interprete, mapa[i][j]);     // valor
            lua_settable(interprete, -3);
        }
        lua_settable( interprete, -3 );
    }
    lua_setglobal(interprete, nombremapa.c_str());
}

void ManejadorLua::crearMapa(std::vector<std::vector<int>> mapa, std::string nombreMapa) {
    this->mapaLargo = mapa.size();
    this->mapaAncho = mapa[0].size();
    crearTabla(mapa, nombreMapa);
}