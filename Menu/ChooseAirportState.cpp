//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "ChooseAirportState.h"
#include "iostream"
using namespace std;

void ChooseAirportState::displayMenu() {
    cout << "________________________________________________________________________________________________________"<< endl;
    cout << "|                                                                                                      |"<< endl;
    cout << "|                          Choose an option for Airports                                               |" << endl;
    cout << "|                                                                                                      |"<< endl;
    cout << "|                                     1 - Display International Airports                               |"<< endl;
    cout << "|                                     2 - Display Domestic Airports                                    |"<< endl;
    cout << "|                                     3 - Display All Airports                                         |"<< endl;
    cout << "|                                                                                                      |"<< endl;
    cout << "|  0 - Go back                                                                                         |"<< endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------"<< endl;
}

State *ChooseAirportState::handleInput() {
    int userInput;
    std::cout << " Enter your choice: ";
    std::cin >> userInput;


    switch (userInput) {
        case 1:
            std::cout << " internacional airports"<< std::endl;
            break;
        case 2:
            std:: cout << " Pais de chegada "<< std::endl;
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

    }
}
