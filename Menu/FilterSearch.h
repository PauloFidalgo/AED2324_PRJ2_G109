//
// Created by Paulo Fidalgo on 24/12/2023.
//

#ifndef AED2324_PRJ2_G109_FILTERSEARCH_H
#define AED2324_PRJ2_G109_FILTERSEARCH_H


#include "State.h"

class FilterSearch : public State{
public:
    void displayMenu() override;
    State * handleInput() override;
};


#endif //AED2324_PRJ2_G109_FILTERSEARCH_H
