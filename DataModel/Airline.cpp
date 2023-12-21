//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Airline.h"

Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country) : code(code), name(name), callsign(callsign), country(country) {}

std::string Airline::getName() const {
    return name;
}

void Airline::increaseNumFlights(){
    this->numFlights++;
}

int Airline::getNumFlights() const {
    return this->numFlights;
}

std::string Airline::getCode() const {
    return this->code;
}

