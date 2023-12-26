//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsStateCity.h"
#include "StatiscsStateAirline.h"
#include "iostream"

using namespace std;

StatiscsStateAirline statiscsStateAirline;

void StatisticsStateCity::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   98 - previous page                                                                                 |" << endl;
    cout << "|                                       Statistics by city :                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Nº flights                                                   |" << endl;
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

State* StatisticsStateCity::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            cout << "Airport city: ";
            cin >> city;
            manager.getNumFlightsPerCity(this->city);
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
        case 98:
            if(!State::statisticsHistory.empty()){
                State* previousState = State::statisticsHistory.top();
                State::statisticsHistory.pop();
                return previousState;
            }
        case 99:
            State::statisticsHistory.push(this);
            return &statiscsStateAirline;
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