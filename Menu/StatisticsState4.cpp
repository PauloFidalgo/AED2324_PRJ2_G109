//
// Created by Wagner Pedrosa on 26/12/2023.
//
#include "StatisticsState1.h"
#include "StatisticsState4.h"
#include "StatisticsState3.h"
#include "iostream"

using namespace std;
StatisticsState4 statisticsState4;

void StatisticsState4::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   98 - previous page                                                                                 |" << endl;
    cout << "|                                       Statistics by airport :                                        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Top K Greatest Traffic Airport                               |" << endl;
    cout << "|                                     2 - Top K Greatest Traffic Airport Per Country                   |" << endl;
    cout << "|                                     3 - Airports by country                                          |" << endl;
    cout << "|                                     4 - Airport Info                                                 |" << endl;
    cout << "|                                     5 - Airline Info                                                 |" << endl;
    cout << "|                                     6 - Out flights                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Main Menu                                                                                       |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatisticsState4::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            cout << "K: ";
            cin >> distance;
            manager.getTopKGreatestTrafficAirport(this->distance);
            return this;
        case 2:
            statisticsState3.getValidCountry();
            cout << "K: ";
            cin >> distance;
            manager.getTopKGreatestTrafficAirportPerCountry(this->distance,airport);
            return this;
        case 3:
            statisticsState3.getValidCountry();
            manager.listAiportsPerCountry(airport);
            return this;
        case 4:
            statisticsState1.getValidAirportCode();
            manager.printAirportInfo(this->airport);
            return this;
        case 5:
            statisticsState1.getValidAirlineCode();
            manager.printAirlineInfo(this->airport);
            return this;
        case 6:
            statisticsState1.getValidAirportCode();
            manager.getOutFlights(this->airport);
            return this;

        case 98:
            if(!State::statisticsHistory.empty()){
                State* previousState = State::statisticsHistory.top();
                State::statisticsHistory.pop();
                return previousState;
            }
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
}