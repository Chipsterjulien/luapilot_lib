// luapilot.cpp
#include "helloThere.hpp"
#include "fileExists.hpp"
#include "fileSize.hpp"
#include "fileUtils.hpp"
#include "listFiles.hpp"
#include "memoryUtils.hpp"
#include "mergeTablesDeep.hpp"
#include "split.hpp"
#include "tableCopy.hpp"
#include <vector>
#include <string>
#include <iostream>

#include <lua.hpp>

static const struct luaL_Reg luapilot[] = {
    {"fileExists", lua_fileExists},
    {"getBasename", lua_getBasename},
    {"getExtension", lua_getExtension},
    {"getFilename", lua_getFilename},
    {"getFileSize", lua_fileSize},
    {"getListFiles", lua_listFiles},
    {"getMemoryUsage", lua_getMemoryUsage},
    {"getPath", lua_getPath},
    {"helloThere", lua_helloThere},
    {"mergeTables", lua_mergeTablesDeep},
    {"split", lua_split},
    {"tableDeepCopy", lua_deepCopy},
    {NULL, NULL}
};

extern "C" int luaopen_luapilot(lua_State *L) {
    luaL_newlib(L, luapilot);
    return 1;
}
