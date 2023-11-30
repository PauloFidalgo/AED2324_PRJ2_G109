//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_EDGE_H
#define AED2324_PRJ2_G109_EDGE_H
#include "Vertex.h"
#include "Graph.h"


template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getWeight() const;
    void setWeight(double weight);
};


#endif //AED2324_PRJ2_G109_EDGE_H
