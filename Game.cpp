//Game.cpp
//Tim Fraedrich & Chidi Nna
#include "Game.hpp"

Game::Game(ifstream& inputFile) : in(inputFile) {
    in >> gameType;
    gameBoard = new Board(in, gameType);
    if (legalCodes.find(gameType) == string::npos) fatal(string("Invalid game type code: ") += gameType);
    cout << *gameBoard << endl; //test print
    Run();
}

Game::~Game() { delete gameBoard; }

void Game::Run() {
    char selection;
    do {
        selection = tolower(menu_c(menuName, menuCount, menuItems, legalSelections));
        switch(selection) {
            case 'm': //mark
                Mark();
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
            default: cout << "Invalid menu item selected" << endl; //cerr
                break;
        }
    } while (selection != 'q');
}

void Game::Mark() {
    char x, y, value;

    //Get square to mark
    cout << endl << "Select a square to mark (Input: x y): ";
    cin >> x >> y;
    while(!isdigit(x) || !isdigit(y)) {
        cout << endl << "Invalid entry" << endl;
        cout << endl << "Select a square to mark (Input: x y): ";
        cin >> x >> y;
    }

    //Get value to mark square with
    cout << endl << "Select a value to mark square (" << x << ", " << y << ") with: ";
    cin >> value;
    while(!isdigit(value)) {
        cout << endl << "Invalid entry" << endl;
        cout << endl << "Select a value to mark square (" << x << ", " << y << ") with: ";
        cin >> value;
    }

    //Mark square and output updated board
    gameBoard->Sub(x - '0', y - '0').Mark(value);
    cout << *gameBoard << endl;
}