//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include <iostream>
#include "Manager.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <limits>

Manager::Manager() {
    this->parser = Parser();
    this->connections = parser.getGraph();
    this->airports = parser.getAirports();
    this->airlines = parser.getAirlines();
    this->cityAirports = parser.getCityAirports();
    this->countryCities = parser.getCountryCities();
    this->airportsByName = parser.getAirportsByName();
    this->airlinesByName = parser.getAirlinesByName();
}

unordered_map<std::string, Airline*> Manager::getAirlines() {
    return this->airlines;
}

unordered_map<string, Airport*> Manager::getAirports() {
    return this->airports;
}

Airport* Manager::getAirport(const std::string &code) const {
    auto it = airports.find(code);

    if (it != airports.end()) {
        return it->second;
    }

    return nullptr;
}

Airline* Manager::getAirline(const std::string &code) const {
    auto it = airlines.find(code);

    if (it != airlines.end()) {
        return it->second;
    }

    return nullptr;
}


bool Manager::hasConnection(const string &s, const string &t) {
    auto source = connections.findVertex(getAirport(s));
    auto target = connections.findVertex(getAirport(t));

    for (auto n : connections.getVertexSet()) {
        n->setVisited(false);
    }

    return dfsVisitBool(source, target);
}

bool Manager::dfsVisitBool(Vertex *v, Vertex *t) {
    v->setVisited(true);

    if (v == t) return true;

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();

        if (!dest->isVisited()) {
            if (dfsVisitBool(dest, t)) return true;
        }
    }
    return false;
}


vector<Vertex*> Manager::airportsAtDistanceK(const string &source, int k) {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }

    auto s = getAirport(source);

    auto depart = connections.findVertex(s);
    depart->setVisited(true);

    queue<Vertex*> q;
    q.push(depart);
    vector<Vertex*> res;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            auto next = q.front();
            q.pop();


            for (auto &edge : next->getAdj()) {
                auto w = edge.getDest();

                if (!w->isVisited()) {
                    if (k - 1 == 0) {
                        res.push_back(w);
                    }
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
        k--;
    }
    return res;
}

void Manager::articulationPoints() {
    for (auto &airport : connections.getVertexSet()) {
        airport->setProcessing(false);
        airport->setNum(-1);
        airport->setLow(-1);
    }

    vector<Airport> res;
    stack<Airport> s;
    int i = 0;

    for (auto &airport : connections.getVertexSet()) {
        if (airport->getNum() == -1) {
            dfsApp(airport, s, res, i);
        }
    }
    int maxLengthName = 0;
    for (auto& elem : res) {
        if (elem.getName().length() > maxLengthName) maxLengthName = elem.getName().length();
    }
    int space = maxLengthName + 8 > 35 ? maxLengthName + 8 : 35;
    int lenEssentialAirportsLabel = (space - 33) / 2;
    int lenFEssentialAirportsLabel = (space - 33) % 2 == 0 ? lenEssentialAirportsLabel : lenEssentialAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenEssentialAirportsLabel, ' ') << "Essential Airports to the network" << string(lenFEssentialAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : res) {
        cout << "| Code: " << elem.getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem.getName() << string(space - 7 - elem.getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Manager::dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i) {
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());
    v->setProcessing(true);
    int child = 0;

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();
        if (dest->getNum() == -1) {
            child++;
            dfsApp(dest, s, res, i);
            v->setLow(min(v->getLow(), dest->getLow()));

            if (dest->getLow() >= v->getNum() && v->getNum() != 0) {
                res.push_back(dest->getInfo());
            }
        }
        else if (dest->isProcessing()) {
            v->setLow(min(v->getLow(), dest->getNum()));
        }
        if (child > 1 && v->getNum() == 0) {
            res.push_back(v->getInfo());
        }
    }
    v->setProcessing(false);
    s.pop();
}

bool hasAirline(Edge &e, vector<Airline*> &air) {
    for (auto &airline : air) {
        if (e.hasAirline(airline)) {
            return true;
        }
    }
    return false;
}


vector<Airport> Manager::hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines) {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    vector<Airport> res;
    queue<Vertex*> q;

    auto init = connections.findVertex(source);
    q.push(init);

    while (!q.empty()) {
        auto next = q.front();
        q.pop();
        next->setVisited(true);

        for (auto edge : next->getAdj()) {
            if (hasAirline(edge, setOfAirlines)) {
                auto dest = edge.getDest();
                if (!dest->isVisited()) {
                    q.push(dest);
                }
            }
        }
    }
    return res;
}

vector<vector<Airport>> Manager::scc() {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
        airport->setProcessing(false);
    }

    vector<vector<Airport>> res;
    stack<Airport> s;

    int i = 0;
    for (auto &airport : connections.getVertexSet()) {
        if (!airport->isVisited()) {
            dfsScc(airport, s, res, i);
        }
    }

    return res;

}

void Manager::dfsScc(Vertex *v, stack<Airport> &s, vector<vector<Airport>> &res, int &i) {
    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    v->setVisited(true);
    i++;
    s.push(v->getInfo());

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();

        if (!dest->isVisited()) {
            dfsScc(dest, s, res, i);

            v->setLow(min(v->getLow(), dest->getLow()));
        }
        else if (dest->isProcessing()) {
            v->setLow(min(v->getLow(), dest->getNum()));
        }
    }

    v->setProcessing(false);

    vector<Airport> scc;
    if (v->getNum() == v->getLow()) {
        while (!s.empty() && s.top().getCode() != v->getInfo().getCode()){
            scc.push_back(s.top());
            s.pop();
        }
        if (!s.empty()) {
            scc.push_back(s.top());
            s.pop();
        }

        if (scc.size() >= 1) {
            res.push_back(scc);
        }
    }
}

