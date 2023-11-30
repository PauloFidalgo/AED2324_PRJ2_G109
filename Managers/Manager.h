//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_MANAGER_H
#define AED2324_PRJ2_G109_MANAGER_H


#include "Parser.h"
#include "../DataStructure/Graph.h"
#include <map>
#include <string>
#include "../DataModel/Airline.h"


class Manager {
private:
    Parser parser;
    std::map<std::string, Airline*> airlines;
    std::map<std::string, Airport*> airports;
    Graph connections;

public:
    Manager();
    std::map<std::string, Airline*> getAirlines();
    std::map<std::string, Airport*> getAirports();
};


#endif //AED2324_PRJ2_G109_MANAGER_H
