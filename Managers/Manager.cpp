//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include <iostream>
#include "Manager.h"
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
    Viewer::printNumAirportsNumFlights(numAirports, numFlights);
}

void Manager::getNumFlightsAndAirlines(Airport *airport) const {
    int numFlights = airport->getNumFlightsOut();
    int numAirlines = 0;
    for (auto &elem : connections.getVertexSet()) {
        if (*airport == elem->getInfo()) {
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
    Viewer::printNumFlightsOutAndAirlines(airport->getCode(), airport->getName(), numFlights, numAirlines);
}

void Manager::getNumFlightsPerCity(const string &city) const {
    int numFlights = 0;
    vector<Airport*> air = getAirportsPerCity(city);
    for (auto& elem : air) {
        numFlights += elem->getNumFlightsOut();
        numFlights += elem->getNumFlightsIn();
    }
    Viewer::printNumFlightsPerCity(city, numFlights);
}

void Manager::getNumFlightsPerAirline(Airline *airline) const {
    int numFlights = airline->getNumFlights();
    Viewer::printNumFlightsPerAirline(airline->getCode(), airline->getName(), numFlights);
}

void Manager::getCountriesCanFlyToAirport(Airport *airport) const {
    vector<Edge> edges = getOutFlights(airport->getCode());
    set<string> countries;
    for (auto& edge : edges) {
        countries.emplace(edge.getDest()->getInfo().getCountry());
    }
    int numCountries = countries.size();
    Viewer::printCountriesAirportCanFlyTo(airport->getCode(), airport->getName(), numCountries);
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
    Viewer::printCountriesCityCanFlyTo(city,numCountries);
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

vector<Airport*> Manager::getAirportsPerCity(const string& city) const {
    auto it = cityAirports.find(city);

    if (it != cityAirports.end()) return it->second;

    return {};
}

unordered_set<string> Manager::getCitiesPerCountry(const string& c) const {
    auto it = countryCities.find(c);

    if (it != countryCities.end()) return it->second;

    return {};
}

vector<Airport*> Manager::getAirportsPerCountry(const string &c) const {
    auto cities = this->getCitiesPerCountry(c);

    vector<Airport*> res;

    if (!cities.empty()) {
        for (auto &city : cities) {
            auto air = this->getAirportsPerCity(city);

            if (!air.empty()) {
                res.insert(res.end(), make_move_iterator(air.begin()), make_move_iterator(air.end()));
            }
        }
    }

    return res;
}

void Manager::getAirportDestinantionsDistance1(Airport *airport) const {
    auto depart = connections.findVertex(airport);
    set<string> countries;
    set<string> cities;
    for (auto &elem : depart->getAdj()) {
        countries.emplace(elem.getDest()->getInfo().getCountry());
        cities.emplace(elem.getDest()->getInfo().getCity());
    }
    int numAirports = depart->getAdj().size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printAirportDestinationsDistance1(airport->getCode(), airport->getName(), numAirports, numCities, numCountries);
}

void Manager::getCityDestinationsDistance1(const string& city) const {
    vector<Airport *> air = getAirportsPerCity(city);
    set<string> airportCodes;
    set<string> countries;
    set<string> cities;
    for (const auto& elem : air) {
        auto depart = connections.findVertex(elem);
        for (auto &edge : depart->getAdj()) {
            if (edge.getDest()->getInfo().getCity() != city) {
                airportCodes.emplace(edge.getDest()->getInfo().getCode());
                countries.emplace(edge.getDest()->getInfo().getCountry());
                cities.emplace(edge.getDest()->getInfo().getCity());
            }
        }
    }
    int numAirports = airportCodes.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printCityDestinationsDistance1(city, numAirports, numCities, numCountries);
}
void Manager::getCountryDestinationsDistance1(const string& country) const {
    vector<Airport *> air = getAirportsPerCountry(country);
    set<string> airportCodes;
    set<string> countries;
    set<string> cities;
    for (const auto& elem : air) {
        auto depart = connections.findVertex(elem);
        for (auto &edge : depart->getAdj()) {
            if (edge.getDest()->getInfo().getCountry() != country) {
                airportCodes.emplace(edge.getDest()->getInfo().getCode());
                countries.emplace(edge.getDest()->getInfo().getCountry());
                cities.emplace(edge.getDest()->getInfo().getCity());
            }
        }
    }
    int numAirports = airportCodes.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printCountryDestinationsDistance1(country, numAirports, numCities, numCountries);
}

void Manager::getAirportDestinantions(Airport *airport) const {
    vector<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }

    auto depart = connections.findVertex(airport);

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
    Viewer::printAirportDestinations(airport->getCode(), airport->getName(), numAirports, numCities, numCountries);
}
void Manager::getCityDestinantions(const string& city) const {
    vector<Airport *> airportsCity = getAirportsPerCity(city);
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airportCity : airportsCity) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo().getCity() == city) airport->setVisited(true);
            else airport->setVisited(false);
        }

        auto depart = connections.findVertex(airportCity);

        queue<Vertex*> q;
        depart->setVisited(true);
        for (auto& edge : depart->getAdj()) {
            q.push(edge.getDest());
            edge.getDest()->setVisited(true);
        }

        while (!q.empty()) {
            Vertex *currentVertex = q.front();
            q.pop();
            air.emplace(currentVertex->getInfo().getCode());
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
    }

    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printCityDestinations(city, numAirports, numCities, numCountries);
}

