#ifndef Vertex_H
#define Vertex_H

class Vertex
{
private:
    char value;
    int weight;

public:
    Vertex(char value = ' ', int weight = 0);
    char getValue();
    int getWeight();
    void setWeight(int weight);
};
#endif