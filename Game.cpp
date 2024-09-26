//Game.cpp
//Game Class
//Tim Fraedrich & Chidi Nna

#include "Game.hpp"

Game::Game(ifstream& inputFile) : in(inputFile) {
    in >> gameType;
    if (legalCodes.find(gameType) == string::npos) fatal(string("Invalid game type code: ") += gameType);
}

void Game::Run() {
    char selection;
    do {
        selection = tolower(menu_c(menuName, menuCount, menuItems, legalSelections));
        switch(selection) {
            case 'm': //mark
                cout << endl << "Marking" << endl;
                break;
            case 'u': //undo
                cout << endl << "Undoing" << endl;
                break;
            case 'r': //redo
                cout << endl << "Redoing" << endl;
                break;
            case 's': //save
                cout << endl << "Saving game" << endl;
                break;
            case 'l': //load
                cout << endl << "Loading game" << endl;
                break;
            case 'q': //quit
                cout << endl << "Now exiting." << endl;
                break;
            default: cerr << "Invalid menu item selected" << endl;
                break;
        }
    } while (selection != 'q');
}