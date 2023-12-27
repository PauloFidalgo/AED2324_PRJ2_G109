//
// Created by Paulo Fidalgo on 24/12/2023.
//

#ifndef AED2324_PRJ2_G109_FLIGHTSEARCHSTATE_H
#define AED2324_PRJ2_G109_FLIGHTSEARCHSTATE_H


#include "State.h"

class FlightSearchState : public State{
private:
    bool isSelectingFrom;
    string from;
    string to;
    double x;
    double y;
    Airport* fromCode;
    Airport* toCode;
    vector<Airport*> fromAirports;
    vector<Airport*> toAirports;

public:
    FlightSearchState();

    void displayMenu() override;
    State* handleInput() override;

};


#endif //AED2324_PRJ2_G109_FLIGHTSEARCHSTATE_H
