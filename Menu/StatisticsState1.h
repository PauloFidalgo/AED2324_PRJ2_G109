//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE1_H
#define AED2324_PRJ2_G109_STATISTICSSTATE1_H

#include "State.h"

class StatisticsState1: public State {
private:
    string code;
    int distance;
    Airport* airport;
    Airline* airline;
    string userInputStr;
    int userInput;


public:
    void displayMenu() override;
    State * handleInput() override;

};

extern StatisticsState1 statisticsState1;
#endif //AED2324_PRJ2_G109_STATISTICSSTATE1_H
