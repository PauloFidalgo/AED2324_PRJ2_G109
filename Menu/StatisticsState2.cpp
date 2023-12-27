//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState2.h"
#include "StatisticsState1.h"
#include "StatisticsState3.h"
#include "iostream"
#include "sstream"

using namespace std;

StatisticsState2 statisticsState2;
void StatisticsState2::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|    previous - previous page                                                      next- next page     |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Statistics:                                                |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Nº flights and Airlines                                       |" << endl;
    cout << "|                                     2. Nª flights per Airline                                        |" << endl;
    cout << "|                                     3. Nº Airports And Flights                                       |" << endl;
    cout << "|                                     4. Nº Flights And Airlines                                       |" << endl;
    cout << "|                                     5. Nº stops                                                      |" << endl;
    cout << "|                                     6. Articulation points                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Main Menu                                                                                    |" << endl;
    cout << "|  exit - Exit                                                                                         |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* StatisticsState2::handleInput() {
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
        return &statisticsState3;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                string city = getValidCity();
                manager.getNumFlightsPerCity(city);
                return this;
            }
            case 2: {
                Airport* airport = getValidAirport();
                manager.getAirportDestinantionsDistance1(airport);
                return this;
            }
            case 3:
                manager.getNumAirportsAndFlights();
                return this;
            case 4: {
                Airport* airport = getValidAirport();
                manager.getAirportDestinantions(airport);
                return this;
            }
            case 5: {
                string city = this->getValidCity();
                vector<Airport*> airports = manager.getAirportsPerCity(city);
                manager.getCityDestinantions(airports,city);
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