void Manager::DFS(Vertex* current, Vertex *destination, int maxFlights, vector<Airport>& currentPath,
                  vector<vector<Airport>>& allPaths) {
    if (current == destination) {
        allPaths.push_back(currentPath);
        return;
    }

    if (maxFlights == 0 ) return;

    current->setVisited(true);

    for (Edge& flight : current->getAdj()) {
        Vertex* neighbor = flight.getDest();

        if (!neighbor->isVisited()) {
            currentPath.push_back(neighbor->getInfo());
            DFS(neighbor, destination, maxFlights - 1, currentPath, allPaths);
            currentPath.pop_back();
        }
    }

    current->setVisited(false);
}

vector<vector<Airport>> Manager::pathMaximumConnectionFlights(const string& startAirport, const string& destination, int maxFlights) {
    for (auto& node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    Vertex* start = connections.findVertex(getAirport(startAirport));
    Vertex* end = connections.findVertex(getAirport(destination));

    std::vector<std::vector<Airport>> allPaths;
    std::vector<Airport> currentPath;

    currentPath.push_back(start->getInfo());
    DFS(start, end, maxFlights, currentPath, allPaths);

    return allPaths;
}



vector<Edge> Manager::getOutFlights(const string &code) const {
    auto v = getAirport(code);


    if (v == nullptr) return {};

    auto vertex = connections.findVertex(v);
    if (vertex == nullptr) return {};

    return vertex->getAdj();
}

void Manager::getNumAirportsAndFlights() const {
    int numAirports = airports.size();
    int numFlights = 0;
    for (auto& elem : connections.getVertexSet()) {
        numFlights += elem->getInfo().getNumFlightsOut();
    }
    int space = numFlights > numAirports ? to_string(numFlights).length() + 2  : to_string(numAirports).length() + 2;
    int lenAirports = (space - to_string(numAirports).length()) / 2;
    int lenFAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenAirports : lenAirports + 1;
    int lenFlights = (space - to_string(numFlights).length()) / 2;
    int lenFFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenFlights : lenFlights + 1;
    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "| Number of airports |" << string(lenAirports, ' ') << numAirports << string(lenFAirports, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenFlights, ' ') << numFlights << string(lenFFlights, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}

void Manager::getNumFlightsAndAirlines(const string &airportCode) const {
    auto airport = airports.find(airportCode);
    int numFlights = airport->second->getNumFlightsOut();
    int numAirlines = 0;
    for (auto &elem : connections.getVertexSet()) {
        if (*airport->second == elem->getInfo()) {
            set<Airline*> air;
            for (auto& edge : elem->getAdj()) {
                for (auto& airline : edge.getAirlines()) {
                    air.emplace(airline);
                }
            }
            numAirlines = air.size();
            break;
        }
    }
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    int lenNumAirlines = (space - to_string(numAirlines).length()) / 2;
    int lenFNumAirlines = (space - to_string(numAirlines).length()) % 2 == 0 ? lenNumAirlines : lenNumAirlines + 1;

    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airport Code    |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|    Airport Name    |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "| Number of airlines |" << string(lenNumAirlines, ' ') << numAirlines << string(lenFNumAirlines, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}
void Manager::getNumFlightsAndAirlinesByName(const string &airportName) const {
    auto airport = airportsByName.find(airportName);
    int numFlights = airport->second->getNumFlightsOut();
    int numAirlines = 0;
    for (auto &elem : connections.getVertexSet()) {
        if (*airport->second == elem->getInfo()) {
            set<Airline*> air;
            for (auto& edge : elem->getAdj()) {
                for (auto& airline : edge.getAirlines()) {
                    air.emplace(airline);
                }
            }
            numAirlines = air.size();
            break;
        }
    }
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airport->second->getCode().length()) / 2;
    int lenFAirportCode = (space - airport->second->getCode().length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airportName.length()) / 2;
    int lenFAirportName = (space - airportName.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    int lenNumAirlines = (space - to_string(numAirlines).length()) / 2;
    int lenFNumAirlines = (space - to_string(numAirlines).length()) % 2 == 0 ? lenNumAirlines : lenNumAirlines + 1;

    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airport Code    |" << string(lenAirportCode, ' ') << airport->second->getCode() << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|    Airport Name    |" << string(lenAirportName, ' ') << airportName << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "| Number of airlines |" << string(lenNumAirlines, ' ') << numAirlines << string(lenFNumAirlines, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}

void Manager::getNumFlightsPerCity(const string &city) const {
    int numFlights = 0;
    for (auto& elem : connections.getVertexSet()) {
        if (elem->getInfo().getCity() == city) {
            numFlights += elem->getInfo().getNumFlightsOut();
            numFlights += elem->getInfo().getNumFlightsIn();
        }
    }
    int space = city.length() > to_string(numFlights).length() ? city.length() + 2: to_string((numFlights)).length() + 2;
    int lenCity = (space - city.length()) / 2;
    int lenFCity = (space - city.length()) % 2 == 0 ? lenCity : lenFCity + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    cout << "---------------------" << string(space + 1, '-') << endl;
    cout << "|       City        |" << string(lenCity, ' ') << city << string (lenFCity, ' ') << '|' << endl;
    cout << "| Number of flights |" << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '|' << endl;
    cout << "---------------------" << string(space + 1, '-') << endl;
}

void Manager::getNumFlightsPerAirline(const string &airlineCode) const {
    auto airline = airlines.find(airlineCode);
    int numFlights = airline->second->getNumFlights();
    int space = airline->second->getName().length() > to_string(numFlights).length() ? airline->second->getName().length() + 2: to_string((numFlights)).length() + 2;
    int lenAirlineCode = (space - airlineCode.length()) / 2;
    int lenFAirlineCode = (space - airlineCode.length()) % 2 == 0 ? lenAirlineCode : lenAirlineCode + 1;
    int lenAirlineName = (space - airline->second->getName().length()) / 2;
    int lenFAirportName = (space - airline->second->getName().length()) % 2 == 0 ? lenAirlineName : lenAirlineName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airline code    |" << string(lenAirlineCode, ' ') << airlineCode << string(lenFAirlineCode, ' ') << '|' << endl;
    cout << "|    Airline name    |" << string(lenAirlineName, ' ') << airline->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}
void Manager::getNumFlightsPerAirlineByName(const string &airlineName) const {
    auto airline = airlinesByName.find(airlineName);
    int numFlights = airline->second->getNumFlights();
    int space = airline->second->getName().length() > to_string(numFlights).length() ? airline->second->getName().length() + 2: to_string((numFlights)).length() + 2;
    int lenAirlineCode = (space - airline->second->getCode().length()) / 2;
    int lenFAirlineCode = (space - airline->second->getCode().length()) % 2 == 0 ? lenAirlineCode : lenAirlineCode + 1;
    int lenAirlineName = (space - airlineName.length()) / 2;
    int lenFAirportName = (space - airlineName.length()) % 2 == 0 ? lenAirlineName : lenAirlineName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airline code    |" << string(lenAirlineCode, ' ') << airline->second->getCode() << string(lenFAirlineCode, ' ') << '|' << endl;
    cout << "|    Airline name    |" << string(lenAirlineName, ' ') << airlineName << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}

void Manager::getCountriesCanFlyToAirport(const string &airportCode) const {
    auto airport = airports.find(airportCode);
    vector<Edge> edges = getOutFlights(airportCode);
    set<string> countries;
    for (auto& edge : edges) {
        countries.emplace(edge.getDest()->getInfo().getCountry());
    }
    int numCountries = countries.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
    cout << "|            Airport Code            |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|            Airport Name            |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Countries you can fly to |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
}
void Manager::getCountriesCanFlyToAirportByName(const string &airportName) const {
    auto airport = airportsByName.find(airportName);
    vector<Edge> edges = getOutFlights(airportName);
    set<string> countries;
    for (auto& edge : edges) {
        countries.emplace(edge.getDest()->getInfo().getCountry());
    }
    int numCountries = countries.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airport->second->getCode().length()) / 2;
    int lenFAirportCode = (space - airport->second->getCode().length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airportName.length()) / 2;
    int lenFAirportName = (space - airportName.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
    cout << "|            Airport Code            |" << string(lenAirportCode, ' ') << airport->second->getCode().length() << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|            Airport Name            |" << string(lenAirportName, ' ') << airportName << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Countries you can fly to |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
}


void Manager::getCountriesCanFlyToCity(const string &city) const {
    set<string> countries;
    for (auto& elem : connections.getVertexSet()) {
        if (elem->getInfo().getCity() == city) {
            for (auto& edge : elem->getAdj()) {
                countries.emplace(edge.getDest()->getInfo().getCountry());
            }
        }
    }
    int numCountries = countries.size();
    int space = city.length() > 7 ? city.length() + 2: 7;
    int lenCity = (space - city.length()) / 2;
    int lenFCity = (space - city.length()) % 2 == 0 ? lenCity : lenFCity + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
    cout << "|                City                |" << string(lenCity, ' ') << city << string(lenFCity, ' ') << '|' << endl;
    cout << "| Number of Countries you can fly to |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
}

bool notIn(vector<Airport> &v, const Airport &t) {
    for (auto &it : v) {
        if (it == t) return false;
    }
    return true;
}


vector<Airport> Manager::bfsMinConnections(const string &s, const string &t) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    auto first = connections.findVertex(getAirport(s));
    auto last = connections.findVertex(getAirport(t));

    vector<Airport> path;

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);

    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();

        for (Edge& flight : current->getAdj()) {
            Vertex* neighbor = flight.getDest();

            if (!neighbor->isVisited()) {
                q.push(neighbor);
                neighbor->setVisited(true);
                parent[neighbor] = current;

                if (neighbor == last) {
                    break;
                }
            }
        }
    }

    Vertex* current = last;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }
    return path;
}

