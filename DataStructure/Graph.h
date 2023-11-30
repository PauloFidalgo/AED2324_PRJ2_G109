//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_GRAPH_H
#define AED2324_PRJ2_G109_GRAPH_H

#include <vector>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

/****************** Provided structures  ********************/

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    int inDegree(const T &v) const;

};

#endif //AED2324_PRJ2_G109_GRAPH_H
