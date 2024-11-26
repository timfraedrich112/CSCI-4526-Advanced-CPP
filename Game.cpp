//Game.cpp
//Tim Fraedrich & Chidi Nna
#include "Game.hpp"

Game::Game(ifstream& inputFile) : in(inputFile) {
    // Read the game type from the input file
    in >> gameType;

    // Check if the game type is valid; if not, handle as a stream error
    if (legalCodes.find(gameType) == string::npos) {
        fatal("Stream Error: Invalid game type code '" + string(1, gameType) + "' encountered in input file.");
    }


    if (tolower(gameType) == 'd') {
        gameBoard = new DiagBoard(in, gameType, 29);
    } else {
        gameBoard = new Board(in, gameType);
    }

    cout << *gameBoard << endl; //test print
    Run();
}


Game::~Game() { delete gameBoard; }

void Game::Run() {
    char selection;
    do {
        try {
            selection = tolower(menu_c(menuName, menuCount, menuItems, legalSelections));
            if (legalSelections.find(selection) == string::npos) {
                throw invalid_argument("Invalid menu item selected.");
            }

            switch (selection) {
                case 'm':
                    Mark();
                    break;
                case 'u':
                    cout << endl << "Undoing" << endl;
                    break;
                case 'r':
                    cout << endl << "Redoing" << endl;
                    break;
                case 's':
                    cout << endl << "Saving game" << endl;
                    break;
                case 'l':
                    cout << endl << "Loading game" << endl;
                    break;
                case 'q':
                    cout << endl << "Now exiting." << endl;
                    break;
                default:
                    cout << "Invalid menu item selected." << endl;
                    break;
            }
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl; // L
        }
    } while (selection != 'q');
}

void Game::Mark() {
    char x, y, value;

    try {
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
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl; // Log the invalid coordinates or mark value
    }
}
