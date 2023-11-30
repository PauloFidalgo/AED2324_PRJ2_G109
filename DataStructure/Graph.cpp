//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Graph.h"


/****************** Provided constructors and functions ********************/

int Graph::getNumVertex() const {
    return vertexSet.size();
}

vector<Vertex * > Graph::getVertexSet() const {
    return vertexSet;
}

Vertex * Graph::findVertex(const Airport &in) const {
    for (auto v : vertexSet)
        if (v->airport == in)
            return v;
    return NULL;
}