//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_VERTEX_H
#define AED2324_PRJ2_G109_VERTEX_H
#include "Edge.h"


template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field

    void addEdge(Vertex<T> *dest, double w);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);

};


#endif //AED2324_PRJ2_G109_VERTEX_H