void Manager::getCountryDestinantions(const string& country) const {
    vector<Airport *> airportsCountry = getAirportsPerCountry(country);
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airportCountry : airportsCountry) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo().getCountry() == country) airport->setVisited(true);
            else airport->setVisited(false);
        }

        auto depart = connections.findVertex(airportCountry);

        queue<Vertex*> q;
        depart->setVisited(true);
        for (auto& edge : depart->getAdj()) {
            q.push(edge.getDest());
            edge.getDest()->setVisited(true);
        }

        while (!q.empty()) {
            Vertex *currentVertex = q.front();
            q.pop();
            air.emplace(currentVertex->getInfo().getCode());
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
    }

    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printCountryDestinations(country, numAirports, numCities, numCountries);
}

void Manager::getAirportDestinantionsUntilDistanceK(Airport *airport, const int &k) const {
    vector<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    auto depart = connections.findVertex(airport);

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
    Viewer::printAirportDestinations(airport->getCode(), airport->getName(), numAirports, numCities, numCountries);
}

void Manager::getCityDestinantionsUntilDistanceK(const string& city, const int &k) const {
    vector<Airport *> airportsCity = getAirportsPerCity(city);
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto & airportCity : airportsCity) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo().getCity() == city) airport->setVisited(true);
            else airport->setVisited(false);
        }
        auto depart = connections.findVertex(airportCity);

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
                air.emplace(currentVertex->getInfo().getCode());
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
    }

    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printCityDestinations(city, numAirports, numCities, numCountries);
}

void Manager::getCountryDestinantionsUntilDistanceK(const string& country, const int &k) const {
    vector<Airport *> airportsCountry = getAirportsPerCountry(country);
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto & airportCountry : airportsCountry) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo().getCity() == country) airport->setVisited(true);
            else airport->setVisited(false);
        }
        auto depart = connections.findVertex(airportCountry);

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
                air.emplace(currentVertex->getInfo().getCode());
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
    }

    int numAirports = air.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printCountryDestinations(country, numAirports, numCities, numCountries);
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
    Viewer::printDiameterPairs(result, maxDiameter);
}
auto comparatorAirportDesc = [](Airport *a, Airport *b) {
    int trafficA = a->getNumFlightsIn() + a->getNumFlightsOut();
    int trafficB = b->getNumFlightsIn() + b->getNumFlightsOut();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA > trafficB;
};
auto comparatorAirportAsc = [](Airport *a, Airport *b) {
    int trafficA = a->getNumFlightsIn() + a->getNumFlightsOut();
    int trafficB = b->getNumFlightsIn() + b->getNumFlightsOut();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA < trafficB;
};

void Manager::getTopKGreatestTrafficAirport(int k, const bool& asc) const {
    auto comparator = asc ? comparatorAirportAsc : comparatorAirportDesc;
    set<Airport *, decltype(comparator)> airportsByTraffic(comparator);
    for (auto& elem : airports) {
        airportsByTraffic.insert(elem.second);
    }
    int nameSize = 0;
    vector<Airport *> air;
    for (auto &elem : airportsByTraffic) {
        if (elem->getName().length() > nameSize) nameSize = elem->getName().length();
        air.push_back(elem);
        k--;
        if (k == 0) break;
    }
    Viewer::printAirportGreatestTraffic(air, nameSize);
}

auto comparatorPairsDesc = [](const pair<string, int> &a, const pair<string, int> &b) {
    int trafficA = a.second;
    int trafficB = b.second;

    if (trafficA == trafficB) {
        return a.first < b.first;
    }

    return trafficA > trafficB;
};
auto comparatorPairsAsc = [](const pair<string, int> &a, const pair<string, int> &b) {
    int trafficA = a.second;
    int trafficB = b.second;

    if (trafficA == trafficB) {
        return a.first < b.first;
    }

    return trafficA < trafficB;
};


