#ifndef EDGE_H
#define EDGE_H

class Edge
{
    char start;
    char end;
    int weight;
    int id;

public:
    Edge(char start, char end, int weight, int id);
    char getStart();
    char getEnd();
    int getWeight();
    void setStart(char start);
    void setEnd(char end);
    void setWeight(int weight);
};
#endif