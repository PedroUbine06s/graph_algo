#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "class/graph.h"

void readFile(Graph &graph, std::string filename)
{
    std::ifstream file(filename);
    char start, end;
    int weight;
    int id;
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
        id = graph.getNumEdges() + 1;
        graph.addEdge(Edge(start, end, weight, id));
    }
    file.close();
}

int main()
{
    std::vector<Graph> graphs(3);
    std::vector<std::string> fileNames = {"graphs/g1.txt", "graphs/g2.txt", "graphs/g3.txt"};

    for (int i = 0; i < graphs.size(); i++)
    {
        readFile(graphs[i], fileNames[i]);
    }
    graphs[0].printGraph();
    std::cout << "----------------" << std::endl;
    graphs[1].printGraph();
    std::cout << "----------------" << std::endl;
    graphs[2].printGraph();
    std::cout << "----------------" << std::endl;

    return 0;
}
