//
// Created by Wagner Pedrosa on 30/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE8_H
#define AED2324_PRJ2_G109_STATISTICSSTATE8_H
#include "State.h"

class StatisticsState8 : public State {
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu() override;
    State * handleInput() override;
};

extern StatisticsState8 statisticsState8;


#endif //AED2324_PRJ2_G109_STATISTICSSTATE8_H
