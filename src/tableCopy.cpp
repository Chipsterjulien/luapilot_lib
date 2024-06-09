#include "tableCopy.hpp"
#include "deepCopyTable.hpp"

// Fonction de copie profonde (deep copy) pour Lua
int lua_deepCopy(lua_State* L) {
    // Vérifier qu'il y a exactement un argument
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "Expected one table as argument");
    }

    // Vérifier que l'argument est une table
    if (!lua_istable(L, 1)) {
        return luaL_error(L, "Expected argument to be a table");
    }

    // Créer une nouvelle table pour le résultat
    lua_newtable(L);
    int resultTableIndex = lua_gettop(L);

    int nextIndex = 1; // Indice pour les clés numériques
    lua_pushvalue(L, 1); // Copier la table source au sommet de la pile
    deepCopyTable(L, lua_gettop(L), resultTableIndex, nextIndex); // Copier les éléments
    lua_pop(L, 1); // Supprimer la copie de la table source

    return 1; // Retourner la nouvelle table copiée
}