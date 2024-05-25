#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include "class/graph/graph.h"

std::string breadthFirstSearch(Graph &graph, char start_vertex)
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

    while (!queue.empty())
    {
        Vertex current_vertex = queue.front();
        queue.pop();
        output += ", ";
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
    return output;
}

std::string depthFirstSearch(Graph &Graph, char start_vertex, std::map<char, bool> &visited, std::string output)
{
    std::vector<Vertex> adjacency_list = Graph.getAdjacencyList(start_vertex);
    visited[start_vertex] = true;
    ;
    output += start_vertex;
    output += ", ";

    for (Vertex vertex : adjacency_list)
    {
        if (!visited[vertex.getValue()])
        {
            output = depthFirstSearch(Graph, vertex.getValue(), visited, output);
        }
    }
    return output;
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
    Graph graph1;
    readFile(graph1, "graphs/g1.txt", false);
    graph1.orderInLexicographicOrder();

    Graph graph2;
    readFile(graph2, "graphs/g2.txt", true);
    graph2.orderInLexicographicOrder();
    std::map<char, bool> visitedDFS;

    std::cout << "BUSCA EM LARGURA" << std::endl;
    std::cout << "Fazendo busca em largura a partir do vertice 'b': ";
    std::cout << breadthFirstSearch(graph1, 'b') << std::endl;

    std::cout << "\nBUSCA EM PROFUNDIDADE" << std::endl;
    std::cout << "Fazendo busca em profundidade a partir do vertice 'a': ";
    std::cout << depthFirstSearch(graph2, 'a', visitedDFS, "") << std::endl;

    return 0;
}
