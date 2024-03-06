/**
 * @file graph.h
 * @brief Declaration of the Graph class and associated C functions for graph operations.
 */

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

/**
 * @class Node
 * @brief Represents a node in the graph.
 */
class Node {
public:
    vertex v; /**< The vertex value of the node. */
    Node *next; /**< Pointer to the next node in the adjacency list. */

    /**
     * @brief Constructor for the Node class.
     * @param v The vertex value of the node.
     */
    explicit Node(vertex v) : v(v), next(nullptr) {}
};

/**
 * @class Graph
 * @brief Represents an undirected graph with methods for creating nodes, adding edges, and accessing adjacency lists.
 */
class Graph {
public:
    /**
     * @brief Constructor for the Graph class.
     * @param vertices The number of vertices in the graph.
     */
    explicit Graph(int vertices);

    /**
     * @brief Destructor for the Graph class.
     * @details Frees memory allocated for nodes in each adjacency list.
     */
    ~Graph();

    /**
     * @brief Adds an undirected edge between the source and destination vertices.
     * @param source The source vertex of the edge.
     * @param destination The destination vertex of the edge.
     */
    void addEdge(vertex source, vertex destination);

    /**
     * @brief Gets the number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    unsigned int getNumVertices() const { return numVertices; }

    /**
     * @brief Gets the adjacency lists of the graph.
     * @return A vector of pointers to the head nodes of the adjacency lists.
     */
    vector<Node *> getAdjacencyLists();

protected:
    /**
     * @brief Creates a new graph node with the given vertex value.
     * @param v The vertex value for the new node.
     * @return A pointer to the newly created node.
     */
    Node *createNode(vertex v);

private:
    unsigned int numVertices; /**< The number of vertices in the graph. */
    vector<Node *> adjacencyLists; /**< A vector of pointers to the head nodes of the adjacency lists. */
};

#endif

#endif //PARALLELBFS_GRAPH_H
