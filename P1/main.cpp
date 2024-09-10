//Project 1.cpp
//Tim Fraedrich & Chidi Nna
#include "tools.hpp"
#include "State.hpp"

int main(int argc, char* argv[]) {
    banner();

    State s1('1');
    State s2('-');
    cout << s1 << endl << s2 << endl;
    s2.Mark('9');
    cout << s2 << endl;

    bye();
    return 0;
}