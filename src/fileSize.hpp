#ifndef FILESIZE_HPP
#define FILESIZE_HPP

#include <lua.hpp>
#include <string>
#include <cstdint>

bool fileSize(const std::string &path, std::uint64_t &size);
int lua_fileSize(lua_State *L);

#endif // FILESIZE_HPP