vector<Airport> Manager::findShortestPath(const string &u, const string &v) {
    unordered_map<Vertex*, int> distances;
    for (Vertex* vertex : connections.getVertexSet()) {
        distances[vertex] = numeric_limits<int>::max();
        vertex->setVisited(false);
    }

    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<>> pq;


    Vertex* sourceAirport = connections.findVertex(getAirport(u));
    Vertex* targetAirport = connections.findVertex(getAirport(v));


    if (!sourceAirport || !targetAirport) {
        cerr << "Source or target airport not found." << endl;
        return {};
    }

    distances[sourceAirport] = 0;
    pq.emplace(0, sourceAirport);

    unordered_map<Vertex*, Vertex*> parent;

    while (!pq.empty()) {
        Vertex* current = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distances[current]) {
            continue;
        }

        for (Edge& flight : current->getAdj()) {
            Vertex* neighbor = flight.getDest();

            if (!neighbor->isVisited()) {
                int weight = flight.getWeight();

                int newDistance = currentDistance + weight;

                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.push({newDistance, neighbor});
                    parent[neighbor] = current;
                }
            }
        }
    }

    vector<Airport> path;
    Vertex* current = targetAirport;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }

    return path;
}

bool excludeCountries(Vertex* v, vector<string> &countries) {
    for (const auto& country : countries) {
        if (v->getInfo().getCountry() == country) {
            return true;
        }
    }
    return false;
}


