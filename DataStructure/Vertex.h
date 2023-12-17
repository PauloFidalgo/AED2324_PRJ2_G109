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
class Airline;

class Vertex {
protected:
    Airport* airport;                // contents
    std::vector<Edge> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing; // auxiliary field
    int low;
    int num;

    void addEdge(Vertex *dest, double w);
    bool removeEdgeTo(Vertex *d);
public:
    Vertex(Airport* in);
    Airport getInfo() const;
    void setInfo(const Airport &in);
    int getLow() const;
    int getNum() const;
    void setLow(int low);
    void setNum(int num);
    bool isVisited() const;
    void setVisited(const bool &v);
    bool isProcessing() const;
    void setProcessing(const bool &p);
    const std::vector<Edge> &getAdj() const;
    std::vector<Edge> &getAdj();
    void setAdj(const std::vector<Edge> &destinations);
    void addAdj(Edge &destination, Airline* airline);
    bool hasFlight(const Airport *destination);
    friend class Graph;

};


#endif //AED2324_PRJ2_G109_VERTEX_H
