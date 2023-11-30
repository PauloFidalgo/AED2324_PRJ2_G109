//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Vertex.h"

Vertex::Vertex(const Airport &in): airport(in) {}


Airport Vertex::getInfo() const {
    return airport;
}

void Vertex::setInfo(const Airport &in) {
    airport = in;
}

bool Vertex::isProcessing() const {
    return processing;
}

void Vertex::setProcessing(const bool &p) {
    this->processing = p;
}


bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(const bool &v) {
    this->visited = v;
}

const std::vector<Edge> &Vertex::getAdj() const {
    return adj;
}

void Vertex::setAdj(const std::vector<Edge> &destinations) {
    this->adj = destinations;
}

void Vertex::addAdj(Edge &destination, std::string airline) {
    for (auto& flight : this->adj) {
        if (flight.dest->airport == destination.dest->airport) {
            flight.addAirline(airline);
            return;
        }
    }
    destination.addAirline(airline);
    this->adj.push_back(destination);
}

bool Vertex::hasFlight(const Edge &destination) {
    for (auto& flight : this->adj) {
        if (flight.dest->airport == destination.dest->airport) {
            return true;
        }
    }
    return false;
}