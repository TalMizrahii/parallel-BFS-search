/**
 * @file graph.cpp
 * @brief Implementation of the Graph class and associated C functions for graph operations.
 */

#include "graph.h"

#ifdef __cplusplus

/**
 * @brief Constructor for the Graph class.
 * @param vertices The number of vertices in the graph.
 * @details Initializes the graph with the specified number of vertices.
 */
Graph::Graph(int vertices) : numVertices(vertices) {
    adjacencyLists.resize(vertices, nullptr);
}

/**
 * @brief Destructor for the Graph class.
 * @details Frees memory allocated for nodes in each adjacency list.
 */
Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        Node *current = adjacencyLists[i];
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
}

/**
 * @brief Creates a new graph node with the given vertex value.
 * @param v The vertex value for the new node.
 * @return A pointer to the newly created node.
 */
Node *Graph::createNode(vertex v) {
    return new Node(v);
}

/**
 * @brief Adds an undirected edge between the source and destination vertices.
 * @param source The source vertex of the edge.
 * @param destination The destination vertex of the edge.
 */
void Graph::addEdge(vertex source, vertex destination) {
    // Add edge to the adjacency list of both vertices.
    Node *newNode = createNode(destination);
    newNode->next = adjacencyLists[source];
    adjacencyLists[source] = newNode;

    newNode = createNode(source);
    newNode->next = adjacencyLists[destination];
    adjacencyLists[destination] = newNode;
}

/**
 * @brief Gets the adjacency lists of the graph.
 * @return A vector of pointers to the head nodes of the adjacency lists.
 */
std::vector<Node *> Graph::getAdjacencyLists() {
    return this->adjacencyLists;
}

/**
 * @brief Creates a new graph with the specified number of vertices.
 * @param vertices The number of vertices in the new graph.
 * @return A pointer to the newly created graph.
 */
extern "C" {
    Graph* createGraph(int vertices) {
        return new Graph(vertices);
    }

    /**
     * @brief Destroys the given graph and frees associated memory.
     * @param graph A pointer to the graph to be destroyed.
     */
    void destroyGraph(Graph* graph) {
        delete graph;
    }

    /**
     * @brief Adds an undirected edge between the source and destination vertices in the given graph.
     * @param graph A pointer to the graph where the edge will be added.
     * @param source The source vertex of the edge.
     * @param destination The destination vertex of the edge.
     */
    void addEdge(Graph* graph, int source, int destination) {
        graph->addEdge(source, destination);
    }
} // extern "C"

#endif // __cplusplus
