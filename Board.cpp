//Board.cpp
#include "Board.hpp"

Board::Board(ifstream& inputFile, char type, int clusterCount)
    : in(inputFile), n(0), bd(nullptr), unmarked(0) {
    cout << "Board constructor started" << endl;

    if (tolower(type) == 't' || tolower(type) == 'd') {
        n = 9; // Traditional board size
    } else if (tolower(type) == 's') {
        n = 6; // Sixy board size
    } else {
        fatal("Stream Error: Invalid game type: " + string(1, type));
    }

    bd = new Square[n * n];
    unmarked = n * n;
    GetPuzzle();

    makeClusters(); // Calls derived class's implementation
    for (int j = 1; j <= n; ++j) {
        if (tolower(type) == 's') {
            Sub(j, 1).Shoop('7');
            Sub(j, 1).Shoop('8');
            Sub(j, 1).Shoop('9');
        }

        for (int k = 1; k <= n; ++k) {
            if (Sub(j, k).getState().isFixed()) {
                Sub(j, k).Shoop(Sub(j, k).getState().getValue());
            }
        }
    }

    cout << "Board constructor finished" << endl;
}

void Board::makeClusters() {
    for (short j = 0; j < n; ++j) {
        createRow(j);
    }

    for (short j = 0; j < n; ++j) {
        createColumn(j);
    }
    if (n == 9) {
        for (short j = 0; j < 3; ++j) {
            for (short k = 0; k < 3; ++k) {
                createBox(j, k);  // 9x9 traditional board, create boxes
            }
        }
    }

    // Only for SixyBoard (6x6 board) create Vertical and Horizontal Boxes
    if (n == 6) {
        static_cast<SixyBoard*>(this)->createVBoxes();  // Call SixyBoard-specific function
        static_cast<SixyBoard*>(this)->createHBoxes();  // Call SixyBoard-specific function
    }
}

void Board::createRow(short j) {
    Square* rowSquares[n];
    for (int x = 0; x < n; ++x) {
        rowSquares[x] = &Sub(j + 1, x + 1);
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Row, n, rowSquares);
    clusters.push_back(clusterCreated);
    for (int x = 0; x < n; ++x) {
        Sub(j + 1, x + 1).addCluster(clusterCreated);
    }
}

void Board::createColumn(short k) {
    Square* colSquares[n];
    for (int x = 0; x < n; ++x) {
        colSquares[x] = &Sub(x + 1, k + 1);
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Column, n, colSquares);
    clusters.push_back(clusterCreated);
    for (int x = 0; x < n; ++x) {
        Sub(x + 1, k + 1).addCluster(clusterCreated);
    }
}

void Board::createBox(short j, short k) {
    Square* boxSquares[9];
    int index = 0;
    for (short n = 0; n < 3; ++n) {
        for (short l = 0; l < 3; ++l) {
            boxSquares[index++] = &Sub(j * 3 + n + 1, k * 3 + l + 1);
        }
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Box, n, boxSquares);
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


char Board::getMarkChar(int row, int col) const {
    //return 'X';
    return Sub(row, col).getState().getValue();
}

string Board::getPossibilityString(int row, int col) const {
    //return "Possibility String for row " + std::to_string(row) + ", col " + std::to_string(col);
    return Sub(row, col).getPossibilities();
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
        if (!(in.get(input)) || (input != '\n' && input != '\r')) {
            fatal("Stream Error: Expected end of line after row " + to_string(j));
        }
    }
    if (in >> input) {
        fatal("Stream Error: Expected end of file but found additional data.");
    }
}

Square& Board::Sub(int row, int column) const {
    return bd[n * (row - 1) + (column - 1)];
}

void Board::restoreBoard(Frame* f) const {
    for (int j = 0; j < n * n; ++j) {
        bd[j].setState(f->states[j]);
    }
}

DiagBoard::DiagBoard(ifstream& inputFile, char type, int clusterCount): Board(inputFile, type, clusterCount) {
    cout << "DiagBoard constructor started" << endl;
    createDiagonals();
    for (int j = 1; j <= 9; ++j) {
        for (int k = 1; k <= 9; ++k) {
            if (Sub(j, k).getState().isFixed()) {
                Sub(j, k).Shoop(Sub(j, k).getState().getValue());
            }
        }
    }
    cout << "DiagBoard constructor finished" << endl;
}

void DiagBoard::createDiagonals() {
    Square* diagSquares[9];
    for (int n = 0; n < 9; ++n) {
        diagSquares[n] = &Sub(n + 1, n + 1);
    }
    Cluster* clusterCreated = new Cluster(ClusterT::Diagonal, n, diagSquares);
    clusters.push_back(clusterCreated);
    for (int n = 0; n < 9; ++n) {
        Sub(n + 1, n + 1).addCluster(clusterCreated);
    }

    int m = 9;
    for (int n = 0; n < 9; ++n) {
        diagSquares[n] = &Sub(n + 1, m);
        m--;
    }
    clusterCreated = new Cluster(ClusterT::Diagonal, n, diagSquares);
    clusters.push_back(clusterCreated);
    m = 9;
    for (int n = 0; n < 9; ++n) {
        Sub(n + 1, m).addCluster(clusterCreated);
        m--;
    }
}

DiagBoard::~DiagBoard() {
    cout << "Deleting DiagBoard" << endl;
    delete[] bd;
    for (Cluster* cluster : clusters) {
        delete cluster;
    }
}

TradBoard::TradBoard(ifstream& inputFile, char type, int clusterCount): Board(inputFile, type, clusterCount) {
    cout << "TradBoard constructor started" << endl;
    // (Add any other specific logic here if needed)
    cout << "TradBoard constructor finished" << endl;
}

TradBoard::~TradBoard() {
    cout << "Deleting TradBoard" << endl;
    delete[] bd;
    for (Cluster* cluster : clusters) {
        delete cluster;
    }
}

SixyBoard::SixyBoard(ifstream& inputFile, char type, int clusterCount): Board(inputFile, type, clusterCount) {
	cout << "SixyBoard constructor started" << endl;
    //createVBoxes();
    //createHBoxes();
    cout << "SixyBoard constructor finished" << endl;
}

void SixyBoard::createVBoxes() {
    for (int i = 0; i < n; ++i) {
        Square* vbox[n];
        for (int j = 0; j < n; ++j) {
            vbox[j] = &Sub(j + 1, i + 1); // Creating vertical boxes
        }
        Cluster* clusterCreated = new Cluster(ClusterT::VBox, n, vbox);
        clusters.push_back(clusterCreated);
        for (int j = 0; j < n; ++j) {
            Sub(j + 1, i + 1).addCluster(clusterCreated);
        }
    }
}

void SixyBoard::createHBoxes() {
    for (int i = 0; i < n; ++i) {
        Square* hbox[n];
        for (int j = 0; j < n; ++j) {
            hbox[j] = &Sub(i + 1, j + 1); // Creating horizontal boxes
        }
        Cluster* clusterCreated = new Cluster(ClusterT::HBox, n, hbox);
        clusters.push_back(clusterCreated);
        for (int j = 0; j < n; ++j) {
            Sub(i + 1, j + 1).addCluster(clusterCreated);
        }
    }
}

SixyBoard::~SixyBoard() {
    cout << "Deleting SixyBoard" << endl;
    delete[] bd;
    for (Cluster* cluster : clusters) {
        delete cluster;
    }
}

