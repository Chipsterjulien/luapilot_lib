cmake_minimum_required(VERSION 3.10)
project(luapilot)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Définir le répertoire des sources
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Scanner récursivement le répertoire src pour trouver tous les fichiers .cpp et .hpp
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp")

# Inclure les fichiers headers
include_directories(${SRC_DIR})
include_directories(${LUA_INCLUDE})

# Ajouter la bibliothèque partagée
add_library(luapilot SHARED ${SOURCES})

# Lier Lua et les autres bibliothèques nécessaires
target_link_libraries(luapilot ${LUA_LIB} ncurses tinfo)

# Définir les options de compilation pour créer une bibliothèque partagée
set_target_properties(luapilot PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)
