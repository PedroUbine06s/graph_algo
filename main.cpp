#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include "class/graph/graph.h"

// Função para fazer a busca em largura
std::string breadthFirstSearch(Graph &graph, char start_vertex)
{
    std::vector<Vertex> adjacency_list = graph.getAdjacencyList(start_vertex);
    std::queue<Vertex> queue;
    // Mapa para guardar os vertices visitados
    std::map<char, bool> visited;
    std::string output(1, start_vertex);
    // Adiciona os vertices adjacentes na fila inicial
    for (int i = 0; i < adjacency_list.size(); i++)
    {
        queue.push(adjacency_list[i]);
        visited[adjacency_list[i].getValue()] = true;
    }
    // Marca o vertice inicial como visitado
    visited[start_vertex] = true;

    while (!queue.empty())
    {
        // Pega o vertice atual da fila e desenfileira
        Vertex current_vertex = queue.front();
        queue.pop();

        output += ", ";
        output += current_vertex.getValue();

        // Pega os vertices adjacentes ao vertice atual
        std::vector<Vertex> adjacency_list = graph.getAdjacencyList(current_vertex.getValue());

        // Adiciona os vertices adjacentes na fila
        for (Vertex vertex : adjacency_list)
        {
            // Se o vertice não foi visitado, ele é adicionado na fila
            if (!visited[vertex.getValue()])
            {
                queue.push(vertex);
                visited[vertex.getValue()] = true;
            }
        }
    }
    return output;
}
// Função recursiva para fazer a busca em profundidade
std::string depthFirstSearch(Graph &graph, char start_vertex, std::map<char, bool> &visited, std::string output)
{
    std::vector<Vertex> adjacency_list = graph.getAdjacencyList(start_vertex);
    visited[start_vertex] = true;
    ;
    output += start_vertex;
    output += ", ";

    for (Vertex vertex : adjacency_list)
    {
        // Se o vertice não foi visitado, ele chama a função recursivamente
        if (!visited[vertex.getValue()])
        {
            output = depthFirstSearch(graph, vertex.getValue(), visited, output);
        }
    }
    // Retorna a string com os vertices visitados para ser impressa
    return output;
}

std::map<char, int> initDistance(Graph graph, char start_vertex)
{
    std::map<char, int> distance;
    std::vector<char> vertices = graph.getVertices();
    for (char vertex : vertices)
    {
        distance[vertex] = -1;
    }
    distance[start_vertex] = 0;
    return distance;
};

std::map<char, bool> initVisited(Graph graph, char start_vertex)
{
    std::map<char, bool> visited;
    std::vector<char> vertices = graph.getVertices();
    for (char vertex : vertices)
    {
        visited[vertex] = false;
    }
    visited[start_vertex] = true;
    return visited;
};

// Função para atualizar a distancia de um vertice
void updateDistance(std::map<char, int> &distance, char vertex, int new_distance)
{
    if (distance[vertex] == -1 || distance[vertex] > new_distance)
    {
        distance[vertex] = new_distance;
    }
}

Vertex getShortestNonVisetedPath(std::vector<Vertex> adjacency_vertex, std::map<char, int> distance, std::map<char, bool> visited)
{
    Vertex shortest_vertex;
    int shortest_distance = -1;
    for (Vertex vertex : adjacency_vertex)
    {
        if (!visited[vertex.getValue()])
        {
            if (shortest_distance == -1 || distance[vertex.getValue()] < shortest_distance)
            {
                shortest_distance = distance[vertex.getValue()];
                shortest_vertex = vertex;
            }
        }
    }
    return shortest_vertex;
}

std::map<char, char> initPrevius(Graph graph)
{
    std::map<char, char> previus;
    std::vector<char> vertices = graph.getVertices();
    for (char vertex : vertices)
    {
        previus[vertex] = ' ';
    }
    return previus;
};
// Algorigtmo de djkstra recursivo
bool djkstraAlgo(Graph &graph, std::map<char, int> &distance, std::map<char, bool> &visited, std::map<char, char> &previus, char stopVertex, char startVertex)
{
    // Quando o vertice de inicio é igual ao vertice de parada, retornamos true pois encontramos o menor caminho
    if (startVertex == stopVertex)
    {
        return true;
    }

    std::vector<Vertex> adjancency_vertex = graph.getAdjacencyList(startVertex);
    for (Vertex v : adjancency_vertex)
    {
        // Se o vertice já foi visitado, ele é ignorado
        if (visited[v.getValue()])
            continue;
        // Soma a distancia do vertice atual com o peso da aresta
        int distance_sum = distance[startVertex] + v.getWeight();
        // Se a distancia do vertice atual é -1 ou a distancia somada é menor que a distancia atual, a distancia é atualizada
        if (distance[v.getValue()] == -1 || distance_sum < distance[v.getValue()])
        {
            // Se a distancia do vertice atual é -1, ele é transformado em 0 para poder somar com o peso da aresta
            int transformed = distance[v.getValue()] == -1 ? 0 : distance[v.getValue()];
            // Atualiza a distancia do vertice, somando a distancia do vertice atual com o peso da aresta
            updateDistance(distance, v.getValue(), transformed + v.getWeight() + distance[startVertex]);
            // Atualiza o mapa de vertices previos para guardar o caminho
            previus[v.getValue()] = startVertex;
        }
    }
    // Marca o vertice atual como visitado
    visited[startVertex] = true;
    // Pega o vertice com o menor caminho que ainda não foi visitado
    Vertex shortest_vertex = getShortestNonVisetedPath(adjancency_vertex, distance, visited);
    // Se não houver vertice com menor caminho, retorna false
    return djkstraAlgo(graph, distance, visited, previus, stopVertex, shortest_vertex.getValue());
}

std::string printPath(std::map<char, char> previus, char start, char end)
{
    std::string path = "";
    char current_vertex = end;
    while (current_vertex != start)
    {
        path = current_vertex + path;
        current_vertex = previus[current_vertex];
    }
    path = current_vertex + path;
    return path;
}
// Funcão para ler o arquivo e montar o grafo, se o grafo for direcionado, ele adiciona a aresta de volta
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
        // Se a linha tiver mais de 5 caracteres, significa que tem um peso e ele é adicionado
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

    Graph graph3;
    readFile(graph3, "graphs/g3.txt", false);
    std::map<char, int> distance = initDistance(graph3, 'x');
    std::map<char, bool> visited = initVisited(graph3, 'x');
    std::map<char, char> previus = initPrevius(graph3);
    djkstraAlgo(graph3, distance, visited, previus, 't', 'x');
    std::string path = printPath(previus, 'x', 't');

    std::cout << "BUSCA EM LARGURA" << std::endl;
    std::cout << "Fazendo busca em largura a partir do vertice 'b': ";
    std::cout << breadthFirstSearch(graph1, 'b') << std::endl;

    std::cout << "\nBUSCA EM PROFUNDIDADE" << std::endl;
    std::cout << "Fazendo busca em profundidade a partir do vertice 'a': ";
    std::cout << depthFirstSearch(graph2, 'a', visitedDFS, "") << std::endl;

    std::cout << "\nDJKSTRA" << std::endl;
    std::cout << "Fazendo o algo de djkstra para encontrar o menor caminho entre 'x' e 't'" << std::endl;
    std::cout << "Distancia do menor caminho: " << distance['t'] << std::endl;
    std::cout << "Caminho: " << path << std::endl;
    return 0;
}
