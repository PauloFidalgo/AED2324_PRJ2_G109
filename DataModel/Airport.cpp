//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Airport.h"

Airport::Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
                 const double &latitude, const double &longitude) : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

bool Airport::operator==(const Airport &other) const {
    return other.code == this->code;
}

/*!
 * @brief Permite obter a latitude de um aeroporto
 * @return double correspondente à latitude do aeroporto
 */
const double &Airport::getLatitude() const {
    return this->latitude;
}

/*!
 * @brief Permite obter a longitude de um aeroporto
 * @return double correspondente à longitude do aeroporto
 */
const double &Airport::getLongitude() const {
    return this->longitude;
}

/*!
 * @brief Permite obter o código de um aeroporto
 * @return string correspondente ao código do aeroporto
 */
std::string Airport::getCode() const{
    return this->code;
}

/*!
 * @brief Permite obter o nome de um aeroporto
 * @return string correspondente ao nome do aeroporto
 */
std::string Airport::getName() const {
    return this->name;
}

/*!
 * @brief Permite obter o páis de um aeroporto
 * @return string correspondente ao país do aeroporto
 */
std::string Airport::getCountry() const {
    return this->country;
}

/*!
 * @brief Permite obter a cidade ao aeroporto
 * @return string correspondente à cidade do aeroporto
 */
std::string Airport::getCity() const {
    return this->city;
}

/*!
 * @brief Permite incrementar o número de voos que saem do aeroporto
 */
void Airport::increaseNumFlightsOut() {
    numFlightsOut++;
}

/*!
 * @brief Permite obter o número de voos que saem do aeroporto
 * @return int correspondente ao número de voos que saem do aeroporto
 */
int Airport::getNumFlightsOut() const {
    return numFlightsOut;
}

/*!
 * @brief Permite incrementar o número de voos para um aeroporto
 */
void Airport::increaseNumFlightsIn() {
    numFlightsIn++;
}

/*!
 * @brief Permite obter o número de voos para um aeroporto
 * @return int correspondente ao número de voos para um aeroporto
 */
int Airport::getNumFlightsIn() const {
    return numFlightsIn;
}
