//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Vertex.h"

/*!
 * @brief Construtor da classe Vertex.
 * @param in Um apontador para o Aeroporto associado ao vértice.
 */
Vertex::Vertex(Airport* in): airport(in) {}

/*!
 * @brief Obtém o Aeroporto associado ao vértice.
 * @return Um apontador para o Aeroporto associado ao vértice.
 */
Airport* Vertex::getInfo() const {
    return airport;
}

/*!
 * @brief Define as informações do Aeroporto associado ao vértice.
 * @param in As informações do Aeroporto que serão definidas.
 */
void Vertex::setInfo(const Airport &in) {
    *airport = in;
}

/*!
 * @brief Verifica se o vértice está em processo de processamento.
 * @return true se o vértice está em processo de processamento, false caso contrário.
 */
bool Vertex::isProcessing() const {
    return processing;
}

/*!
 * @brief Define se o vértice está em processo de processamento.
 * @param p Booleano indicando se o vértice está em processo de processamento.
 */
void Vertex::setProcessing(const bool &p) {
    this->processing = p;
}

/*!
 * @brief Verifica se o vértice foi visitado.
 * @return true se o vértice foi visitado, false caso contrário.
 */
bool Vertex::isVisited() const {
    return visited;
}

/*!
 * @brief Obtém o valor low associado ao vértice.
 * @return O valor low associado ao vértice.
 */
int Vertex::getLow() const {
    return low;
}

/*!
 * @brief Obtém o número associado ao vértice.
 * @return O número associado ao vértice.
 */
int Vertex::getNum() const {
    return num;
}

/*!
 * @brief Define o valor low associado ao vértice.
 * @param low O valor low que será definido.
 */
void Vertex::setLow(int low) {
    this->low = low;
}

/*!
 * @brief Define o número associado ao vértice.
 * @param num O número que será definido.
 */
void Vertex::setNum(int num) {
    this->num = num;
}

/*!
 * @brief Define se o vértice foi visitado.
 * @param v Booleano indicando se o vértice foi visitado.
 */
void Vertex::setVisited(const bool &v) {
    this->visited = v;
}

/*!
 * @brief Obtém uma referência para o vetor de arestas adjacentes ao vértice.
 * @return Uma referência para o vetor de arestas adjacentes ao vértice.
 */
const std::vector<Edge> &Vertex::getAdj() const {
    return adj;
}

/*!
 * @brief Obtém uma referência para o vetor de arestas adjacentes ao vértice.
 * @return Uma referência para o vetor de arestas adjacentes ao vértice.
 */
std::vector<Edge> &Vertex::getAdj() {
    return adj;
}

/*!
 * @brief Define as arestas adjacentes ao vértice.
 * @param destinations Um vetor contendo as arestas que serão definidas como adjacentes ao vértice.
 */
void Vertex::setAdj(const std::vector<Edge> &destinations) {
    this->adj = destinations;
}

/*!
 * @brief Adiciona uma aresta adjacente ao vértice.
 * @param destination A aresta que será adicionada como adjacente.
 * @param airline A companhia aérea associada à aresta.
 * O(n)
 */
void Vertex::addAdj(Edge &destination, Airline* airline) {
    for (auto& flight : this->adj) {
        if (flight.dest->airport == destination.dest->airport) {
            flight.addAirline(airline);
            return;
        }
    }
    destination.addAirline(airline);
    this->adj.push_back(destination);
}

/*!
 * @brief Adiciona uma aresta ao vértice.
 * @param d O vértice de destino da aresta.
 * @param w O peso da aresta.
 */
void Vertex::addEdge(Vertex *d, double w) {
    adj.push_back(Edge(d, w));
}

/*!
 * @brief Verifica se existe um voo para um determinado Aeroporto de destino.
 * @param destination O Aeroporto de destino a ser verificado.
 * @return true se houver um voo para o Aeroporto de destino, false caso contrário.
 */
bool Vertex::hasFlight(const Airport *destination) {
    for (auto& flight : this->adj) {
        if (flight.dest->airport->getCode() == destination->getCode()) {
            return true;
        }
    }
    return false;
}

/*!
 * @brief Remove uma aresta para um vértice específico.
 * @param d O vértice de destino da aresta a ser removida.
 * @return true se a aresta foi removida com sucesso, false caso contrário.
 */
bool Vertex::removeEdgeTo(Vertex *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}
