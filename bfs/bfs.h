#ifndef PARALLELBFS_BFS_H
#define PARALLELBFS_BFS_H

#include "../SyncGraph/graph.h"

#ifdef __cplusplus
extern "C" {
#endif
    void bfs(Graph *graph, int **m);
#ifdef __cplusplus
}
#endif
#endif //PARALLELBFS_BFS_H
