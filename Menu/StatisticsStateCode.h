//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATECODE_H
#define AED2324_PRJ2_G109_STATISTICSSTATECODE_H

#include "State.h"

class StatisticsStateCode: public State {
private:
    string code;

public:
    void displayMenu() override;
    State * handleInput() override;
};


#endif //AED2324_PRJ2_G109_STATISTICSSTATECODE_H
