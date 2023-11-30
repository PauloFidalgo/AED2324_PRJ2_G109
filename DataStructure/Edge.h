//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_EDGE_H
#define AED2324_PRJ2_G109_EDGE_H
#include "Vertex.h"
#include "Graph.h"

class Graph;
class Vertex;
class Airport;

class Edge {
    Vertex * dest;      // destination vertex
    double weight;         // edge weight
    std::vector<std::string> airlines;
public:
    Edge(Vertex *d, double w);
    void addAirline(const std::string &airline);
    std::vector<std::string> getAirlines() const;
    Vertex *getDest() const;
    void setDest(Vertex *dest);
    double getWeight() const;
    void setWeight(double weight);
    friend class Graph;
    friend class Vertex;
};


#endif //AED2324_PRJ2_G109_EDGE_H
