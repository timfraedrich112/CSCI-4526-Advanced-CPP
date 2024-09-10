cmake_minimum_required(VERSION 3.29)
project(CSCI_4526_Advanced_CPP)

set(CMAKE_CXX_STANDARD 14)

include_directories(P1)

add_executable(CSCI_4526_Advanced_CPP
    P1/main.cpp
    P1/State.cpp
    P1/State.hpp
    P1/tools.cpp
    P1/tools.hpp)
