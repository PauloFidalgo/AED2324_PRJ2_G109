//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Manager.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <cmath>

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

/*! @brief Permite verificar se um número inteiro k está entre 0 e o número máximo de aeroportos
 * @param x Valor que se pretende verificar se é positivo e menor que número de aeroportos
 * @return true se x positivo e menor que número de aeroportos
 * @return false se x negativo ou maior que número de aeroportos
 */
bool Manager::getMaxKAirports(const int &x) const {
    return x > 0 && x < airports.size();
}

/*! @brief Permite verificar se um número inteiro k está entre 0 e o número máximo de companhias aéreas
 * @param x Valor que se pretende verificar se é positivo e menor que número de companhias aéreas
 * @return true se x positivo e menor que número de companhias aéreas
 * @return false se x negativo ou maior que número de companhias aéreas
 */
bool Manager::getMaxKAirlines(const int &x) const {
    return x > 0 && x < airlines.size();
}

/*! @brief Permite verificar se um número inteiro k está entre 0 e o número máximo de cidades
 * @param x Valor que se pretende verificar se é positivo e menor que número de cidades
 * @return true se x positivo e menor que número de cidades
 * @return false se x negativo ou maior que número de cidades
 */
bool Manager::getMaxKCities(const int &x) const {
    return x > 0 && x < cityAirports.size();
}

/*! @brief Permite verificar se um número inteiro k está entre 0 e o número máximo de países
 * @param x Valor que se pretende verificar se é positivo e menor que número de países
 * @return true se x positivo e menor que número de países
 * @return false se x negativo ou maior que número de países
 */
bool Manager::getMaxKCountries(const int &x) const {
    return x > 0 && x < countryCities.size();
}

/*! @brief Permite pequisar um aeroporto por código
 * @param code Código do aeroporto que se pretende obter
 * @return apontador para airport se code for válido
 * @return nullptr se code não existir
 */
Airport* Manager::getAirportPerCode(const std::string &code) const {
    auto it = airports.find(code);

    if (it != airports.end()) {
        return it->second;
    }

    return nullptr;
}

/*! @brief Permite pequisar um aeroporto por nome
 * @param name Nome do aeroporto que se pretende obter
 * @return apontador para airport se o name do aeroporto for válido
 * @return nullptr se name não existir
 */
Airport* Manager::getAirportPerName(const std::string &name) const {
    auto it = airportsByName.find(name);

    if (it != airportsByName.end()) {
        return it->second;
    }

    return nullptr;
}

/*! @brief Permite verificar o nome de uma cidade
 * @param name Nome da cidade que se pretende verificar se é válido
 * @return true se nome da cidade for válido
 * @return false se nome da cidade for inválido
 */
bool Manager::validateCityName(const std::string &name) const {
    auto it = cityAirports.find(name);

    if (it != cityAirports.end()) {
        return true;
    }

    return false;
}

/*! @brief Permite verificar o nome de um país
 * @param name Nome do país que se pretende verficiar se é válido
 * @return true se nome do país for válido
 * @return false se nome do país for inválido
 */
bool Manager::validateCountryName(const std::string &name) const {
    auto it = countryCities.find(name);

    if (it != countryCities.end()) {
        return true;
    }

    return false;
}

/*! @brief Permite obter o conjunto de aeroportos por país
 * @param country Nome do país para o qual se pretende obter o conjunto de companhias
 * @return unordered_set com apontadores para Airline se nome do país for válido
 * @return unordered_set vazio se nome do país for inválido
 */
unordered_set<Airline*> Manager::getAirlinesPerCountry(const string& country) const {
    auto it = countryAirlines.find(country);

    if (it != countryAirlines.end()) return it->second;

    return {};
}

/*! @brief Permite pequisar uma companhia por código
 * @param code Code da companhia que se pretende obter
 * @return apontador para Airline se code for válido
 * @return nullptr se code for inválido
 */
Airline* Manager::getAirlinePerCode(const std::string &code) const {
    auto it = airlines.find(code);

    if (it != airlines.end()) {
        return it->second;
    }

    return nullptr;
}

/*! @brief Permite pequisar uma companhia por nome
 * @param name Nome da companhia que se pretende obter
 * @return apontador para Airline se name for válido
 * @return nullptr se name for inválido
 */
Airline* Manager::getAirlinePerName(const std::string &name) const {
    auto it = airlinesByName.find(name);

    if (it != airlinesByName.end()) {
        return it->second;
    }

    return nullptr;
}

/*! @brief Permite obter todos os aeroportos de uma cidade
 * @param city Nome da cidade para a qual se pretende obter o conjunto de aeroportos
 * @return vector de apontadores para Airport se city for válida
 * @return nullptr se city for inválida
 */
vector<Airport*> Manager::getAirportsPerCity(const string& city) const {
    auto it = cityAirports.find(city);

    if (it != cityAirports.end()) return it->second;

    return {};
}

/*! @brief Permite obter todos os aeroportos de um país
 * @param country Nome do país para o qual se pretende obter o conjunto de aeroportos
 * @return vector de apontadores para Airport se country for válido
 * @return nullptr se country for inválido
 */
