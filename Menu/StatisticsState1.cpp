//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState1.h"
#include "StatisticsState2.h"
#include <sstream>
#include "iostream"

using namespace std;

StatisticsState1 statisticsState1;
void StatisticsState1::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                 next - next page     |" << endl;
    cout << "|                                             Statistics                                               |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Nº flights and Airlines                                       |" << endl;
    cout << "|                                     2. Nº flights per Airlines                                       |" << endl;
    cout << "|                                     3. Nº country's that can fly to a specific airport               |" << endl;
    cout << "|                                     4. Get City destinations distance 1                              |" << endl;
    cout << "|                                     5. Get Country destinations distance 1                           |" << endl;
    cout << "|                                     6. Get Airport destinations until certain distance               |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Main Menu                                                                                    |" << endl;
    cout << "|  exit - Exit                                                                              page - 1   |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* StatisticsState1::handleInput() {
    cout << "Enter your choice: ";
    cin >> userInputStr;

    if (userInputStr == "back") {
        if (!State::stateHistory.empty()) {
            State *previousState = State::stateHistory.top();
            State::stateHistory.pop();
            return previousState;
        } else {
            std::cout << "No previous Menu available" << std::endl;
            return this;
        }
    }
    if(userInputStr == "next"){
        State::statisticsHistory.push(this);
        return &statisticsState2;
    }
    if(userInputStr == "exit"){
        exit(0);
    }
    else
    {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                Airport *airport = getValidSingleAirport();
                if (airport) manager.getNumFlightsAndAirlines(airport);
                return this;
            }
            case 2: {
                Airline *airline = getValidSingleAirline();
                if (airline) manager.getNumFlightsPerAirline(airline);
                return this;
            }
            case 3: {
                Airport *airport = getValidSingleAirport();
                if (airport) manager.getCountriesCanFlyToAirport(airport);
                return this;
            }
            case 4: {
                vector<Airport*> airports = getValidAirportsSingleCity();
                if (!airports.empty()) manager.getCityDestinationsDistance1(airports,name);
                return this;
            }
            case 5: {
                auto airports = getValidAirportsSingleCountry();
                if (!airports.empty()) manager.getCountryDestinationsDistance1(airports,name);
                return this;
            }
            case 6: {
                Airport *airport = getValidSingleAirport();
                int distance = getValidAirportK();
                if (airport != nullptr && distance != -1) manager.getAirportDestinantionsUntilDistanceK(airport, distance);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}