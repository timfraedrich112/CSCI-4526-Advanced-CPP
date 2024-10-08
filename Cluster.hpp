//Cluster.hpp
//Cluster Class
//Tim Fraedrich & Chidi Nna

#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include "tools.hpp"
#include "Square.hpp"

enum class ClusterType { Box, Column, Row };
static constexpr string clusterTypeStrings[3] = {"Box", "Column", "Row"};

class Cluster {
private:
    const char* typeName;
    ClusterType type;
    Square* s[9];
public:
    Cluster(ClusterType cl, Square* inputSquares[]);
    void Shoop(char val);
    ostream& Print(ostream& out);
};

inline ostream& operator << (ostream& out, Cluster& c) { return c.Print(out); }

#endif //CLUSTER_HPP