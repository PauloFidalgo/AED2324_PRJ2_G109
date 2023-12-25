//
// Created by Wagner Pedrosa on 25/12/2023.
//

#ifndef AED2324_PRJ2_G109_COORDINATESFILTERSTATE_H
#define AED2324_PRJ2_G109_COORDINATESFILTERSTATE_H

#include "State.h"

class CoordinatesFilterState : public State{
private:
    int x;
    int y;
public:
    // Constructor
    CoordinatesFilterState();

    // Setters
    void setX(const int& x);
    void setY(const int& y);

    void displayMenu() override;
    State * handleInput() override;

    int getX() const;

    int getY() const;

};


#endif //AED2324_PRJ2_G109_COORDINATESFILTERSTATE_H
