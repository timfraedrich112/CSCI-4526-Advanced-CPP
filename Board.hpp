//Board.hpp
//Board Class
//Tim Fraedrich & Chidi Nna
#ifndef BOARD_HPP
#define BOARD_HPP
#include "tools.hpp"
#include "Square.hpp"

class Board {
private:
    ifstream& in;
    int n;
    Square* bd;
    short unmarked;
    void GetPuzzle();
    Square& Sub(int row, int column);
public:
    Board(ifstream& in, char type);
    ~Board();
    ostream& Print(ostream& out);
};

inline ostream& operator << (ostream& out, Board& b) { return b.Print(out); }

#endif //BOARD_HPP