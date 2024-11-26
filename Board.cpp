//Board.cpp
//Tim Fraedrich & Chidi Nna
#include "Board.hpp"

// Step 2: Declare a static array of three const strings
static const string clusterTypeStrings[3] = {"Box", "Row", "Column"};

Board::Board(ifstream& inputFile, char type,  int clusterCount) : in(inputFile) {
    cout << "Board constructor started" << endl;

    // Check for valid game type
    if (tolower(type) == 't' || tolower(type) == 'd') {
        n = 9;
    } else if (tolower(type) == 's') {
        n = 6;
    } else {
        fatal("Stream Error: Invalid game type: " + string(1, type));
    }

    bd = new Square[n * n];
    unmarked = n * n;
    GetPuzzle();

    // Create clusters
    makeClusters();

    // Shoop all fixed values
    for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
            if (Sub(j, k).getState().isFixed()) {
                Sub(j, k).Shoop(Sub(j, k).getState().getValue());
            }
        }
    }

    cout << "Board constructor finished" << endl;
}

Board::~Board() {
    cout << "Deleting board" << endl;
    delete[] bd;

    // Clean up clusters
    for (Cluster* cluster : clusters) {
        delete cluster;
    }
}

void Board::makeClusters() {
    for (short j = 0; j < 9; ++j) {
        createRow(j);
    }
    for (short j = 0; j < 9; ++j) {
        createColumn(j);
    }
    for (short j = 0; j < 3; ++j) {
        for (short k = 0; k < 3; ++k) {
            createBox(j, k);
        }
    }
}

// Function to create a row cluster
void Board::createRow(short j) {
    Square* rowSquares[9];
    for (int n = 0; n < 9; ++n) {
        rowSquares[n] = &Sub(j + 1, n + 1);
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Row, rowSquares);
    clusters.push_back(clusterCreated);
    for (int n = 0; n < 9; ++n) {
        Sub(j + 1, n + 1).addCluster(clusterCreated);
    }
}

// Function to create a column cluster
void Board::createColumn(short k) {
    Square* colSquares[9];
    for (int n = 0; n < 9; ++n) {
        colSquares[n] = &Sub(n + 1, k + 1);
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Column, colSquares);
    clusters.push_back(clusterCreated);
    for (int n = 0; n < 9; ++n) {
        Sub(n + 1, k + 1).addCluster(clusterCreated);
    }
}

// Function to create a box cluster
void Board::createBox(short j, short k) {
    Square* boxSquares[9];
    int index = 0;
    for (short n = 0; n < 3; ++n) {
        for (short l = 0; l < 3; ++l) {
            boxSquares[index++] = &Sub(j * 3 + n + 1, k * 3 + l + 1);
        }
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Box, boxSquares);
    clusters.push_back(clusterCreated);
    for (short n = 0; n < 3; ++n) {
        for (short l = 0; l < 3; ++l) {
            Sub(j * 3 + n + 1, k * 3 + l + 1).addCluster(clusterCreated);
        }
    }
}

ostream& Board::Print(ostream& out) {
    out << "Printing board:" << endl;
    for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
            out << Sub(j, k) << endl;
        }
        out << endl;
    }

    out << "Printing clusters:" << endl;
    for (Cluster* cluster : clusters) {
        out << *cluster << endl;
    }

    out << "Finished printing board" << endl;
    return out;
}

void Board::GetPuzzle() {
    char input;
    for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
            if (!(in >> input)) {
                fatal("Stream Error: Unexpected end of file while reading puzzle.");
            }
            cout << n * (j - 1) + (k - 1) << ": " << input << ", ";
            if ((input == '-') || (input > '0' && input <= '9')) {
                Sub(j, k) = Square(input, j, k);
            } else {
                fatal("Stream Error: Invalid character for square value: " + string(1, input));
            }
        }
        if (!(in.get(input)) || input != '\n') {
            fatal("Stream Error: Expected end of line after row " + to_string(j));
        }
    }
    if (in >> input) {
        fatal("Stream Error: Expected end of file but found additional data.");
    }
}

Square& Board::Sub(int row, int column) {
    return bd[n * (row - 1) + (column - 1)];
}

DiagBoard::DiagBoard(ifstream& in, char type, int clusterCount): Board(in, type, clusterCount) {
    cout << "DiagBoard constructor started" << endl;
    //add diagonal clusters
    createDiagonals();

    //shoop all squares
    for (int j = 1; j <= 9; ++j) {
        for (int k = 1; k <= 9; ++k) {
            if (Sub(j,k).getState().isFixed()) {
                Sub(j, k).Shoop(Sub(j,k).getState().getValue());
            }
        }
    }
    cout << "DiagBoard constructor finished" << endl;
}

void DiagBoard::createDiagonals() {
    //first diagonal (top left to bottom right)
    Square* diagSquares[9]; // Local array for squares
    for (int n = 0; n < 9; ++n) {
        diagSquares[n] = &Sub(n + 1, n + 1); // Fill with pointers to squares in the diagonal
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Diagonal, diagSquares);
    clusters.push_back(clusterCreated);
    for (int n = 0; n < 9; ++n) {
        Sub(n + 1, n + 1).addCluster(clusterCreated);
    }

    //second diagonal (top right to bottom left)
    int m = 9;
    for (int n = 0; n < 9; ++n) {
        diagSquares[n] = &Sub(n + 1, m); // Fill with pointers to squares in the diagonal
        m--;
    }
    clusterCreated = new Cluster(ClusterT::Diagonal, diagSquares);
    clusters.push_back(clusterCreated);
    m = 9;
    for (int n = 0; n < 9; ++n) {
        Sub(n + 1, m).addCluster(clusterCreated);
        m--;
    }
}

DiagBoard::~DiagBoard() {
    cout << "Deleting diag board" << endl;
}
