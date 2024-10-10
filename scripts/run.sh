#!/bin/sh

premake5 ecc
premake5 gmake
make config=debug -j
./bin/Debug/Game
