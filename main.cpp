// Project 5
// Tim Fraedrich & Chidi Nna
#include "tools.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {
    banner();  // Print the banner

    // Open and check file from command line
    if (argc != 2) fatal(string("Usage: ") + argv[0] + " filename.txt");
    ifstream input(argv[1]);  // argv[0] is the name of the program.
    if (!input.is_open()) fatal(string("Cannot open text file ") + argv[1]);

    // Call the updated test function
    Game g(input);

    input.close();

    bye();  // Print exit
    return 0;
}