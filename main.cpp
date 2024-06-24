// luapilot.cpp
#include "chdir.hpp"
#include "currentDir.hpp"
#include "deepCopyTable.hpp"
#include "helloThere.hpp"
#include "fileExists.hpp"
#include "fileSize.hpp"
#include "fileUtils.hpp"
#include "listFiles.hpp"
#include "memoryUtils.hpp"
#include "mergeTables.hpp"
#include "rmdir.hpp"
#include "mkdir.hpp"
#include "split.hpp"
#include <vector>
#include <string>
#include <iostream>

#include <lua.hpp>

static const struct luaL_Reg luapilot[] = {
    {"chdir", lua_chdir},
    {"currentDir", lua_currentDir},
    {"deepCopyTable", lua_deepCopyTable},
    {"fileExists", lua_fileExists},
    {"getBasename", lua_getBasename},
    {"getExtension", lua_getExtension},
    {"getFilename", lua_getFilename},
    {"getFileSize", lua_fileSize},
    {"getListFiles", lua_listFiles},
    {"getMemoryUsage", lua_getMemoryUsage},
    {"getPath", lua_getPath},
    {"helloThere", lua_helloThere},
    {"mergeTables", lua_mergeTables},
    {"mkdir", lua_mkdir},
    {"rmdir", lua_rmdir},
    {"rmdir_all", lua_rmdir_all},
    {"split", lua_split},
    {NULL, NULL}};

extern "C" int luaopen_luapilot(lua_State *L) {
    luaL_newlib(L, luapilot);
    return 1;
}
