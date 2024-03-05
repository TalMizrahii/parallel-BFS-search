#include "graph.h"

Graph::Graph(int vertices) : numVertices(vertices), adjacencyLists(vertices, nullptr), numVisits(vertices, 0), numVisitsMutexes(vertices) {
    for (int i = 0; i < vertices; i++) {
        std::lock_guard<std::mutex> lock(numVisitsMutexes[i]);
    }
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        Node* current = adjacencyLists[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

Node* createNode(vertex v) {
    return new Node(v);
}

void Graph::addEdge(vertex source, vertex destination) {
    Node* newNode = createNode(destination);
    newNode->next = adjacencyLists[source];
    adjacencyLists[source] = newNode;

    newNode = createNode(source);
    newNode->next = adjacencyLists[destination];
    adjacencyLists[destination] = newNode;
}

void Graph::printGraph() {
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Adjacency list of vertex " << i << ": ";
        Node* current = adjacencyLists[i];
        while (current != nullptr) {
            std::cout << current->v << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}
