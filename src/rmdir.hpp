#ifndef RMDIR_HPP
#define RMDIR_HPP

#include <filesystem>
#include <string>
#include <optional>
#include <lua.hpp>

/**
 * Remove a file or an empty directory.
 * @param path The file or directory path to remove.
 * @return A string with the error message if any, or an empty string if successful.
 */
std::optional<std::string> rmdir(std::string_view path);

/**
 * Remove a directory and all its contents.
 * @param path The directory path to remove.
 * @return A string with the error message if any, or an empty string if successful.
 */
std::optional<std::string> rmdir_all(std::string_view path);

/**
 * Lua binding for removing a file or an empty directory.
 * @param L The Lua state.
 * @return Number of return values (1: error message or nil).
 * Lua usage: error_message = lua_rmdir(path)
 *   - path: The file or directory path to remove.
 */
int lua_rmdir(lua_State* L);

/**
 * Lua binding for removing a directory and all its contents.
 * @param L The Lua state.
 * @return Number of return values (1: error message or nil).
 * Lua usage: error_message = lua_rmdir_all(path)
 *   - path: The directory path to remove.
 */
int lua_rmdir_all(lua_State* L);

#endif // RMDIR_HPP
