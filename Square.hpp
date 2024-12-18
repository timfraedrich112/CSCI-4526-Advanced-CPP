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

    short getNumbers() { return numbers; }
    char getValue() { return value; }
    bool isFixed() { return fixed; }

    ostream& Print(ostream& out) const;
};

inline std::ostream& operator<<(std::ostream& out, State& s) { return s.Print(out); }

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
    void Shoop(char val);
    void addCluster(Cluster* cluster) { clusters.push_back(cluster); }

    string getPossibilities();
    State& getState() { return s; }
    void setState(const State newState) { s = newState; }

    ostream& Print(ostream& out);  // Print function
};

inline std::ostream& operator<<(std::ostream& out, Square& s) { return s.Print(out); }

#endif SQUARE_HPP