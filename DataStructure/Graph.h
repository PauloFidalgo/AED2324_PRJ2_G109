//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_GRAPH_H
#define AED2324_PRJ2_G109_GRAPH_H

#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "../DataModel/Airline.h"
#include <string>
using namespace std;


class Vertex;
class Edge;
class Airport;

/****************** Provided structures  ********************/

class Graph {
    std::vector<Vertex *> vertexSet;    // vertex set
public:
    Vertex *findVertex(Airport* in) const;
    int getNumVertex() const;
    bool addVertex(Airport* in);
    bool removeVertex(Airport* in);
    bool addEdge(Airport* sourc, Airport* dest, double w, Airline* airline);
    bool removeEdge(Airport* sourc, Airport* dest);
    std::vector<Vertex * > getVertexSet() const;
    int inDegree(Airport* v) const;

};

#endif //AED2324_PRJ2_G109_GRAPH_H
