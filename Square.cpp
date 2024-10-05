//State.cpp
//State and Square Class
//Tim Fraedrich & Chidi Nna.
#include "Square.hpp"

State::State(char input)
	: value(input) {
	if (value == '-') {
		numbers = 0x3fe;
		fixed = false;
	} else if (value > '0' && value <= '9') {
		numbers = 0;
		fixed = true;
	} else {
       cout << "Error: Invalid input character '" << input << "' for State." << endl; //cerr
   }
}

void State::Mark(char ch) {
    if (fixed) {
        cout << "Error: Cannot mark fixed square." << endl; //cerr
        return;  // Prevent marking the value
    }
    value = ch;
    numbers = 0;  // Reset possibilities after marking
}

ostream& State::Print(ostream& out) {
	out << "Value: " << value << "\t\t";
	out << "Fixed:  " << boolalpha << fixed << '\t';
	out << "Possibilities: ";
	short num = numbers;
	for (int k = 1; k <= 9; ++k) {
		num >>= 1;
		if (num & 1) out << k;
		else out << '-';
	}
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
	out << "Square: (" << row << ", " << column << ") \t" << s << '\t';
	return out;
}

