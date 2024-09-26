// Project2.cpp
// Tim Fraedrich & Chidi Nna
#include "tools.hpp"
#include "State.hpp"
#include "Game.hpp"

// test State class
void testState() {
    // Test 1: State with a fixed value
    State s1('1');
    cout << "Test 1: State with fixed value '1'" << endl;
    cout << s1 << endl;

    // Test 2: State with all possibilities ('-')
    State s2('-');
    cout << "Test 2: State with all possibilities '-'" << endl;
    cout << s2 << endl;

    // Test 3: Marking a value on a non-fixed square
    cout << "Test 3: Marking value '9' on non-fixed square" << endl;
    s2.Mark('9');
    cout << s2 << endl;

    // Test 4: Try marking a value on a fixed square
    cout << "Test 4: Attempt to mark value on a fixed square (should show error)" << endl;
    s1.Mark('3');
    cout << s1 << endl;
}

// test Square class
void testSquare() {
    // Test 1: Square with fixed state value '1'
    Square sq1('1', 1, 1);
    cout << "Test 1: Square (1, 1) with fixed state value '1'" << endl;
    cout << sq1 << endl;

    // Test 2: Square with all possibilities ('-')
    Square sq2('-', 2, 2);
    cout << "Test 2: Square (2, 2) with all possibilities '-'" << endl;
    cout << sq2 << endl;

    // Test 3: Marking a value on a non-fixed square
    cout << "Test 3: Marking value '9' on non-fixed square (2, 2)" << endl;
    sq2.Mark('9');
    cout << sq2 << endl;

    // Test 4: Try marking a value on a fixed square
    cout << "Test 4: Attempt to mark value on a fixed square (1, 1) (should show error)" << endl;
    sq1.Mark('3');
    cout << sq1 << endl;
}

int main(int argc, char* argv[]) {
    banner();  // Print the banner

    // Open and check file from command line
    if (argc != 2) fatal(string("Usage: ") + argv[0] + " filename.txt");
    ifstream input(argv[1]);  // argv[0] is the name of the program.
    if (!input.is_open()) fatal(string("Cannot open text file ") + argv[1]);

    Game game(input);
    game.Run();

    //Call the unit tests
    //testState();
    //testSquare();

    input.close();
    bye();  // Print exit
    return 0;
}
