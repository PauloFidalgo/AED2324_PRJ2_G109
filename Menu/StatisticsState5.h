//
// Created by Wagner Pedrosa on 28/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE5_H
#define AED2324_PRJ2_G109_STATISTICSSTATE5_H
#include "State.h"
#include "StatisticsState6.h"

class StatisticsState5 : public State {
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu() override;
    State * handleInput() override;
};

extern StatisticsState5 statisticsState5;

#endif //AED2324_PRJ2_G109_STATISTICSSTATE5_H
