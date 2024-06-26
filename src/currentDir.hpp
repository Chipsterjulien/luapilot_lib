#ifndef CURRENT_DIR_HPP
#define CURRENT_DIR_HPP

#include <string>
#include <lua.hpp>

// Struct to hold the result of currentDir function
struct CurrentDirResult {
    std::string path;
    std::string error_message;
};

/**
 * Get the current working directory.
 * @return A CurrentDirResult struct containing the current directory path and an error message if any.
 */
CurrentDirResult currentDir();

/**
 * Lua binding for getting the current working directory.
 * @param L The Lua state.
 * @return Number of return values (2: current directory path and error message).
 * Lua usage: path, error_message = lua_currentDir()
 */
int lua_currentDir(lua_State* L);

#endif // CURRENT_DIR_HPP
