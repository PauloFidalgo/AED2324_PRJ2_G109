//
// Created by Wagner Pedrosa on 01/12/2023.
//
#include "iostream"
#include "FilghtSearchState.h"
#include "ChooseTypeOfAirportState.h"
#include "FilterState.h"

using namespace std;

FilterState filter;
ChooseTypeOfAirportState chooseAirport;



void FilghtSearchState::displayMenu() {
    cout << "________________________________________________________________________________________________________"<< endl;
    cout << "|                                                                                                      |"<< endl;
    cout << "|                                     Chose an option                                                  |" << endl;
    cout << "|                                                                                                      |"<< endl;
    cout << "|                                     1 - Country from                                                 |"<< endl;
    cout << "|                                     2 - Country to                                                   |"<< endl;
    cout << "|                                     3 - Filters                                                      |" << endl;
    cout << "|                                                                                                      |"<< endl;
    cout << "|  0 - anterior                                                                                        |"<< endl;
    cout << "|  q - Quit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------"<< endl;\

}

State *FilghtSearchState::handleInput() {
    int userInput;
    std::cout << " Enter your choice: ";
    std::cin >> userInput;


    switch (userInput) {
        case 1:
            State::stateHistory.push(this);
            return &chooseAirport;
        case 2:
            State::stateHistory.push(this);
            return &chooseAirport;
        case 3:
            State::stateHistory.push(this);
            return &filter;
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