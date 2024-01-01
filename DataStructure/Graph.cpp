//
// Created by Wagner Pedrosa on 30/11/2023.
//

#include "Graph.h"


/****************** Provided constructors and functions ********************/

/*!
 * @brief Permite obter o número de vértices do grafo
 * @return inteiro correspondente ao número de vértices do grafo
 */
int Graph::getNumVertex() const {
    return vertexSet.size();
}

/*!
 * @brief Permite obter o conjunto de vértices do grafo
 * @return vetor de apontadores para vértices do grafo
 */
vector<Vertex * > Graph::getVertexSet() const {
    return vertexSet;
}

/*!
 * @brief Permite adicionar um vértice ao grafo
 * @param in apontador para aeroporto correspondente ao vértice que se pretende adicionar
 * @return true no caso de ter sido possível adicionar o vértice
 * @return false no caso contrário
 */
bool Graph::addVertex(Airport* in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}

/*!
 * @brief Permite adicionar um edge ao grafo, dando um ponto de partida, chegada, peso e airline
 * @param sourc apontador para aeroporto de partida do edge que se pretende adicionar
 * @param dest apontador para aeroporto de destino do edge que se pretende adicionar
 * @param w valor correspondente à distância entre os dois aeroportos
 * @param airline apontador para airline que faz esse voo
 * @return true no caso de ter sido possível adicionar o edge
 * @return false no caso contrário
 * (|V|)
 */
bool Graph::addEdge(Airport* sourc, Airport *dest, double w, Airline* airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL) {
        return false;
    }
    Edge e = Edge(v2, w);
    v1->addAdj(e, airline);
    return true;
}

/*!
 * @brief Permite remover um edge do grafo, dando um ponto de partida e chegada
 * @param sourc apontador para aeroporto de partida do edge que se pretende remover
 * @param dest apontador para aeroporto de destino do edge que se pretende remover
 * @return true no caso de ter sido possível remover o edge
 * @return false no caso contrário
 */
bool Graph::removeEdge(Airport* sourc, Airport* dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*!
 * @brief Permite remover um vértice do grafo
 * @param in apontador para aeroporto que se pretende remover
 * @return true no caso de ter sido possível remover o Aeroporto
 * @return false no caso contrário
 */
bool Graph::removeVertex(Airport* in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->airport  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

/*!
 * @brief Permite verificar se um aeroporto existe no grafo
 * @param in Apontador para o aeroporto que se quer procurar
 * @return apontador para o vértice correspondente a esse aeroporto no caso de existir
 * @return nullptr no caso do aeroporto não existir
 */
Vertex * Graph::findVertex(Airport* in) const {
    for (auto v : vertexSet)
        if (v->airport == in)
            return v;
    return NULL;
}
