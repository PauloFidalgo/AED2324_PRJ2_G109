//
// Created by Paulo Fidalgo on 24/12/2023.
//

#include "FlightSearchState.h"
#include <iostream>
#include <string>
#include "FilterState.h"
#include "CoordinatesFilterState.h"

FilterState filterState;
CoordinatesFilterState coordinatesFilterState;


using namespace std;


FlightSearchState::FlightSearchState(): isSelectingFrom(true){}

void FlightSearchState::displayMenu() {
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

State *FlightSearchState::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::cout << "Code " << (isSelectingFrom ? "From" : "To") << ": ";
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
            std::cout << "Airport Name " << (isSelectingFrom ? "From" : "To") << ": ";
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
        case 3:
            std::cout << "Country " << (isSelectingFrom ? "From" : "To") << ": ";
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
        case 4:
                std::cout << "Select x: ";
                std::cin >> x;
                std::cout << "Select y: ";
                std::cin >> y;

                coordinatesFilterState.setX(x);
                coordinatesFilterState.setY(y);
                return &coordinatesFilterState;

        case 0:
            if(!State::stateHistory.empty()){
                State* previousState = State::stateHistory.top();
                State::stateHistory.pop();
                isSelectingFrom = true;
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
}

const std::string &FlightSearchState::getTo() const {
    return to;
}

const std::string &FlightSearchState::getFrom() const {
    return from;
}

const double &FlightSearchState::getX() const {
    return x;
}

const double &FlightSearchState::getY() const {
    return y;
}