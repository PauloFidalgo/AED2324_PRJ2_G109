#include "State.h"

std::stack<State*> State::stateHistory;


State::~State() {
    while (!stateHistory.empty()){
        delete stateHistory.top();
        stateHistory.pop();
    }
}