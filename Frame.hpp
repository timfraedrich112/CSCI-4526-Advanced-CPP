//Frame.hpp
//Tim Fraedrich & Chidi Nna
#ifndef FRAME_HPP
#define FRAME_HPP
#include "tools.hpp"
#include "Square.hpp"

class Frame {
public:
    vector<State> states;
    Frame() = default;
    ~Frame() = default;
    void addState(const State s) { states.push_back(s); }
};

class Stack: std::vector<Frame*> {
public:
    Stack() = default;
    ~Stack() { zap(); }
    void push(Frame* snapshot) { this->push_back(snapshot); }
    void pop() { this->pop_back(); }
    Frame* top() const { return empty() ? nullptr : this->back(); }
    int size() const { return std::vector<Frame*>::size(); }
    void zap() { while(!empty()) pop(); }
};

#endif //FRAME_HPP