double Manager::getTripDistance(const vector<string> &trip) {
    double res = 0.0;

    auto it = trip.begin();
    string first = *it;

    it++;
    while (it != trip.end()) {
        res += getDistance(first, *it);
        it++;
    }
    return res;
}

double Manager::getDistance(const string &u, const string &v) {
    auto p = findShortestPath(u, v);

    auto it = p.begin();
    double dist = 0.0;

    while (it != p.end()) {
        auto source = connections.findVertex(getAirport(it->getCode()));

        if (source) {
            auto nextIt = std::next(it);

            if (nextIt != p.end()) {
                for (auto &edge : source->getAdj()) {
                    if (edge.getDest()->getInfo().getCode() == nextIt->getCode()) {
                        dist += edge.getWeight();
                        break;
                    }
                }
            } else {
                break;
            }

            it = nextIt;
        } else {
            break;
        }
    }
    return dist;
}

vector<Airport> Manager::scheduleTripMinDistance(const string &u, const string &v, vector<string> & visit) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    vector<Airport> res;

    visit.push_back(v);
    string first = u;

    for (auto &country : visit) {
        auto min_dist = findShortestPath(first, country);

        for (auto &c : min_dist) {
            if (std::find(res.begin(), res.end(),c) == res.end())
            res.push_back(c);
        }

        first = country;
    }

    auto min_dist = findShortestPath(first, v);

    for (auto &c : min_dist) {
        if (std::find(res.begin(), res.end(),c) == res.end())
        res.push_back(c);
    }

    return res;
}

vector<Airport> Manager::scheduleTripMinConnection(const string &u, const string &v, vector<string>& visit) {
    vector<Airport> path;


    visit.push_back(v);
    string p = u;

    for (auto &flight : visit) {

        auto res = bfsMinConnections(p, flight);

        for (auto &airport : res) {
            if (notIn(path, airport)) {
                path.push_back(airport);
            }
        }
        p = flight;
    }


    return path;
}

vector<Airport> Manager::findShortestPathExcludeCountries(const string &u, const string &v, vector<string> &countries) {
    unordered_map<Vertex*, int> distances;
    for (auto &node : connections.getVertexSet()) {
        distances[node] = numeric_limits<int>::max();
        if (!excludeCountries(node, countries)) {
            node->setVisited(false);
        }
        else {
            node->setVisited(true);
        }
    }

    auto depart = connections.findVertex(getAirport(u));
    auto arrival = connections.findVertex(getAirport(v));


    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<>> pq;


    Vertex* sourceAirport = connections.findVertex(getAirport(u));
    Vertex* targetAirport = connections.findVertex(getAirport(v));


    if (!sourceAirport || !targetAirport) {
        cerr << "Source or target airport not found." << endl;
        return {};
    }

    distances[sourceAirport] = 0;
    pq.emplace(0, sourceAirport);

    unordered_map<Vertex*, Vertex*> parent;

    while (!pq.empty()) {
        Vertex* current = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distances[current]) {
            continue;
        }

        for (Edge& flight : current->getAdj()) {
            Vertex* neighbor = flight.getDest();

            if (!neighbor->isVisited()) {
                int weight = flight.getWeight();

                int newDistance = currentDistance + weight;

                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.emplace(newDistance, neighbor);
                    parent[neighbor] = current;
                }
            }
        }
    }

    vector<Airport> path;
    Vertex* current = targetAirport;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }

    return path;
}

vector<Airport> Manager::findMinConnectionsExcludeCountries(const string &s, const string &t, vector<string> & countries) {
    for (auto node : connections.getVertexSet()) {
        if (excludeCountries(node, countries)) {
            node->setVisited(true);
        }
        else {
            node->setVisited(false);
        }
    }

    auto first = connections.findVertex(getAirport(s));
    auto last = connections.findVertex(getAirport(t));

    vector<Airport> path;

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);

    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();

        for (Edge& flight : current->getAdj()) {
            Vertex* neighbor = flight.getDest();

            if (!neighbor->isVisited()) {
                q.push(neighbor);
                neighbor->setVisited(true);
                parent[neighbor] = current;

                if (neighbor == last) {
                    break;
                }
            }
        }
    }

    Vertex* current = last;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }
    return path;
}

