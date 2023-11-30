//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_PARSER_H
#define AED2324_PRJ2_G109_PARSER_H

#include <map>
#include <string>
#include "../DataModel/Airline.h"
#include "../DataStructure/Graph.h"

class Parser {
private:
    void readFlights(Graph &g) const;
public:
    Parser();
    std::map<std::string, Airline> readAirlines() const;
    Graph getGraph() const;
};


#endif //AED2324_PRJ2_G109_PARSER_H
