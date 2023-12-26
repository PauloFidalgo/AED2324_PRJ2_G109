//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatiscsStateAirline.h"
#include "iostream"

using namespace std;

void StatiscsStateAirline::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   98 - previous page                                                                                 |" << endl;
    cout << "|                                       Statistics by airline :                                        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Nº flights by code                                           |" << endl;
    cout << "|                                     2 - Nº flights by name                                           |" << endl;
    cout << "|                                     3 - Avoid passing through 1 or more country's                    |" << endl;
    cout << "|                                     4 - Pass trough 1 or more country's                              |" << endl;
    cout << "|                                     5 - Minimize the number of distinct airlines                     |" << endl;
    cout << "|                                     6 - Distance Travelled                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Main Menu                                                                                       |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatiscsStateAirline::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            cout << "Airline Code: ";
            cin >> airline;
            manager.getNumFlightsPerAirline(this->airline);
            return this;
        case 2:
            cout << "Airline Name: ";
            cin >> airline;
            manager.getNumFlightsPerAirlineByName(this->airline);
            return this;
        case 3:
            std::cout << "Country" << std::endl;
            break;
        case 4:
            std::cout << "Coordinates" << std::endl;
            break;
        case 98:
            if(!State::statisticsHistory.empty()){
                State* previousState = State::statisticsHistory.top();
                State::statisticsHistory.pop();
                return previousState;
            }
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