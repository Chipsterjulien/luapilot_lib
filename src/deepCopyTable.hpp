#ifndef DEEP_COPY_TABLE_HPP
#define DEEP_COPY_TABLE_HPP

#include <lua.hpp>

void deepCopyTable(lua_State *L, int srcIndex, int destIndex, int &nextIndex);

#endif