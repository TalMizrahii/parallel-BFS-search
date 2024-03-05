#ifndef PARALLELBFS_GRAPH_H
#define PARALLELBFS_GRAPH_H
#include <iostream>
#include <vector>
#include <mutex>

typedef int vertex;

class Node {
public:
    vertex v;
    Node* next;

    Node(vertex v) : v(v), next(nullptr) {}
};

class Graph {
public:
    Graph(int vertices);
    ~Graph();

    void addEdge(vertex source, vertex destination);
    void printGraph();

private:
    unsigned int numVertices;
    std::vector<Node*> adjacencyLists;
    std::vector<int> numVisits; // Number of times a vertex has been visited
    std::vector<std::mutex> numVisitsMutexes; // Mutex for each vertex
};

#endif //PARALLELBFS_GRAPH_H

