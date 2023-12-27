//
// Created by Paulo Fidalgo on 30/11/2023.
//
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
    this->countryAirlines = parser.getAirlinesCountry();
}

unordered_map<std::string, Airline*> Manager::getAirlines() {
    return this->airlines;
}

unordered_map<string, Airport*> Manager::getAirports() {
    return this->airports;
}

Airport* Manager::getAirportPerCode(const std::string &code) const {
    auto it = airports.find(code);

    if (it != airports.end()) {
        return it->second;
    }

    return nullptr;
}

Airport* Manager::getAirportPerName(const std::string &name) const {
    auto it = airportsByName.find(name);

    if (it != airportsByName.end()) {
        return it->second;
    }

    return nullptr;
}
bool Manager::validateCityName(const std::string &name) const {
    auto it = cityAirports.find(name);

    if (it != cityAirports.end()) {
        return true;
    }

    return false;
}
bool Manager::validateCountryName(const std::string &name) const {
    auto it = countryCities.find(name);

    if (it != countryCities.end()) {
        return true;
    }

    return false;
}

Airline* Manager::getAirlinePerCode(const std::string &code) const {
    auto it = airlines.find(code);

    if (it != airlines.end()) {
        return it->second;
    }

    return nullptr;
}

Airline* Manager::getAirlinePerName(const std::string &name) const {
    auto it = airlinesByName.find(name);

    if (it != airlinesByName.end()) {
        return it->second;
    }

    return nullptr;
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

vector<Airport*> Manager::getAiportsPerCity(const string& city) const {
    auto it = cityAirports.find(city);

    if (it != cityAirports.end()) return it->second;

    return {};
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

vector<Airport*> Manager::getAirportsPerCoordinatesRange(const double &x, const double &y, const int &range) {
    double dist;
    vector<Airport*> res;
    for (auto &airport : connections.getVertexSet()) {
        dist = haversine(x, y, airport->getInfo()->getLatitude(), airport->getInfo()->getLongitude());

        if (dist <= range) {
            res.push_back(airport->getInfo());
        }
    }

    return res;
}

Airport* Manager::getClosestAirport(const double &x, const double &y) {
    double min = MAXFLOAT, dist;
    Airport* closest;

    for (auto &airport : connections.getVertexSet()) {
        dist = haversine(x, y, airport->getInfo()->getLatitude(), airport->getInfo()->getLongitude());
        if (dist < min) {
            min = dist;
            closest = airport->getInfo();
        }
    }

    return closest;
}

unordered_set<string> Manager::getCitiesPerCountry(const string& c) {
    auto it = countryCities.find(c);

    if (it != countryCities.end()) return it->second;

    return {};
}

bool Manager::hasConnection(Airport* s, Airport* t) {
    auto source = connections.findVertex(s);
    auto target = connections.findVertex(t);

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

    auto s = getAirportPerCode(source);

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

vector<Airport*> Manager::articulationPoints() {
    for (auto &airport : connections.getVertexSet()) {
        airport->setProcessing(false);
        airport->setNum(-1);
        airport->setLow(-1);
    }

    vector<Airport*> res;
    stack<Airport*> s;
    int i = 0;

    for (auto &airport : connections.getVertexSet()) {
        if (airport->getNum() == -1) {
            dfsApp(airport, s, res, i);
        }
    }
    return res;
}

void Manager::dfsApp(Vertex *v, stack<Airport*> &s, vector<Airport*> &res, int &i) {
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());
    v->setVisited(true);
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

bool hasAirline(Edge &e, const vector<Airline*> &air) {
    for (auto &airline : air) {
        if (e.hasAirline(airline)) {
            return true;
        }
    }
    return false;
}

bool hasOtherAirline(Edge &e, const unordered_set<Airline*> &air) {
    for (auto &airline : e.getAirlines()) {
        for (auto ai : air) {
            if (ai != airline) return true;
        }
    }
    return false;
}

vector<Airport*> Manager::hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines) {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    vector<Airport*> res;
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

vector<vector<Airport*>> Manager::scc() {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
        airport->setProcessing(false);
    }

    vector<vector<Airport*>> res;
    stack<Airport*> s;

    int i = 0;
    for (auto &airport : connections.getVertexSet()) {
        if (!airport->isVisited()) {
            dfsScc(airport, s, res, i);
        }
    }

    return res;

}

void Manager::dfsScc(Vertex *v, stack<Airport*> &s, vector<vector<Airport*>> &res, int &i) {
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

    vector<Airport*> scc;
    if (v->getNum() == v->getLow()) {
        while (!s.empty() && s.top()->getCode() != v->getInfo()->getCode()){
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

void Manager::DFS(Vertex* current, Vertex *destination, int maxFlights, vector<Airport*>& currentPath, vector<vector<Airport*>>& allPaths) {
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

vector<vector<Airport*>> Manager::pathMaximumConnectionFlights(Airport* startAirport, Airport* destination, int maxFlights) {
    for (auto& node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    Vertex* start = connections.findVertex(startAirport);
    Vertex* end = connections.findVertex(destination);

    std::vector<std::vector<Airport*>> allPaths;
    std::vector<Airport*> currentPath;

    currentPath.push_back(start->getInfo());
    DFS(start, end, maxFlights, currentPath, allPaths);

    return allPaths;
}

vector<Edge> Manager::getOutFlights(Airport* airport) const {

    if (airport == nullptr) return {};

    auto vertex = connections.findVertex(airport);
    if (vertex == nullptr) return {};

    return vertex->getAdj();
}

void Manager::getNumAirportsAndFlights() const {
    int numAirports = airports.size();
    int numFlights = 0;
    for (auto& elem : connections.getVertexSet()) {
        numFlights += elem->getInfo()->getNumFlightsOut();
    }
    Viewer::printNumAirportsNumFlights(numAirports, numFlights);
}

void Manager::getNumFlightsAndAirlines(Airport *airport) const {
    int numFlights = airport->getNumFlightsOut();
    int numAirlines = 0;
    for (auto &elem : connections.getVertexSet()) {
        if (airport == elem->getInfo()) {
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

void Manager::getNumFlightsPerCity(const string city) const {
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
/*
void Manager::getCountriesCanFlyToAirport(Airport *airport) const {
    vector<Edge> edges = getOutFlights(airport->getCode());
    set<string> countries;
    for (auto& edge : edges) {
        countries.emplace(edge.getDest()->getInfo()->getCountry());
    }
    int numCountries = countries.size();
    Viewer::printCountriesAirportCanFlyTo(airport->getCode(), airport->getName(), numCountries);
}
*/

void Manager::getCountriesCanFlyToCity(const string &city) const {
    set<string> countries;
    for (auto& elem : connections.getVertexSet()) {
        if (elem->getInfo()->getCity() == city) {
            for (auto& edge : elem->getAdj()) {
                countries.emplace(edge.getDest()->getInfo()->getCountry());
            }
        }
    }
    int numCountries = countries.size();
    Viewer::printCountriesCityCanFlyTo(city,numCountries);
}

bool notIn(vector<Airport*> &v, Airport* &t) {
    for (auto &it : v) {
        if (it == t) return false;
    }
    return true;
}

int Manager::getNumStops(Airport* s, Airport* t) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    auto first = connections.findVertex(s);
    auto last = connections.findVertex(t);

    queue<Vertex*> q;

    q.push(first);
    first->setVisited(true);
    int k = -1;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            auto next = q.front();
            q.pop();

            if (next == last) return k;

            for (auto &n : next->getAdj()) {
                auto dest = n.getDest();

                if (!dest->isVisited()) {
                    dest->setVisited(true);
                    q.push(dest);
                }
            }
        }
        k++;
    }

    return -1;
}

vector<vector<Airport*>> Manager::bfsMinConnections(Airport* s, Airport* t) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    auto first = connections.findVertex(s);
    auto last = connections.findVertex(t);

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);
    bool found = false;

    vector<Vertex*> res;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            Vertex* current = q.front();
            q.pop();


            for (Edge& flight : current->getAdj()) {
                Vertex* neighbor = flight.getDest();

                if (!neighbor->isVisited()) {
                    q.push(neighbor);
                    parent[neighbor] = current;
                    neighbor->setVisited(true);

                    if (neighbor == last) {
                        found = true;
                        neighbor->setVisited(false);
                        res.push_back(current);
                    }
                }
            }
        }

        if (found) break;
    }

    vector<vector<Airport*>> result;
    for (auto v : res) {
        Vertex* current = v;
        vector<Airport*> path;
        while (current != nullptr) {
            path.insert(path.begin(), current->getInfo());
            current = parent[current];
        }
        path.push_back(t);
        result.push_back(path);
    }
    return result;
}

vector<vector<Airport*>> Manager::bfsMinConnectionsExcludeAirports(Airport* s, Airport* t, const vector<Airport*> &exclude, const unordered_set<Airline*> &airlinesToExclude) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    for (auto &air : exclude) {
        auto airport = connections.findVertex(air);
        airport->setVisited(true);
    }

    auto first = connections.findVertex(s);
    auto last = connections.findVertex(t);

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);
    bool found = false;

    vector<Vertex*> res;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            Vertex* current = q.front();
            q.pop();


            for (Edge& flight : current->getAdj()) {
                Vertex* neighbor = flight.getDest();

            if (airlinesToExclude.empty() || hasOtherAirline(flight,airlinesToExclude)) {
                if (!neighbor->isVisited()) {
                    q.push(neighbor);
                    parent[neighbor] = current;
                    neighbor->setVisited(true);

                    if (neighbor == last) {
                        found = true;
                        neighbor->setVisited(false);
                        res.push_back(current);
                    }
                }
            }
            }
        }
        if (found) break;
    }

    vector<vector<Airport*>> result;
    for (auto v : res) {
        Vertex* current = v;
        vector<Airport*> path;
        while (current != nullptr) {
            path.insert(path.begin(), current->getInfo());
            current = parent[current];
        }
        path.push_back(t);
        result.push_back(path);
    }
    return result;
}


