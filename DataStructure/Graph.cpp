//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Graph.h"


/****************** Provided constructors and functions ********************/

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}