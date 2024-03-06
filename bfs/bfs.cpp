/**
 * @file bfs.cpp
 * @brief Implementation of BFS algorithms using ThreadPool for parallel processing.
 */

#include "bfs.h"
#include <queue>
#include <mutex>
#include <vector>
#include "../ThreadPoolCPP/ThreadPool.h"

/**
 * @brief Performs a BFS traversal starting from a given vertex.
 * @param graph A pointer to the Graph object.
 * @param startVertex The starting vertex for BFS.
 * @param m Pointer to the matrix to store BFS distances.
 * @param mutexV A mutex to synchronize access to the matrix.
 */
void bfsVisit(Graph *graph, int startVertex, int **m, std::mutex &mutexV) {
    std::vector<bool> visited(graph->getNumVertices(), false);
    // Queue to manage the BFS traversal. Store vertex, depth, and parent in a vector.
    std::queue<std::vector<int>> q;
    // Mark the starting vertex as visited and enqueue it with depth 0
    visited[startVertex] = true;
    q.emplace(std::vector<int>{startVertex, 0});
    // Process the queue until it's empty
    while (!q.empty()) {
        // Extract the vector containing vertex, depth, and parent from the queue
        auto current = q.front();
        q.pop();
        int v = current[0];
        int depth = current[1];
        // Lock the mutex before accessing the shared matrix
        std::lock_guard<std::mutex> lock(mutexV);
        // Update the distance of the vertex from the start vertex in the matrix
        m[startVertex][v] = depth;
        // Explore all adjacent vertices
        for (Node *adj = graph->getAdjacencyLists()[v]; adj != nullptr; adj = adj->next) {
            int adjVertex = adj->v;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                // Push the vector containing adjacent vertex, depth + 1, and parent to the queue
                q.emplace(std::vector<int>{adjVertex, depth + 1});
            }
        }
    }
}

/**
 * @brief Performs BFS traversal in parallel using a ThreadPool.
 * @param graph A pointer to the Graph object.
 * @param m Pointer to the matrix to store BFS distances.
 */
void bfs(Graph *graph, int **m) {
    ThreadPool pool(graph);
    std::mutex mutexV;

    const unsigned int verticesNumber = graph->getNumVertices();

    // Initialize matrix m.
    for (auto i = 0u; i < verticesNumber; ++i) {
        std::fill(m[i], m[i] + verticesNumber, -1);
        m[i][i] = 0;
    }

    // Enqueue BFS visits in the thread pool.
    for (auto i = 0u; i < verticesNumber; ++i) {
        pool.enqueueTask([graph, i, m, &mutexV]() {
            bfsVisit(graph, i, m, mutexV);
        });
    }
}