vector<Airport*> Manager::findShortestPath(Airport* u, Airport* v) {
    unordered_map<Vertex*, int> distances;
    for (Vertex* vertex : connections.getVertexSet()) {
        distances[vertex] = numeric_limits<int>::max();
        vertex->setVisited(false);
    }

    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<>> pq;


    Vertex* sourceAirport = connections.findVertex(u);
    Vertex* targetAirportPerCode = connections.findVertex(v);


    if (!sourceAirport || !targetAirportPerCode) {
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

    vector<Airport*> path;
    Vertex* current = targetAirportPerCode;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }

    return path;
}

bool excludeCountries(Vertex* v, vector<string> &countries) {
    for (const auto& country : countries) {
        if (v->getInfo()->getCountry() == country) {
            return true;
        }
    }
    return false;
}

double Manager::getTripDistance(const vector<Airport *> &trip) {
    double res = 0.0;

    auto it = trip.begin();
    auto first = *it;

    it++;
    while (it != trip.end()) {
        res += getDistance(first, *it);
        it++;
    }
    return res;
}

double Manager::getDistance(Airport *u, Airport* v) {
    auto p = findShortestPath(u, v);

    auto it = p.begin();
    double dist = 0.0;

    while (it != p.end()) {
        auto source = connections.findVertex(getAirportPerCode((*it)->getCode()));

        if (source) {
            auto nextIt = std::next(it);

            if (nextIt != p.end()) {
                for (auto &edge : source->getAdj()) {
                    if (edge.getDest()->getInfo()->getCode() == (*nextIt)->getCode()) {
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

vector<Airport*> Manager::scheduleTripMinDistance(Airport* u, Airport* v, vector<Airport*> & visit) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    vector<Airport*> res;

    visit.push_back(v);
    auto first = u;

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

vector<vector<Airport*>> Manager::scheduleTripMinConnectionCities(Airport* u, Airport* v, vector<string>& visit) {
    vector<vector<Airport*>> visits;
    bool first = true;

    for (auto& city : visit) {
        auto air = getAiportsPerCity(city);

        if (first) {
            for (auto& airport : air) {
                vector<Airport*> aux;
                aux.push_back(airport);
                visits.push_back(aux);
            }
            first = false;
        } else {
            vector<vector<Airport*>> newVisits;
            for (auto& path : visits) {
                for (auto& airport : air) {
                    vector<Airport*> newPath = path; // Copy the current path
                    newPath.push_back(airport);
                    newVisits.push_back(newPath);
                }
            }
            visits = newVisits;
        }
    }

    vector<vector<Airport*>> res;
    vector<pair<int, vector<vector<Airport*>>>> auxiliary;

    first = true;
    int min;
    vector<vector<Airport*>> aux;

    for (auto& vec : visits) {
        auto next = scheduleTripMinConnectionAirports(u, v, vec, {}, {});
        auto it = next.begin();

        if (first || it->size() <= min) {
            aux = next;
            min = it->size();
            auxiliary.emplace_back(min, aux);
            first = false;
        }
    }

    for (auto& trip : auxiliary) {
        if (trip.first == min) {
            res.insert(res.end(), trip.second.begin(), trip.second.end());
        }
    }

    return res;
}

vector<vector<Airport*>> Manager::scheduleTripMinConnectionCountries(Airport* u, Airport* v, vector<string>& visit) {
    vector<vector<Airport*>> visits;
    bool first = true;

    for (auto& country : visit) {
        auto air = getAirportsPerCountry(country);

        if (first) {
            for (auto& airport : air) {
                vector<Airport*> aux;
                aux.push_back(airport);
                visits.push_back(aux);
            }
            first = false;
        } else {
            vector<vector<Airport*>> newVisits;
            for (auto& path : visits) {
                for (auto& airport : air) {
                    vector<Airport*> newPath = path; // Copy the current path
                    newPath.push_back(airport);
                    newVisits.push_back(newPath);
                }
            }
            visits = newVisits;
        }
    }

    vector<vector<Airport*>> res;
    vector<pair<int, vector<vector<Airport*>>>> auxiliary;

    first = true;
    int min;
    vector<vector<Airport*>> aux;

    for (auto& vec : visits) {
        auto next = scheduleTripMinConnectionAirports(u, v, vec, {}, {});
        auto it = next.begin();

        if (first || it->size() <= min) {
            aux = next;
            min = it->size();
            auxiliary.emplace_back(min, aux);
            first = false;
        }
    }

    for (auto& trip : auxiliary) {
        if (trip.first == min) {
            res.insert(res.end(), trip.second.begin(), trip.second.end());
        }
    }

    return res;
}

vector<vector<Airport*>> Manager::scheduleTripMinConnectionAirports(Airport* u, Airport* v, const vector<Airport*>& visit, const vector<Airport*> &exclude, const unordered_set<Airline*> &airlinesToExclude) {
    vector<vector<Airport*>> path;

    auto start = u;
    bool first = true;

    for (auto &code : visit) {

        vector<vector<Airport*>> currentPaths = bfsMinConnectionsExcludeAirports(start, code, exclude, airlinesToExclude);

        if (!first) {
            vector<vector<Airport *>> re;
            for (auto &pa: path) {
                for (auto &trip: currentPaths) {
                    vector<Airport *> aux;
                    aux.insert(aux.end(), pa.begin(), pa.end());
                    aux.insert(aux.end(), trip.begin() + 1, trip.end());
                    re.push_back(aux);
                }
            }
            path.clear();
            path.insert(path.end(), re.begin(), re.end());
        }
        else {
            for (auto &pa : currentPaths) {
                vector<Airport*> air;
                for (auto &b : pa) {
                    air.push_back(b);
                }
                path.push_back(air);
                first = false;
            }
        }

        start = code;
    }

    vector<vector<Airport*>> lastLeg = bfsMinConnectionsExcludeAirports(start, v, exclude, airlinesToExclude);

    vector<vector<Airport *>> re;
    for (auto &pa: path) {
        for (auto &trip: lastLeg) {
            vector<Airport *> aux;
            aux.insert(aux.end(), pa.begin(), pa.end());
            aux.insert(aux.end(), trip.begin() + 1, trip.end());
            re.push_back(aux);
        }
    }

    return re;
}

vector<Airport*> Manager::findShortestPathExcludeCountries(Airport* u, Airport* v, vector<string> &countries) {
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

    auto depart = connections.findVertex(u);
    auto arrival = connections.findVertex(v);


    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<>> pq;


    Vertex* sourceAirport = connections.findVertex(u);
    Vertex* targetAirportPerCode = connections.findVertex(v);


    if (!sourceAirport || !targetAirportPerCode) {
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

    vector<Airport*> path;
    Vertex* current = targetAirportPerCode;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }

    return path;
}

vector<vector<Airport*>> Manager::findMinConnectionsExcludeCountries(Airport* s, Airport* t, vector<string> &countries) {
    for (auto node : connections.getVertexSet()) {
        if (excludeCountries(node, countries)) {
            node->setVisited(true);
        }
        else {
            node->setVisited(false);
        }
    }

    auto first = connections.findVertex(s);
    auto last = connections.findVertex(t);

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);
    bool found = false;

    vector<Vertex*> res;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            Vertex* current = q.front();
            q.pop();


            for (Edge& flight : current->getAdj()) {
                Vertex* neighbor = flight.getDest();

                if (!neighbor->isVisited()) {
                    q.push(neighbor);
                    parent[neighbor] = current;
                    neighbor->setVisited(true);

                    if (neighbor == last) {
                        found = true;
                        neighbor->setVisited(false);
                        res.push_back(current);
                    }
                }
            }
        }

        if (found) break;
    }

    vector<vector<Airport*>> result;
    for (auto v : res) {
        Vertex* current = v;
        vector<Airport*> path;
        while (current != nullptr) {
            path.insert(path.begin(), current->getInfo());
            current = parent[current];
        }
        path.push_back(t);
        result.push_back(path);
    }
    return result;
}

vector<vector<Airport*>> Manager::findMinConnectionsExcludeCities(Airport* s, Airport* t, vector<string> &cities) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    for (auto &city : cities) {
        auto cityAir = getAiportsPerCity(city);
        for (auto &airport : cityAir) {
            auto vertex = connections.findVertex(airport);
            vertex->setVisited(true);
        }
    }

    auto first = connections.findVertex(s);
    auto last = connections.findVertex(t);

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);
    bool found = false;

    vector<Vertex*> res;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            Vertex* current = q.front();
            q.pop();


            for (Edge& flight : current->getAdj()) {
                Vertex* neighbor = flight.getDest();

                if (!neighbor->isVisited()) {
                    q.push(neighbor);
                    parent[neighbor] = current;
                    neighbor->setVisited(true);

                    if (neighbor == last) {
                        found = true;
                        neighbor->setVisited(false);
                        res.push_back(current);
                    }
                }
            }
        }

        if (found) break;
    }

    vector<vector<Airport*>> result;
    for (auto v : res) {
        Vertex* current = v;
        vector<Airport*> path;
        while (current != nullptr) {
            path.insert(path.begin(), current->getInfo());
            current = parent[current];
        }
        path.push_back(t);
        result.push_back(path);
    }
    return result;
}

