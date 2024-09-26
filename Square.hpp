//State.hpp
//State and Square Class
//Tim Fraedrich & Chidi Nna
#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "tools.hpp"

class State {
private:                 // All members private for encapsulation
	short numbers;
	char value;
	bool fixed;
public:
	State() = default;  // A default null constructor.
	State(char input); // A constructor with a char parameter
	~State() = default;  // A default destructor.
	void Mark(char ch); // mark(char ch)
	ostream& Print(ostream& out);

    short getNumbers() { return numbers; }
	char getValue() { return value; }

};

//method for print( ostream&) that prints all data in the State in a readable format
inline ostream& operator << (ostream& out, State& s) { return s.Print(out); }

class Square {
private:
	State s;
	short row, column;
public:
	Square() = default;  // A default null constructor.
	Square(char value, short row, short column); // A constructor with three parameters
	~Square(); // A destructor.
	void Mark(char ch); // A public function that calls State’s mark function
	ostream& Print(ostream& out);
};

//method for print( ostream&) that prints all data in the Square and State class
inline ostream& operator << (ostream& out, Square& s) { return s.Print(out); }

#endif