#include "vertex.h"

Vertex::Vertex(char vertex, int weight)
{
    this->value = vertex;
    this->weight = weight;
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