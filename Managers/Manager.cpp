//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Manager.h"

Manager::Manager() {
    this->parser = Parser();
    this->airlines = parser.readAirlines();
    this->connections = parser.getGraph();
}