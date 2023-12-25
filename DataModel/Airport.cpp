//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Airport.h"

Airport::Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
                 const double &latitude, const double &longitude) : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

bool Airport::operator==(const Airport &other) const {
    return other.code == this->code;
}

const double &Airport::getLatitude() const {
    return this->latitude;
}

const double &Airport::getLongitude() const {
    return this->longitude;
}

std::string Airport::getCode() const{
    return this->code;
}

std::string Airport::getName() const {
    return this->name;
}

std::string Airport::getCountry() const {
    return this->country;
}

std::string Airport::getCity() const {
    return this->city;
}

void Airport::increaseNumFlightsOut() {
    numFlightsOut++;
}

int Airport::getNumFlightsOut() const {
    return numFlightsOut;
}

void Airport::increaseNumFlightsIn() {
    numFlightsIn++;
}

int Airport::getNumFlightsIn() const {
    return numFlightsIn;
}
