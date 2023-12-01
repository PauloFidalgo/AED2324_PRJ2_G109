//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Edge.h"

Edge::Edge(Vertex *d, double w): dest(d), weight(w) {}


Vertex *Edge::getDest() const {
    return this->dest;
}

void Edge::setDest(Vertex *d) {
    this->dest = d;
}

double Edge::getWeight() const {
    return this->weight;
}

void Edge::setWeight(double weight) {
    this->weight = weight;
}

void Edge::addAirline(Airline* airline) {
    this->airlines.push_back(airline);
}

std::vector<Airline *> Edge::getAirlines() const {
    return this->airlines;
}