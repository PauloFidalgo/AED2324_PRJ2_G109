//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "FilterState.h"
#include "iostream"
#include "FlightSearchState.h"

using namespace std;

void FilterState::setFrom( Airport* fromAirport) {
    this->fromAirport = fromAirport;
}

void FilterState::setTo( Airport* toAirport) {
    this->toAirport = toAirport;
}
void FilterState::setFrom( vector<Airport*> fromAirports) {
    this->fromAirports = fromAirports;
}

void FilterState::setTo( vector<Airport*> toAirports) {
    this->toAirports = toAirports;
}


void FilterState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                            Filters :                                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|      1 - exclude 1 or more airlines                    8 - include 1 or more airports                |" << endl;
    cout << "|      2 - include 1 or more airlines                    9 - Avoid passing through 1 or more country's |" << endl;
    cout << "|      3 - exclude 1 or more country                     10 - Pass trough 1 or more country's          |" << endl;
    cout << "|      4 - include 1 or more country                     11 - Minimize the number of distinct airlines |" << endl;
    cout << "|      5 - exclude 1 or more city                        12 - Distance Travelled                       |" << endl;
    cout << "|      6 - include 1 or more city                        13 - Minimize Stops                           |" << endl;
    cout << "|      7 - exclude 1 or more airports                                                                  |" << endl;
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
            break;
        case 2:
            this->includeAirlines();
            break;
        case 3:
            excludeCountries();
            break;
        case 4:
            this->includeCountries();
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            excludeCountries();
            break;
        case 10:
            this->includeCountries();
            break;
        case 13:
            manager.manageFlightSearchFromMenu(this->toAirports,this->fromAirports,airportsToVisit,cityCountry,excludedAirports,excludedAirlines,includedAirlines);
            break;
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
    return nullptr;
}



void FilterState::excludeAirlines() {
    if ( excludedAirlines.empty() ){
        excludedAirlines = this->getValidAirlines();
    } else {
        auto aux = this->getValidAirlines();
        excludedAirlines.insert(aux.begin(),aux.end());
    }
}

void FilterState::excludeAirlinesPerCountry() {
    if ( excludedAirlines.empty() ){
        excludedAirlines = this->getValidAirlinePerCountry();
    } else {
        auto aux = this->getValidAirlinePerCountry();
        excludedAirlines.insert(aux.begin(),aux.end());
    }
}


void FilterState::includeAirlines() {
    if ( includedAirlines.empty() ){
        includedAirlines = this->getValidAirlines();
    } else {
        auto aux = this->getValidAirlines();
        includedAirlines.insert(aux.begin(),aux.end());
    }
}

void FilterState::excludeAirports() {
    if ( excludedAirports.empty() ){
        excludedAirports = this->getValidAirports();
    } else {
        auto aux = this->getValidAirports();
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
}


void FilterState::includeAirports() {
    includedAirports = this->getValidAirports();
}

void FilterState::includeCountries() {
    if ( cityCountry.empty() ){
        cityCountry = this->getValidAirportsPerCountries();
    } else {
        auto aux = this->getValidAirportsPerCountries();
        int size = cityCountry.size();
        for(auto& x : aux){
            cityCountry.insert({size + x.first,x.second});
        }
    }
}


void FilterState::excludeCountries() {

    if ( excludedAirports.empty() ){
        excludedAirports = this->getValidAirportsPerCountry();
    } else {
        auto aux = this->getValidAirportsPerCountry();
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
}

void FilterState::includeCities() {
    if ( cityCountry.empty() ){
        cityCountry = this->getValidAirportsPerCities();
    } else {
        auto aux = this->getValidAirportsPerCities();
        int size = cityCountry.size();
        for(auto& x : aux){
            cityCountry.insert({size + x.first,x.second});
        }
    }
}


void FilterState::excludeCities() {
    if ( excludedAirports.empty() ){
        excludedAirports = this->getValidAirportsPerCity();
    } else {
        auto aux = this->getValidAirportsPerCity();
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
}

 vector<Airport*>& FilterState::getFromAirports() {
    return fromAirports;
}

unordered_set<Airline*>& FilterState::getFromAirline() {
    return fromAirlines;
}
unordered_set<Airline*>& FilterState::getToAirline() {
    return toAirlines;
}