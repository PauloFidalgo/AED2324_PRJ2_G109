//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_FILTERSTATE_H
#define AED2324_PRJ2_G109_FILTERSTATE_H
#include "State.h"
class FilterState: public State {
private:
    vector<Airport*> fromAirports;
    vector<Airport*> toAirports;
    map<int,vector<Airport*>> cityCountry;
    unordered_set<Airline*> excludedAirlines;
    unordered_set<Airline*> includedAirlines;
    vector<Airport*> excludedAirports;
    vector<Airport*> includedAirports;
    vector<string> includedCountries;
    vector<string> excludedCountries;
public:
    // Constructor
    FilterState(vector<Airport*> &from, vector<Airport*> &to);

    void displayMenu() override;
    State * handleInput() override;
    void excludeAirlinesPerCountry();
    void includeAirlinesPerCountry();
    void includeAirlines();

    void excludeAirlines();

    void includeCountries();

    void excludeCountries();

    void excludeAirports();

    void includeAirports();
    void includeCities();
    void excludeCities();

    void verifyExcludedAirlines();
    void verifyIncludedAirlines();
    void verifyIncludedAirports();
    void verifyExcludeAirports();
    void verifyVisitCountryCity();
    bool isAirportToBeRemoved(Airport* airport) const;

};


#endif //AED2324_PRJ2_G109_FILTERSTATE_H
