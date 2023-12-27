//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState2.h"
#include "StatisticsState1.h"
#include "StatisticsState3.h"
#include "iostream"

using namespace std;

StatisticsState2 statisticsState2;
void StatisticsState2::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|       98 - previous page                                                        99 - next page       |" << endl;
    cout << "|                                        Statistics by name :                                          |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Nº flights and Airlines                                      |" << endl;
    cout << "|                                     2 - Nª flights per Airline                                       |" << endl;
    cout << "|                                     3 - Nº country's                                                 |" << endl;
    cout << "|                                     4 - Get destinations distance 1                                  |" << endl;
    cout << "|                                     5 - Get destinations                                             |" << endl;
    cout << "|                                     6 - Distance Travelled                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Main Menu                                                                                       |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* StatisticsState2::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

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
            manager.getDestinantionsUntilDistanceK(name,distance);
            return this;
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
        case 98:
            if(!State::statisticsHistory.empty()){
                State* previousState = State::statisticsHistory.top();
                State::statisticsHistory.pop();
                return previousState;
            }
        case 99:
            State::statisticsHistory.push(this);
            return &statisticsState3;
        case -1:
            exit(0);
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
}

string* StatisticsState2::getValidAirportName() {
    do {
        cout << "Airport code: ";
        cin >> name;
        if (manager.getAirportsByName().find(name) == manager.getAirportsByName().end()) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (manager.getAirportsByName().find(name) == manager.getAirportsByName().end());
    return &name;
}

string* StatisticsState2::getValidAirlineName() {
    do {
        cout << "Airline code: ";
        cin >> name;
        if (manager.getAirlinesByName().find(name) == manager.getAirlinesByName().end()) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (manager.getAirlinesByName().find(name) == manager.getAirlinesByName().end());
    return &name;
}

