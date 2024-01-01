//
// Created by Wagner Pedrosa on 29/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISCTICSSTATE7_H
#define AED2324_PRJ2_G109_STATISCTICSSTATE7_H
#include "State.h"
#include "StatisticsState8.h"

class StatisticsState7: public State {
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu();
    State * handleInput();
};


#endif //AED2324_PRJ2_G109_STATISCTICSSTATE7_H
