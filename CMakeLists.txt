cmake_minimum_required(VERSION 2.8)

project(GAME_OF_LIFE)

add_compile_options(-std=c++11)
set(SOURCE_FILES_LIST game_of_life.cpp)

add_executable(game_of_life ${SOURCE_FILES_LIST})