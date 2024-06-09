#ifndef FILE_EXISTS_HPP
#define FILE_EXISTS_HPP

#include <string>
#include <lua.hpp>

bool fileExists(const std::string& path);
int lua_fileExists(lua_State* L);
int luaopen_fileexists(lua_State* L);

#endif // FILE_EXISTS_HPP
