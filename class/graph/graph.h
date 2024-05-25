#ifndef GRAPH_H
#define GRAPH_H
#include "../vertex/vertex.h"
#include <vector>
#include <map>

class Graph
{
private:
    std::map<char, std::vector<Vertex>> adjacency_list;

public:
    void addEdge(char vertex, Vertex destiny_vertex);
};
#endif