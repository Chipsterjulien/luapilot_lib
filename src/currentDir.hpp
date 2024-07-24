#ifndef CURRENTDIR_HPP
#define CURRENTDIR_HPP

#include <filesystem>
#include <optional>
#include <string>
#include <lua.hpp>

/**
 * @brief Get the current working directory.
 *
 * @return std::optional<std::string> The current directory path if successful,
 *         or std::nullopt on failure.
 */
std::optional<std::string> currentDir();

/**
 * @brief Lua binding for getting the current working directory.
 *
 * This function is a Lua binding that exposes the currentDir function to Lua scripts.
 * It returns the current directory path if successful, or an error message if it fails.
 *
 * @param L The Lua state.
 * @return int Number of return values (2: current directory path and error message).
 *
 * @note Lua usage: currentDir, err = lua_currentDir()
 */
int lua_currentDir(lua_State* L);

#endif // CURRENTDIR_HPP
