// Project1.cpp
// Tim Fraedrich & Chidi Nna
#include "tools.hpp"
#include "State.hpp"

// Unit test function to test State class
void unitTest() {
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

    // Test 5: Change possibilities for testing (0x23e)
    State s3('-');
    s3.setPossibilities(0x23e);  // Custom possibility list
    cout << "Test 5: State with custom possibilities (0x23e)" << endl;
    cout << s3 << endl;

    // Test 6: Change possibilities for testing (0x0f2)
    State s4('-');
    s4.setPossibilities(0x0f2);  // Custom possibility list
    cout << "Test 6: State with custom possibilities (0x0f2)" << endl;
    cout << s4 << endl;
}

int main(int argc, char* argv[]) {
    banner();  // Print the banner

    unitTest();  // Call the unit test

    bye();  // Print the exit message from tools
    return 0; //
}

