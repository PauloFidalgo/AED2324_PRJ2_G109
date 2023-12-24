//
// Created by Paulo Fidalgo on 24/12/2023.
//

#include "FilterMinimization.h"
#include <iostream>
using namespace std;

void FilterMinimization::displayMenu() {
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Minimize:                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Number of Stops                                              |" << endl;
    cout << "|                                     2 - Distance Travelled                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State *FilterMinimization::handleInput() {
    int userInput;
    std::cout << " Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::cout << "Max Scales" << std::endl;
            break;
        case 2:
            std::cout << "Choose specific Airlines" << std::endl;
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
