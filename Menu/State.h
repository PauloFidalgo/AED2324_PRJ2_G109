//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATE_H
#define AED2324_PRJ2_G109_STATE_H
#include "stack"
#include "../Managers/Manager.h"

class State {
protected:
    static std:: stack<State*> stateHistory;
    Manager manager;

public:
    State();
    virtual void displayMenu() = 0;
    virtual State* handleInput() = 0;
    virtual ~State();
};


#endif //AED2324_PRJ2_G109_STATE_H
