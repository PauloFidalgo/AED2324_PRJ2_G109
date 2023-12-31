//
// Created by Wagner Pedrosa on 27/12/2023.
//

#include "BarsState.h"
#include <sstream>

BarsState barsState;
int BarsState::shouldUseGraphicBar()   {
    return useGraphicBar;
}

void BarsState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                       Do you want graphic bar?                                       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                 1. Yes                                                        2. No                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  exit - Exit                                                                                         |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* BarsState::handleInput() {
    cin.clear();
    cout << "Enter your choice: ";
    cin >> userInputStr;

    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                useGraphicBar = 1;
                break;
            }
            case 2: {
                useGraphicBar = 0;
                break;
            }
            case -1 :{
                useGraphicBar = -1;
                break;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return handleInput();
        }
    }
}
