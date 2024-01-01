//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE2_H
#define AED2324_PRJ2_G109_STATISTICSSTATE2_H
#include "State.h"
#include "StatisticsState3.h"

class StatisticsState2: public State {
private:
    string userInputStr;
    int userInput;
public:
    void displayMenu() override;
    State * handleInput() override;

};

extern StatisticsState2 statisticsState2;
#endif //AED2324_PRJ2_G109_STATISTICSSTATE2_H