void Manager::getTopKGreatestTrafficCity(int k, const bool& asc) const {
    auto comparator = asc ? comparatorPairsAsc : comparatorPairsDesc;
    set<pair<string, int>, decltype(comparator)> cityByTraffic(comparator);
    for (auto &elem : cityAirports) {
        int numFlights = 0;
        for (auto &air : elem.second) {
            numFlights += air->getNumFlightsOut() + air->getNumFlightsIn();
        }
        cityByTraffic.insert({elem.first, numFlights});
    }
    int nameSize = 0;
    vector<pair<string, int>> cities;
    for (auto &elem : cityByTraffic) {
        if (elem.first.length() > nameSize) nameSize = elem.first.length();
        cities.push_back(elem);
        k--;
        if (k == 0) break;
    }
    Viewer::printCityGreatestTraffic(cities, nameSize);
}

void Manager::getTopKGreatestTrafficCountry(int k, const bool& asc) const {
    auto comparator = asc ? comparatorPairsAsc : comparatorPairsDesc;
    set<pair<string, int>, decltype(comparator)> countriesByTraffic(comparator);
    for (auto &countrycities : countryCities) {
        int numFlights = 0;
        for (auto& city : countrycities.second) {
            vector<Airport *> airportsPerCity = getAirportsPerCity(city);
            for (auto &air : airportsPerCity) {
                numFlights += air->getNumFlightsOut() + air->getNumFlightsIn();
            }
        }
        countriesByTraffic.insert({countrycities.first, numFlights});
    }
    int nameSize = 0;
    vector<pair<string, int>> countries;
    for (auto &elem : countriesByTraffic) {
        if (elem.first.length() > nameSize) nameSize = elem.first.length();
        countries.push_back(elem);
        k--;
        if (k == 0) break;
    }
    Viewer::printCountryGreatestTraffic(countries, nameSize);
}

void Manager::getTopKGreatestTrafficAirportPerCity(int k, const string &city, const bool& asc) const {
    auto comparator = asc ? comparatorAirportAsc : comparatorAirportDesc;
    set<Airport *, decltype(comparator)> airportsByTraffic(comparator);
    vector<Airport *> airportsPerCity = getAirportsPerCity(city);
    for (auto& elem : airportsPerCity) {
        airportsByTraffic.insert(elem);
    }
    int nameSize = 0;
    vector<Airport *> air;
    for (auto &elem : airportsByTraffic) {
        if (elem->getName().length() > nameSize) nameSize = elem->getName().length();
        air.push_back(elem);
        k--;
        if (k == 0) break;
    }
    Viewer::printAirportGreatestTraffic(air, nameSize);
}

void Manager::getTopKGreatestTrafficAirportPerCountry(int k, const string &country, const bool& asc) const {
    auto comparator = asc ? comparatorAirportAsc : comparatorAirportDesc;
    set<Airport *, decltype(comparator)> airportsByTraffic(comparator);
    vector<Airport *> airportsPerCountry = getAirportsPerCountry(country);
    for (auto& elem : airportsPerCountry) {
        airportsByTraffic.insert(elem);
    }
    int nameSize = 0;
    vector<Airport *> air;
    for (auto &elem : airportsByTraffic) {
        if (elem->getName().length() > nameSize) nameSize = elem->getName().length();
        air.push_back(elem);
        k--;
        if (k == 0) break;
    }
    Viewer::printAirportGreatestTraffic(air, nameSize);
}

void Manager::getTopKGreatestTrafficCityPerCountry(int k, const string &country, const bool& asc) const {
    auto comparator = asc ? comparatorPairsAsc : comparatorPairsDesc;
    set<pair<string, int>, decltype(comparator)> cityByTraffic(comparator);
    auto selectedCountryCities = countryCities.find(country);
    for (auto &elem : selectedCountryCities->second) {
        int numFlights = 0;
        vector<Airport *> airportsPerCity = getAirportsPerCity(elem);
        for (auto &air : airportsPerCity) {
            numFlights += air->getNumFlightsOut() + air->getNumFlightsIn();
        }
        cityByTraffic.insert({elem, numFlights});
    }
    int nameSize = 0;
    vector<pair<string, int>> cities;
    for (auto &elem : cityByTraffic) {
        if (elem.first.length() > nameSize) nameSize = elem.first.length();
        cities.push_back(elem);
        k--;
        if (k == 0) break;
    }
    Viewer::printCityGreatestTraffic(cities, nameSize);
}

auto comparatorAirlineDesc = [](Airline *a, Airline *b) {
    int trafficA = a->getNumFlights();
    int trafficB = b->getNumFlights();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA > trafficB;
};
auto comparatorAirlineAsc = [](Airline *a, Airline *b) {
    int trafficA = a->getNumFlights();
    int trafficB = b->getNumFlights();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA < trafficB;
};

