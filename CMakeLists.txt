cmake_minimum_required(VERSION 3.29)
project(P1)

set(CMAKE_CXX_STANDARD 20)

add_executable(P1
        tools.cpp
        tools.hpp
        main.cpp
        Game.cpp
        Game.hpp
        Square.cpp
        Square.hpp
        Board.cpp
        Board.hpp
        Cluster.cpp)
