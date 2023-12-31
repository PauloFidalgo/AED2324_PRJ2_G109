//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include <algorithm>
#include "FilterState.h"
#include "iostream"
#include "FlightSearchState.h"

using namespace std;
FilterState::FilterState(vector<Airport*> &from, vector<Airport*> &to) {
    fromAirports = from;
    toAirports = to;
}

void FilterState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|        Filters:                                        Search:                                       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|        1 - Exclude 1 or more Airlines                  11 - Minimize Number of Distinct Airlines     |" << endl;
    cout << "|        2 - Include 1 or more Airlines                  12 - Distance Travelled                       |" << endl;
    cout << "|        3 - Exclude 1 or more Airlines Per Country      13 - Minimize Stops                           |" << endl;
    cout << "|        4 - Include 1 or more Airlines Per Country                                                    |" << endl;
    cout << "|        5 - Exclude 1 or more Airports                                                                |" << endl;
    cout << "|        6 - Include 1 or more Airports                                                                |" << endl;
    cout << "|        7 - Exclude 1 or more Cities                                                                  |" << endl;
    cout << "|        8 - Include 1 or more Cities                                                                  |" << endl;
    cout << "|        9 - Exclude 1 or more Countries                                                               |" << endl;
    cout << "|        10 - Include 1 or more Countries                                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* FilterState::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            this->excludeAirlines();
            return this;
        case 2:
            this->includeAirlines();
            return this;
        case 3:
            this->excludeAirlinesPerCountry();
            return this;
        case 4:
            this->includeAirlinesPerCountry();
            return this;
        case 5:
            this->excludeAirports();
            return this;
        case 6:
            this->includeAirports();
            return this;
        case 7:
            this->excludeCities();
            return this;
        case 8:
            this->includeCities();
            return this;
        case 9:
            this->excludeCountries();
            return this;
        case 10:
            this->includeCountries();
            return this;
        case 11:
            // Min Different airlines
            return this;
        case 12:
            manager.manageFlightSearchFromMenuMinDistance(fromAirports,toAirports,includedAirports,cityCountry,excludedAirports,excludedAirlines,includedAirlines);
            toAirports.clear();
            fromAirports.clear();
            includedAirports.clear();
            cityCountry.clear();
            excludedAirports.clear();
            includedAirlines.clear();
            while (stateHistory.size() != 1) stateHistory.pop();
            return stateHistory.top();
        case 13:
            manager.manageFlightSearchFromMenu(fromAirports,toAirports,includedAirports,cityCountry,excludedAirports,excludedAirlines,includedAirlines);
            toAirports.clear();
            fromAirports.clear();
            includedAirports.clear();
            cityCountry.clear();
            excludedAirports.clear();
            includedAirlines.clear();
            while (stateHistory.size() != 1) stateHistory.pop();
            return stateHistory.top();
        case 0:
            if(!State::stateHistory.empty()){
                State* previousState = State::stateHistory.top();
                State::stateHistory.pop();
                return previousState;
            }
            else {
                std::cout << "No previous Menu available" << std::endl;
                return this;
            }
        case -1:
            exit(0);
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
}



void FilterState::excludeAirlines() {
    auto aux = this->getValidAirlines();
    if ( excludedAirlines.empty() && !aux.empty()){
        excludedAirlines = aux;
    } else if (!aux.empty()) {
        excludedAirlines.insert(aux.begin(),aux.end());
    }
    verifyExcludedAirlines();
}

void FilterState::excludeAirlinesPerCountry() {
    auto aux = this->getValidAirlinePerCountry();
    if ( excludedAirlines.empty() && !aux.empty()){
        excludedAirlines = aux;
    } else if (!aux.empty()) {
        for (auto &i : aux) {
            excludedAirlines.insert(i);
        }
    }
    verifyExcludedAirlines();
}

void FilterState::includeAirlinesPerCountry() {
    auto aux = this->getValidAirlinePerCountry();
    if ( includedAirlines.empty() && !aux.empty()){
        includedAirlines = aux;
    } else if (!aux.empty()) {
        for (auto &i : aux) {
            includedAirlines.insert(i);
        }
    }
    verifyIncludedAirlines();
}


void FilterState::includeAirlines() {
    auto aux = this->getValidAirlines();
    if ( includedAirlines.empty() && !aux.empty()){
        includedAirlines = aux;
    } else if (!aux.empty()) {
        for (auto &i : aux) {
            includedAirlines.insert(i);
        }
    }
    verifyIncludedAirlines();
}

