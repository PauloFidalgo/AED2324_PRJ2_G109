//
// Created by Paulo Fidalgo on 24/12/2023.
//

#ifndef AED2324_PRJ2_G109_FILTERMINIMIZATION_H
#define AED2324_PRJ2_G109_FILTERMINIMIZATION_H


#include "State.h"

class FilterMinimization : public State {
public:
    void displayMenu() override;
    State * handleInput() override;
};


#endif //AED2324_PRJ2_G109_FILTERMINIMIZATION_H
