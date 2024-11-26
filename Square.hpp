//Square.hpp
//Tim Fraedrich & Chidi Nna
#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "tools.hpp"
#include "Cluster.hpp"

class Cluster; // Forward declaration of Cluster

class State {
private:
    short numbers;
    char value;
    bool fixed;
public:
    State() = default;
    State(char input);
    ~State() = default;
    void Mark(char ch);
    void UpdateNumbers(int val);
    std::ostream& Print(std::ostream& out);


    short getNumbers() { return numbers; }
    char getValue() { return value; }
    bool isFixed() { return fixed; }

};

//prints all data in the State in a readable format
inline std::ostream& operator<<(std::ostream& out, State& s) {
    return s.Print(out);
}

class Square {
private:
    State s;  // The state of the square
    short row, column;  // Row and column position of the square
    std::vector<Cluster*> clusters;  // Vector to store pointers to Cluster objects

public:
    Square() = default;
    Square(char value, short row, short column);
    ~Square();

    void Mark(char ch);  // Mark function to mark the square
    std::ostream& Print(std::ostream& out);  // Print function

    // Function to add a Cluster pointer to the vector of clusters
    void addCluster(Cluster* cluster) { clusters.push_back(cluster); }

    // Function to loop through all Clusters and call Cluster::Shoop()
    void Shoop(char val);

    State& getState() { return s; }

};

// Inline operator to print Square object easily
inline std::ostream& operator<<(std::ostream& out, Square& s) { return s.Print(out); }

#endif  // SQUARE_HPP