unordered_map<string, int> Manager::outFlightsPerAirport(const string &s) {
    unordered_map<string, int> res;

    auto airport = connections.findVertex(getAirport(s));

    for (auto &a : airport->getAdj()) {
        auto flights = a.getAirlines();
        for (auto airline : flights) {
            auto it = res.find(airline->getName());

            if (it == res.end()) {
                res.insert({airline->getName(), 1});
            }
            else {
                it->second++;
            }
        }
    }

    return res;
}

unordered_map<string, int> Manager::inFlightsPerAirport(const string &d) {
    unordered_map<string, int> res;

    auto airport = connections.findVertex(getAirport(d));

    for (auto &node : connections.getVertexSet()) {
        if (node == airport) continue;

        for (auto &flight : node->getAdj()) {
            if (flight.getDest() == airport) {

                for (auto &airline : flight.getAirlines()) {
                    auto it = res.find(airline->getName());

                    if (it == res.end()) {
                        res.insert({airline->getName(), 1});
                    }
                    else {
                        it->second++;
                    }
                }
            }
        }
    }
    return res;
}

vector<Airport*> Manager::getAiportsPerCity(const string& city) {
    auto it = cityAirports.find(city);

    if (it != cityAirports.end()) return it->second;

    return {};
}

unordered_set<string> Manager::getCitiesPerCountry(const string& c) {
    auto it = countryCities.find(c);

    if (it != countryCities.end()) return it->second;

    return {};
}

vector<Airport*> Manager::getAirportsPerCountry(const string &c) {
    auto cities = this->getCitiesPerCountry(c);

    vector<Airport*> res;

    if (!cities.empty()) {
        for (auto &city : cities) {
            auto air = this->getAiportsPerCity(city);

            if (!air.empty()) {
                res.insert(res.end(), make_move_iterator(air.begin()), make_move_iterator(air.end()));
            }
        }
    }

    return res;
}
void Manager::getDestinantionsDistance1(const string &airportCode) const {
    auto airport = airports.find(airportCode);
    auto depart = connections.findVertex(airport->second);
    set<string> countries;
    set<string> cities;
    for (auto &elem : depart->getAdj()) {
        countries.emplace(elem.getDest()->getInfo().getCountry());
        cities.emplace(elem.getDest()->getInfo().getCity());
    }
    int numAirports = depart->getAdj().size();
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
    cout << "|          Airport Code           |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|          Airport Name           |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of destination Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of destination Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of destination Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
}
void Manager::getDestinationsDistance1ByName(const string &airportName) const {
    auto airport = airportsByName.find(airportName);
    auto depart = connections.findVertex(airport->second);
    set<string> countries;
    set<string> cities;
    for (auto &elem : depart->getAdj()) {
        countries.emplace(elem.getDest()->getInfo().getCountry());
        cities.emplace(elem.getDest()->getInfo().getCity());
    }
    int numAirports = depart->getAdj().size();
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airport->second->getCode().length()) / 2;
    int lenFAirportCode = (space - airport->second->getCode().length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airportName.length()) / 2;
    int lenFAirportName = (space - airportName.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
    cout << "|          Airport Code           |" << string(lenAirportCode, ' ') << airport->second->getCode() << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|          Airport Name           |" << string(lenAirportName, ' ') << airportName << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of destination Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of destination Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of destination Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
}

void Manager::getDestinantions(const string &airportCode) const {
    vector<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    auto airport = airports.find(airportCode);
    auto depart = connections.findVertex(airport->second);

    queue<Vertex*> q;
    depart->setVisited(true);
    for (auto& edge : depart->getAdj()) {
        q.push(edge.getDest());
        edge.getDest()->setVisited(true);
    }

    while (!q.empty()) {
        Vertex *currentVertex = q.front();
        q.pop();
        air.push_back(currentVertex->getInfo().getCode());
        countries.emplace(currentVertex->getInfo().getCountry());
        cities.emplace(currentVertex->getInfo().getCity());
        for (auto& edge : currentVertex->getAdj()) {
            Vertex *neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                q.push(neighbor);
                neighbor->setVisited(true);
            }
        }
    }
    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
    cout << "|         Airport Code          |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|         Airport Name          |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Reachable Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of Reachable Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of Reachable Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
}
void Manager::getDestinantionsByName(const string &airportName) const {
    vector<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    auto airport = airportsByName.find(airportName);
    auto depart = connections.findVertex(airport->second);

    queue<Vertex*> q;
    depart->setVisited(true);
    for (auto& edge : depart->getAdj()) {
        q.push(edge.getDest());
        edge.getDest()->setVisited(true);
    }

    while (!q.empty()) {
        Vertex *currentVertex = q.front();
        q.pop();
        air.push_back(currentVertex->getInfo().getCode());
        countries.emplace(currentVertex->getInfo().getCountry());
        cities.emplace(currentVertex->getInfo().getCity());
        for (auto& edge : currentVertex->getAdj()) {
            Vertex *neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                q.push(neighbor);
                neighbor->setVisited(true);
            }
        }
    }
    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airport->second->getCode().length()) / 2;
    int lenFAirportCode = (space - airport->second->getCode().length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airportName.length()) / 2;
    int lenFAirportName = (space - airportName.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
    cout << "|         Airport Code          |" << string(lenAirportCode, ' ') << airport->second->getCode() << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|         Airport Name          |" << string(lenAirportName, ' ') << airportName << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Reachable Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of Reachable Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of Reachable Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
}

