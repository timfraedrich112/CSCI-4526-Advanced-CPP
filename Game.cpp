//Game.cpp
#include "Game.hpp"


Game::Game(ifstream& inputFile) : in(inputFile) {
    // Read the game type from the input file
    in >> gameType;

    // Check if the game type is valid; if not, handle as a stream error
    if (legalCodes.find(gameType) == string::npos) {
        fatal("Stream Error: Invalid game type code '" + string(1, gameType) + "' encountered in input file.");
    }

    // Instantiate the Board based on game type
    if (tolower(gameType) == 'd') {
        gameBoard = new DiagBoard(in, gameType, 29);
    } else if (tolower(gameType) == 's') {
        gameBoard = new SixyBoard(in, gameType, 24);
    } else {
        gameBoard = new TradBoard(in, gameType);
    }

    // Instantiate the Viewer and give it a reference to the Board (gameBoard)
    fancyView = new Viewer(gameBoard->getSize(), gameBoard->getSize(), *gameBoard);  // Pass the gameBoard as reference to Viewer

    undoStack.push(CreateFrame());
    Run();
}

Game::~Game() {
    delete gameBoard;
    delete fancyView;
}

void Game::Run() {
    char selection;
    do {
        // Show the board using the Viewer (assuming show function is defined in Viewer)
        fancyView->show(cout);
        try {
            selection = tolower(menu_c(menuName, menuCount, menuItems, legalSelections));
            if (legalSelections.find(selection) == string::npos) {
                throw invalid_argument("Invalid menu item selected.");
            }

            switch (selection) {
                case 'm':
                    Mark();
                    break;
                case 't':
                    TurnOff();
                    break;
                case 'u':
                    Undo();
                    break;
                case 'r':
                    Redo();
                    break;
                case 'q':
                    cout << endl << "Now exiting." << endl;
                    break;
                default:
                    cout << "Invalid menu item selected." << endl;
                    break;
            }
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl; // Log the invalid argument
        }
    } while (selection != 'q');
}

void Game::Mark() {
    char x, y, value;

    try {
    	// Get square to mark
    	cout << endl << "Select a square to mark (Input: x y): ";
    	cin >> x >> y;
    	while ((!isdigit(x) || !isdigit(y))
    	    || (tolower(gameType) == 's' && (x > '6' || y > '6'))
    	    ) {
    	    cout << endl << "Invalid entry" << endl;
    	    cout << endl << "Select a square to mark (Input: x y): ";
    	    cin >> x >> y;
    	}
        if (gameBoard->Sub(x - '0', y - '0').getState().isFixed()) {
            throw invalid_argument("Inputted Square contains a fixed value");
        }

    	// Get value to mark square with
    	cout << endl << "Select a value to mark square (" << x << ", " << y << ") with: ";
    	cin >> value;
    	while (!isdigit(value)
    	    || (tolower(gameType) == 's' && value > '6')
    	    ) {
    	    cout << endl << "Invalid entry" << endl;
    	    cout << endl << "Select a value to mark square (" << x << ", " << y << ") with: ";
    	    cin >> value;
    	}

    	// Mark square and output updated board
        short num = gameBoard->Sub(x - '0', y - '0').getState().getNumbers();
        if (num & 1 << (value - '0')) { //Number is a possibility: mark and create frame
            gameBoard->Sub(x - '0', y - '0').Mark(value);
            undoStack.push(CreateFrame());
            redoStack.zap();
        } else { //not possible
            throw invalid_argument("Inputted value is not possible");
        }

    } catch (const invalid_argument& e) {
        cerr << e.what() << endl; // Log the invalid coordinates or mark value
    }
}

void Game::TurnOff() {
    char x, y, value;

    try {
        // Get square to turn off option for
        cout << endl << "Select a square to turn off an option for (Input: x y): ";
        cin >> x >> y;
        while ((!isdigit(x) || !isdigit(y))
            || (tolower(gameType) == 's' && (x > '6' || y > '6'))
            ) {
            cout << endl << "Invalid entry" << endl;
            cout << endl << "Select a square to turn off an option for (Input: x y): ";
            cin >> x >> y;
        }

        if (gameBoard->Sub(x - '0', y - '0').getState().isFixed()) {
            throw invalid_argument("Cannot turn off option for fixed square");
        }

        // Get value to turn off
        cout << endl << "Select the value to turn off on square (" << x << ", " << y << "): ";
        cin >> value;
        while (!isdigit(value)
            || (tolower(gameType) == 's' && value > '6')
            ) {
            cout << endl << "Invalid entry" << endl;
            cout << endl << "Select a value to mark square (" << x << ", " << y << ") with: ";
            cin >> value;
        }

        short num = gameBoard->Sub(x - '0', y - '0').getState().getNumbers();
        if (num & 1 << (value - '0')) { //Number is a possibility: turn off bit
            gameBoard->Sub(x - '0', y - '0').getState().UpdateNumbers(value - '0');
            undoStack.push(CreateFrame());
            redoStack.zap();
        } else { //not possible
            throw invalid_argument("Inputted value already turned off");
        }
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl; // Log the invalid coordinates or mark value
    }
}

void Game::Undo() {
    try {
        if (undoStack.size() <= 1) {
            throw invalid_argument("Undo stack is empty");
        }

        Frame* previousFrame = undoStack.top();
        undoStack.pop();
        redoStack.push(previousFrame);
        gameBoard->restoreBoard(undoStack.top());

    } catch (const invalid_argument& e) {
        cerr << e.what() << endl; // Log the invalid coordinates or mark value
    }
}

void Game::Redo() {
    try {
        if (redoStack.size() < 1) {
            throw invalid_argument("Redo stack is empty");
        }

        Frame* previousFrame = redoStack.top();
        redoStack.pop();
        undoStack.push(previousFrame);
        gameBoard->restoreBoard(undoStack.top());

    } catch (const invalid_argument& e) {
        cerr << e.what() << endl; // Log the invalid coordinates or mark value
    }
}

Frame* Game::CreateFrame() const {
    Frame* currentBoard = new Frame();
    for (int j = 1; j <= gameBoard->getSize(); ++j) {
        for (int k = 1; k <= gameBoard->getSize(); ++k) {
            currentBoard->states.push_back(gameBoard->Sub(j, k).getState());
        }
    }
    return currentBoard;
}