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
    void displayMenu() override;
    State * handleInput() override;
};

extern StatisticsState7 statisticsState7;

#endif //AED2324_PRJ2_G109_STATISCTICSSTATE7_H
