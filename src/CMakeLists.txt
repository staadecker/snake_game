﻿# CMakeList.txt : CMake project for snake_game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("snake_game")

# Add source to this project's executable.
add_executable (snake_game "main.c" "game.c" "game_structure.c")
add_executable (test_game "test_game.c" "game.c" "game_structure.c")
add_executable (test_game_structure "test_game_structure.c" "game_structure.c")

# TODO: Add tests and install targets if needed.
