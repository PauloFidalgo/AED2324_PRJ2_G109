//
// Created by Wagner Pedrosa on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_VERTEX_H
#define AED2324_PRJ2_G109_VERTEX_H
#include "Edge.h"
#include <vector>
#include "../DataModel/Airport.h"

class Edge;
class Graph;
class Airport;

class Vertex {
protected:
    Airport airport;                // contents
    std::vector<Edge> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field

    void addEdge(Vertex *dest, double w);
    bool removeEdgeTo(Vertex *d);
public:
    Vertex(const Airport &in);
    Airport getInfo() const;
    void setInfo(const Airport &in);
    bool isVisited() const;
    void setVisited(const bool &v);
    bool isProcessing() const;
    void setProcessing(const bool &p);
    const std::vector<Edge> &getAdj() const;
    void setAdj(const std::vector<Edge> &destinations);
    void addAdj(Edge &destination, const std::string &airline);
    bool hasFlight(const Edge &destination);
    friend class Graph;

};


#endif //AED2324_PRJ2_G109_VERTEX_H