void Manager::getDestinantionsUntilDistanceK(const string &airportCode, const int &k) const {
    vector<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    auto airport = airports.find(airportCode);
    auto depart = connections.findVertex(airport->second);

    queue<pair<Vertex*, int>> q;
    depart->setVisited(true);
    for (auto& edge : depart->getAdj()) {
        q.push({edge.getDest(), 1});
        edge.getDest()->setVisited(true);
    }

    while (!q.empty()) {
        Vertex *currentVertex = q.front().first;
        int n = q.front().second;
        q.pop();
        if (n <= k) {
            air.push_back(currentVertex->getInfo().getCode());
            countries.emplace(currentVertex->getInfo().getCountry());
            cities.emplace(currentVertex->getInfo().getCity());
        }
        else break;
        for (auto& edge : currentVertex->getAdj()) {
            Vertex *neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                q.push({neighbor, n + 1});
                neighbor->setVisited(true);
            }
        }
    }
    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
    cout << "|         Airport Code          |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|         Airport Name          |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Reachable Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of Reachable Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of Reachable Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
}
void Manager::getDestinantionsUntilDistanceKByName(const string &airportName, const int &k) const {
    vector<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    auto airport = airportsByName.find(airportName);
    auto depart = connections.findVertex(airport->second);

    queue<pair<Vertex*, int>> q;
    depart->setVisited(true);
    for (auto& edge : depart->getAdj()) {
        q.push({edge.getDest(), 1});
        edge.getDest()->setVisited(true);
    }

    while (!q.empty()) {
        Vertex *currentVertex = q.front().first;
        int n = q.front().second;
        q.pop();
        if (n <= k) {
            air.push_back(currentVertex->getInfo().getCode());
            countries.emplace(currentVertex->getInfo().getCountry());
            cities.emplace(currentVertex->getInfo().getCity());
        }
        else break;
        for (auto& edge : currentVertex->getAdj()) {
            Vertex *neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                q.push({neighbor, n + 1});
                neighbor->setVisited(true);
            }
        }
    }
    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airport->second->getCode().length()) / 2;
    int lenFAirportCode = (space - airport->second->getCode().length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airportName.length()) / 2;
    int lenFAirportName = (space - airportName.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
    cout << "|         Airport Code          |" << string(lenAirportCode, ' ') << airport->second->getCode() << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|         Airport Name          |" << string(lenAirportName, ' ') << airportName << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Reachable Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of Reachable Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of Reachable Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
}

void Manager::findComponentDiameterPairs(Vertex *origin, vector<pair<Airport, Airport>> &result, int &i) const {
    queue<pair<Vertex *, int>> q;
    origin->setVisited(true);
    q.emplace(origin, 0);


    while (!q.empty()) {
        auto [v, distance] = q.front();
        q.pop();

        if (distance == i) {
            result.emplace_back(origin->getInfo(), v->getInfo());
        }
        else if (distance > i) {
            i = distance;
            result.clear();
        }

        for (auto& e : v->getAdj()) {
            Vertex *w = e.getDest();
            if (!w->isVisited()) {
                w->setVisited(true);
                q.emplace(w, distance + 1);
            }
        }
    }


    for (auto vertex : connections.getVertexSet()) {
        vertex->setVisited(false);
    }
}


void Manager::diameterPairs() const {
    vector<pair<Airport, Airport>> result;
    int maxDiameter = 0;
    int maxNameLength = 0;
    for (auto &elem : connections.getVertexSet()) {
        findComponentDiameterPairs(elem, result, maxDiameter);
    }
    for (auto& elem : result) {
        int maxLength = max(elem.first.getName().length(), elem.second.getName().length());
        if (maxLength > maxNameLength) maxNameLength = maxLength;
    }
    int space = maxNameLength + 8 > 22 ? maxNameLength + 8 : 22;
    int lenSourceAirportsLabel = (space - 15) / 2;
    int lenFSourceAirportsLabel = (space - 15) % 2 == 0 ? lenSourceAirportsLabel : lenSourceAirportsLabel + 1;
    int lenDestAirportsLabel = (space - 21) / 2;
    int lenFDestAirportsLabel = (space - 21) % 2 == 0 ? lenDestAirportsLabel : lenDestAirportsLabel + 1;
    cout << string(space * 2 + 3, '-') << endl;
    cout << '|' << string(lenSourceAirportsLabel, ' ') << "Source Airports" << string (lenFSourceAirportsLabel, ' ') << "| " << string(lenDestAirportsLabel, ' ') << "Destination Airports" << string(lenFDestAirportsLabel, ' ') << '|' << endl;
    cout << string(space * 2 + 3, '-') << endl;
    for (auto& elem : result) {
        cout << "| Code: " << elem.first.getCode() << string(space - 10, ' ') << "| Code: " << elem.second.getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem.first.getName() << string(space - 7 - elem.first.getName().length(), ' ') << "| Name: " << elem.second.getName() << string(space - 7 - elem.second.getName().length(), ' ') << '|' << endl;
        cout << string(space * 2 + 3, '-') << endl;
    }
    cout << "The maximum trip between two airports has " << maxDiameter << " stops." << endl;
}
auto comparatorAirport = [](Airport *a, Airport *b) {
    int trafficA = a->getNumFlightsIn() + a->getNumFlightsOut();
    int trafficB = b->getNumFlightsIn() + b->getNumFlightsOut();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA > trafficB;
};

