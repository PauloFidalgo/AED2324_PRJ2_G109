//
// Created by Paulo Fidalgo on 24/12/2023.
//

#include "FlightSearch.h"
#include <iostream>
#include <string>
#include "FilterState.h"

FilterState filterState;


using namespace std;


FlightSearch::FlightSearch(): isSelectingFrom(true){}

void FlightSearch::displayMenu() {
    const std::string origin = isSelectingFrom ? "From" : "  To";
    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|      "<< origin << "                     Search by:                                                             |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Code                                                         |" << endl;
    cout << "|                                     2 - Airport name                                                 |" << endl;
    cout << "|                                     3 - Country                                                      |" << endl;
    cout << "|                                     4 - Coordinates                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State *FlightSearch::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::cout << "Code for " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                std::cin >> from;
                isSelectingFrom = false;
                return this;
            } else {
                std::cin >> to;
                isSelectingFrom = true;
                filterState.setFrom(from);
                filterState.setTo(to);

                return &filterState;
            }
        case 2:
            std::cout << "Enter airport name: ";
            break;
        case 3:
            std::cout << "Enter country: ";
            break;
        case 4:
            std::cout << "Enter coordinates: ";
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

const std::string &FlightSearch::getTo() const {
    return to;
}

const std::string &FlightSearch::getFrom() const {
    return from;
}