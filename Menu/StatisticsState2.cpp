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
    cout << "|                                     3. Nº country's                                                  |" << endl;
    cout << "|                                     4. Get destinations distance 1                                   |" << endl;
    cout << "|                                     5. Get destinations                                              |" << endl;
    cout << "|                                     6. Distance Travelled                                            |" << endl;
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
            case 1:
                getValidCity();
                manager.getNumFlightsPerCity(code);
                return this;
            case 2:
                getValidAirlineName();
                manager.getNumFlightsPerAirline(airline);
                return this;
            case 3:
                manager.getNumAirportsAndFlights();
                return this;
            case 4:
                getValidAirportName();
                manager.getNumFlightsAndAirlines();
                return this;
            case 5:
                getValidAirportName();
                manager.getNumStops();
                return this;
            case 6:
                statisticsState1.getValidAirportCode();
                cout << "Distance: ";
                cin >> distance;
                manager.get(name, distance);
                return this;
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

