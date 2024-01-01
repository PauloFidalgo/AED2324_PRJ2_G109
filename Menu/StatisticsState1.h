//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE1_H
#define AED2324_PRJ2_G109_STATISTICSSTATE1_H

#include "State.h"
#include "StatisticsState2.h"

class StatisticsState1: public State {
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu() override;
    State * handleInput() override;
    State* returnToMenu();

};


#endif //AED2324_PRJ2_G109_STATISTICSSTATE1_H
