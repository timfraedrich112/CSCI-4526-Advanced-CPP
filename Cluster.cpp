//Cluster.cpp
//Tim Fraedrich & Chidi Nna
#include "Cluster.hpp"
#include "Square.hpp"

Cluster::Cluster(ClusterT cl, Square* inputSquares[]) : type(cl) {
    typeName = clusterTypeNames[static_cast<int>(type)];
    for (int i = 0; i < 9; ++i) {
        squares[i] = inputSquares[i];  // Initialize squares
    }
}

void Cluster::Shoop(char val) {
    // Convert the char to an integer (ASCII conversion)
    int intVal = val - '0';

    // For each Square in the cluster, remove the possibility corresponding to the value
    for (int i = 0; i < 9; ++i) {
        if (squares[i]) {  // Check if the Square pointer is not null
            // Access the State of the square to eliminate the possibility
            State& state = squares[i]->getState();  //additional function: needs the get the State to work
            //state.setNumbers(state.getNumbers() & ~(1 << intVal)); //additional function: needs the setNumber to work
            state.UpdateNumbers(intVal);
        }
    }
}

std::ostream& Cluster::Print(std::ostream& out) {
    out << "Cluster type: " << typeName << endl;
    for (int i = 0; i < 9; ++i) {
        out << *squares[i] << endl;  // Assuming << operator is defined for Square
    }
    return out;
}
