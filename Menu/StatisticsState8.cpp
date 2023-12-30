//
// Created by Wagner Pedrosa on 30/12/2023.
//

#include "StatisticsState8.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
StatisticsState8 statisticsState8;


void StatisticsState8::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                             1. Top K Airlines That Fly More To An Airport Ratio (Ascending)          |" << endl;
    cout << "|                             2. Top K Airlines That Fly More To An Airport Ratio (Descending)         |" << endl;
    cout << "|                             3. Strongly connected Components                                         |" << endl;
    cout << "|                             4. Connected Components                                                  |" << endl;
    cout << "|                             5. Top K Greatest Traffic Airline                                        |" << endl;
    cout << "|                             6.                                                                       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 8    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatisticsState8::handleInput() {
    cout << "Enter your choice: ";
    cin >> userInputStr;

    if (userInputStr == "back") {
        if (!State::stateHistory.empty()) {
            State *previousState = State::stateHistory.top();
            State::stateHistory.pop();
            return previousState;
        } else {
            std::cout << "No previous Menu available" << std::endl;
            return this;
        }
    }
    if (userInputStr == "previous") {
        if (!State::statisticsHistory.empty()) {
            State *previousState = State::statisticsHistory.top();
            State::statisticsHistory.pop();
            return previousState;
        }
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto k = getValidAirportK();
                auto airport = getValidSingleAirport();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKAirlinesThatFlyMoreToAnAirportRatio(k,airport,bars,true);
            }
            case 2: {
                auto k = getValidAirportK();
                auto airport = getValidSingleAirport();
                auto bar = bars();
                manager.getTopKAirlinesThatFlyMoreToAnAirportRatio(k,airport,bar,false);
                return this;
            }
            case 3: {
                manager.scc();
                return this;
            }
            case 4: {
                //manager.cc();
                return this;
            }
            case 5: {
                int k = getValidAirlineK();
                manager.getTopKGreatestTrafficAirline(k);
                return this;
            }
            case 6:

            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}