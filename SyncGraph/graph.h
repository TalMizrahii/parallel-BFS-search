#ifndef PARALLELBFS_GRAPH_H
#define PARALLELBFS_GRAPH_H


#ifdef __cplusplus
extern "C" {
#endif
    typedef struct Graph Graph;
    Graph *createGraph(int vertices);
    void addEdge(Graph *graph, int source, int destination);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus

#include <iostream>
#include <vector>
#include <mutex>

typedef int vertex;
using namespace std;
class Node {
public:
    vertex v;
    Node *next;

    explicit Node(vertex v) : v(v), next(nullptr) {}
};

class Graph {
public:
    explicit Graph(int vertices);
    ~Graph();

    void addEdge(vertex source, vertex destination);

    unsigned int getNumVertices() const { return numVertices; }

    vector<Node *> getAdjacencyLists();

protected:
    Node *createNode(vertex v);

private:
    unsigned int numVertices;
    vector<Node *> adjacencyLists;
};

#endif
#endif //PARALLELBFS_GRAPH_H
