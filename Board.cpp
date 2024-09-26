//Board.cpp
//Board Class
//Tim Fraedrich & Chidi Nna

#include "Board.hpp"

Board::Board(ifstream& inputFile, char type) : in(inputFile) {
    if (tolower(type) == 't' || tolower(type) == 'd') n = 9;
    else if (tolower(type == 's')) n = 6;
    else fatal(string("Invalid type: ") += type);

    bd = new Square[n * n];
    unmarked = n * n;
    GetPuzzle();
    cout << "Constructor Finished!" << endl;
}

Board::~Board() {
    delete[] bd;
    cerr << "Deleting board" << endl;
}

void Board::GetPuzzle() {
    char num;
    for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
            cout << n * (j - 1) + (k - 1) << ": ";
            in >> num;
            cout << num;
            if ((num == '-') || (num > '0' && num <= '9'))
                Subscript(j, k) = Square(num, j, k);
            else fatal(string("Invalid number inside square") += num);
        }
        //in >> num;
        //if (num == '\n') cout << "new line success" << endl; //for testing can be removed later
        //else fatal("did not find new line");
    }
    //in >> num;
    //if (in.eof()) cout << "end of file success" << endl; //for testing can be removed later
    //else fatal("did not find eof");
}

Square& Board::Subscript(int row, int column) {
    return bd[n * (row - 1) + (column - 1)];
}

ostream& Board::Print(ostream& out) {
    out << "PRINTING" << endl;
    for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
            Subscript(j, k).Print(out);
        }
        out << endl;
    }
    return out;
}