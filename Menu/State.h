//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATE_H
#define AED2324_PRJ2_G109_STATE_H
#include "stack"
#include "../Managers/Manager.h"

class State {
protected:
    static std:: stack<State*> stateHistory;
    static std:: stack<State*> statisticsHistory;
    Manager manager;
    string code;
    int distance;
    string userInputStr;
    int userInput;
    string name;

public:
    State();
    virtual void displayMenu() = 0;
    virtual State* handleInput() = 0;
    virtual ~State();
    Airport* getValidAirport();
    Airline* getValidAirline();
    string* getValidCity();
    string* getValidCountry();
    int* getValidAirportK();
    Airport* getValidAirportPerCoordinates();

    vector<Airport *> getValidAirportsPerCity();

    vector<Airport *> getValidAirportsPerCountry();

    vector<Airport *> getAirportsRange(int x);
};


#endif //AED2324_PRJ2_G109_STATE_H
