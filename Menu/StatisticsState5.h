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
    void displayMenu();
    State * handleInput();
};


#endif //AED2324_PRJ2_G109_STATISTICSSTATE5_H
