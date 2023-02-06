#!/bin/sh

# supprime ancien dossier de build et le refait
rm -rf build
mkdir build
cd build

# genère la solution du projet
cmake build ../

# compile le projet en un éxecutable
cmake --build ./