#include "edge.h"

Edge::Edge(char start, char end, int weight)
{
    this->start = start;
    this->end = end;
    this->weight = weight;
}

// Getters

char Edge::getEnd()
{
    return this->end;
}
char Edge::getStart()
{
    return this->start;
}
int Edge::getWeight()
{
    return this->weight;
}

// Setters

void Edge::setEnd(char end)
{
    this->end = end;
}
void Edge::setStart(char start)
{
    this->start = start;
}
void Edge::setWeight(int weight)
{
    this->weight = weight;
}
