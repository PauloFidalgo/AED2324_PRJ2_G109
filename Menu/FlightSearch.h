//
// Created by Paulo Fidalgo on 24/12/2023.
//

#ifndef AED2324_PRJ2_G109_FLIGHTSEARCH_H
#define AED2324_PRJ2_G109_FLIGHTSEARCH_H


#include "State.h"

class FlightSearch : public State{
private:
    bool isSelectingFrom;
    string from;
    string to;
    double x;
    double y;

public:
    FlightSearch();

    void displayMenu() override;
    State* handleInput() override;

    const std::string& getFrom() const;
    const std::string& getTo() const;
    const int& getX() const;
    const int& getY() const;

};


#endif //AED2324_PRJ2_G109_FLIGHTSEARCH_H
