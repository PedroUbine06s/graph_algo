#include "graph.h"
#include <iostream>
#include <vector>

// Função para adicionar uma aresta no grafo
void Graph::addEdge(char vertex, Vertex destiny_vertex)
{
    // Se o vertice não existe no grafo, ele é adicionado
    this->adjacency_list[vertex].push_back(destiny_vertex);
}

std::vector<Vertex> Graph::getAdjacencyList(char key)
{
    return this->adjacency_list[key];
}

Vertex Graph::getVertex(char key)
{
    return this->adjacency_list[key][0];
}

// Função para ordenar a lista de adjacência em ordem lexicográfica
void Graph::orderInLexicographicOrder()
{
    for (std::pair<const char, std::vector<Vertex>> &pair : this->adjacency_list)
    {
        for (int i = 0; i < pair.second.size(); i++)
        {
            for (int j = i + 1; j < pair.second.size(); j++)
            {
                if (pair.second[i].getValue() > pair.second[j].getValue())
                {
                    Vertex temp = pair.second[i];
                    pair.second[i] = pair.second[j];
                    pair.second[j] = temp;
                }
            }
        }
    }
}

// Função para retornar todos os vertices do grafo,
std::vector<char> Graph::getVertices()
{
    std::vector<char> keys;
    for (const auto &pair : adjacency_list)
    {
        keys.push_back(pair.first);
    }
    return keys;
}