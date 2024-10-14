cmake_minimum_required(VERSION 3.29)
project(P5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(P5
    Board.cpp
    Board.hpp
    Cluster.cpp
    Cluster.hpp
    Game.cpp
    Game.hpp
    main.cpp
    Square.cpp
    Square.hpp
    tools.cpp
    tools.hpp)
