# CMakeList.txt : CMake project for snake_game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("snake_game")

# Add source to this project's executable.
add_executable (snake_game "main.c" "game_structure.h" "game.c" "game.h")
add_executable (test_game "test_game.c" "game.h" "game.c" "minunit.h" "game_structure.h")

# TODO: Add tests and install targets if needed.
