//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsStateCode.h"
#include "StatisticsStateName.h"
#include "iostream"

using namespace std;
StatisticsStateName statisticsStateName;

void StatisticsStateCode::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                 99 - next page       |" << endl;
    cout << "|                                       Statistics by code :                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Nº flights and Airlines                                      |" << endl;
    cout << "|                                     2 - include 1 or more airlines                                   |" << endl;
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

State* StatisticsStateCode::handleInput() {
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
            std::cout << "Name" << std::endl;
            break;
        case 3:
            std::cout << "Country" << std::endl;
            break;
        case 4:
            std::cout << "Coordinates" << std::endl;
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