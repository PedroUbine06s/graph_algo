#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "class/graph/graph.h"

void breadthFirstSearch(Graph &graph, char start_vertex)
{
    std::vector<Vertex> adjacency_list = graph.getAdjacencyList(start_vertex);
    std::queue<Vertex> queue;
    std::map<char, bool> visited;
    std::string output(1, start_vertex);
    for (int i = 0; i < adjacency_list.size(); i++)
    {
        queue.push(adjacency_list[i]);
        visited[adjacency_list[i].getValue()] = true;
    }

    visited[start_vertex] = true;
    bool is_first = true;

    while (!queue.empty())
    {
        Vertex current_vertex = queue.front();

        queue.pop();
        if (current_vertex.getValue() == 'a')
        {
            std::cout << std::endl;
        };
        output += current_vertex.getValue();
        std::vector<Vertex> adjacency_list = graph.getAdjacencyList(current_vertex.getValue());
        for (Vertex vertex : adjacency_list)
        {
            if (!visited[vertex.getValue()])
            {
                queue.push(vertex);
                visited[vertex.getValue()] = true;
            }
        }
    }
    std::cout << output;
    std::cout << std::endl;
}

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
        if (line.size() > 5)
        {
            std::string weight_str = line.substr(4, line.find(';') - 4);
            int weight_int = std::stoi(weight_str);
            destiny_vertex.setWeight(weight_int);
        }
        graph.addEdge(origin_vertex, destiny_vertex);

        if (!isDirected)
        {

            Vertex origin_vertex_obj(origin_vertex);
            if (line.size() > 5)
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
    readFile(graph, "graphs/g1.txt", false);
    graph.orderInLexicographicOrder();
    breadthFirstSearch(graph, 'b');
    return 0;
}
