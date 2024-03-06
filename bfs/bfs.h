/**
 * @file bfs.h
 * @brief Declaration of the BFS functions for parallel processing.
 */

#ifndef PARALLELBFS_BFS_H
#define PARALLELBFS_BFS_H

#include "../SyncGraph/graph.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief Performs BFS traversal in parallel using a ThreadPool.
     * @param graph A pointer to the Graph object.
     * @param m Pointer to the matrix to store BFS distances.
     */
    void bfs(Graph *graph, int **m);
#ifdef __cplusplus
}
#endif

#endif //PARALLELBFS_BFS_H
