//Cluster.cpp
//Cluster Class
//Tim Fraedrich & Chidi Nna

#include "Cluster.hpp"

Cluster::Cluster(ClusterType cl, Square* inputSquares[])
    : type(cl) {
    switch (cl) {
        case ClusterType::Box: typeName = clusterTypeStrings[0].c_str(); break;
        case ClusterType::Column: typeName = clusterTypeStrings[1].c_str(); break;
        case ClusterType::Row: typeName = clusterTypeStrings[2].c_str(); break;
        default: fatal("Unknown cluster type");
    }

    //Square::AddCluster() for each square added to cluster (needs "this")

}

void Cluster::Shoop(char val) {
    // Convert the char parameter to an int value. (Character subtraction)
    /* For each of the cluster’s nine Square pointers, use the Square* to turn off the bit
       corresponding to the parameter value. Do this for all Squares in the Cluster, even if they
       are fixed or equal to the Square that initiated the move. This will help to make the
       possibility display useful. */
}

ostream& Cluster::Print(ostream& out) {
    out << typeName << ": " << endl;
    for (int k = 0; k < 9; k++) {
        out << *s << endl;
    }
    out << endl;
    return out;
}