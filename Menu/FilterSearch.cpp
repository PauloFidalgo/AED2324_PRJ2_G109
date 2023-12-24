//
// Created by Paulo Fidalgo on 24/12/2023.
//

#include "FilterSearch.h"
#include <iostream>

using namespace std;

void FilterSearch::displayMenu() {
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Search by:                                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Code                                                         |" << endl;
    cout << "|                                     2 - Name                                                         |" << endl;
    cout << "|                                     3 - Country                                                      |" << endl;
    cout << "|                                     4 - City                                                         |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State *FilterSearch::handleInput() {
    int userInput;
    std::cout << " Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::cout << "Code" << std::endl;
            break;
        case 2:
            std::cout << "Name" << std::endl;
            break;
        case 3:
            std::cout << "Country" << std::endl;
            break;
        case 4:
            std::cout << "City" << std::endl;
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
