//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState2.h"
#include "StatisticsStateCity.h"
#include "iostream"

using namespace std;
StatisticsStateCity statisticsStateCity;

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
            cout << "Airport name: ";
            cin >> name;
            manager.getNumFlightsAndAirlinesByName(this->name);
            return this;
        case 2:
            cout << "Airline Name: ";
            cin >> name;
            manager.getNumFlightsPerAirlineByName(this->name);
            return this;
        case 3:
            cout << "Airport Name: ";
            cin >> name;
            manager.getCountriesCanFlyToAirportByName(this->name);
            return this;
        case 4:
            cout << "Airport Name: ";
            cin >> name;
            manager.getDestinationsDistance1ByName(this->name);
            return this;
        case 5:
            cout << "Airport Name: ";
            cin >> name;
            manager.getDestinantionsByName(this->name);
            return this;
        case 6:
            cout << "Airport Name: ";
            cin >> name;
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
            return &statisticsStateCity;
        case -1:
            exit(0);
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
    return nullptr;
}