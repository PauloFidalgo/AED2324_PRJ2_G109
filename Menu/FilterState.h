//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_FILTERSTATE_H
#define AED2324_PRJ2_G109_FILTERSTATE_H
#include "State.h"
class FilterState: public State {
private:
    Airport* fromAirport;
    Airport* toAirport;
    vector<Airport*> fromAirports;
    vector<Airport*> toAirports;
    vector<Airline*> airlines;
public:
    // Constructor
    FilterState();

    // Setters
    void setFrom( Airport* fromAirport);
    void setTo( Airport* toAirport);
    void setFrom( vector<Airport*> fromAirports);
    void setTo( vector<Airport*> toAirports);

    void displayMenu() override;
    State * handleInput() override;

    const vector<Airport *> &getToAirports() const;

    void setToAirports(const vector<Airport *> &toAirports);

    Airline *getInputAirlines();

    void includeAirlines();

    void excludeAirlines();
};


#endif //AED2324_PRJ2_G109_FILTERSTATE_H
