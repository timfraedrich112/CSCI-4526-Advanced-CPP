//Game.hpp
//Game Class
//Tim Fraedrich & Chidi Nna
#ifndef GAME_HPP
#define GAME_HPP
#include "tools.hpp"
#include "State.hpp"

class Board;

class Game {
private:
    const string menuName = "Select an option";
    int menuCount = 6;
    const string menuItems[6] = {"M: Mark", "U: Undo", "R: Redo", "S: Save Game", "L: Load Game", "Q: Quit and Discard Game"};
    const string legalCodes = "tTdDsS";
    const string legalSelections = "mMuUrRsSlLqQ";
    Board* board;
    char gameType;
    short gameSize;
    ifstream& in;
public:
    Game(ifstream& inputFile);
    void Run();
};

#endif