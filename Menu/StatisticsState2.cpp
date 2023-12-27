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
                getValidAirportName();
                manager.getNumFlightsAndAirlinesByName(this->name);
                return this;
            case 2:
                getValidAirlineName();
                manager.getNumFlightsPerAirlineByName(this->name);
                return this;
            case 3:
                getValidAirportName();
                manager.getCountriesCanFlyToAirportByName(this->name);
                return this;
            case 4:
                getValidAirportName();
                manager.getDestinationsDistance1ByName(this->name);
                return this;
            case 5:
                getValidAirportName();
                manager.getDestinantionsByName(this->name);
                return this;
            case 6:
                statisticsState1.getValidAirportCode();
                cout << "Distance: ";
                cin >> distance;
                manager.getDestinantionsUntilDistanceK(name, distance);
                return this;
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

Airport* StatisticsState2::getValidAirportName() {
    do {
        cout << "Airport code: ";
        cin >> name;
        airport = manager.getAirportPerName(name);
        if (!airport) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!airport);
    return airport;
}

Airline* StatisticsState2::getValidAirlineName() {
    do {
        cout << "Airline code: ";
        cin >> name;
        airline = manager.getAirlinePerName(name);
        if (!airline) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (!airline);
    return airline;
}

