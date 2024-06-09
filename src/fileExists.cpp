#include "fileExists.hpp"
#include <filesystem>

namespace fs = std::filesystem;

bool fileExists(const std::string &path) {
    return fs::exists(path) && fs::is_regular_file(path);
}

int lua_fileExists(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);
    bool exists = fileExists(std::string(path));
    lua_pushboolean(L, exists);
    return 1;
}

int luaopen_fileexists(lua_State* L) {
    lua_register(L, "fileExists", lua_fileExists);
    return 0;
}
