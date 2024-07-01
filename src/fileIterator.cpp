#include "fileIterator.hpp"
#include <iostream>

namespace fs = std::filesystem;

/**
 * @brief Constructs a FileIterator.
 * 
 * Initializes the FileIterator to iterate over files in the specified path.
 * 
 * @param path The directory path to iterate.
 * @param recursive Whether to iterate recursively.
 */
FileIterator::FileIterator(const std::string& path, bool recursive) {
    loadFiles(path, recursive);
    current = files.begin();
}

/**
 * @brief Loads files from the given directory.
 * 
 * Loads all regular files from the specified directory into the internal list. 
 * If recursive is true, it recursively loads files from subdirectories.
 * 
 * @param path The directory path to load files from.
 * @param recursive Whether to load files recursively.
 */
void FileIterator::loadFiles(const std::string& path, bool recursive) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry)) {
            files.push_back(entry.path().string());
        }

        if (recursive && fs::is_directory(entry)) {
            loadFiles(entry.path().string(), recursive);
        }
    }
}

/**
 * @brief Gets the next file in the iteration.
 * 
 * Returns the next file path in the iteration.
 * 
 * @return The next file path.
 */
const std::string& FileIterator::next() {
    return *(current++);
}

/**
 * @brief Checks if there are more files to iterate.
 * 
 * @return True if there are more files, false otherwise.
 */
bool FileIterator::hasNext() const {
    return current != files.end();
}

/**
 * @brief Creates a FileIterator and pushes it onto the Lua stack.
 * 
 * This function is called from Lua to create a new FileIterator.
 * It expects two arguments on the Lua stack:
 * 1. The directory path to iterate.
 * 2. A boolean indicating whether to iterate recursively.
 * 
 * @param L Lua state.
 * @return The number of return values (1).
 */
int lua_createFileIterator(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);
    bool recursive = lua_gettop(L) >= 2 && lua_toboolean(L, 2);

    // Allocate FileIterator and push it as a userdata
    void* userdata = lua_newuserdata(L, sizeof(FileIterator));
    new (userdata) FileIterator(path, recursive);

    // Set the metatable for garbage collection
    luaL_getmetatable(L, "FileIterator");
    lua_setmetatable(L, -2);

    return 1;
}

/**
 * @brief Gets the next file from the FileIterator.
 * 
 * This function is called from Lua to get the next file from the FileIterator.
 * It expects one argument on the Lua stack:
 * 1. The FileIterator userdata.
 * 
 * It returns the next file path or nil if there are no more files.
 * 
 * @param L Lua state.
 * @return The number of return values (1).
 */
int lua_nextFile(lua_State* L) {
    FileIterator* iterator = (FileIterator*)luaL_checkudata(L, 1, "FileIterator");

    if (iterator->hasNext()) {
        lua_pushstring(L, iterator->next().c_str());
    } else {
        lua_pushnil(L);
    }

    return 1;
}

/**
 * @brief Garbage collection for FileIterator.
 * 
 * This function is called from Lua when the FileIterator userdata is garbage collected.
 * It destroys the FileIterator.
 * 
 * @param L Lua state.
 * @return The number of return values (0).
 */
int lua_gcFileIterator(lua_State* L) {
    FileIterator* iterator = (FileIterator*)luaL_checkudata(L, 1, "FileIterator");
    iterator->~FileIterator();
    return 0;
}

/**
 * @brief Opens the FileIterator library in Lua.
 * 
 * This function registers the FileIterator functions with Lua.
 * It creates a metatable for the FileIterator userdata and registers the
 * createFileIterator function.
 * 
 * @param L Lua state.
 * @return The number of return values (0).
 */
extern "C" int luaopen_file_iterator(lua_State* L) {
    luaL_newmetatable(L, "FileIterator");

    lua_pushcfunction(L, lua_gcFileIterator);
    lua_setfield(L, -2, "__gc");

    lua_pushcfunction(L, lua_nextFile);
    lua_setfield(L, -2, "next");

    lua_pop(L, 1);

    lua_register(L, "createFileIterator", lua_createFileIterator);

    return 0;
}
