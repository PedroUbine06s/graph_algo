#include <iostream>
#include <fstream>
#include "class/graph/graph.h"

void readFile(Graph &graph, std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        char origin_vertex = line[0];
        char destiny_vertex_char = line[2];
        Vertex destiny_vertex(destiny_vertex_char);
        if (line.size() > 4)
        {
            destiny_vertex.setWeight(line[4]);
        }
        graph.addEdge(origin_vertex, destiny_vertex);
    }
    file.close();
}

int main()
{
    Graph graph;
    readFile(graph, "graphs/g1.txt");
    std::cout << "Graph created" << std::endl;
    return 0;
}
