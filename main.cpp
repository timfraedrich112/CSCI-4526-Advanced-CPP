// Project 5
// Tim Fraedrich & Chidi Nna
#include "tools.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {
    banner();  // Print the banner

    if (argc != 2) {
        fatal("Usage: " + std::string(argv[0]) + " filename.txt");
    }

    std::ifstream input(argv[1]);  // argv[1] should be the file name
    if (!input.is_open()) {
        fatal("Cannot open text file " + std::string(argv[1]));
    }

    Game g(input);
    input.close();

    bye();
    return 0;
}


//Program Notes moving forward No more unit tests
