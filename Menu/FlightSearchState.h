//
// Created by Paulo Fidalgo on 24/12/2023.
//

#ifndef AED2324_PRJ2_G109_FLIGHTSEARCHSTATE_H
#define AED2324_PRJ2_G109_FLIGHTSEARCHSTATE_H


#include "State.h"

class FlightSearchState : public State{
private:
    bool isSelectingFrom;
    Airport* fromCode;
    Airport* toCode;
    vector<Airport*> fromAirports;
    vector<Airport*> toAirports;

    void validateToAirports();
public:
    FlightSearchState();

    void displayMenu();
    State* handleInput();

};


#endif //AED2324_PRJ2_G109_FLIGHTSEARCHSTATE_H
