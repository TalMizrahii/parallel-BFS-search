#include "graph.h"
#include "bfs.cpp"

#ifdef __cplusplus

Graph::Graph(int vertices) : numVertices(vertices) {
    adjacencyLists.resize(vertices, nullptr);
}

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

Node *Graph::createNode(vertex v) {
    return new Node(v);
}

void Graph::addEdge(vertex source, vertex destination) {
    Node *newNode = createNode(destination);
    newNode->next = adjacencyLists[source];
    adjacencyLists[source] = newNode;

    newNode = createNode(source);
    newNode->next = adjacencyLists[destination];
    adjacencyLists[destination] = newNode;
}

void bfs(Graph *graph, int **m) {
    bfsStart(graph, m);
}

std::vector<Node *> Graph::getAdjacencyLists() {
    return this->adjacencyLists;
}
extern "C" {

    Graph* createGraph(int vertices) {
        return new Graph(vertices);
    }

    void destroyGraph(Graph* graph) {
        delete graph;
    }

    void addEdge(Graph* graph, int source, int destination) {
        graph->addEdge(source, destination);
    }

} // extern "C"

#endif // __cplusplus