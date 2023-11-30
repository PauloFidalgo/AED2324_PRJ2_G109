//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_GRAPH_H
#define AED2324_PRJ2_G109_GRAPH_H

#include <vector>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

class Vertex;
class Edge;
class Airport;

/****************** Provided structures  ********************/

class Graph {
    std::vector<Vertex *> vertexSet;    // vertex set
public:
    Vertex *findVertex(const Airport &in) const;
    int getNumVertex() const;
    bool addVertex(const Airport &in);
    bool removeVertex(const Airport &in);
    bool addEdge(const Airport &sourc, const Airport &dest, double w);
    bool removeEdge(const Airport &sourc, const Airport &dest);
    std::vector<Vertex * > getVertexSet() const;
    int inDegree(const Airport &v) const;

};

#endif //AED2324_PRJ2_G109_GRAPH_H
