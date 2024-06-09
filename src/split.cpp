#include "split.hpp"
#include <string>
#include <vector>
#include <sstream>

// Fonction pour scinder une chaîne de caractères
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;

    // Vérifiez si la chaîne est vide
    if (str.empty()) {
        return tokens;
    }

    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Fonction Lua pour scinder une chaîne de caractères
int lua_split(lua_State* L) {
    if (lua_gettop(L) != 2 || !lua_isstring(L, 1) || !lua_isstring(L, 2)) {
        return luaL_error(L, "Expected two arguments: (string, delimiter)");
    }

    std::string str = lua_tostring(L, 1);
    std::string delimiter = lua_tostring(L, 2);
    if (delimiter.length() != 1) {
        return luaL_error(L, "Delimiter should be a single character");
    }

    std::vector<std::string> tokens = split(str, delimiter[0]);

    lua_newtable(L);
    for (size_t i = 0; i < tokens.size(); ++i) {
        lua_pushnumber(L, i + 1);
        lua_pushstring(L, tokens[i].c_str());
        lua_settable(L, -3);
    }

    return 1;
}
