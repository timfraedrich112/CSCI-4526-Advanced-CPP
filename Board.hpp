//Board.hpp
//Tim Fraedrich & Chidi Nna
#ifndef BOARD_HPP
#define BOARD_HPP

#include "tools.hpp"
#include "Square.hpp"
#include "Cluster.hpp"
#include "CanView.hpp"
#include "Frame.hpp"

class Board : public CanView {
protected:
    ifstream& in;
    int n;
    Square* bd;
    short unmarked;
    vector<Cluster*> clusters;
    void GetPuzzle();
    void makeClusters();
    void createRow(short j);
    void createColumn(short k);
    void createBox(short j, short k);

public:
    Square& Sub(int row, int column) const;
    Board(ifstream& in, char type, int clusterCount = 27);
    int getSize() const { return n; }
    void restoreBoard(Frame* f) const;
    ostream& Print(ostream& out);
    virtual char getMarkChar(int row, int col) const;
    virtual string getPossibilityString(int row, int col) const override;
    virtual ~Board() = default;
};

inline ostream& operator << (ostream& out, Board& b) { return b.Print(out); }

class DiagBoard : public Board {
private:
    void createDiagonals();

public:
    DiagBoard(ifstream& in, char type, int clusterCount = 29);
    ~DiagBoard();
};

class SixyBoard : public Board {
public:
    void createVBoxes();
    void createHBoxes();

    SixyBoard(ifstream& in, char type, int clusterCount = 24);
    ~SixyBoard();
};

class TradBoard : public Board {
public:
    TradBoard(ifstream& in, char type, int clusterCount = 27);
    ~TradBoard();
};

#endif BOARD_HPP