cmake_minimum_required(VERSION 3.27)
project(A1 C)

set(CMAKE_C_STANDARD 23)
add_executable(A1 movieRecommendations.c
        movieRecommendations.h
        main.c
)
