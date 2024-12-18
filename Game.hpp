//Game.hpp
//Tim Fraedrich & Chidi Nna
#ifndef GAME_HPP
#define GAME_HPP
#include "tools.hpp"
#include "Board.hpp"
#include "Viewer.hpp"
#include "Frame.hpp"

class Game {
private:
    const string menuName = "Select an option";
    int menuCount = 5;
    const string menuItems[5] = {"M: Mark", "T: Turn Off Option", "U: Undo", "R: Redo", "Q: Quit and Discard Game"};
    const string legalCodes = "tTdDsS";
    const string legalSelections = "mMtTuUrRqQ";
    Board* gameBoard;
    Viewer* fancyView;
    Stack undoStack;
    Stack redoStack;
    char gameType;
    short gameSize;
    ifstream& in;
    Frame* CreateFrame() const;

    void Mark();
    void TurnOff();
    void Undo();
    void Redo();

public:
    Game(ifstream& inputFile);
    ~Game();
    void Run();
};

#endif GAME_HPP