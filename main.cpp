// Project 5
// Tim Fraedrich & Chidi Nna
#include "tools.hpp"
#include "Square.hpp"
#include "Game.hpp"

// test State class
void TestState() {
    cout << "\nTESTING STATE:" << endl << endl;
    // Test 1: State with a fixed value
    State s1('1');
    cout << "Test 1: State with fixed value '1'" << endl;
    cout << s1 << endl << endl;

    // Test 2: State with all possibilities ('-')
    State s2('-');
    cout << "Test 2: State with all possibilities '-'" << endl;
    cout << s2 << endl << endl;

    // Test 3: Marking a value on a non-fixed square
    cout << "Test 3: Marking value '9' on non-fixed square" << endl;
    s2.Mark('9');
    cout << s2 << endl << endl;

    // Test 4: Try marking a value on a fixed square
    cout << "Test 4: Attempt to mark value on a fixed square (should show error)" << endl;
    s1.Mark('3');
    cout << s1 << endl << endl;
}

// test Square class
void TestSquare(ofstream& outputFile) {
    cout << "\nTESTING SQUARE:" << endl << endl;
    outputFile << "\nTESTING SQUARE:" << endl << endl;

    // Test 1: Square with fixed state value '1'
    Square sq1('1', 1, 1);
    cout << "Test 1: Square (1, 1) with fixed state value '1'" << endl;
    outputFile << "Test 1: Square (1, 1) with fixed state value '1'" << endl;
    cout << sq1 << endl << endl;
    outputFile << sq1 << endl << endl;

    // Test 2: Square with all possibilities ('-')
    Square sq2('-', 2, 2);
    cout << "Test 2: Square (2, 2) with all possibilities '-'" << endl;
    outputFile << "Test 2: Square (2, 2) with all possibilities '-'" << endl;
    cout << sq2 << endl << endl;
    outputFile << sq2 << endl << endl;

    // Test 3: Marking a value on a non-fixed square
    cout << "Test 3: Marking value '9' on non-fixed square (2, 2)" << endl;
    outputFile << "Test 3: Marking value '9' on non-fixed square (2, 2)" << endl;
    sq2.Mark('9');
    cout << sq2 << endl << endl;
    outputFile << sq2 << endl << endl;

    // Test 4: Try marking a value on a fixed square
    cout << "Test 4: Attempt to mark value on a fixed square (1, 1) (should show error)" << endl;
    outputFile << "Test 4: Attempt to mark value on a fixed square (1, 1) (should show error)" << endl;
    sq1.Mark('3');
    cout << sq1 << endl << endl;
    outputFile << sq1 << endl << endl;
}

// test Board class
void TestBoard(ifstream& input, ofstream& outputFile) {
    cout << "\nTESTING BOARD:" << endl << endl;
    outputFile << "\nTESTING BOARD:" << endl << endl;

    // Use the first character from the input file to determine the type of board
    char type;
    input >> type;  // Read the type from the file

    // Create a Board object with the type and input file
    Board board(input, type);

    // Print the board to both console and output file
    cout << board << endl;  // Uses the overloaded operator<< for Board
    outputFile << board << endl;  // Print the board to the file
}

// test Cluster class
void TestCluster(ofstream& outputFile) {
    cout << "\nTESTING CLUSTER:" << endl << endl;
    outputFile << "\nTESTING CLUSTER:" << endl << endl;

    // Create squares for row
    Square* squaresRow[9];
    for (int k = 0; k < 9; ++k) {
        squaresRow[k] = new Square('-', 1, k + 1);  // All possibilities
    }
    Cluster rowCluster(ClusterT::Row, squaresRow);

    // Test the Shoop function
    cout << "Initial Row Cluster: " << endl << rowCluster << endl;
    outputFile << "Initial Row Cluster: " << endl << rowCluster << endl;

    rowCluster.Shoop('5');  // Mark value '5'
    cout << "Row Cluster after Shoop(5):" << endl << rowCluster << endl;
    outputFile << "Row Cluster after Shoop(5):" << endl << rowCluster << endl;

    rowCluster.Shoop('9');  // Mark value '5'
    cout << "Same Row Cluster after Shoop(9):" << endl << rowCluster << endl;
    outputFile << "Same Row Cluster after Shoop(9):" << endl << rowCluster << endl;

    // Cleanup
    for (int k = 0; k < 9; ++k) {
        delete squaresRow[k];
    }
}

void TestUpdatedClasses(ifstream& input, ofstream& outputFile) {
    // Running the existing tests
    TestSquare(outputFile);
    TestBoard(input, outputFile);

    // New tests for Cluster
    TestCluster(outputFile);
}

int main(int argc, char* argv[]) {
    banner();  // Print the banner

    // Open and check file from command line
    if (argc != 2) fatal(string("Usage: ") + argv[0] + " filename.txt");
    ifstream input(argv[1]);  // argv[0] is the name of the program.
    if (!input.is_open()) fatal(string("Cannot open text file ") + argv[1]);

    // Open output file for writing results of TestBoard and TestSquare
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) fatal("Cannot open output file for writing results");

    // Call the updated test function
    TestUpdatedClasses(input, outputFile);

    input.close();
    outputFile.close();

    bye();  // Print exit
    return 0;
}