void FilterState::excludeAirports() {
    auto aux = this->getValidAirports();
    if ( excludedAirports.empty() && !aux.empty()){
        excludedAirports = aux;
    } else if (!aux.empty()) {
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
    verifyExcludeAirports();
}


void FilterState::includeAirports() {
    auto aux = this->getValidAirports();
    if (includedAirports.empty() && !aux.empty()) {
        includedAirports = aux;
    }
    else if (!aux.empty()) {
        includedAirports.insert(includedAirports.end(), aux.begin(), aux.end());
    }
    verifyIncludedAirports();
}

void FilterState::includeCountries() {
    auto aux = this->getValidAirportsPerCountries();
    if ( cityCountry.empty() && !aux.empty()){
        cityCountry = aux;
    } else if (!aux.empty()) {
        int size = cityCountry.size();
        for(auto& x : aux){
            cityCountry.insert({size + x.first,x.second});
        }
    }
    verifyVisitCountryCity();
}


void FilterState::excludeCountries() {
    auto aux = this->getValidAirportsPerCountry();
    if ( excludedAirports.empty() && !aux.empty()){
        excludedAirports = aux;
    } else if (!aux.empty()) {
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
    verifyExcludeAirports();
}

void FilterState::includeCities() {
    auto aux = this->getValidAirportsPerCities();
    if ( cityCountry.empty() && !aux.empty()){
        cityCountry = aux;
    } else if (!aux.empty()) {
        int size = cityCountry.size();
        for(auto& x : aux){
            cityCountry.insert({size + x.first,x.second});
        }
    }
    verifyVisitCountryCity();
}


void FilterState::excludeCities() {
    auto aux = this->getValidAirportsPerCity();
    if ( excludedAirports.empty() && !aux.empty()){
        excludedAirports = aux;
    } else if (!aux.empty()) {
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
    verifyExcludeAirports();
}

void FilterState::verifyExcludeAirports() {
    vector<Airport*> res;

    for (auto &it : excludedAirports) {
        bool found = false;
        for (auto &i : includedAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }
    vector<Airport*> aux;
    for (auto &it : res) {
        bool found = false;
        for (auto &i : fromAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) aux.push_back(it);
    }

    res.clear();
    for (auto &it : aux) {
        bool found = false;
        for (auto &i : toAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }

    excludedAirports = res;
}


void FilterState::verifyIncludedAirports() {
    vector<Airport*> res;

    for (auto &it : includedAirports) {
        bool found = false;
        for (auto &i : excludedAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }
    vector<Airport*> aux;
    for (auto &it : res) {
        bool found = false;
        for (auto &i : fromAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) aux.push_back(it);
    }

    res.clear();
    for (auto &it : aux) {
        bool found = false;
        for (auto &i : toAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }

    includedAirports = res;
}


void FilterState::verifyIncludedAirlines() {
    unordered_set<Airline*> res;

    for (auto it : includedAirlines) {
        auto p = excludedAirlines.find(it);

        if (p == excludedAirlines.end()) {
            res.insert(it);
        }
    }
    includedAirlines = res;
}


void FilterState::verifyExcludedAirlines() {
    unordered_set<Airline*> res;

    for (auto it : excludedAirlines) {
        auto p = includedAirlines.find(it);

        if (p == includedAirlines.end()) {
            res.insert(it);
        }
    }
    excludedAirlines = res;
}


void FilterState::verifyVisitCountryCity() {
    for (auto it = cityCountry.begin(); it != cityCountry.end(); ) {
        auto &airportVector = it->second;

        airportVector.erase(
                std::remove_if(
                        airportVector.begin(),
                        airportVector.end(),
                        [this](auto airport) {
                            return isAirportToBeRemoved(airport);
                        }
                ),
                airportVector.end()
        );

        if (airportVector.empty()) {
            it = cityCountry.erase(it);
        } else {
            ++it;
        }
    }
}

bool FilterState::isAirportToBeRemoved(Airport* airport) const {

    return std::find(toAirports.begin(), toAirports.end(), airport) != toAirports.end() ||
           std::find(fromAirports.begin(), fromAirports.end(), airport) != fromAirports.end() ||
           std::find(excludedAirports.begin(), excludedAirports.end(), airport) != excludedAirports.end() ||
           std::find(includedAirports.begin(), includedAirports.end(), airport) != includedAirports.end();
}