void Manager::getTopKGreatestTrafficAirport(int k) const {
    set<Airport *, decltype(comparatorAirport)> airportsByTraffic(comparatorAirport);
    int nameSize = 0;
    for (auto& elem : airports) {
        if (elem.second->getName().length() > nameSize) nameSize = elem.second->getName().length();
        airportsByTraffic.insert(elem.second);
    }
    int space1 = nameSize + 8 ? nameSize + 8 : 10;
    int lenAirportsLabel = (space1 - 8) / 2;
    int lenFAirportsLabel = (space1 - 8) % 2 == 0 ? lenAirportsLabel : lenAirportsLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenAirportsLabel, ' ') << "Airports" << string (lenFAirportsLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : airportsByTraffic) {
        int numFlights = elem->getNumFlightsOut() + elem->getNumFlightsIn();
        int lenNumFlights = (19 - to_string(numFlights).length()) / 2;
        int lenFNumFlights = (19 - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| Code: " << elem->getCode() << string(space1 - 10, ' ') << "|                   |" << endl;
        cout << string(space1 + 1, ' ') << '-' << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '-' << endl;
        cout << "| Name: " << elem->getName() << string(space1 - 8 - elem->getName().length(), ' ') <<" |                   |" << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
        k--;
        if (k == 0) return;
    }
}
void Manager::getTopKGreatestTrafficAirportPerCountry(int k, const string &country) const {
    set<Airport *, decltype(comparatorAirport)> airportsByTraffic(comparatorAirport);
    int nameSize = 0;
    for (auto& elem : airports) {
        if (elem.second->getCountry() == country) {
            if (elem.second->getName().length() > nameSize) nameSize = elem.second->getName().length();
            airportsByTraffic.insert(elem.second);
        }
    }
    int space1 = nameSize + 8 ? nameSize + 8 : 10;
    int lenAirportsLabel = (space1 - 8) / 2;
    int lenFAirportsLabel = (space1 - 8) % 2 == 0 ? lenAirportsLabel : lenAirportsLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenAirportsLabel, ' ') << "Airports" << string (lenFAirportsLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : airportsByTraffic) {
        int numFlights = elem->getNumFlightsOut() + elem->getNumFlightsIn();
        int lenNumFlights = (19 - to_string(numFlights).length()) / 2;
        int lenFNumFlights = (19 - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| Code: " << elem->getCode() << string(space1 - 10, ' ') << "|                   |" << endl;
        cout << string(space1 + 1, ' ') << '-' << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '-' << endl;
        cout << "| Name: " << elem->getName() << string(space1 - 8 - elem->getName().length(), ' ') <<" |                   |" << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
        k--;
        if (k == 0) return;
    }
}

auto comparatorAirline = [](Airline *a, Airline *b) {
    int trafficA = a->getNumFlights();
    int trafficB = b->getNumFlights();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA > trafficB;
};

void Manager::getTopKGreatestTrafficAirline(int k) const {
    set<Airline *, decltype(comparatorAirline)> airlinesByTraffic(comparatorAirline);
    int nameSize = 0;
    for (auto& elem : airlines) {
        if (elem.second->getName().length() > nameSize) nameSize = elem.second->getName().length();
        airlinesByTraffic.insert(elem.second);
    }
    int space1 = nameSize + 8 > 10 ? nameSize + 8 : 10;
    int lenAirlinesLabel = (space1 - 8) / 2;
    int lenFAirlinesLabel = (space1 - 8) % 2 == 0 ? lenAirlinesLabel : lenAirlinesLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenAirlinesLabel, ' ') << "Airlines" << string (lenFAirlinesLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : airlinesByTraffic) {
        int numFlights = elem->getNumFlights();
        int lenNumFlights = (19 - to_string(numFlights).length()) / 2;
        int lenFNumFlights = (19 - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| Code: " << elem->getCode() << string(space1 - 10, ' ') << "|                   |" << endl;
        cout << string(space1 + 1, ' ') << '-' << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '-' << endl;
        cout << "| Name: " << elem->getName() << string(space1 - 8 - elem->getName().length(), ' ') <<" |                   |" << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
        k--;
        if (k == 0) return;
    }
}

void Manager::getTopKGreatestTrafficAirlinePerCountry(int k, const string &country) const {
    set<Airline *, decltype(comparatorAirline)> airlinesByTraffic(comparatorAirline);
    int nameSize = 0;
    for (auto& elem : airlines) {
        if (elem.second->getCountry() == country) {
            if (elem.second->getName().length() > nameSize) nameSize = elem.second->getName().length();
            airlinesByTraffic.insert(elem.second);
        }
    }
    int space1 = nameSize + 8 > 10 ? nameSize + 8 : 10;
    int lenAirlinesLabel = (space1 - 8) / 2;
    int lenFAirlinesLabel = (space1 - 8) % 2 == 0 ? lenAirlinesLabel : lenAirlinesLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenAirlinesLabel, ' ') << "Airlines" << string (lenFAirlinesLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : airlinesByTraffic) {
        int numFlights = elem->getNumFlights();
        int lenNumFlights = (19 - to_string(numFlights).length()) / 2;
        int lenFNumFlights = (19 - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| Code: " << elem->getCode() << string(space1 - 10, ' ') << "|                   |" << endl;
        cout << string(space1 + 1, ' ') << '-' << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '-' << endl;
        cout << "| Name: " << elem->getName() << string(space1 - 8 - elem->getName().length(), ' ') <<" |                   |" << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
        k--;
        if (k == 0) return;
    }
}

