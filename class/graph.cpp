#include "graph.h"
#include <iostream>

Graph::Graph()
{
    this->numVertices = 0;
    this->numEdges = 0;
}

void Graph::addEdge(Edge edge)
{
    this->edges.push_back(edge);
    this->numEdges++;
    this->numVertices = calculateNumVertices();
}

void Graph::printGraph()
{
    for (int i = 0; i < this->numEdges; i++)
    {
        std::cout << this->edges[i].getStart() << " " << this->edges[i].getEnd() << " " << this->edges[i].getWeight() << std::endl;
    }
}

int Graph::calculateNumVertices()
{
    std::vector<char> vertices;
    for (int i = 0; i < this->numEdges; i++)
    {
        vertices.push_back(this->edges[i].getStart());
        vertices.push_back(this->edges[i].getEnd());
    }
    for (int i = 0; i < vertices.size(); i++)
    {
        for (int j = i + 1; j < vertices.size(); j++)
        {
            if (vertices[i] == vertices[j])
            {
                vertices.erase(vertices.begin() + j);
                j--;
            }
        }
    }

    return vertices.size();
}