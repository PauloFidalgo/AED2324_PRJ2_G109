//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE4_H
#define AED2324_PRJ2_G109_STATISTICSSTATE4_H
#include "State.h"

class StatisticsState4 : public State {
private:
    string airport;
    int distance;

public:
    void displayMenu() override;
    State * handleInput() override;
};

extern StatisticsState4 statisticsState4;

#endif //AED2324_PRJ2_G109_STATISTICSSTATE4_H
