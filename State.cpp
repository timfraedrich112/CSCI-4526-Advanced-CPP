//State.cpp
//State and Square Class
//Tim Fraedrich & Chidi Nna.
#include "State.hpp"

State::State(char input)
	: value(input) {
	if (value == '-') {
		numbers = 0x3fe;
		fixed = false;
	} else if (value > '0' && value <= '9') {
		numbers = 0;
		fixed = true;
	} else {
       cerr << "Error: Invalid input character '" << input << "' for State." << endl;
   }
}

void State::Mark(char ch) {
    if (fixed) {
        cerr << "Error: Cannot mark fixed square." << endl;
        return;  // Prevent marking the value
    }
    value = ch;
    numbers = 0;  // Reset possibilities after marking
}

ostream& State::Print(ostream& out) {
	out << "Value: " << value << '\t';
	out << "Fixed: " << boolalpha << fixed << '\t';
	out << "numbers: ";
	short num = numbers;
	for (int n = 1; n <= 9; n++) {
		num >>= 1;
		if (num & 1) out << n;
		else out << '-';
	}
	out << endl;
	return out;
}

Square::Square(char value, short inputRow, short inputColumn)
	: s(value), row(inputRow), column(inputColumn) {
	cout << "Square (" << row << ", " << column << ") created" << endl;
}

Square::~Square() {
	cout << "Deleting Square (" << row << ", " << column << ")" << endl;
}

void Square::Mark(char ch) {
	s.Mark(ch);
}

ostream& Square::Print(ostream& out) {
	out << "Square: (" << row << ", " << column << ") " << s << '\t';
	return out;
}

