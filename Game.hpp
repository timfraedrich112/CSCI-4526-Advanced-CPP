//Game.hpp
//Tim Fraedrich & Chidi Nna
#ifndef GAME_HPP
#define GAME_HPP
#include "tools.hpp"
#include "Board.hpp"
#include "Square.hpp"

class Game {
private:
    const string menuName = "Select an option";
    int menuCount = 6;
    const string menuItems[6] = {"M: Mark", "U: Undo", "R: Redo", "S: Save Game", "L: Load Game", "Q: Quit and Discard Game"};
    const string legalCodes = "tTdDsS";
    const string legalSelections = "mMuUrRsSlLqQ";
    Board* gameBoard;
    char gameType;
    short gameSize;
    ifstream& in;
    void Mark();
public:
    Game(ifstream& inputFile);
    ~Game();
    void Run();
};

#endif
