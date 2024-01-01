//
// Created by Wagner Pedrosa on 28/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE6_H
#define AED2324_PRJ2_G109_STATISTICSSTATE6_H
#include "State.h"
#include "StatisticsState7.h"

class StatisticsState6 : public State {
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu();
    State * handleInput();
};



#endif //AED2324_PRJ2_G109_STATISTICSSTATE6_H
