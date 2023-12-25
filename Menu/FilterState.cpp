//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "FilterState.h"
#include "iostream"
#include "FlightSearch.h"

using namespace std;

FilterState::FilterState()
        : from(""), to("") {}

void FilterState::setFrom(const std::string& from) {
    this->from = from;
}

void FilterState::setTo(const std::string& to) {
    this->to = to;
}

void FilterState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Filters :                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - exclude 1 or more airlines                                   |" << endl;
    cout << "|                                     2 - include 1 or more airlines                                   |" << endl;
    cout << "|                                     3 - Avoid passing through 1 or more country's                    |" << endl;
    cout << "|                                     4 - Pass trough 1 or more country's                              |" << endl;
    cout << "|                                     5 - Minimize the number of distinct airlines                     |" << endl;
    cout << "|                                     6 - Distance Travelled                                           |" << endl;
    cout << "|                                     7 - Done                                                         |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* FilterState::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            manager.getNumFlightsAndAirlines(this->from);
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
        case -1:
            exit(0);
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
    return nullptr;
}
