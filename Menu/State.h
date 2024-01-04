//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATE_H
#define AED2324_PRJ2_G109_STATE_H
#include "stack"
#include <sstream>
#include "../Managers/Manager.h"

class State {
protected:
    static std:: stack<State*> stateHistory;
    static std:: stack<State*> statisticsHistory;
    Manager manager;
    string code;
    int distance{};
    string userInputStr;
    int userInput{};
    string name;


public:
    State();
    virtual void displayMenu() = 0;
    virtual State* handleInput() = 0;
    ~State();
    string getValidSingleCity();
    int getValidAirportK();
    Airport* getValidAirportPerCoordinates();
    Airport* getValidSingleAirport();
    map<int,vector<Airport*>> getValidAirportsPerCities();
    string getValidSingleCountry();
    map<int,vector<Airport*>> getValidAirportsPerCountries();
    vector<Airport*> getValidAirportsSingleCountry();
    vector<Airport*> getValidAirportsSingleCity();
    vector<Airport*> getValidAirportsPerCity();
    vector<Airport*> getValidAirportsPerCountry();
    vector<Airport *> getAirportsRange(int x);
    vector<Airport*> getValidAirports();
    unordered_set<Airline*> getValidAirlines();
    unordered_set<Airline*> getValidAirlinePerCountry();
    unordered_set<Airline*> getValidAirlineSingleCountry();
    int getValidCityK();
    int getValidCountryK();
    int getValidAirlineK();
    static bool bars();
    unordered_set<string> getValidCitiesSingleCountry();
    Airline *getValidSingleAirline();
};


#endif //AED2324_PRJ2_G109_STATE_H
