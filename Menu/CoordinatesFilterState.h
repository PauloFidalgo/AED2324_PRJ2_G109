//
// Created by Wagner Pedrosa on 25/12/2023.
//

#ifndef AED2324_PRJ2_G109_COORDINATESFILTERSTATE_H
#define AED2324_PRJ2_G109_COORDINATESFILTERSTATE_H

#include "State.h"

class CoordinatesFilterState : public State{
private:
    double x;
    double y;
public:
    // Constructor
    CoordinatesFilterState();

    // Setters
    void setX(const double& x);
    void setY(const double& y);

    void displayMenu() override;
    State * handleInput() override;

    double getX() const;

    double getY() const;

};


#endif //AED2324_PRJ2_G109_COORDINATESFILTERSTATE_H
