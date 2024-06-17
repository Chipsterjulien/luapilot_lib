#ifndef DEEP_COPY_TABLE_HPP
#define DEEP_COPY_TABLE_HPP

#include <lua.hpp>

// Fonction de copie profonde (deep copy) pour Lua
void deepCopyTable(lua_State *L, int srcIndex, int destIndex, int &nextIndex);
int lua_deepCopy(lua_State *L);

#endif