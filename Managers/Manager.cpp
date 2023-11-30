//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Manager.h"

Manager::Manager() {
    this->parser = Parser();
    this->airlines = parser.getAirlines();
    this->connections = parser.getGraph();
    this->airports = parser.getAirports();
}

map<std::string, Airline*> Manager::getAirlines() {
    return this->airlines;
}

map<string, Airport*> Manager::getAirports() {
    return this->airports;
}