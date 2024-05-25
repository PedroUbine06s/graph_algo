#include "vertex.h"

Vertex::Vertex(char vertex, int weight)
{
    this->value = vertex;
    this->weight = weight;
    this->visited = false;
}

int Vertex::getWeight()
{
    return this->weight;
}

void Vertex::setWeight(int weight)
{
    this->weight = weight;
}

char Vertex::getValue()
{
    return this->value;
}

bool Vertex::isVisited()
{
    return this->visited;
}

void Vertex::setVisited()
{
    this->visited = true;
}