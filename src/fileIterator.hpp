#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

#include <lua.hpp>
#include <filesystem>
#include <vector>
#include <string>

/**
 * @brief A class to iterate over files in a directory.
 */
class FileIterator {
public:
    /**
     * @brief Constructor for FileIterator.
     * @param path The directory path to iterate.
     * @param recursive Whether to iterate recursively.
     */
    FileIterator(const std::string& path, bool recursive);

    /**
     * @brief Get the next file in the iteration.
     * @return The next file path.
     */
    const std::string& next();

    /**
     * @brief Check if there are more files to iterate.
     * @return True if there are more files, false otherwise.
     */
    bool hasNext() const;

private:
    /**
     * @brief Load files from the given directory.
     * @param path The directory path to load files from.
     * @param recursive Whether to load files recursively.
     */
    void loadFiles(const std::string& path, bool recursive);

    std::vector<std::string> files; ///< List of file paths.
    std::vector<std::string>::iterator current; ///< Current iterator position.
};

extern "C" {
    /**
     * @brief Create a FileIterator and push it onto the Lua stack.
     * @param L Lua state.
     * @return Number of return values.
     */
    int lua_createFileIterator(lua_State* L);

    /**
     * @brief Get the next file from the FileIterator.
     * @param L Lua state.
     * @return Number of return values.
     */
    int lua_nextFile(lua_State* L);

    /**
     * @brief Open the FileIterator library in Lua.
     * @param L Lua state.
     * @return Number of return values.
     */
    int luaopen_file_iterator(lua_State* L);
}

#endif // FILE_ITERATOR_HPP
