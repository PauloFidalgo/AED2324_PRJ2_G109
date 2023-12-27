//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState1.h"
#include "StatisticsState2.h"
#include <sstream>
#include "iostream"

using namespace std;

StatisticsState1 statisticsState1;
void StatisticsState1::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                 next - next page     |" << endl;
    cout << "|                                             Statistics                                               |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Nº flights and Airlines                                       |" << endl;
    cout << "|                                     2. Nº flights per Airlines                                       |" << endl;
    cout << "|                                     3. Nº country's                                                  |" << endl;
    cout << "|                                     4. Get destinations distance 1                                   |" << endl;
    cout << "|                                     5. Get destinations                                              |" << endl;
    cout << "|                                     6. Get destinations until certain distance                       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                                          |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* StatisticsState1::handleInput() {
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
    if(userInputStr == "next"){
        State::statisticsHistory.push(this);
        return &statisticsState2;
    }
    if(userInputStr == "exit"){
        exit(0);
    }
    else
    {
            istringstream(userInputStr) >> userInput;
            switch (userInput) {
                case 1:
                    getValidAirportCode();
                    manager.getNumFlightsAndAirlines(this->code);
                    return this;
                case 2:
                    getValidAirlineCode();
                    manager.getNumFlightsPerAirline(this->code);
                    return this;
                case 3:
                    getValidAirportCode();
                    manager.getCountriesCanFlyToAirport(this->code);
                    return this;
                case 4:
                    getValidAirportCode();
                    manager.getDestinantionsDistance1(this->code);
                    return this;
                case 5:
                    getValidAirportCode();
                    manager.getDestinantions(this->code);
                    return this;
                case 6:
                    getValidAirportCode();
                    cout << "Distance: ";
                    cin >> distance;
                    manager.getDestinantionsUntilDistanceK(this->code, this->distance);
                    return this;
                default:
                    std::cout << " Invalid choice. try again" << std::endl;
                    return this;
            }
        }
    }

string* StatisticsState1::getValidAirportCode() {
    do {
        cout << "Airport code: ";
        cin >> code;
        if (!manager.getConnections().findVertex(manager.getAirport(code))) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!manager.getConnections().findVertex(manager.getAirport(code)));
    return &code;
}

string* StatisticsState1::getValidAirlineCode() {
    do {
        cout << "Airline code: ";
        cin >> code;
        if (manager.getAirlines().find(code) == manager.getAirlines().end()) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (manager.getAirlines().find(code) == manager.getAirlines().end());
    return &code;
}