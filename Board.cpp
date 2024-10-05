//Board.cpp
//Board Class
//Tim Fraedrich & Chidi Nna

#include "Board.hpp"

Board::Board(ifstream& inputFile, char type) : in(inputFile) {
    cout << "Board constructor started" << endl;
    if (tolower(type) == 't' || tolower(type) == 'd') n = 9;
    else if (tolower(type == 's')) n = 6;
    else fatal(string("Invalid type: ") += type);

    bd = new Square[n * n];
    unmarked = n * n;
    GetPuzzle();
    cout << "Board constructor finished" << endl;
}

Board::~Board() {
    cout << "Deleting board" << endl; //cerr
    delete[] bd;
}

void Board::GetPuzzle() {
    char input;
    for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
            in >> input;
            cout << n * (j - 1) + (k - 1) << ": " << input << ", ";
            if ((input == '-') || (input > '0' && input <= '9'))
                Sub(j, k) = Square(input, j, k);
            else fatal(string("Invalid number inside square") += input);
        }
        in.get(input);
        if (input == '\n') cout << "new line success" << endl; //for testing can be removed later
        else fatal("did not find new line");
    }
    in >> input;
    if (in.eof()) cout << "end of file success" << endl; //for testing can be removed later
    else fatal("did not find eof");
}

Square& Board::Sub(int row, int column) {
    return bd[n * (row - 1) + (column - 1)];
}

ostream& Board::Print(ostream& out) {
    out << "Printing board:" << endl;
    for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
            out << Sub(j,k) << endl;
        }
        out << endl;
    }
    out << "Finished printing board" << endl;
    return out;
}