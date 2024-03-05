#include "bfs.h"
#include <queue>
#include <mutex>
#include <vector>
#include "../ThreadPoolCPP/ThreadPool.h"


void bfsFromVertex(Graph *graph, int startVertex, int **m, std::mutex &m_mtx) {
    // Keeps track of visited vertices to avoid revisiting them
    std::vector<bool> visited(graph->getNumVertices(), false);

    // Queue to manage the BFS traversal. Store pairs of vertex and its depth.
    std::queue<std::pair<int, int>> q;

    // Mark the starting vertex as visited and enqueue it with depth 0
    visited[startVertex] = true;
    q.push({startVertex, 0});

    // Process the queue until it's empty
    while (!q.empty()) {
        // Extract the vertex and its depth from the queue
        int v = q.front().first;
        int depth = q.front().second;
        q.pop();

        // Lock the mutex before accessing the shared matrix
        std::lock_guard<std::mutex> lock(m_mtx);
        // Update the distance of the vertex from the start vertex in the matrix
        m[startVertex][v] = depth;

        // Explore all adjacent vertices
        for (Node *adj = graph->getAdjacencyLists()[v]; adj != nullptr; adj = adj->next) {
            int adjVertex = adj->v;
            // If the adjacent vertex has not been visited, mark it visited and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                // Enqueue the adjacent vertex with a depth incremented by 1
                q.push({adjVertex, depth + 1});

                // Note: As we enqueue each adjacent vertex, we increase the depth by 1.
                // This ensures that vertices enqueued consecutively have a depth difference of at most 1.
                // This is crucial for maintaining the breadth-first nature of the traversal.
            }
        }
    }
}


void bfs(Graph *graph, int **m) {
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


