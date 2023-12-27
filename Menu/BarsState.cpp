//
// Created by Wagner Pedrosa on 27/12/2023.
//

#include "BarsState.h"
#include <sstream>

BarsState barsState;
bool BarsState::shouldUseGraphicBar() const  {
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
    cout << "Enter your choice: ";
    cin >> userInputStr;

    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                useGraphicBar = true;
                if (!State::statisticsHistory.empty()) {
                    State *previousState = State::statisticsHistory.top();
                    State::statisticsHistory.pop();
                    return previousState;
                }
            }
            case 2: {
                useGraphicBar = false;
                if (!State::statisticsHistory.empty()) {
                    State *previousState = State::statisticsHistory.top();
                    State::statisticsHistory.pop();
                    return previousState;
                }
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}