vector<Airport*> Manager::getAirportsPerCountry(const string &country) const {
    auto cities = this->getCitiesPerCountry(country);

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

/*! @brief Permite obter as cidades de um determinado país
 * @param country Nome do país para o qual se pretende obter o conjunto de cidades
 * @return unordered_set de strings com os nomes das cidades correspondentes ao país, se country for válido
 * @return unordered_set vazio se country for inválido
 */
unordered_set<string> Manager::getCitiesPerCountry(const string& country) const {
    auto it = countryCities.find(country);

    if (it != countryCities.end()) return it->second;

    return {};
}

/*!
 * @brief Calcula a distância haversine entre duas coordenadas geográficas.
 * @param lat1 Latitude da primeira coordenada.
 * @param lon1 Longitude da primeira coordenada.
 * @param lat2 Latitude da segunda coordenada.
 * @param lon2 Longitude da segunda coordenada.
 * @return A distância haversine entre as duas coordenadas.
 */
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

/*! @brief Permite obter todos os aeroportos a uma distância "range" de uma coordenada
 *  @param x latitude
 *  @param y longitude
 *  @param range distância máxima até à qual serão incluídos aeroportos
 *  @return vetor de apontadores para aeroportos se existirem aeroportos a uma distância máxima de range do ponto (x,y)
 *  @return vetor vazio se não existirem aeroportos nesse range
 */
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

/*! @brief Permite obter o aeroporto mais próximo de uma coordenada
 *  @param x latitude
 *  @param y longitude
 *  @return vetor de apontador para o aeroporto mais próximo do ponto (x,y)
 */
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

/*! @brief Determina os vértices críticos do grafo
 *  Vértices críticos, são vértices que caso sejam removidos, fazem aumentar o número de componentes do grafo
 *
 */
void Manager::articulationPoints() {
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
    int maxLengthName = 0;
    for (auto& elem : res) {
        if (elem->getName().length() > maxLengthName) maxLengthName = elem->getName().length();
    }
    Viewer::printArticulationPoints(res, maxLengthName);
}

/*! @brief Função auxiliar que executa uma pesquisa em profundidade, com o objetivo de encontrar os pontos de articulações
 *  @param v Apontador para vértice onde irá começar a visita em profundidade
 *  @param s stack de apontadores para aeroportos, utilidada para determinar os articulation points
 *  @param res vetor de apontadores para aeroportos, onde o resultado será inserido
 *  @param i valor que indica a ordem de visita do vértice
 */
void Manager::dfsApp(Vertex *v, stack<Airport*> &s, vector<Airport*> &res, int &i) {
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

/*! @brief Função auxiliar para verificar alguma companhia do unordered_set<> air está incluída no voo (Edge) e
 *  @param e Edge (voo) para o qual se pretende verificar se alguma companhia está incluída
 *  @param air unordered_set de apontadores para airlines que se quer verificar se, pelo menos uma, está contida no edge
 *  @return true caso exista pelo menos uma companhia que faça esse voo
 *  @return false caso não exista nenhuma companhia do unordered_set que faça esse voo
 */
bool hasAirline(Edge &e, const unordered_set<Airline*> &air) {
    for (auto &airline : air) {
        if (e.hasAirline(airline)) {
            return true;
        }
    }
    return false;
}

/*! @brief Função auxiliar para verificar alguma companhia do vector<> air está incluída no voo (Edge) e
 *  @param e Edge (voo) para o qual se pretende verificar se alguma companhia está incluída
 *  @param air vetor de apontadores para airlines que se quer verificar se, pelo menos uma, está contida no edge
 *  @return true caso exista pelo menos uma companhia que faça esse voo
 *  @return false caso não exista nenhuma companhia do vetor que faça esse voo
 */
bool hasAirline(Edge &e, const vector<Airline*> &air) {
    for (auto &airline : air) {
        if (e.hasAirline(airline)) {
            return true;
        }
    }
    return false;
}

/*! @brief Função auxiliar para verificar se existe alguma companhia incluída no voo (Edge) que não esteja incluída no unordered_set<> air
 *  @param e Edge (voo) para o qual se pretende verificar se, pelo menos, uma companhia que faça esse voo não está contida no unordered_set
 *  @param air unordered_set de apontadores para airlines que se pretende excluir
 *  @return true caso exista pelo menos uma companhia não presente no unordered_set<> que faça esse voo
 *  @return false caso contrário
 */
bool hasOtherAirline(Edge &e, const unordered_set<Airline*> &air) {
    for (auto &airline : e.getAirlines()) {
        for (auto ai : air) {
            if (ai != airline) return true;
        }
    }
    return false;
}

/*! @brief Determina o número de componentes fortemente ligados do grafo
 *  Um componente fortemente ligado é um subset do conjunto de vértices, tal que qualquer vértice concegue aceder a qualquer outro vértice do mesmo componente
 */
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

/*! @brief Função auxiliar que utiliza pesquisa em profundidade determinar o número de componentes fortemente ligados
 *  @param v Apontador para vértice onde irá começar a visita em profundidade
 *  @param s stack de apontadores para aeroportos, utilidada para determinar os componentes fortemente ligados
 *  @param res vetor de apontadores para aeroportos, onde o resultado será inserido
 *  @param i valor que indica a ordem de visita do vértice
 */
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

/*! @brief Permite obter o conjunto de voos que partem de um aeroporto
 *  @param airport apontador para aeroporto para o qual se pretende obter o conjunto de voos que partem desse aeroporto
 *  @return vetor de edges correspondentes aos voos que partem do aeroporto
 */
vector<Edge> Manager::getOutFlights(Airport* airport) const {

    if (airport == nullptr) return {};

    auto vertex = connections.findVertex(airport);
    if (vertex == nullptr) return {};

    return vertex->getAdj();
}

/*! @brief Permite visualizar o número total de aeroportos e o número total de voos da rede
 * O(|V|)
 */
void Manager::getNumAirportsAndFlights() const {
    int numAirports = airports.size();
    int numFlights = 0;
    for (auto& elem : connections.getVertexSet()) {
        numFlights += elem->getInfo()->getNumFlightsOut();
    }
    Viewer::printNumAirportsNumFlights(numAirports, numFlights);
}

/*! @brief Permite visualizar o número total de voos de um aeroporto e de quantas companhias diferentes
 * @param airport apontador para aeroporto para o qual se pretende imprimir o número de voos e companhias que fazem esses voos
 */
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

/*! @brief Permite visualizar o número total de voos de uma cidade
 *  @param city nome da cidade para a qual se pretende imprimir o número de voos
 */
void Manager::getNumFlightsPerCity(const string &city) const {
    int numFlights = 0;
    vector<Airport*> air = getAirportsPerCity(city);
    for (auto& elem : air) {
        numFlights += elem->getNumFlightsOut();
        numFlights += elem->getNumFlightsIn();
    }
    Viewer::printNumFlightsPerCity(city, numFlights);
}

/*! @brief Permite visualizar o número total de voos de uma companhia
 *  @param airline apontador para a Airline para a qual se pretende imprimir o número de voos
 */
void Manager::getNumFlightsPerAirline(Airline *airline) const {
    int numFlights = airline->getNumFlights();
    Viewer::printNumFlightsPerAirline(airline->getCode(), airline->getName(), numFlights);
}
/*! @brief Permite visualizar o número países diferentes que é possível visitar a partir de uma aeorporto
 *  @param airport apontador para o aeroporto para o qual se pretende imprimir o conjunto de países que sao alcançáveis
 */
void Manager::getCountriesCanFlyToAirport(Airport *airport) const {
    vector<Edge> edges = getOutFlights(airport);
    set<string> countries;
    for (auto& edge : edges) {
        countries.emplace(edge.getDest()->getInfo()->getCountry());
    }
    int numCountries = countries.size();
    Viewer::printCountriesAirportCanFlyTo(airport->getCode(), airport->getName(), numCountries);
}

/*! @brief Permite visualizar o número países diferentes que é possível visitar a partir de uma cidade
 *  @param city nome da cidade para a qual se prentende obter o conjunto de países que voam para ela
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

/*! @brief Função auxiliar que implementa uma pesquisa em largura para determinar os caminhos do ponto s até ao t no número mínimo de voos com vários filtros
 *  É possível excluir vários aeroportos, companhias aéreas ou voar apenas em algumas companhias
 *  @param s apontador para o aeroporto de partida
 *  @param t apontador para o aeroporto de destino
 *  @param exclude vetor de apontadores para aeroportos, que se serão excluídos
 *  @param airlinesToExclude unordered_set de apontadores para companhias aéreas que se pretendem excluir
 *  @param flyOnlyAirlines unordered_set de apontadores para as companhias aéreas que serão incluídas
 *  @return vetor de caminhos que satisfazem os requisitos
 */
vector<vector<Airport*>> Manager::bfsMinConnectionsExcludeAirports(Airport* s, Airport* t, const vector<Airport*> &exclude, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    if (s == t) return {};

    for (auto &air : exclude) {
        auto airport = connections.findVertex(air);
        airport->setVisited(true);
    }


    auto first = connections.findVertex(airports[s->getCode()]);
    auto last = connections.findVertex(airports[t->getCode()]);

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

                if (flyOnlyAirlines.empty()) {
                    if (flyOnlyAirlines.empty() && (airlinesToExclude.empty() || hasOtherAirline(flight,airlinesToExclude)) || (!flyOnlyAirlines.empty() &&
                            hasAirline(flight, flyOnlyAirlines))) {
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


/*! @brief Função auxiliar que na determinação da viagem com mínima distância entre dois pontos, com vários filtros
 *  É possível incluir aeroportos para passar, excluir vários aeroportos, companhias aéreas ou voar apenas em algumas companhias *  @param s apontador para o aeroporto de partida
 *  @param source apontador para o aeroporto de partida
 *  @param destination apontador para o aeroporto de destino
 *  @param airporsToVisit apontador para aeroportos que deverão ser visitados sequencialmente
 *  @param airportsToExclude vetor de apontadores para aeroportos, que se serão excluídos
 *  @param airlinesToExclude unordered_set de apontadores para companhias aéreas que se pretendem excluir
 *  @param flyOnlyAirlines unordered_set de apontadores para as companhias aéreas que serão incluídas
 *  @return vetor de apontadores para aeroportos correspondente a um caminho que satisfaz os requisitos e minimiza a distância
 */
vector<Airport*> Manager::scheduleTripMinDistance(Airport* &source, Airport* &destination, vector<Airport*> &airporsToVisit, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines) {

    vector<Airport*> res;

    if (source->getCode() == destination->getCode()) return res;

    auto first = source;

    for (auto &country : airporsToVisit) {
        auto min_dist = findShortestPathExclude(first, country, airportsToExclude, airlinesToExclude, flyOnlyAirlines);

        for (auto &c : min_dist) {
            if (std::find(res.begin(), res.end(),c) == res.end())
                res.push_back(c);
        }

        first = country;
    }

    auto min_dist = findShortestPathExclude(first, destination, airportsToExclude, airlinesToExclude, flyOnlyAirlines);

    for (auto &c : min_dist) {
        if (std::find(res.begin(), res.end(),c) == res.end())
            res.push_back(c);
    }

    return res;
}

/*! @brief Função auxiliar que na determinação das viagens com número mínimo de escalas entre dois pontos, com vários filtros
 *  É possível incluir aeroportos para passar, excluir vários aeroportos, companhias aéreas ou voar apenas em algumas companhias
 *  @param source apontador para o aeroporto de partida
 *  @param destination apontador para o aeroporto de destino
 *  @param airporsToVisit apontador para aeroportos que deverão ser visitados sequencialmente
 *  @param airportsToExclude vetor de apontadores para aeroportos, que se serão excluídos
 *  @param airlinesToExclude unordered_set de apontadores para companhias aéreas que se pretendem excluir
 *  @param flyOnlyAirlines unordered_set de apontadores para as companhias aéreas que serão incluídas
 *  @return vetor de caminhos satisfazem os requisitos e minimizam o número de escalas
 */
vector<vector<Airport*>> Manager::scheduleTripMinConnectionAirports(Airport* source, Airport* destination, const vector<Airport*>& airporsToVisit, const vector<Airport*> &airportsToExclude, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines) {
    vector<vector<Airport*>> path;

    auto start = source;
    bool first = true;

    for (auto &code : airporsToVisit) {

        vector<vector<Airport*>> currentPaths = bfsMinConnectionsExcludeAirports(start, code, airportsToExclude, airlinesToExclude, flyOnlyAirlines);

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
            if (!re.empty()) path.insert(path.end(), re.begin(), re.end());
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

    vector<vector<Airport*>> lastLeg = bfsMinConnectionsExcludeAirports(start, destination, airportsToExclude, airlinesToExclude, flyOnlyAirlines);

    if (path.empty()) return lastLeg;

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

/*! @brief Função auxiliar que na determinação da viagem com mínima distância entre dois pontos, com vários filtros
 *  Esta função utiliza uma fila de prioridade para garantir que o primeiro caminho encontrado é o que minimiza a distância
 *  É possível incluir aeroportos para passar, excluir vários aeroportos, companhias aéreas ou voar apenas em algumas companhias
 *  @param source apontador para o aeroporto de partida
 *  @param destination apontador para o aeroporto de destino
 *  @param airportsToExclude vetor de apontadores para aeroportos, que se serão excluídos
 *  @param airlinesToExclude unordered_set de apontadores para companhias aéreas que se pretendem excluir
 *  @param flyOnlyAirlines unordered_set de apontadores para as companhias aéreas que serão incluídas
 *  @return vetor de apontadores para aeroportos, correspondente a um caminho que satisfaz os requisitos e minimiza a distância
 */
vector<Airport*> Manager::findShortestPathExclude(Airport* source, Airport* destination, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines) {
    unordered_map<Vertex*, int> distances;

    if (source->getCode() == destination->getCode()) return {};

    for (auto &node : connections.getVertexSet()) {
        distances[node] = numeric_limits<int>::max();
        node->setVisited(false);
    }

    for (auto a : airportsToExclude)
    {
        auto p = connections.findVertex(a);
        p->setVisited(true);
    }

    auto sourceAirport = connections.findVertex(getAirportPerCode(source->getCode()));
    auto targetAirportPerCode = connections.findVertex(getAirportPerCode(destination->getCode()));


    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<>> pq;


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

            if (flyOnlyAirlines.empty()) {
                if (flyOnlyAirlines.empty() && (airlinesToExclude.empty() || hasOtherAirline(flight,airlinesToExclude)) || (!flyOnlyAirlines.empty() &&
                                                                                                                            hasAirline(flight, flyOnlyAirlines))) {
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

/*!
 * @brief Função auxiliar para obter as combinações de visitas de países diferentes
 * @param current current iterator
 * @param next next iterator
 * @param cityCountry map de cityCountries a visitar
 * @param res vetor onde será colocado o resultado
 * @param path vetor com a combinação atual
 */
void combinationalHelper(map<int, vector<Airport*>>::iterator &current, map<int, vector<Airport*>>::iterator &next, map<int, vector<Airport*>>& cityCountry, vector<vector<Airport*>>& res, vector<Airport*>& path) {

    if (next == cityCountry.end()) {
        for (auto &po : current->second) {
            path.push_back(po);
            res.push_back(path);
            path.pop_back();
        }
    }
    else {
        auto nnext = cityCountry.find(next->first);
        nnext++;
        for (auto &po : current->second) {
            path.push_back(po);
            combinationalHelper(next, nnext, cityCountry, res, path);
            path.pop_back();
        }
    }
}

/*!
 * @brief Função auxiliar para obter as combinações de visitas de países diferentes
 * @param cityCountry map de cityCountries a visitar
 * @param res vetor onde será colocado o resultado
 */
void allCombinations(map<int, vector<Airport*>>& cityCountry, vector<vector<Airport*>>& res) {
    vector<Airport*> path;
    auto it = cityCountry.begin();
    auto next = std::next(it);
    combinationalHelper(it, next, cityCountry, res, path);
}

/*! @brief Função que recebe pedido do menu para procurar voos de um conjunto de pontos de partida até um conjunto de pontos de destinos, minimizando o número de escalas, com vários filtros
 *  É possível incluir aeroportos para passar, excluir vários aeroportos, companhias aéreas ou voar apenas em algumas companhias
 * @param source vetor de apontadores para aeroportos correspondentes aos aeroportos de partida, inseridos pelo utilizador
 * @param destination vetor de apontadores para aeroportos correspondentes aos aeroportos de destino, inseridos pelo utilizador
 * @param airporsToVisit vetor de apontadores para aeroportos correspondentes aos aeroportos por onde o utilizador pretende passar
 * @param cityCountry mapa de inteiro (correspondente à ordem pela qual devem ser visitados) os países ou cidades inseridas pelo utilizador
 * @param airportsToExclude vetor de apontadores para aeroportos a excluir, inseridos pelo utilizador
 * @param airlinesToExclude unordered_set de apontadores para Airlines a excluir, inseridos pelo utilizador
 * @param flyOnlyAirlines unordered_set de apontadores para Airlines a incluir, inseridos pelo utilizador
 */
void Manager::manageFlightSearchFromMenu(vector<Airport*> &source, vector<Airport*> &destination, vector<Airport*> &airporsToVisit, map<int, vector<Airport*>> &cityCountry, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines) {
    vector<vector<Airport*>> res;
    vector<vector<Airport*>> trip;

    if (!cityCountry.empty()) allCombinations(cityCountry, trip);


    for (auto &from : source) {
        for (auto &to : destination) {

            if (!cityCountry.empty()) {
                for (auto vis : trip) {
                    airporsToVisit.insert(airporsToVisit.end(), vis.begin(), vis.end());
                    auto next = scheduleTripMinConnectionAirports(from, to, airporsToVisit, airportsToExclude, airlinesToExclude, flyOnlyAirlines);

                    for (int i = 0; i < vis.size(); i++) airporsToVisit.pop_back();

                    if (!next.empty()) res.insert(res.end(), next.begin(), next.end());
                }
            }
            else {
                auto next = scheduleTripMinConnectionAirports(from, to, airporsToVisit, airportsToExclude, airlinesToExclude, flyOnlyAirlines);
                if (!next.empty()) res.insert(res.end(), next.begin(), next.end());
            }
        }
    }
    Viewer::printFlightOptions(res);
}

/*! @brief Função que recebe pedido do menu para procurar voos de um conjunto de pontos de partida até um conjunto de pontos de destinos, minimizando a distância percorrida, com vários filtros
 * É possível incluir aeroportos para passar, excluir vários aeroportos, companhias aéreas ou voar apenas em algumas companhias
 * @param source vetor de apontadores para aeroportos correspondentes aos aeroportos de partida, inseridos pelo utilizador
 * @param destination vetor de apontadores para aeroportos correspondentes aos aeroportos de destino, inseridos pelo utilizador
 * @param airporsToVisit vetor de apontadores para aeroportos correspondentes aos aeroportos por onde o utilizador pretende passar
 * @param cityCountry mapa de inteiro (correspondente à ordem pela qual devem ser visitados) os países ou cidades inseridas pelo utilizador
 * @param airportsToExclude vetor de apontadores para aeroportos a excluir, inseridos pelo utilizador
 * @param airlinesToExclude unordered_set de apontadores para Airlines a excluir, inseridos pelo utilizador
 * @param flyOnlyAirlines unordered_set de apontadores para Airlines a incluir, inseridos pelo utilizador
 */
void Manager::manageFlightSearchFromMenuMinDistance(vector<Airport*> &source, vector<Airport*> &destination, vector<Airport*> &airporsToVisit, map<int, vector<Airport*>> &cityCountry, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines) {
    vector<vector<Airport*>> res;
    vector<vector<Airport*>> trip;
    if (!cityCountry.empty()) allCombinations(cityCountry, trip);


    for (auto &from : source) {
        for (auto &to : destination) {

            if (!cityCountry.empty()) {
                for (auto vis : trip) {
                    airporsToVisit.insert(airporsToVisit.end(), vis.begin(), vis.end());
                    auto next = scheduleTripMinDistance(from, to, airporsToVisit, airportsToExclude, airlinesToExclude, flyOnlyAirlines);

                    for (int i = 0; i < vis.size(); i++) airporsToVisit.pop_back();

                    if (!next.empty()) res.push_back(next);
                }
            }
            else {
                auto next = scheduleTripMinDistance(from, to, airporsToVisit, airportsToExclude, airlinesToExclude, flyOnlyAirlines);
                if (!next.empty()) res.push_back(next);
            }
        }
    }
    Viewer::printFlightOptions(res);
}


/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) disponíveis para um aeroporto
 * @param airport apontador para aeroporto para o qual se pretende obter e imprimir os destinos acessíveis diretamente (sem escalas)
 */
void Manager::getAirportDestinantionsDistance1(Airport *airport) const {
    auto depart = connections.findVertex(airport);
    set<string> countries;
    set<string> cities;
    for (auto &elem : depart->getAdj()) {
        countries.emplace(elem.getDest()->getInfo()->getCountry());
        cities.emplace(elem.getDest()->getInfo()->getCity());
    }
    int numAirports = airport->getNumFlightsOut();
    int numCountries = countries.size();
    int numCities = cities.size();
    Viewer::printAirportDestinationsDistance1(airport->getCode(), airport->getName(), numAirports, numCities, numCountries);
}

/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) disponíveis para uma cidade
 * @param air vetor de apontadores para aeroportos
 * @param city nome da cidade para a qual se pretende
 */
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

/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) disponíveis para um país
 *  @param air vetor de apontadores para os aeroportos do país em questão
 *  @param country país para o qual se pretende obter os destinos diretos
 */
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

/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) alcançáveis a partir de um aeroporto
 *  @param airport apontador para o aeroporto para o qual se pretende imprimir os destinos alcançáveis
 */
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

/*! Permite visualizar o número de destinos (aeroportos, cidades e países) alcançáveis a partir de uma cidade
 * @param airportsCity vetor de apontadores para aeroportos da cidade em questão
 * @param city país para a qual se pretende visualizar os destinos alcançáveis
 */
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
        for (auto& edge : depart->getAdj()) {
            if(!edge.getDest()->isVisited()){
                q.push(edge.getDest());
                edge.getDest()->setVisited(true);
            }
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

/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) alcançáveis a partir de um país
 * @param airportsCountry vetor de apontadores para aeroportos do país em questão
 * @param country país para o qual se pretende visualizar os destinos alcançáveis
 */
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

        for (auto& edge : depart->getAdj()) {
            if(!edge.getDest()->isVisited()){
                q.push(edge.getDest());
                edge.getDest()->setVisited(true);
            }
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

/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) alcançáveis a partir de um aeroporto até a uma dada distância (k)
 *  @param airport apontador para o aeroporto onde se pretende começar a pesquisa
 *  @param k distância máxima
 */
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


/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) alcançáveis a partir de uma cidade até a uma dada distância (k)
 *  @param airportsCity vetor de apontadores para aeroportos da cidade em questão
 *  @param city cidade a partir da qual se vai começar a pesquisa
 *  @param k distância máxima
 */
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

        for (auto& edge : depart->getAdj()) {
            if(!edge.getDest()->isVisited()){
                q.emplace(edge.getDest(), 1);
                edge.getDest()->setVisited(true);
            }
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

/*! @brief Permite visualizar o número de destinos (aeroportos, cidades e países) alcançáveis a partir de um país até a uma dada distância (k)
 *  @param airportsCountry vetor de apontadores para aeroportos do país em questão
 *  @param country país a partir do qual se vai começar a pesquisa
 *  @param k distância máxima
 */
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

        for (auto& edge : depart->getAdj()) {
            if(!edge.getDest()->isVisited()){
                q.emplace(edge.getDest(), 1);
                edge.getDest()->setVisited(true);
            }
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

/*! @brief Método auxiliar da função DiameterPairs().
 * Consiste numa BFS que atualiza o número máximo de escalas (i),
 * sempre que é encontrado um caminho entre dois aeoroportos com o número de escalas superior a i. Também mantém
 * um vetor com os pares de aeroportos que correspondem ao número máximo de escalas.
 * @param origin apontador para vértice onde será iniciada a BFS
 * @param result vetor de pares de apontadores para aeroportos correspondentes aos pontos de partida e destinos com o número máximo de escalas
 * @param i o número máximo de escalas, atualizado sempre que se encontra um valor superior
 */

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

/*! @brief Permite visualizar o número de escalas para a viagem com mais escalas, assim como todos os pares de aeroportos - origem-destino, cuja viagem entre eles tem um número de escalas igual ao valor obtido
 *
 */
void Manager::diameterPairs() const {
    vector<pair<Airport*, Airport*>> result;
    int maxDiameter = 0;
    for (auto &elem : connections.getVertexSet()) {
        findComponentDiameterPairs(elem, result, maxDiameter);
    }
    Viewer::printDiameterPairs(result, maxDiameter);
}

/*! @brief Método auxiliar, utilizado para ordenar de forma decrescente um set de aeroportos
 *
 */
auto comparatorAirportDesc = [](Airport *a, Airport *b) {
    int trafficA = a->getNumFlightsIn() + a->getNumFlightsOut();
    int trafficB = b->getNumFlightsIn() + b->getNumFlightsOut();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA > trafficB;
};

/*! Método auxiliar, utilizado para ordenar de forma crescente um set de aeroportos
 *
 */
auto comparatorAirportAsc = [](Airport *a, Airport *b) {
    int trafficA = a->getNumFlightsIn() + a->getNumFlightsOut();
    int trafficB = b->getNumFlightsIn() + b->getNumFlightsOut();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA < trafficB;
};

/*! @brief Permite visualizar os top k aeroportos que têm o maior ou menor número de voos, em forma de lista ou gráfico de barras
 * @param k número de aeroportos a serem impressos
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendent
 */
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
    if (bars) Viewer::printAirportGreatestTrafficBars(air, asc);
    else Viewer::printAirportGreatestTraffic(air, nameSize);
}

/*! @brief Método auxiliar, utilizado para ordenar de forma decrescente um set de pares de strings e inteiros
 *
 */
auto comparatorPairsDesc = [](const pair<string, int> &a, const pair<string, int> &b) {
    int trafficA = a.second;
    int trafficB = b.second;

    if (trafficA == trafficB) {
        return a.first < b.first;
    }

    return trafficA > trafficB;
};

/*! @brief Método auxiliar, utilizado para ordenar de forma crescente um set de pares de strings e inteiros
 *
 */
auto comparatorPairsAsc = [](const pair<string, int> &a, const pair<string, int> &b) {
    int trafficA = a.second;
    int trafficB = b.second;

    if (trafficA == trafficB) {
        return a.first < b.first;
    }

    return trafficA < trafficB;
};

/*! @brief Permite visualizar as top k cidades que têm o maior ou menor número de voos, em forma de lista ou gráfico de barras
 * @param k número de cidades a serem impressas
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendent
 */
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
    if (bars) Viewer::printCityOrCountryGreatestTrafficBars(cities,nameSize,asc);
    else Viewer::printCountryCityStats(cities, "Cities", "Number of flights", nameSize);
}

/*! @brief Permite visualizar os top k países que têm o maior ou menor número de voos, em forma de lista ou gráfico de barras
 * @param k número de países a serem impressos
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendent
 */
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
    if (bars) Viewer::printCityOrCountryGreatestTrafficBars(countries,nameSize,asc);
    else Viewer::printCountryCityStats(countries, "Countries", "Number of flights", nameSize);
}

/*! @brief Permite visualizar os top k aeroportos numa dada cidade que têm o maior ou menor número de voos, em forma de lista ou gráfico de barras
 * @param k número de aeroportos a serem impressos
 * @param airportsPerCity vetor de apontadores para os aeroportos correspondentes à cidade
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
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
    if (bars) Viewer::printAirportGreatestTrafficBars(air, asc);
    else Viewer::printAirportGreatestTraffic(air, nameSize);
}

/*! @brief Permite visualizar os top k aeroportos num dado país que têm o maior ou menor número de voos, em forma de lista ou gráfico de barras
 * @param k número de airports a serem impressos
 * @param airportsPerCountry vetor de apontadores para aeroportos do país em questão
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
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
    if (bars) Viewer::printAirportGreatestTrafficBars(air, asc);
    else Viewer::printAirportGreatestTraffic(air, nameSize);
}

/*! @brief Permite visualizar as top k cidades num dado país que têm o maior ou menor número de voos, em forma de lista ou gráfico de barras
 * @param k número de cidades a serem impressas
 * @param selectedCountryCities unordered_set de strings com as cidades a serem incluídas
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
void Manager::getTopKGreatestTrafficCityPerCountry(int k, const unordered_set<string> &selectedCountryCities, const bool &bars, const bool& asc) const {
    auto comparator = asc ? comparatorPairsAsc : comparatorPairsDesc;
    set<pair<string, int>, decltype(comparator)> cityByTraffic(comparator);
    for (auto &elem : selectedCountryCities) {
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
    if (bars) Viewer::printCityOrCountryGreatestTrafficBars(cities,nameSize,asc);
    else Viewer::printCountryCityStats(cities, "Cities", "Number of flights", nameSize);
}

/*! @brief Método auxiliar, utilizado para ordenar de forma decrescente um set de companhias
 *
 */
auto comparatorAirlineDesc = [](Airline *a, Airline *b) {
    int trafficA = a->getNumFlights();
    int trafficB = b->getNumFlights();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA > trafficB;
};

/*! @brief Método auxiliar, utilizado para ordenar de forma crescente um set de companhias
 *
 */
auto comparatorAirlineAsc = [](Airline *a, Airline *b) {
    int trafficA = a->getNumFlights();
    int trafficB = b->getNumFlights();

    if (trafficA == trafficB) {
        return a->getCode() < b->getCode();
    }

    return trafficA < trafficB;
};

/*! @brief Permite visualizar as top k companhias que têm o maior ou menor número de voos, em forma de lista ou gráfico de barras
 * @param k número de airlines a serem impressas
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
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

/*! @brief Permite visualizar as top k companhias num dado país que têm o maior ou menor número de, em forma de lista ou gráfico de barras
 * @param k número de airlines a serem impressas
 * @param airlinesCountry unordered_set de apontadores para as airlines do país
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */

void Manager::getTopKGreatestTrafficAirlinePerCountry(int k, const unordered_set<Airline *> &airlinesCountry, const bool &bars, const bool& asc) const {
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

/*! @brief Permite visualizar os top k aeroportos para onde voa mais ou menos uma companhia, em forma de lista ou gráfico de barras
 * @param k número de aeroportos a serem impressos
 * @param airline apontador para companhia aérea que queremos verificar para onde tem mais voos
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
void Manager::getTopKAirportsAirlineTravelsTo(int k, Airline *airline, const bool &bars, const bool& asc) const {
    map<Airport *, int> airportNumFlights;
    for (auto &elem : connections.getVertexSet()) {
        for (auto &edge : elem->getAdj()) {
            if (edge.hasAirline(airline)) {
                airportNumFlights[edge.getDest()->getInfo()]++;
            }
        }
    }
    vector<pair<Airport *,int>> vec(airportNumFlights.begin(), airportNumFlights.end());
    if(asc) std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second < b.second;});
    else std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second > b.second;});
    if (k > vec.size()) k = vec.size();
    vector<pair<Airport *,int>> res;
    auto it = vec.begin();
    int nameSize = 0;
    while (k != 0) {
        if (it->first->getName().length() > nameSize) it->first->getName().length();
        res.push_back(*it);
        it++;
        k--;
    }
    if (bars) Viewer::printTopKVectorBars(res, asc);
    else Viewer::printTopKVector(res,"Airports", "Number of Flights", nameSize);

}

/*! @brief Permite visualizar os top k aeroportos que têm o maior ou menor número de companhias a operar no aeroporto, em forma de lista ou gráfico de barras
 * @param k número de aeroportos a serem impressos
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
void Manager::getTopKAirportsWithMoreAirlines(int k, const bool &bars, const bool& asc) const {
    vector<pair<Airport *, int>> airportNumAirlines;
    for (auto& elem : connections.getVertexSet()) {
        set<Airline *> air;
        for (auto &edge : elem->getAdj()) {
            for (auto airline : edge.getAirlines()) {
                air.insert(airline);
            }
        }
        airportNumAirlines.emplace_back(elem->getInfo(), air.size());
    }
    if(asc) std::sort(airportNumAirlines.begin(), airportNumAirlines.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second < b.second;});
    else std::sort(airportNumAirlines.begin(), airportNumAirlines.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second > b.second;});
    if (k > airportNumAirlines.size()) k = airportNumAirlines.size();
    vector<pair<Airport *,int>> res;
    auto it = airportNumAirlines.begin();
    int nameSize = 0;
    while (k != 0) {
        if (it->first->getName().length() > nameSize) nameSize = it->first->getName().length();
        res.push_back(*it);
        it++;
        k--;
    }
    if (bars) Viewer::printTopKVectorBars(res, asc);

    else Viewer::printTopKVector(res,"Airports", "Number of Airlines", nameSize);
}

/*! @brief Permite visualizar as top k companhias que voam mais ou menos para um dado aeroporto, em forma de lista ou gráfico de barras
 * @param k número de airlines a serem impressas
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
void Manager::getTopKAirlinesThatFlyMoreToAnAirport(int k, Airport *airport, const bool &bars, const bool& asc) const {
    map<Airline *, int> airlineNumFlightsToAirport;
    for (auto &elem : connections.getVertexSet()) {
        for (auto &edge : elem->getAdj()) {
            if (edge.getDest()->getInfo() == airport) {
                for(auto &airline : edge.getAirlines()) {
                    airlineNumFlightsToAirport[airline]++;
                }
            }
        }
    }
    vector<pair<Airline *,int>> vec(airlineNumFlightsToAirport.begin(), airlineNumFlightsToAirport.end());
    if(asc) std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second < b.second;});
    else std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second > b.second;});
    if (k > vec.size()) k = vec.size();
    vector<pair<Airline *,int>> res;
    auto it = vec.begin();
    int nameSize = 0;
    while (k != 0) {
        if (it->first->getName().length() > nameSize) nameSize = it->first->getName().length();
        res.push_back(*it);
        it++;
        k--;
    }
    if (bars) Viewer::printTopKVectorBars(res, asc);
    else Viewer::printTopKVector(res, "Airlines", "Number of flights", nameSize);
}


/*! @brief Faz uma listagem das companhias que operam num dado aeroporto
 * @param airport apontador para aeroporto para o qual se irá imprimir as companhias que voam de lá
 */
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

/*! @brief Faz uma listagem dos aeroportos que operam num dado país ou numa dada cidade
 * @param airportsCountry vetor de apontadores para aeroportos da cidade
 * @param countryCity nome da cidade
 */
void Manager::listAirportsPerCountryCity(const vector<Airport *> &airportsCountry, const string &countryCity) const{
    int maxLengthName = 0;

    for (auto& elem : airportsCountry) {
        if (elem->getName().length() > maxLengthName) maxLengthName = elem->getName().length();
    }
    Viewer::printListAirportsPerCountryCity(airportsCountry, maxLengthName, countryCity);
}

/*!@brief Método auxiliar que converte uma string dada pelo utilizador numa string com letras minúsculas apenas
 * @param word palavra que será convertida em letras minúsculas
 * @return palavra em letras minúsculas
 */
string nameToLower(const string& word) {
    string res;
    for (auto& ch : word) {
        res += tolower(ch);
    }
    return res;
}

/*! @brief Permite fazer uma pesquisa de aeroportos por nome
 * @param airportName nome do aeroporto para o qual se pretende imprimir a informação
 */
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

/*! @brief Permite fazer uma pesquisa de companhias por nome
 * @param airlineName nome da airline que se pretende procurar e imprimir informação
 */
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

/*! @brief Permite visualizar informação relativa a um dado aeroporto
 * @param airport apontador para aeroporto para o qual se pretende imprimir a informação
 */
void Manager::printAirportInfo(Airport *airport) {
    Viewer::printAirportInfo(airport);
}

/*! @brief Permite visualizar informação relativa a uma dada companhia
 * @param airline apontador para airline para a qual se pretende imprimir a informação
 */
void Manager::printAirlineInfo(Airline *airline) {
    Viewer::printAirlineInfo(airline);
}

/*! @brief Permite visualizar as top k companhias que apresentam uma maior relação entre o número de voos que efetuam
 * para um dado aeroporto número total de voos que fazem, em forma de lista ou gráfico de barras
 * @param k número de airlines a serem impressas
 * @param airport apontador para o aeroporto que se pretende obter o rácio
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
void Manager::getTopKAirlinesThatFlyMoreToAnAirportRatio(int k, Airport *airport, const bool &bars, const bool &asc) const {
    map<Airline *, int> airlineNumFlightsToAirport;
    for (auto &elem : connections.getVertexSet()) {
        for (auto &edge : elem->getAdj()) {
            if (edge.getDest()->getInfo() == airport) {
                for(auto &airline : edge.getAirlines()) {
                    airlineNumFlightsToAirport[airline]++;
                }
            }
        }
    }
    vector<pair<Airline *,double>> vec(airlineNumFlightsToAirport.begin(), airlineNumFlightsToAirport.end());
    if(asc) std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second < b.second;});
    else std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first->getName() < b.first->getName(); return a.second > b.second;});
    if (k > vec.size()) k = vec.size();
    vector<pair<Airline *,double>> res;
    auto it = vec.begin();
    int nameSize = 0;
    while (k != 0) {
        if (it->first->getName().length() > nameSize) it->first->getName().length();
        res.emplace_back(*it);
        it++;
        k--;
    }
    if (bars) Viewer::printTopKVectorBarsRatio(res, asc);
    else Viewer::printTopKVectorRatio(res, "Airlines", "Number of flights", nameSize);
}


/*!
 * @brief Imprime no terminal o top k países com mais companhias aéreas
 * @param k número de países a serem impressos
 * @param bars bool utilizada para imprimir ou não o gráfico de barras
 * @param asc bool utilizada para imprimir por ordem ascendente ou descendente
 */
void Manager::getTopKCountriesWithMoreAirlines(int k, const bool &bars, const bool &asc) const {
    map<string,set<Airline *>> countriesNumAirlines;
    for (auto &elem : connections.getVertexSet()) {
        set<Airline *> air;
        for (auto &edge : elem->getAdj()) {
            for (auto &airline : edge.getAirlines()) {
                air.insert(airline);
            }
        }
        countriesNumAirlines[elem->getInfo()->getCountry()].insert(air.begin(), air.end());
    }
    vector<pair<string, int>> vec;
    for (auto &elem : countriesNumAirlines) {
        vec.emplace_back(elem.first, elem.second.size());
    }
    if(asc) std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first < b.first; return a.second < b.second;});
    else std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {if(a.second == b.second) return a.first < b.first; return a.second > b.second;});
    if (k > vec.size()) k = vec.size();
    vector<pair<string, int>> res;
    auto it = vec.begin();
    int nameSize = 0;
    while (k != 0) {
        if (it->first.length() > nameSize) nameSize = it->first.length();
        res.emplace_back(*it);
        it++;
        k--;
    }
    if (bars) Viewer::printCityOrCountryGreatestTrafficBars(res, nameSize, asc);
    else Viewer::printCountryCityStats(res, "Countries", "Number of airlines", nameSize);
}
