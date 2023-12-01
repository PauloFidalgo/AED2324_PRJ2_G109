//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "FilterState.h"
#include "iostream"

using namespace std;

void FilterState::displayMenu() {
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Choose a filter                                            |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Max Scales                                                   |" << endl;
    cout << "|                                     2 - Choose specific Airlines                                     |" << endl;
    cout << "|                                     3 - Choose specific countries to pass through                    |" << endl;
    cout << "|                                     4 - Choose specific countries not to pass through                |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State *FilterState::handleInput() {
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
        case 3:
            std::cout << "Choose specific countries to pass through " << std::endl;
            break;
        case 4:
            std::cout << "Choose specific countries not to pass through" << std::endl;
            break;
        case 0:
            if(!State::stateHistory.empty()){
                State* previousState = State::stateHistory.top();
                State::stateHistory.pop();
                return previousState;
            }
            else{
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
