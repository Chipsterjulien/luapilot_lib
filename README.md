# luapilot_lib (LuaPilot Library)

## Introduction

The LuaPilot library is a collection of utilities and functions designed to facilitate various operations in Lua. This project provides various tools for file manipulation, text splitting, and table operations, among others.

## Compilation

If you want to compile the LuaPilot library, clone the repository and compile the project using the provided script.

```sh
git clone https://github.com/Chipsterjulien/luapilot_lib.git
cd luapilot_lib
./build_local.sh
```

## Usage

**Download** library :

Download the [latest library here](https://github.com/Chipsterjulien/luapilot_lib/releases)

For example, put luapilot.so into libraries directory. Below are some examples :

```lua
package.cpath = package.cpath .. ";./libraries/?.so" -- Include the path where our .so is located, here in the libraries directory

local luapilot = require("luapilot") -- Import the C++ module luapilot
local inspect = require("inspect")

-- List files in a directory
local files, err = luapilot.listFiles(".")
if err then
    print(err)
else
    for _, file in ipairs(files) do
        print(file)
    end
end

-- Check if a file exists
local fileFound, err = luapilot.fileExists("my/folder/file.txt")
print(err or "File exists: " .. tostring(fileFound))

-- Merge two tables
local table1 = {a = 1, b = 2}
local table2 = {b = 3, c = 4}
local table3 = {"g", "h", "i"}
local t3 = {i = 8, j = { k = 9, l = 10} }
local t4 = { i = 8, j = { k = 9, l = 10, m = { n = 11, o = 12, } } }
local mergedTable = luapilot.mergeTables(table1, table2)
print(inspect(mergedTable))

-- Merge multiple tables
local mergedMultipleTables = luapilot.mergeTables(table1, table2, {d = 5}, {e = 6}, t4, t3)
print(inspect(mergedMultipleTables))

-- Make a deep copy of a table
local deepCopy = luapilot.deepCopyTable(t4)
print(inspect(deepCopy))

-- Split a string
local parts = luapilot.split("hello,world", ",")
for _, part in ipairs(parts) do
    print(part)
end
```
