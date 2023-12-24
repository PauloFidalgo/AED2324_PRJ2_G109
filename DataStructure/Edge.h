//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_EDGE_H
#define AED2324_PRJ2_G109_EDGE_H
#include "Vertex.h"
#include "Graph.h"
#include <string>
#include <set>

class Graph;
class Vertex;
class Airport;
class Airline;

class Edge {
    Vertex * dest;      // destination vertex
    double weight;         // edge weight
    std::set<Airline*> airlines;
public:
    Edge(Vertex *d, double w);
    void addAirline(Airline* airline);
    std::set<Airline*> getAirlines() const;
    Vertex* getDest() const;
    void setDest(Vertex *dest);
    double getWeight() const;
    void setWeight(double weight);
    friend class Graph;
    friend class Vertex;

    bool hasAirline(Airline *airline) const;
};


#endif //AED2324_PRJ2_G109_EDGE_H
