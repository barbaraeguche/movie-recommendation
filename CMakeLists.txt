cmake_minimum_required(VERSION 3.5.0)
project(movie-recommendation VERSION 0.1.0 LANGUAGES C)

add_executable(movie-recommendation main.c movies.c)

include(CTest)
enable_testing()