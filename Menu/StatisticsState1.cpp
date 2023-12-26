//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState1.h"
#include "StatisticsState2.h"
#include "iostream"

using namespace std;
StatisticsState2 statisticsStateName;

void StatisticsState1::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                 99 - next page       |" << endl;
    cout << "|                                       Statistics by code :                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Nº flights and Airlines                                      |" << endl;
    cout << "|                                     2 - Nº flights per Airlines                                      |" << endl;
    cout << "|                                     3 - Nº country's                                                 |" << endl;
    cout << "|                                     4 - Get destinations distance 1                                  |" << endl;
    cout << "|                                     5 - Get destinations                                             |" << endl;
    cout << "|                                     6 - Get destinations until certain distance                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Main Menu                                                                                       |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* StatisticsState1::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            cout << "Airport code: ";
            cin >> code;
            manager.getNumFlightsAndAirlines(this->code);
            return this;
        case 2:
            cout << "Airline Code: ";
            cin >> code;
            manager.getNumFlightsPerAirline(this->code);
            return this;
        case 3:
            cout << "Airport Code: ";
            cin >> code;
            manager.getCountriesCanFlyToAirport(this->code);
            return this;
        case 4:
            cout << "Airport Code: ";
            cin >> code;
            manager.getDestinantionsDistance1(this->code);
            return this;
        case 5:
            cout << "Airport Code: ";
            cin >> code;
            manager.getDestinantions(this->code);
            return this;
        case 6:
            cout << "Airport Code: ";
            cin >> code;
            cout << "Distance: ";
            cin >> distance;
            manager.getDestinantionsUntilDistanceK(this->code,this->distance);
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
        case 99:
            State::statisticsHistory.push(this);
            return &statisticsStateName;
        case -1:
            exit(0);
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
    return nullptr;
}