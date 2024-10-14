//Board.hpp
//Tim Fraedrich & Chidi Nna
#ifndef BOARD_HPP
#define BOARD_HPP

#include "tools.hpp"
#include "Square.hpp"
#include "Cluster.hpp"

class Board {
private:
    ifstream& in;
    int n;
    Square* bd;
    short unmarked;
    void GetPuzzle();   //
    vector<Cluster*> clusters;  // vector of Cluster pointers

    // Private helper functions for creating clusters
    void makeClusters();       // Function to create all clusters
    void createRow(short j);   // Function to create a row cluster
    void createColumn(short k); // Function to create a column cluster
    void createBox(short j, short k); // Function to create a box cluster

public:
    Square& Sub(int row, int column);
    Board(ifstream& in, char type);
    ~Board();
    ostream& Print(ostream& out);
};

inline ostream& operator<<(ostream& out, Board& b) { return b.Print(out); }

#endif // BOARD_HPP
