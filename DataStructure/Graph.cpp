//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Graph.h"
#include "../DataModel/Airline.h"


/****************** Provided constructors and functions ********************/

int Graph::getNumVertex() const {
    return vertexSet.size();
}

vector<Vertex * > Graph::getVertexSet() const {
    return vertexSet;
}


bool Graph::addVertex(Airport* in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}

bool Graph::addEdge(Airport* sourc, Airport *dest, double w, Airline* airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL) {
        return false;
    }
    Edge e = Edge(v2, w);
    v1->addAdj(e, airline);
    return true;
}

bool Graph::removeEdge(Airport* sourc, Airport* dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}


bool Graph::removeVertex(Airport* in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->airport  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

Vertex * Graph::findVertex(Airport* in) const {
    for (auto v : vertexSet)
        if (v->airport == in)
            return v;
    return NULL;
}