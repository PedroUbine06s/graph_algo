#include "graph.h"
#include <iostream>

void Graph::addEdge(char vertex, Vertex destiny_vertex)
{
    this->adjacency_list[vertex].push_back(destiny_vertex);
}