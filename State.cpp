//State.cpp
//Tim Fraedrich & Chidi Nna.
#include "State.hpp"

State::State(char input) {
	value = input;
	if (value == '-') {
		possibilities = 0x3fe;
		fixed = false;
	} else if (value > '0' && value <= '9') {
		possibilities = 0;
		fixed = true;
	}
}

void State::Mark(char ch) {
	if (fixed) { cout << "Square is fixed" << endl; return; }
	value = ch;
}

ostream& State::Print(ostream& out) {
	out << "Value: " << value << endl;
	out << "Fixed: " << boolalpha << fixed << endl;
	out << "Possibilities: ";
	short num = possibilities;
	for (int n = 1; n <= 9; ++n) {
		num = num >> 1;
		if (num % 2) out << n;
		else out << '-';
	}
	out << endl;
	return out;
}
