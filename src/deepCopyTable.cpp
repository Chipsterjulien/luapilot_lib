#include "deepCopyTable.hpp"

void deepCopyTable(lua_State *L, int srcIndex, int destIndex, int &nextIndex) {
    lua_pushnil(L); // Première clé
    while (lua_next(L, srcIndex) != 0) {
        if (lua_type(L, -2) == LUA_TNUMBER) {
            // Clé numérique, ajouter à la fin de la liste
            if (lua_istable(L, -1)) {
                lua_newtable(L); // create new table for the subtable
                deepCopyTable(L, lua_gettop(L) - 1, lua_gettop(L), nextIndex);
                lua_rawseti(L, destIndex, nextIndex++); // Add the new table to the result
            } else {
                lua_pushvalue(L, -1);                   // Copier la valeur
                lua_rawseti(L, destIndex, nextIndex++); // Ajouter à la fin de la table de destination
            }
        } else {
            // Clé non numérique, copier normalement
            lua_pushvalue(L, -2); // Copier la clé
            if (lua_istable(L, -1)) {
                lua_newtable(L); // create new table for the subtable
                deepCopyTable(L, lua_gettop(L) - 1, lua_gettop(L), nextIndex);
                lua_settable(L, destIndex); // Set the new table in the result
            } else {
                lua_pushvalue(L, -2);       // Copier la valeur
                lua_settable(L, destIndex); // Insérer dans la table de destination
            }
        }
        lua_pop(L, 1); // Supprimer la valeur, garder la clé pour lua_next
    }
}