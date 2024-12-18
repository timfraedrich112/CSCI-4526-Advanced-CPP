//Cluster.hpp
//Tim Fraedrich & Chidi Nna
#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "tools.hpp"

class Square;

enum class ClusterT {
    Row,
    Column,
    Box,
    Diagonal,
    VBox,
    HBox
};

static const string clusterTypeNames[6] = {"Row", "Column", "Box", "Diagonal", "VBox", "HBox"};

class Cluster {
private:
    ClusterT type;
    int clusterSize;
    string typeName;
    Square** squares;  // Array of Square pointers

public:
    Cluster(ClusterT cl, int n, Square* inputSquares[]);  // Constructor with Square
    ~Cluster() = default;

    void Shoop(char val);
    std::ostream& Print(std::ostream& out);
};

inline std::ostream& operator<<(std::ostream& out, Cluster& c) { return c.Print(out); }

#endif CLUSTER_HPP