void Manager::getTopKGreatestTrafficAirline(int k, const bool& asc) const {
    auto comparator = asc ? comparatorAirlineAsc : comparatorAirlineDesc;
    set<Airline *, decltype(comparator)> airlinesByTraffic(comparator);
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

void Manager::getTopKGreatestTrafficAirlinePerCountry(int k, const string &country, const bool& asc) const {
    auto comparator = asc ? comparatorAirlineAsc : comparatorAirlineDesc;
    set<Airline *, decltype(comparator)> airlinesByTraffic(comparator);
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

void Manager::getTopKAirportsAirlineTravelsTo(int k, Airline *airline, const bool& asc) const {
    int nameSize = 0;
    map<pair<string, string>, int> airportNumFlights;
    for (auto &elem : connections.getVertexSet()) {
        for (auto &edge : elem->getAdj()) {
            if (edge.hasAirline(airline)) {
                if (edge.getDest()->getInfo().getName().length() > nameSize) nameSize = edge.getDest()->getInfo().getName().length();
                airportNumFlights[{edge.getDest()->getInfo().getCode(),edge.getDest()->getInfo().getName()}]++;
            }
        }
    }
    vector<pair<pair<string,string>,int>> vec(airportNumFlights.begin(), airportNumFlights.end());
    if(asc) std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first.second < b.first.second; return a.second > b.second;});
    else std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first.second < b.first.second; return a.second > b.second;});
    if (k > vec.size()) k = vec.size();
    vector<pair<pair<string,string>,int>> res;
    auto it = vec.begin();
    while (k != 0) {
        res.push_back(*it);
        it++;
        k--;
    }
    Viewer::printTopKAirportsAirlineTravelsTo(res, nameSize);

}

void Manager::getTopKAirportsWithMoreAirlines(int k, const bool& asc) const {
    set<pair<int, pair<string,string>>> airportNumAirlines;
    for (auto& elem : connections.getVertexSet()) {
        set<Airline *> air;
        for (auto &edge : elem->getAdj()) {
            for (auto airline : edge.getAirlines()) {
                air.insert(airline);
            }
        }
        airportNumAirlines.insert({air.size(), {elem->getInfo().getCode(), elem->getInfo().getName()}});
    }
    vector<pair<int,pair<string,string>>> res;
    int nameSize = 0;
    if (k > airportNumAirlines.size()) k = airportNumAirlines.size();
    if (asc) {
        auto it = airportNumAirlines.rbegin();
        while (k!= 0) {
            if (it->second.second.length() > nameSize) nameSize = it->second.second.length();
            res.push_back(*it);
            it++;
            k--;
        }
    }
    else {
        auto it = airportNumAirlines.begin();
        while (k!= 0) {
            if (it->second.second.length() > nameSize) nameSize = it->second.second.length();
            res.push_back(*it);
            it++;
            k--;
        }
    }
    Viewer::printTopKAirportsWithMoreAirlines(res,nameSize);
}

void Manager::getTopKAirlinesThatFlyMoreToAnAirport(int k, Airport *airport, const bool& asc) const {
    int nameSize = 0;
    map<pair<string, string>, int> airlineNumFlightsToAirport;
    for (auto &elem : connections.getVertexSet()) {
        for (auto &edge : elem->getAdj()) {
            if (edge.getDest()->getInfo() == *airport) {
                for(auto &airline : edge.getAirlines()) {
                    airlineNumFlightsToAirport[{airline->getCode(), airline->getName()}]++;
                }
            }
        }
    }
    vector<pair<pair<string,string>,int>> vec(airlineNumFlightsToAirport.begin(), airlineNumFlightsToAirport.end());
    if(asc) std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first.second < b.first.second; return a.second > b.second;});
    else std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first.second < b.first.second; return a.second > b.second;});
    if (k > vec.size()) k = vec.size();
    vector<pair<pair<string,string>,int>> res;
    auto it = vec.begin();
    while (k != 0) {
        res.push_back(*it);
        it++;
        k--;
    }
    Viewer::printTopKAirlinesThatTravelToAnAirport(res, nameSize);
}

void Manager::listAirlinesPerAirport(Airport *airport) {
    auto air = connections.findVertex(airport);
    set<Airline *> airlinesInAirport;
    for (auto& edge : air->getAdj()) {
        for (auto &airline : edge.getAirlines()) {
            airlinesInAirport.insert(airline);
        }
    }
    int nameSize = 0;
    for (auto & elem : airlinesInAirport) {
        if (elem->getName().length() > nameSize) nameSize = elem->getName().length();
    }
    Viewer::printAirlinesPerAirport(airlinesInAirport, nameSize);
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
    Viewer::printListAirportsPerCountry(res, maxLengthName, country);
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
    Viewer::printSearchAirports(res,maxLengthName,airportName);
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
    Viewer::printSearchAirlines(res,maxLengthName,airlineName);
}

void Manager::printAirportInfo(Airport *airport) {
    Viewer::printAirportInfo(airport);
}

void Manager::printAirlineInfo(Airline *airline) {
    Viewer::printAirlineInfo(airline);
}

