//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE4_H
#define AED2324_PRJ2_G109_STATISTICSSTATE4_H
#include "State.h"
#include "StatisticsState5.h"

class StatisticsState4 : public State {
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu();
    State * handleInput();
};


#endif //AED2324_PRJ2_G109_STATISTICSSTATE4_H
