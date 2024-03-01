#include "../Graph/graph.h"

void dfs_visit(Graph *graph, vertex v) {
    node *neighborPtr = graph->adjacencyLists[v];

    printf("%d ", v);
    graph->num_visits[v]++;


    while (neighborPtr != NULL) {
        vertex neighbor = neighborPtr->v;

        /* 
         * If the neighbor has not been visited, visit it.
         * Either way, increment the number of visits.
         * NOTE: No tracking of "black" vertices is done here,
         * since we don't care about the order of the visits.
         */
        if (graph->num_visits[neighbor] == 0) {
            dfs_visit(graph, neighbor);
        } else {
            graph->num_visits[neighbor]++;
        }

        neighborPtr = neighborPtr->next;
    }
}

void dfs(Graph *graph) {
    int numVertices = graph->numVertices;

    for (vertex v = 0; v < numVertices; v++) {
        if (graph->num_visits[v] == 0) {
            printf("DFS Traversal: ");
            dfs_visit(graph, v);
            printf("\n");
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

    /* Perform DFS on the graph */
    dfs(graph);    
}