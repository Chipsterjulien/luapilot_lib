// luapilot.cpp
#include "attributes.hpp"
#include "chdir.hpp"
#include "copy.hpp"
#include "copyTree.hpp"
#include "currentDir.hpp"
#include "deepCopyTable.hpp"
#include "fileExists.hpp"
#include "fileSize.hpp"
#include "fileUtils.hpp"
#include "find.hpp"
#include "helloThere.hpp"
#include "isdir.hpp"
#include "isfile.hpp"
#include "link.hpp"
#include "listFiles.hpp"
#include "md5.hpp"
#include "memoryUtils.hpp"
#include "mergeTables.hpp"
#include "mkdir.hpp"
#include "moveTree.hpp"
#include "joinPath.hpp"
#include "rename.hpp"
#include "remove.hpp"
#include "rmdir.hpp"
#include "mode.hpp"
#include "sha1.hpp"
#include "sha3_256.hpp"
#include "sha3_512.hpp"
#include "sha256.hpp"
#include "sha512.hpp"
#include "sleep.hpp"
#include "split.hpp"
#include "symlinkattr.hpp"
#include "touch.hpp"
#include "fileIterator.hpp"

#include <vector>
#include <string>
#include <iostream>

#include <lua.hpp>

static const struct luaL_Reg luapilot[] = {
    {"setAttributes", lua_setattr},
    {"getAttributes", lua_getattr},
    {"chdir", lua_chdir},
    {"copy", lua_copy_file},
    {"copyTree", lua_copyTree},
    {"currentDir", lua_currentDir},
    {"deepCopyTable", lua_deepCopyTable},
    {"fileExists", lua_fileExists},
    {"fileSize", lua_fileSize},
    {"find", lua_find},
    {"getBasename", lua_getBasename},
    {"getExtension", lua_getExtension},
    {"getFilename", lua_getFilename},
    {"getMemoryUsage", lua_getMemoryUsage},
    {"getDetailedMemoryUsage", lua_getDetailedMemoryUsage},
    {"getMode", lua_getmode},
    {"getPath", lua_getPath},
    {"helloThere", lua_helloThere},
    {"isdir", lua_isDir},
    {"isfile", lua_isFile},
    {"joinPath", lua_joinPath},
    {"link", lua_link},
    {"listFiles", lua_listFiles},
    {"md5sum", lua_md5sum},
    {"mergeTables", lua_mergeTables},
    {"mkdir", lua_mkdir},
    {"moveTree", lua_moveTree},
    {"remove", lua_remove_file},
    {"rename", lua_rename},
    {"rmdir", lua_rmdir},
    {"rmdirAll", lua_rmdir_all},
    {"setMode", lua_setmode},
    {"sha1sum", lua_sha1sum},
    {"sha3_256sum", lua_sha3_256sum},
    {"sha3_512sum", lua_sha3_512sum},
    {"sha256sum", lua_sha256sum},
    {"sha512sum", lua_sha512sum},
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
