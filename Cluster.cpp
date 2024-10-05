//Cluster.cpp
//Cluster Class
//Tim Fraedrich & Chidi Nna

#include "Cluster.hpp"

Cluster::Cluster(const char* clusterType, Square** s) {
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
    return out;
}