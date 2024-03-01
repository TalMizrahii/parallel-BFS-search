#include "../SyncGraph/graph.h"
#include "../ThreadPool/ThreadPool.h"
#include "../ThreadPool/TaskQueue.h"

struct dfsArgs {
    Graph *graph;
    vertex v;
    ThreadPool *q;
};

typedef struct dfsArgs dfsArgs;

void * parallel_dfs_visit(void *args) {
    /* Extract arguments */
    dfsArgs *data = (dfsArgs *) args;
    Graph *graph = data->graph;
    vertex v = data->v;
    ThreadPool *q = data->q;
    free(data);

    /* Log the visit */
    printf("%d ", v);

    /* Start the visit */
    node *neighborsPtr = graph->adjacencyLists[v];

    while (neighborsPtr != NULL) {
        vertex neighbor = neighborsPtr->v;

        /* Synchronously increment the number of visits for the neighbor */
        pthread_mutex_lock(&graph->num_visits_mutexes[neighbor]);
        int neighborVisits = graph->num_visits[neighbor]++;
        pthread_mutex_unlock(&graph->num_visits_mutexes[neighbor]);

        /* If the neighbor has not been visited, add a new task to the queue */
        if (neighborVisits == 0) {
            dfsArgs *params = malloc(sizeof(dfsArgs));
            params->graph = graph;
            params->v = neighbor;
            params->q = q;
            TaskData td = {parallel_dfs_visit, params};

            insert(q->q, td);
        }

        neighborsPtr = neighborsPtr->next;
    }

    /* Decrement the number of running threads */
    --(q->runningThreads);
}

void parallel_dfs(Graph *graph) {
    int numVertices = graph->numVertices;
    dfsArgs *args;

    /* For each vertex, if it is not visited, perform DFS. */
    for (vertex v = 0; v < numVertices; v++) {
        if (graph->num_visits[v] == 0) {
            printf("\nDFS Traversal: ");

            /* Init thread pool */
            TaskQueue q;
            initQueue(&q);

            ThreadPool pool;
            pool.maxThreads = 4;
            pool.runningThreads = 0;
            pool.q = &q;

            /* Insert the root task to the queue */    
            args = malloc(sizeof(dfsArgs));
            args->graph = graph;
            args->v = v;
            args->q = &pool;

            //pthread_mutex_lock(&graph->num_visits_mutexes[neighbor]);
            graph->num_visits[v]++;
            //pthread_mutex_unlock(&graph->num_visits_mutexes[neighbor]);

            TaskData td = {parallel_dfs_visit, args};
            insert(pool.q, td);
            
            /* Start the tasks */
            runThreadPool(&pool);
        }
    }
}

void main(void) {
    int numVertices, numEdges;

    /* Create graph based on user input */
    printf("Enter Number of Vertices and Edges in the Graph: ");
    scanf("%d%d", &numVertices, &numEdges);
    Graph *graph = createGraph(numVertices);

    printf("Add %d Edges of the Graph \
            (Vertex numbering should be from 0 to %d)\n",
             numEdges, numVertices - 1);

    int source, destination;
    for (int i = 0; i < numEdges; i++) {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }

    /* Perform DFS */
    parallel_dfs(graph);
}