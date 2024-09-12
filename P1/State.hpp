//State.hpp
//Tim Fraedrich & Chidi Nna
#include "tools.hpp"

class State {   //Define a class State
private:                 //All members private for encapsulation
	short possibilities;
	char value;
	bool fixed;
public:
	State() = default;  //A default null constructor.
	State(char input); // A constructor with a char parameter
	~State() = default;  //A default destructor.
	void Mark(char ch); // mark(char ch)
	ostream& Print(ostream& out);

    void setPossibilities(short newPossibilities) {  //Public Setter for test cases
        possibilities = newPossibilities;
    }

    // Public getter for possibilities for test cases
    short getPossibilities() const {
        return possibilities;
    }

};

//method for print( ostream&) that prints all data in the State in a readable format
inline ostream& operator << (ostream& out, State& s) {  //
	return s.Print(out);
}
