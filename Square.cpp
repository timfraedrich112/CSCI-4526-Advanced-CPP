//Square.cpp
//Tim Fraedrich & Chidi Nna
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
        std::cout << "Error: Invalid input character '" << input << "' for State." << std::endl;
    }
}

void State::Mark(char ch) {
    if (fixed) {
        cout << "Error: Cannot mark fixed square." << endl;
        return;  // Prevent marking the value
    }
    value = ch;
}

void State::UpdateNumbers(int val) {
    numbers &= ~(1 << val);
}

std::ostream& State::Print(std::ostream& out) {
    out << "Value: " << value << "    ";
    out << "Possibilities: ";
    short num = numbers;
    for (int k = 1; k <= 9; ++k) {
        num >>= 1;
        if (num & 1) out << k;
        else out << '-';
    }
    out << "\tFixed:  " << boolalpha << fixed;
    return out;
}

Square::Square(char value, short inputRow, short inputColumn)
    : s(value), row(inputRow), column(inputColumn) {
    std::cout << "Square (" << row << ", " << column << ") created" << std::endl;
}

Square::~Square() {
    std::cout << "Deleting Square (" << row << ", " << column << ")" << std::endl;
}

void Square::Mark(char ch) {
    s.Mark(ch);
    Shoop(ch);
}

void Square::Shoop(char val) {
    for (Cluster* cluster : clusters) {
        cluster->Shoop(val);  // Call Shoop function for each Cluster the square belongs to
    }
}

std::ostream& Square::Print(std::ostream& out) {
    out << "(" << row << ", " << column << ") \t" << s << '\t';
    return out;
}