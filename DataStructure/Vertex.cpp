//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Vertex.h"

Vertex::Vertex(Airport* in): airport(in) {}


Airport Vertex::getInfo() const {
    return *airport;
}

void Vertex::setInfo(const Airport &in) {
    *airport = in;
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

int Vertex::getLow() const {
    return low;
}

int Vertex::getNum() const {
    return num;
}

void Vertex::setLow(int low) {
    this->low = low;
}

void Vertex::setNum(int num) {
    this->num = num;
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

void Vertex::addAdj(Edge &destination, Airline* airline) {
    for (auto& flight : this->adj) {
        if (flight.dest->airport == destination.dest->airport) {
            flight.addAirline(airline);
            return;
        }
    }
    destination.addAirline(airline);
    this->adj.push_back(destination);
}

void Vertex::addEdge(Vertex *d, double w) {
    adj.push_back(Edge(d, w));
}

bool Vertex::hasFlight(const Airport *destination) {
    for (auto& flight : this->adj) {
        if (flight.dest->airport->getCode() == destination->getCode()) {
            return true;
        }
    }
    return false;
}

bool Vertex::removeEdgeTo(Vertex *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}