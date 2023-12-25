//
// Created by Wagner Pedrosa on 25/12/2023.
//

#include "CoordinatesFilterState.h"
#include "iostream"
using namespace std;

CoordinatesFilterState::CoordinatesFilterState(): x(0),y(0) {}

void CoordinatesFilterState::setX(const int &x) {
    this->x = x;
}

void CoordinatesFilterState::setY(const int &y) {
    this->y = y;
}


void CoordinatesFilterState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Filters :                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Closest                                                      |" << endl;
    cout << "|                                     2 - 25 KM Range                                                  |" << endl;
    cout << "|                                     3 - 50 KM Range                                                  |" << endl;
    cout << "|                                     4 - 100 KM Range                                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* CoordinatesFilterState::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::cout << "Closest" << std::endl;
            std::cout << this->x;
            std::cout << this->y;
            return this;
        case 2:
            std::cout << "25 km" << std::endl;
            break;
        case 3:
            std::cout << "50 km" << std::endl;
            break;
        case 4:
            std::cout << "100 km" << std::endl;
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