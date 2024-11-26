//Cluster.hpp
//Tim Fraedrich & Chidi Nna
#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "tools.hpp"

class Square;

enum class ClusterT {   //ClusterType is needed to clearly differentiate between the three types of
	                       //clusters in the Sudoku-like game (Rows, Columns, and Boxes)
    Row,
    Column,
    Box,
	Diagonal

};

static const string clusterTypeNames[4] = {"Row", "Column", "Box", "Diagonal"};

class Cluster {
private:
    ClusterT type;
    string typeName;
    Square* squares[9];  // Array of Square pointers

public:
    Cluster(ClusterT cl, Square* inputSquares[]);  // Constructor with Square
    ~Cluster() = default;

    void Shoop(char val);
    std::ostream& Print(std::ostream& out);
};

// Overload the << operator for Cluster
inline std::ostream& operator<<(std::ostream& out, Cluster& c) { return c.Print(out); }

#endif  //
