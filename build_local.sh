#!/bin/bash

# Fonction pour formater les tailles en Ko ou Mo
function format_size {
    local size=$1
    if [ $size -ge 1048576 ]; then
        echo "$(bc <<< "scale=2; $size/1048576") Mo"
    elif [ $size -ge 1024 ]; then
        echo "$(bc <<< "scale=2; $size/1024") Ko"
    else
        echo "$size bytes"
    fi
}

# Vérifier si CMake est installé
if ! command -v cmake &> /dev/null; then
    echo "CMake n'est pas installé. Veuillez l'installer avant de continuer."
    exit 1
fi

# Vérifier si pkg-config est installé
if ! command -v pkg-config &> /dev/null; then
    echo "pkg-config n'est pas installé. Veuillez l'installer avant de continuer."
    exit 1
fi

# Vérifier si wget est installé
if ! command -v wget &> /dev/null; then
    echo "wget n'est pas installé. Veuillez l'installer avant de continuer."
    exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"
DOWNLOAD_DIR="${SCRIPT_DIR}/downloads"
LUA_VERSION="5.4.7"
LUA_DIR="lua-$LUA_VERSION"
LUA_TAR="$LUA_DIR.tar.gz"
LUA_BUILD_DIR="${BUILD_DIR}/lua_build"
LUA_LIB="${LUA_BUILD_DIR}/${LUA_DIR}/src/liblua.a"
LUA_INCLUDE="${LUA_BUILD_DIR}/${LUA_DIR}/src"

# Répertoire pour installer luapilot.so
LIBRARIES_DIR="${SCRIPT_DIR}/libraries"
SHARED_LIB="luapilot.so"

# Supprimer l'ancien fichier luapilot.so s'il existe dans le répertoire de build
SHARED_LIB_BUILD=$(find "$BUILD_DIR" -name "luapilot.so")
if [ -n "$SHARED_LIB_BUILD" ]; then
    echo "Suppression de l'ancien fichier $SHARED_LIB_BUILD..."
    rm "$SHARED_LIB_BUILD"
fi

# Supprimer l'ancien fichier luapilot.so s'il existe
if [ -f "$LIBRARIES_DIR/$SHARED_LIB" ]; then
    echo "Suppression de l'ancien fichier $SHARED_LIB..."
    rm "$LIBRARIES_DIR/$SHARED_LIB"
fi

# Créer les répertoires nécessaires
mkdir -p "$DOWNLOAD_DIR"
mkdir -p "$LUA_BUILD_DIR"
mkdir -p "$BUILD_DIR"
mkdir -p "$LIBRARIES_DIR"

# Télécharger Lua si nécessaire
if [ ! -f "$DOWNLOAD_DIR/$LUA_TAR" ]; then
    echo "Téléchargement de Lua $LUA_VERSION..."
    wget "http://www.lua.org/ftp/$LUA_TAR" -O "$DOWNLOAD_DIR/$LUA_TAR"
    if [ $? -ne 0 ]; then
        echo "Échec du téléchargement de Lua."
        exit 1
    fi
fi

# Décompresser Lua si nécessaire
if [ ! -d "$LUA_BUILD_DIR/$LUA_DIR" ]; then
    echo "Décompression de Lua $LUA_VERSION..."
    tar -xzf "$DOWNLOAD_DIR/$LUA_TAR" -C "$LUA_BUILD_DIR"
    if [ $? -ne 0 ]; then
        echo "Échec de la décompression de Lua."
        exit 1
    fi
fi

# Compiler Lua si les fichiers nécessaires sont absents
if [ ! -f "$LUA_LIB" ] || [ ! -f "${LUA_INCLUDE}/lua.h" ]; then
    echo "Compilation de Lua $LUA_VERSION..."
    cd "$LUA_BUILD_DIR/$LUA_DIR"
    sed -i 's/^MYCFLAGS=.*/MYCFLAGS=-fPIC/' src/Makefile
    sed -i 's/^MYLIBS=.*/MYLIBS=-lm/' src/Makefile
    sed -i 's/^ALL_T=.*/ALL_T=liblua.a/' src/Makefile

    make clean
    make linux -j$(nproc)
    if [ $? -ne 0 ]; then
        echo "Échec de la compilation de Lua."
        exit 1
    fi
else
    echo "Lua $LUA_VERSION est déjà compilé."
fi

# Revenir au répertoire du script
cd "$SCRIPT_DIR"

# Créer le répertoire de build pour le projet
PROJECT_BUILD_DIR="${BUILD_DIR}/project_build"
mkdir -p "$PROJECT_BUILD_DIR"
cd "$PROJECT_BUILD_DIR"

# Générer les fichiers de build avec CMake
cmake "$SCRIPT_DIR" -DLUA_LIB="$LUA_LIB" -DLUA_INCLUDE="$LUA_INCLUDE"
if [ $? -ne 0 ]; then
    echo "Échec de la configuration avec CMake."
    exit 1
fi

# Compiler le projet
make -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Échec de la compilation du projet."
    exit 1
fi

# Recherche du fichier luapilot.so dans le répertoire de build
SHARED_LIB_BUILD=$(find "$PROJECT_BUILD_DIR" -name "luapilot.so")

# Vérifier si le fichier luapilot.so existe
if [ ! -f "$SHARED_LIB_BUILD" ]; then
    echo "Fichier $SHARED_LIB_BUILD non trouvé."
    exit 1
fi

# Vérifier si upx est installé
if command -v upx &> /dev/null; then
    echo "UPX est installé."
    # Compression du fichier luapilot.so avec UPX
    echo "Compression de $SHARED_LIB_BUILD avec UPX..."
    original_size=$(stat -c%s "$SHARED_LIB_BUILD")
    upx --best "$SHARED_LIB_BUILD"
    if [ $? -ne 0 ]; then
        echo "Échec de la compression de $SHARED_LIB_BUILD avec UPX."
        exit 1
    fi
    compressed_size=$(stat -c%s "$SHARED_LIB_BUILD")
    size_reduction=$((original_size - compressed_size))
    original_size_formatted=$(format_size $original_size)
    compressed_size_formatted=$(format_size $compressed_size)
    size_reduction_formatted=$(format_size $size_reduction)
    echo "Taille originale : $original_size_formatted"
    echo "Taille après compression : $compressed_size_formatted"
    echo "Réduction de taille : $size_reduction_formatted"
else
    echo "UPX n'est pas installé. $SHARED_LIB_BUILD ne sera pas compressé."
fi

# Copier luapilot.so dans le répertoire libraries
cp "$SHARED_LIB_BUILD" "$LIBRARIES_DIR/$SHARED_LIB"
if [ $? -ne 0 ]; then
    echo "Échec de la copie de $SHARED_LIB_BUILD dans $LIBRARIES_DIR."
    exit 1
fi

echo
# Indiquer que le processus est terminé
echo "Compilation terminée avec succès."


cd "${SCRIPT_DIR}"
cp "libraries/luapilot.so" "test/libraries/luapilot.so"
cd test
lua main.lua