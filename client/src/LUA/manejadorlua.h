//
// Created by stephi on 2/1/21.
//

#ifndef WOLFSTEIN_MANEJADORLUA_H
#define WOLFSTEIN_MANEJADORLUA_H

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

class ManejadorLua {
    lua_State *interprete;
public:
    ManejadorLua();
    ~ManejadorLua();

    void vaciarStack();
};


#endif //WOLFSTEIN_MANEJADORLUA_H
