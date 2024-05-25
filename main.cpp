#include <iostream>
#include <fstream>
#include <string>
#include "class/graph/graph.h"

void readFile(Graph &graph, std::string filename, bool isDirected)
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
            std::string weight_str = line.substr(4, line.find(';') - 4);
            int weight_int = std::stoi(weight_str);
            destiny_vertex.setWeight(weight_int);
        }
        graph.addEdge(origin_vertex, destiny_vertex);
        if (!isDirected)
        {

            Vertex origin_vertex_obj(origin_vertex);
            if (line.size() > 4)
            {
                std::string weight_str = line.substr(4, line.find(';') - 4);
                int weight_int = std::stoi(weight_str);
                origin_vertex_obj.setWeight(weight_int);
            }

            graph.addEdge(destiny_vertex_char, origin_vertex_obj);
        }
    }
    file.close();
}

int main()
{
    Graph graph;
    readFile(graph, "graphs/g3.txt", false);
    std::cout << "Graph created" << std::endl;
    return 0;
}
