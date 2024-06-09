#include "mergeTablesDeep.hpp"
#include "deepCopyTable.hpp"

int lua_mergeTablesDeep(lua_State* L) {
    int n = lua_gettop(L); // get the number of tables
    if (n < 2) {
        return luaL_error(L, "Expected at least two tables as arguments");
    }

    for (int i = 1; i <= n; ++i) {
        if (!lua_istable(L, i)) {
            return luaL_error(L, "Expected all arguments to be tables");
        }
    }

    lua_newtable(L); // create new table for the result
    int resultTableIndex = lua_gettop(L); // get the index of the new table

    int nextIndex = 1; // Indice pour les clés numériques
    for (int i = 1; i <= n; ++i) {
        lua_pushvalue(L, i);                                      // Copie de la table courante
        deepCopyTable(L, lua_gettop(L), resultTableIndex, nextIndex); // Copie les éléments de la table au sommet de la pile vers la table en cours de construction
        lua_pop(L, 1);                                            // Supprime la copie de la table de la pile
    }

    return 1; // return the new table
}
