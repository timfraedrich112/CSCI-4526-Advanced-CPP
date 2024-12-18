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
        throw std::invalid_argument("Invalid input character for State.");
    }
}

void State::Mark(char ch) {
    try {
        if (fixed) {
            throw std::logic_error("Cannot mark fixed square.");
        }
        value = ch;
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
        throw;
    }
}

void State::UpdateNumbers(int val) {
    numbers &= ~(1 << val);
}

ostream& State::Print(ostream& out) const {
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
    try {
        s.Mark(ch);
        Shoop(ch);
    } catch (const std::exception& e) {
        std::cout << "Error while marking square: " << e.what() << std::endl;
        throw;
    }
}

void Square::Shoop(char val) {
    for (Cluster* cluster : clusters) {
        cluster->Shoop(val);
    }
}

string Square::getPossibilities() {
    string output = "";
    short num = getState().getNumbers();
    for (int k = 1; k <= 9; ++k) {
        num >>= 1;
        if (num & 1) output += to_string(k);
        else output += '-';
    }
    return output;
}

std::ostream& Square::Print(std::ostream& out) {
    out << "(" << row << ", " << column << ") \t" << s << '\t';
    return out;
}