void Manager::listAiportsPerCountry(const string &country) const{

    int maxLengthName = 0;
    vector<Airport *> res;
    for (auto& elem : airportsByName) {
        if (elem.second->getCountry() == country) {
            if (elem.first.length() > maxLengthName) maxLengthName = elem.first.length();
            res.push_back(elem.second);
        }
    }
    int space = maxLengthName + 8 > 40 ? maxLengthName + 8 : 40;
    int lenEssentialAirportsLabel = (space - 12 - country.length()) / 2;
    int lenFEssentialAirportsLabel = (space - 12 - country.length()) % 2 == 0 ? lenEssentialAirportsLabel : lenEssentialAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenEssentialAirportsLabel, ' ') << "Airports in " << country << string(lenFEssentialAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : res) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}
string nameToLower(const string& word) {
    string res;
    for (auto& ch : word) {
        res += tolower(ch);
    }
    return res;
}

void Manager::searchAirportsByName(const string &airportName) {
    if (airportName == "") {
        cout << "Invalid name." << endl;
        return;
    }
    vector<Airport *> res;
    int maxLengthName = 0;
    for (auto& airport : airportsByName) {
        if (nameToLower(airport.second->getName()).find(nameToLower(airportName)) != string::npos)  {
            if (airport.second->getName().length() > maxLengthName) maxLengthName = airport.second->getName().length();
            res.push_back(airport.second);
        }
    }
    if (res.empty()) {
        cout << "No airports with the name " << airportName << " were found." << endl;
        return;
    }
    int space = maxLengthName + 8 > 10 ? maxLengthName + 8 : 10;
    int lenAirportsLabel = (space - 8) / 2;
    int lenFAirportsLabel = (space - 8) % 2 == 0 ? lenAirportsLabel : lenAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenAirportsLabel, ' ') << "Airports" << string(lenAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : res) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Manager::searchAirlinesByName(const string &airlineName) {
    if (airlineName == "") {
        cout << "Invalid name." << endl;
        return;
    }
    vector<Airline *> res;
    int maxLengthName = 0;
    for (auto& airline : airlinesByName) {
        if (nameToLower(airline.second->getName()).find(nameToLower(airlineName)) != string::npos)  {
            if (airline.second->getName().length() > maxLengthName) maxLengthName = airline.second->getName().length();
            res.push_back(airline.second);
        }
    }
    if (res.empty()) {
        cout << "No airlines with the name " << airlineName << " were found." << endl;
        return;
    }
    int space = maxLengthName + 8 > 10 ? maxLengthName + 8 : 10;
    int lenAirlinesLabel = (space - 8) / 2;
    int lenFAirlinesLabel = (space - 8) % 2 == 0 ? lenAirlinesLabel : lenAirlinesLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenAirlinesLabel, ' ') << "AirLines" << string(lenFAirlinesLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : res) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Manager::printAirportInfo(const string& airportCode) {
    auto airport = airports.find(airportCode);
    int nameLength = airport->second->getName().length();
    int space = nameLength + 8 > 41 ? nameLength + 8 : 41;
    cout << string(space + 2, '-') << endl;
    cout << "| Code: " << airportCode << string(space - 10, ' ') << '|' << endl;
    cout << "| Name: " << airport->second->getName() << string(space - 7 - nameLength, ' ') << '|' << endl;
    cout << "| City: " << airport->second->getCity() << string(space - 7 - airport->second->getCity().length(), ' ') << '|' << endl;
    cout << "| Country: " << airport->second->getCountry() << string(space - 10 - airport->second->getCountry().length(), ' ') << '|' << endl;
    cout << "| Coordinates: " << '(' << to_string(airport->second->getLatitude()) << ", " << to_string(airport->second->getLongitude()) << ')' << string(space - 18 - to_string(airport->second->getLatitude()).length() - to_string(airport->second->getLongitude()).length(), ' ') << '|' << endl;
    cout << "| Number of Departures: " << airport->second->getNumFlightsOut() << string(space - 23 - to_string(airport->second->getNumFlightsOut()).length(), ' ') << '|' << endl;
    cout << "| Number of Arrivals: " << airport->second->getNumFlightsIn() << string(space - 21 - to_string(airport->second->getNumFlightsIn()).length(), ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
}

void Manager::printAirlineInfo(const string& airlineCode) {
    auto airline = airlines.find(airlineCode);
    int nameLength = airline->second->getName().length();
    int space = nameLength + 8 > 27 ? nameLength + 8 : 27;
    cout << string(space + 2, '-') << endl;
    cout << "| Code: " << airlineCode << string(space - 10, ' ') << '|' << endl;
    cout << "| Name: " << airline->second->getName() << string(space - 7 - nameLength, ' ') << '|' << endl;
    cout << "| Callsign: " << airline->second->getCallsign() << string(space - 11 - airline->second->getCallsign().length(), ' ') << '|' << endl;
    cout << "| Country: " << airline->second->getCountry() << string(space - 10 - airline->second->getCountry().length(), ' ') << '|' << endl;
    cout << "| Number of Flights: " << airline->second->getNumFlights() << string(space - 20 - to_string(airline->second->getNumFlights()).length(), ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
}

