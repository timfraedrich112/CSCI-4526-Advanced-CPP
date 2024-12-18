//main.cpp
//Tim Fraedrich & Chidi Nna
//P11 Sudoku Helper
//CSCI 4526 Advanced C++
#include <iostream>
#include <fstream>
#include "Game.hpp"

using namespace std;

int main(int argc, char** argv) {
    //Quit program if input file not provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    // Open the input file
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Could not open input file " << argv[1] << endl;
        return 1;
    }

    try {
        Game game(inputFile);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Closing input file
    inputFile.close();
    return 0;
}