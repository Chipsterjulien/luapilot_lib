// luapilot.cpp
#include "attributes.hpp"
#include "chdir.hpp"
#include "currentDir.hpp"
#include "deepCopyTable.hpp"
#include "fileExists.hpp"
#include "fileIterator.hpp"
#include "fileSize.hpp"
#include "fileUtils.hpp"
#include "find.hpp"
#include "helloThere.hpp"
#include "link.hpp"
#include "listFiles.hpp"
#include "memoryUtils.hpp"
#include "mergeTables.hpp"
#include "mkdir.hpp"
#include "rmdir.hpp"
#include "setmode.hpp"
#include "sleep.hpp"
#include "split.hpp"
#include "symlinkattr.hpp"
#include "touch.hpp"
#include <vector>
#include <string>
#include <iostream>

#include <lua.hpp>

static const struct luaL_Reg luapilot[] = {
    {"attributes", lua_setattr},
    {"chdir", lua_chdir},
    {"currentDir", lua_currentDir},
    {"deepCopyTable", lua_deepCopyTable},
    {"fileExists", lua_fileExists},
    {"fileSize", lua_fileSize},
    {"find", lua_find},
    {"getBasename", lua_getBasename},
    {"getExtension", lua_getExtension},
    {"getFilename", lua_getFilename},
    {"getFileSize", lua_fileSize},
    {"getMemoryUsage", lua_getMemoryUsage},
    {"getPath", lua_getPath},
    {"link", lua_link},
    {"listFiles", lua_listFiles},
    {"helloThere", lua_helloThere},
    {"mergeTables", lua_mergeTables},
    {"mkdir", lua_mkdir},
    {"rmdir", lua_rmdir},
    {"rmdirAll", lua_rmdir_all},
    {"setmode", lua_setmode},
    {"sleep", lua_sleep},
    {"split", lua_split},
    {"symlinkattr", lua_symlinkattr},
    {"touch", lua_touch},
    {"createFileIterator", lua_createFileIterator},
    {NULL, NULL}};

extern "C" int luaopen_luapilot(lua_State *L) {
    luaL_newlib(L, luapilot);

    luaL_requiref(L, "file_iterator", luaopen_file_iterator, 1);
    lua_setfield(L, -2, "file_iterator");

    return 1;
}
