#ifndef GRAPH_H
#define GRAPH_H
#include "edge.h"
#include <vector>

class Graph
{
    std::vector<Edge> edges;
    int numVertices;
    int numEdges;

public:
    Graph();
    void addEdge(Edge edge);
    void printGraph();
    int getNumEdges();

private:
    int calculateNumVertices();
};
#endif