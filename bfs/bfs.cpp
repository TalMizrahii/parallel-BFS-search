#include <queue>
#include <mutex>
#include <vector>
#include "ThreadPool.h"
#include "graph.h"

/**
 * Performs BFS from a given start vertex and updates the shortest path matrix m.
 * @param graph The graph to traverse.
 * @param startVertex The starting vertex for BFS.
 * @param m The matrix to store the shortest paths.
 * @param m_mtx Mutex for synchronizing access to the matrix.
 */
void bfsFromVertex(Graph *graph, int startVertex, int **m, std::mutex &m_mtx) {
    // Keeps track of visited vertices to avoid revisiting them
    vector<bool> visited(graph->getNumVertices(), false);

    // Queue to manage the BFS traversal. Store pairs of vertex and its depth.
    queue<vector<int>> toVisit;

    // Mark the starting vertex as visited and enqueue it with depth 0
    visited[startVertex] = true;
    vector<int> v;
    v.push_back(startVertex);
    v.push_back(0);
    toVisit.push(v);

    // Process the queue until it's empty
    while (!toVisit.empty()) {
        // Extract the vertex and its depth from the queue
        int vertex = toVisit.front()[0];
        int depth = toVisit.front()[1];
        toVisit.pop();

        // Lock the mutex before accessing the shared matrix
        std::lock_guard<std::mutex> lock(m_mtx);
        // Update the distance of the vertex from the start vertex in the matrix
        m[startVertex][vertex] = depth;

        // Explore all adjacent vertices
        for (Node *adj = graph->getAdjacencyLists()[vertex]; adj != nullptr; adj = adj->next) {
            int adjVertex = adj->v;
            // If the adjacent vertex has not been visited, mark it visited and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                // Enqueue the adjacent vertex with a depth incremented by 1
                vector<int> vNext;
                vNext.push_back(adjVertex);
                vNext.push_back(depth + 1);
                toVisit.push(vNext);
            }
        }
    }
}


void bfsStart(Graph *graph, int **m) {
    ThreadPool pool;
    std::mutex mutexV;
    unsigned int verticesNumber = graph->getNumVertices();
    for (unsigned int i = 0; i < verticesNumber; i++) {
        std::fill(m[i], m[i] + verticesNumber, -1);
        m[i][i] = 0;
    }

    for (int i = 0; i < verticesNumber; i++) {
        pool.enqueueTask([graph, i, m, &mutexV] {
            bfsFromVertex(graph, i, m, mutexV);
        });
    }
    delete graph;
}
