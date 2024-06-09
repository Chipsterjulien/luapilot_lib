# luapilot_lib (LuaPilot Library)

## Introduction

La bibliothèque LuaPilot est une collection d'utilitaires et de fonctions conçue pour faciliter diverses opérations en Lua. Ce projet fournit divers outils pour la manipulation de fichiers, la gestion de la mémoire, et les opérations sur les tableaux, entre autres.

## Installation

Pour utiliser la bibliothèque LuaPilot, clonez le dépôt et compilez le projet en utilisant le script fourni.

```sh
git clone <repository_url>
cd luapilot_lib
./build_local.sh
```

## Utilisation

Une fois compilé, importez le fichier .so dans votre script lua. Voici quelques exemples :

```lua
package.cpath = package.cpath .. ";./libraries/?.so" -- Inclusion du path où se trouve notre .so, ici dans le répertoire libraries

local luapilot = require("luapilot") -- Importation du module C++ luapilot

-- Fonction split
local a = luapilot.split("Bonjour tout le monde", " ")
for _, e in ipairs(a) do
    print(e)
end

-- Ici on prépare des tables pour les fusionner par la suite
local table1 = {"a", "b", "c"}
local table2 = {"d", "e", "f"}
local table3 = {"g", "h", "i"}
local t3 = {i = 8, j = { k = 9, l = 10} }
local t4 = { i = 8, j = { k = 9, l = 10, m = { n = 11, o = 12, } } }

print("Merge tables deep")
local mergedTables = luapilot.mergeTables(table1, table2, table3, t3, t4)

print("Deep copy table t4")
local myNewTable = luapilot.tableDeepCopy(mergedTables)

-- On veut savoir si un fichier existe
local path = "my/path/filename.txt"
local exists = luapilot.fileExists(path)

-- On souhaite connaître la taille en ko d'un fichier
local sizeInKo = luapilot.getFileSize(path)

-- D'autres fonctions utiles sur un fichier
print(luapilot.getBasename(path))
print(luapilot.getExtension(path))
print(luapilot.getFilename(path))
print(luapilot.getPath(path))

-- Obtenir la liste récursive des fichiers contenus dans un répertoire
local filesList = luapilot.getFilesList("my/path/", true)
for _, filename in ipairs(filesList) do
    print(filename)
end
```
