//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Airline.h"

Airline::Airline::Airline() {}

Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country) : code(code), name(name), callsign(callsign), country(country) {}


/*!
 * @brief Permite obter o nome da uma companhia
 * @return string correspondente ao nome da companhia
 */
std::string Airline::getName() const {
    return name;
}

/*!
 * @brief Permite incrementar o número de voos de uma companhia
 */
void Airline::increaseNumFlights(){
    this->numFlights++;
}

/*!
 * @brief Permite obter o número total de voos de uma companhia
 * @return int correspondente ao número de voos da companhia
 * O(1)
 */
int Airline::getNumFlights() const {
    return this->numFlights;
}

/*!
 * @brief Permite obter o código identificador da companhia
 * @return string correspondente ao código
 */
std::string Airline::getCode() const {
    return this->code;
}

/*!
 * @brief Permite obter o país de uma companhia
 * @return string correspondente ao país
 */
std::string Airline::getCountry() const {
    return country;
}

/*!
 * @brief Permite obter o CallSign de uma companhia
 * @return string correspondente ao callsign
 */
std::string Airline::getCallsign() const {
    return callsign;
}

