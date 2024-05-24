#include <iostream>
#include <fstream>
#include "class/graph.h"

void readFile(Graph &graph, std::string filename)
{
    std::ifstream file(filename);
    char start, end;
    int weight;
    if (!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        start = line[0];
        end = line[2];
        if (line.size() > 5)
            weight = line[5];
        else
            weight = 0;
        graph.addEdge(Edge(start, end, weight));
    }
    file.close();
}

int main()
{
    Graph graph1;
    readFile(graph1, "graphs/g1.txt");
    Graph graph2;
    readFile(graph2, "graphs/g2.txt");
    Graph graph3;
    readFile(graph3, "graphs/g3.txt");
    graph2.printGraph();
    return 0;
}
