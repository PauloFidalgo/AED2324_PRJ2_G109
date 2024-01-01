//
// Created by Paulo Fidalgo on 24/12/2023.
//

#include "FlightSearchState.h"
#include <iostream>
#include <string>
#include "FilterState.h"
#include <sstream>


using namespace std;

/*! @brief Construtor da classe FlightSearchState que inicializa a variável isSelectingFrom como true.
*/
FlightSearchState::FlightSearchState(): isSelectingFrom(true){}

/*! @brief função que mostra o menu com as possibilidades de pesquisa de voos, onde é permitido ao utilizador escolher o ponto de partida e o ponto de chegada.
 *
 */
void FlightSearchState::displayMenu() {
    const std::string origin = isSelectingFrom ? "From" : "To  ";
    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|         "<< origin << "                     Search by:                                                          |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Airport                                                      |" << endl;
    cout << "|                                     2 - City                                                         |" << endl;
    cout << "|                                     3 - Country                                                      |" << endl;
    cout << "|                                     4 - Coordinates ( Closest Airport )                              |" << endl;
    cout << "|                                     5 - Coordinates ( 50 Km Range )                                  |" << endl;
    cout << "|                                     6 - Coordinates ( 100 Km Range )                                 |" << endl;
    cout << "|                                     7 - Coordinates ( 150 Km Range )                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Go back                                                                                       |" << endl;
    cout << "| exit - Exit                                                                                          |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}



/*!@brief  função que, permite ao utilizador escolher o ponto de partida e o ponto de chagada consoante as várias opções apresentadas no menu
 */
State *FlightSearchState::handleInput() {
    cout << "Enter your choice: ";
    cin >> userInputStr;

    if (fromAirports.empty()) isSelectingFrom = true;

    if (userInputStr == "back") {
        if (!State::stateHistory.empty()) {
            State *previousState = State::stateHistory.top();
            State::stateHistory.pop();
            isSelectingFrom = true;
            return previousState;
        } else {
            std::cout << "No previous Menu available" << std::endl;
            return this;
        }
    }
    else if (userInputStr == "exit") {
        exit(0);
    } else {
        try {
            userInput = stoi(userInputStr);
        }
        catch (exception &e) {
            cout << "Invalid choice" << endl;
            cin.clear();
            return this;
        }
        switch (userInput) {
            case 1:
                std::cout << "Airport code or name " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromCode = this->getValidSingleAirport();
                    if (!fromCode) return this;
                    fromAirports.push_back(fromCode);
                    isSelectingFrom = false;
                    return this;
                } else {
                    toCode = this->getValidSingleAirport();
                    if (!toCode) return this;
                    toAirports.push_back(toCode);
                    validateToAirports();
                    isSelectingFrom = true;
                    if (!fromAirports.empty() && !toAirports.empty()) {
                        auto* f = new FilterState(fromAirports, toAirports);
                        return f;
                    }
                    fromAirports.clear();
                    toAirports.clear();
                    return this;
                }
            case 2:
                std::cout << "City Name " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getValidAirportsSingleCity();
                    if (fromAirports.empty()) return this;
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getValidAirportsSingleCity();
                    if (toAirports.empty()) return this;
                    isSelectingFrom = true;
                    validateToAirports();
                    if (!fromAirports.empty() && !toAirports.empty()) {
                        auto* f = new FilterState(fromAirports, toAirports);
                        return f;
                    }
                    fromAirports.clear();
                    toAirports.clear();
                    return this;
                }
            case 3:
                std::cout << "Country Name " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getValidAirportsSingleCountry();
                    if (fromAirports.empty()) return this;
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getValidAirportsSingleCountry();
                    if (toAirports.empty()) return this;
                    isSelectingFrom = true;
                    validateToAirports();
                    if (!fromAirports.empty() && !toAirports.empty()) {
                        auto* f = new FilterState(fromAirports, toAirports);
                        return f;
                    }
                    fromAirports.clear();
                    toAirports.clear();
                    return this;
                }
            case 4:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromCode = this->getValidAirportPerCoordinates();
                    if (fromAirports.empty()) return this;
                    fromAirports.push_back(fromCode);
                    isSelectingFrom = false;
                    return this;
                } else {
                    toCode = this->getValidAirportPerCoordinates();
                    if (toAirports.empty()) return this;
                    toAirports.push_back(toCode);
                    isSelectingFrom = true;
                    validateToAirports();
                    if (!fromAirports.empty() && !toAirports.empty()) {
                        auto* f = new FilterState(fromAirports, toAirports);
                        return f;
                    }
                    fromAirports.clear();
                    toAirports.clear();
                    return this;
                }
            case 5:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getAirportsRange(50);
                    if (fromAirports.empty()) return this;
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getAirportsRange(50);
                    if (toAirports.empty()) return this;
                    isSelectingFrom = true;
                    validateToAirports();
                    if (!fromAirports.empty() && !toAirports.empty()) {
                        auto* f = new FilterState(fromAirports, toAirports);
                        return f;
                    }
                    fromAirports.clear();
                    toAirports.clear();
                    return this;
                }
            case 6:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getAirportsRange(100);
                    if (fromAirports.empty()) return this;
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getAirportsRange(100);
                    if (toAirports.empty()) return this;
                    isSelectingFrom = true;
                    validateToAirports();
                    if (!fromAirports.empty() && !toAirports.empty()) {
                        auto* f = new FilterState(fromAirports, toAirports);
                        return f;
                    }
                    fromAirports.clear();
                    toAirports.clear();
                    return this;
                }
            case 7:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getAirportsRange(150);
                    if (fromAirports.empty()) return this;
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getAirportsRange(150);
                    if (toAirports.empty()) return this;
                    isSelectingFrom = true;
                    validateToAirports();
                    if (!fromAirports.empty() && !toAirports.empty()) {
                        auto* f = new FilterState(fromAirports, toAirports);
                        return f;
                    }
                    fromAirports.clear();
                    toAirports.clear();
                    return this;
                }
            case 0:
                if (!State::stateHistory.empty()) {
                    State *previousState = State::stateHistory.top();
                    State::stateHistory.pop();
                    isSelectingFrom = true;
                    return previousState;
                } else {
                    std::cout << "No previous Menu available" << std::endl;
                    return this;
                }
            case -1:
                exit(0);
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

/*! @brief função que verifica se o aeroporto de partida não é o mesmo que o aeroporto de chagada.
 *
 */
void FlightSearchState::validateToAirports() {

    if (fromAirports.size() == 1 && toAirports.size() == 1) {
        auto it = fromAirports.begin();
        auto n = toAirports.begin();

        Airport* a = *it;
        Airport* b = *n;

        if (a->getCode() == b->getCode()) {
            toAirports = {};
        }
    }
}