//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState2.h"
#include "iostream"
#include "sstream"

using namespace std;

void StatisticsState2::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|    previous - previous page                                                      next- next page     |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Statistics:                                                |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Nº flights per city                                           |" << endl;
    cout << "|                                     2. Airports Destinations Distance 1                              |" << endl;
    cout << "|                                     3. Nº Airports and Flights                                       |" << endl;
    cout << "|                                     4. Airport Destinations                                          |" << endl;
    cout << "|                                     5. City Destinations                                             |" << endl;
    cout << "|                                     6. Articulation points                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Main Menu                                                                                    |" << endl;
    cout << "|  exit - Exit                                                                              page - 2   |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* StatisticsState2::handleInput() {
    State* nextState = new StatisticsState3();
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
    if (userInputStr == "previous") {
        if (!State::statisticsHistory.empty()) {
            State *previousState = State::statisticsHistory.top();
            State::statisticsHistory.pop();
            return previousState;
        }
    }

    if (userInputStr == "next") {
        State::statisticsHistory.push(this);
        return nextState;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                string city = getValidSingleCity();
                if (!city.empty()) manager.getNumFlightsPerCity(city);
                return this;
            }
            case 2: {
                Airport* airport = getValidSingleAirport();
                if (airport) manager.getAirportDestinantionsDistance1(airport);
                return this;
            }
            case 3:
                manager.getNumAirportsAndFlights();
                return this;
            case 4: {
                Airport* airport = getValidSingleAirport();
                if (airport) manager.getAirportDestinantions(airport);
                return this;
            }
            case 5: {
                vector<Airport*> airports = getValidAirportsSingleCity();
                if (!airports.empty()) manager.getCityDestinantions(airports,name);
                return this;
            }
            case 6:
                manager.articulationPoints();
                return this;
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

