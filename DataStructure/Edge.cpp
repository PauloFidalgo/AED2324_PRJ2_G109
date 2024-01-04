//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include <set>
#include "Edge.h"

Edge::Edge(Vertex *d, double w): dest(d), weight(w) {}

/*!
 * @brief Permite obter o vértice de destino de um edge
 * @return apontador para vértice de destino
 * O(1)
 */
Vertex *Edge::getDest() const {
    return this->dest;
}

/*!
 * @brief Setter para vértice de destino de um edge
 * @param d vértice de destino
 * O(1)
 */
void Edge::setDest(Vertex *d) {
    this->dest = d;
}

/*!
 * @brief Permite obter a distância correspondente a um edge
 * @return double correspondente à distância de um edge
 * O(1)
 */
double Edge::getWeight() const {
    return this->weight;
}

/*!
 * @brief Setter para distância de um edge
 * @param weight distância
 * O(1)
 */
void Edge::setWeight(double weight) {
    this->weight = weight;
}

/*!
 * @brief Permite adicionar uma airline a um edge, significa que essa airline faz esse voo
 * @param airline apontador para airline a ser adicionada ao set de airlines de um edge
 * O(1)
 */
void Edge::addAirline(Airline* airline) {
    this->airlines.insert(airline);
}

/*!
 * @brief Permite obter o set de airlines correspondentes a um edge
 * @return set de apontadores para airlines que fazem esse voo
 * O(1)
 */
std::unordered_set<Airline *> Edge::getAirlines() const {
    return this->airlines;
}

/*!
 * @brief Permite verificar se o set de airlines correspondentes ao edge contém uma airline
 * @param airline apontador para airline que se pretende verificar se está contida no set de airlines do edge
 * @return true no caso afirmativo
 * @return false no caso negativo
 * O(1)
 */
bool Edge::hasAirline(Airline *airline) const {
    auto it = airlines.find(airline);

    return it != airlines.end();
}
