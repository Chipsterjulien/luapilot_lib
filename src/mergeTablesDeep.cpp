#include "mergeTablesDeep.hpp"
#include "deepCopyTable.hpp"

int lua_mergeTablesDeep(lua_State* L) {
    int n = lua_gettop(L); // obtenir le nombre de tables
    if (n < 2) {
        return luaL_error(L, "Expected at least two tables as arguments");
    }

    for (int i = 1; i <= n; ++i) {
        if (!lua_istable(L, i)) {
            return luaL_error(L, "Expected all arguments to be tables");
        }
    }

    lua_newtable(L); // créer une nouvelle table pour le résultat
    int resultTableIndex = lua_gettop(L); // obtenir l'index de la nouvelle table

    int nextIndex = 1; // Indice pour les clés numériques
    for (int i = 1; i <= n; ++i) {
        lua_pushvalue(L, i); // Copier la table courante
        deepCopyTable(L, lua_gettop(L), resultTableIndex, nextIndex); // Copier les éléments de la table au sommet de la pile vers la table en cours de construction
        lua_pop(L, 1); // Supprimer la copie de la table de la pile
    }

    return 1; // retourner la nouvelle table
}