vector<vector<Airport*>> Manager::findMinConnectionsExcludeAirports(Airport* s, Airport* t, vector<Airport*> &air) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    for (auto &airport : air) {
        auto vertex = connections.findVertex(airport);
        vertex->setVisited(true);
    }

    auto first = connections.findVertex(s);
    auto last = connections.findVertex(t);

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);
    bool found = false;

    vector<Vertex*> res;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            Vertex* current = q.front();
            q.pop();


            for (Edge& flight : current->getAdj()) {
                Vertex* neighbor = flight.getDest();

                if (!neighbor->isVisited()) {
                    q.push(neighbor);
                    parent[neighbor] = current;
                    neighbor->setVisited(true);

                    if (neighbor == last) {
                        found = true;
                        neighbor->setVisited(false);
                        res.push_back(current);
                    }
                }
            }
        }

        if (found) break;
    }

    vector<vector<Airport*>> result;
    for (auto v : res) {
        Vertex* current = v;
        vector<Airport*> path;
        while (current != nullptr) {
            path.insert(path.begin(), current->getInfo());
            current = parent[current];
        }
        path.push_back(t);
        result.push_back(path);
    }
    return result;
}

vector<vector<Airport*>> Manager::manageFlightSearchFromMenu(vector<Airport*> &source, vector<Airport*> &destination, vector<Airport*> &airporsToVisit, vector<Airport*> &cityCountry, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude) {
    vector<vector<Airport*>> res;

    for (auto &from : source) {
        for (auto &to : destination) {
            if (!cityCountry.empty()) {
                for (auto vis : cityCountry) {
                    airporsToVisit.push_back(vis);
                    auto next = scheduleTripMinConnectionAirports(from, to, airporsToVisit, airportsToExclude, airlinesToExclude);
                    airporsToVisit.pop_back();
                    res.insert(res.end(), next.begin(), next.end());
                }
            }
            else {
                auto next = scheduleTripMinConnectionAirports(from, to, airporsToVisit, airportsToExclude, airlinesToExclude);
                res.insert(res.end(), next.begin(), next.end());
            }
        }
    }
    return res;
}

