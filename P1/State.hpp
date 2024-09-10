//State.hpp 
//Tim Fraedrich & Chidi Nna
#include "tools.hpp"

class State {
private:
	short possibilities;
	char value;
	bool fixed;
public:
	State() = default;
	State(char input);
	~State() = default;
	void Mark(char ch);
	ostream& Print(ostream& out);
};

inline ostream& operator << (ostream& out, State& s) {
	return s.Print(out);
}