unordered_map<string, int> Manager::outFlightsPerAirport(Airport* s) {
    unordered_map<string, int> res;

    auto airport = connections.findVertex(s);

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

unordered_map<string, int> Manager::inFlightsPerAirport(Airport* d) {
    unordered_map<string, int> res;

    auto airport = connections.findVertex(d);

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
        countries.emplace(elem.getDest()->getInfo()->getCountry());
        cities.emplace(elem.getDest()->getInfo()->getCity());
    }
    int numAirports = depart->getAdj().size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printAirportDestinationsDistance1(airport->getCode(), airport->getName(), numAirports, numCities, numCountries);
}

void Manager::getCityDestinationsDistance1(vector<Airport *> air, const string& city) const {
    set<string> airportCodes;
    set<string> countries;
    set<string> cities;
    for (const auto& elem : air) {
        auto depart = connections.findVertex(elem);
        for (auto &edge : depart->getAdj()) {
            if (edge.getDest()->getInfo()->getCity() != city) {
                airportCodes.emplace(edge.getDest()->getInfo()->getCode());
                countries.emplace(edge.getDest()->getInfo()->getCountry());
                cities.emplace(edge.getDest()->getInfo()->getCity());
            }
        }
    }
    int numAirports = airportCodes.size();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printCityDestinationsDistance1(city, numAirports, numCities, numCountries);
}
void Manager::getCountryDestinationsDistance1(vector<Airport *> air, const string& country) const {
    set<string> airportCodes;
    set<string> countries;
    set<string> cities;
    for (const auto& elem : air) {
        auto depart = connections.findVertex(elem);
        for (auto &edge : depart->getAdj()) {
            if (edge.getDest()->getInfo()->getCountry() != country) {
                airportCodes.emplace(edge.getDest()->getInfo()->getCode());
                countries.emplace(edge.getDest()->getInfo()->getCountry());
                cities.emplace(edge.getDest()->getInfo()->getCity());
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
        air.push_back(currentVertex->getInfo()->getCode());
        countries.emplace(currentVertex->getInfo()->getCountry());
        cities.emplace(currentVertex->getInfo()->getCity());
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
void Manager::getCityDestinantions(const vector<Airport *> &airportsCity, const string& city) const {
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airportCity : airportsCity) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo()->getCity() == city) airport->setVisited(true);
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
            air.emplace(currentVertex->getInfo()->getCode());
            countries.emplace(currentVertex->getInfo()->getCountry());
            cities.emplace(currentVertex->getInfo()->getCity());
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

void Manager::getCountryDestinantions(const vector<Airport *> &airportsCountry, const string& country) const {
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto &airportCountry : airportsCountry) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo()->getCountry() == country) airport->setVisited(true);
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
            air.emplace(currentVertex->getInfo()->getCode());
            countries.emplace(currentVertex->getInfo()->getCountry());
            cities.emplace(currentVertex->getInfo()->getCity());
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
            air.push_back(currentVertex->getInfo()->getCode());
            countries.emplace(currentVertex->getInfo()->getCountry());
            cities.emplace(currentVertex->getInfo()->getCity());
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

void Manager::getCityDestinantionsUntilDistanceK(const vector<Airport *> &airportsCity, const string& city, const int &k) const {
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto & airportCity : airportsCity) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo()->getCity() == city) airport->setVisited(true);
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
                air.emplace(currentVertex->getInfo()->getCode());
                countries.emplace(currentVertex->getInfo()->getCountry());
                cities.emplace(currentVertex->getInfo()->getCity());
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

void Manager::getCountryDestinantionsUntilDistanceK(const vector<Airport *> &airportsCountry, const string& country, const int &k) const {
    set<string> air;
    set<string> countries;
    set<string> cities;
    for (auto & airportCountry : airportsCountry) {
        for (auto &airport : connections.getVertexSet()) {
            if (airport->getInfo()->getCity() == country) airport->setVisited(true);
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
                air.emplace(currentVertex->getInfo()->getCode());
                countries.emplace(currentVertex->getInfo()->getCountry());
                cities.emplace(currentVertex->getInfo()->getCity());
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



void Manager::findComponentDiameterPairs(Vertex *origin, vector<pair<Airport*, Airport*>> &result, int &i) const {
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
    vector<pair<Airport*, Airport*>> result;
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


void Manager::getTopKGreatestTrafficAirport(int k, const bool &bars, const bool& asc) const {
    auto comparator = asc ? comparatorAirportAsc : comparatorAirportDesc;
    set<Airport *, decltype(comparator)> airportsByTraffic(comparator);
    for (auto& elem : airports) {
        airportsByTraffic.insert(elem.second);
    }
    int nameSize = 0;
    vector<Airport *> air;
    if (k > airportsByTraffic.size()) k = airportsByTraffic.size();
    for (auto &elem : airportsByTraffic) {
        if (elem->getName().length() > nameSize) nameSize = elem->getName().length();
        air.push_back(elem);
        k--;
        if (k == 0) break;
    }
    if (bars) Viewer::printAiportGreatestTrafficBars(air, asc);
    else Viewer::printAirportGreatestTraffic(air, nameSize);
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


void Manager::getTopKGreatestTrafficCity(int k, const bool &bars, const bool& asc) const {
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

void Manager::getTopKGreatestTrafficCountry(int k, const bool &bars, const bool& asc) const {
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

void Manager::getTopKGreatestTrafficAirportPerCity(int k, const vector<Airport *> &airportsPerCity, const bool &bars, const bool& asc) const {
    auto comparator = asc ? comparatorAirportAsc : comparatorAirportDesc;
    set<Airport *, decltype(comparator)> airportsByTraffic(comparator);
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
    if (bars) Viewer::printAiportGreatestTrafficBars(air, asc);
    else Viewer::printAirportGreatestTraffic(air, nameSize);
}

void Manager::getTopKGreatestTrafficAirportPerCountry(int k, const vector<Airport *> &airportsPerCountry, const bool &bars, const bool& asc) const {
    auto comparator = asc ? comparatorAirportAsc : comparatorAirportDesc;
    set<Airport *, decltype(comparator)> airportsByTraffic(comparator);
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
    if (bars) Viewer::printAiportGreatestTrafficBars(air, asc);
    else Viewer::printAirportGreatestTraffic(air, nameSize);
}

void Manager::getTopKGreatestTrafficCityPerCountry(int k,pair<string, set<string>> *selectedCountryCities, const bool &bars, const bool& asc) const {
    auto comparator = asc ? comparatorPairsAsc : comparatorPairsDesc;
    set<pair<string, int>, decltype(comparator)> cityByTraffic(comparator);
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

void Manager::getTopKGreatestTrafficAirline(int k, const bool &bars, const bool& asc) const {
    auto comparator = asc ? comparatorAirlineAsc : comparatorAirlineDesc;
    set<Airline *, decltype(comparator)> airlinesByTraffic(comparator);
    for (auto& elem : airlines) {
        airlinesByTraffic.insert(elem.second);
    }
    vector<Airline *> air;
    int nameSize = 0;
    for (auto &elem : airlinesByTraffic) {
        if (elem->getName().length() > nameSize) nameSize = elem->getName().length();
        air.push_back(elem);
        k--;
        if (k == 0) break;
    }
    if (bars) Viewer::printAirlineGreatestTrafficBars(air, asc);
    else Viewer::printAirlineGreatestTraffic(air, nameSize);

}

void Manager::getTopKGreatestTrafficAirlinePerCountry(int k, const vector<Airline *> &airlinesCountry, const bool &bars, const bool& asc) const {
    auto comparator = asc ? comparatorAirlineAsc : comparatorAirlineDesc;
    set<Airline *, decltype(comparator)> airlinesByTraffic(comparator);
    for (auto& elem : airlinesCountry) {
        airlinesByTraffic.insert(elem);
    }
    vector<Airline *> air;
    int nameSize = 0;
    for (auto &elem : airlinesByTraffic) {
        if (elem->getName().length() > nameSize) nameSize = elem->getName().length();
        air.push_back(elem);
        k--;
        if (k == 0) break;
    }
    if (bars) Viewer::printAirlineGreatestTrafficBars(air, asc);
    else Viewer::printAirlineGreatestTraffic(air, nameSize);
}

void Manager::getTopKAirportsAirlineTravelsTo(int k, Airline *airline, const bool &bars, const bool& asc) const {
    int nameSize = 0;
    map<pair<string, string>, int> airportNumFlights;
    for (auto &elem : connections.getVertexSet()) {
        for (auto &edge : elem->getAdj()) {
            if (edge.hasAirline(airline)) {
                if (edge.getDest()->getInfo()->getName().length() > nameSize) nameSize = edge.getDest()->getInfo()->getName().length();
                airportNumFlights[{edge.getDest()->getInfo()->getCode(),edge.getDest()->getInfo()->getName()}]++;
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
    Viewer::printTopKVector(res,"Airports", "Number of Flights", nameSize);

}

void Manager::getTopKAirportsWithMoreAirlines(int k, const bool &bars, const bool& asc) const {
    set<pair<int, pair<string,string>>> airportNumAirlines;
    for (auto& elem : connections.getVertexSet()) {
        set<Airline *> air;
        for (auto &edge : elem->getAdj()) {
            for (auto airline : edge.getAirlines()) {
                air.insert(airline);
            }
        }
        airportNumAirlines.insert({air.size(), {elem->getInfo()->getCode(), elem->getInfo()->getName()}});
    }
    vector<pair<pair<string,string>, int>> res;
    int nameSize = 0;
    if (k > airportNumAirlines.size()) k = airportNumAirlines.size();
    if (asc) {
        auto it = airportNumAirlines.rbegin();
        while (k!= 0) {
            if (it->second.second.length() > nameSize) nameSize = it->second.second.length();
            res.emplace_back(it->second, it->first);
            it++;
            k--;
        }
    }
    else {
        auto it = airportNumAirlines.begin();
        while (k!= 0) {
            if (it->second.second.length() > nameSize) nameSize = it->second.second.length();
            res.emplace_back(it->second, it->first);
            it++;
            k--;
        }
    }
    Viewer::printTopKVector(res,"Airports", "Number of Airlines", nameSize);
}

void Manager::getTopKAirlinesThatFlyMoreToAnAirport(int k, Airport *airport, const bool &bars, const bool& asc) const {
    int nameSize = 0;
    map<pair<string, string>, int> airlineNumFlightsToAirport;
    for (auto &elem : connections.getVertexSet()) {
        for (auto &edge : elem->getAdj()) {
            if (edge.getDest()->getInfo() == airport) {
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
    Viewer::printTopKVector(res, "Airlines", "Number of flights", nameSize);
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


void Manager::listAiportsPerCountry(const vector<Airport *> &airportsCountry, const string &country) const{
    int maxLengthName = 0;
    vector<Airport *> res;
    for (auto& elem : airportsCountry) {
        if (elem->getName().length() > maxLengthName) maxLengthName = elem->getName().length();
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
    if (airportName.empty()) {
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
    if (airlineName.empty()) {
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

vector<Airport*> Manager::validateCountry(const string &country) const {
    auto it = countryCities.find(country);
    vector<Airport*> res;

    if (it != countryCities.end()) {
        for (auto &city : it->second) {
            auto air = getAiportsPerCity(city);
            res.insert(res.end(), air.begin(), air.end());
        }
    }

    return res;
}

vector<Airport*> Manager::validateCity(const string &city) const {
    auto it = cityAirports.find(city);

    if (it != cityAirports.end()) return it->second;

    return {};
}

unordered_set<Airline*> Manager::getAirlinesPerCountry(const string& country) {
    auto it = countryAirlines.find(country);

    if (it != countryAirlines.end()) return it->second;

    return {};
}




