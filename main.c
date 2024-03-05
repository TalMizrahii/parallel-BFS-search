#include "SyncGraphOld/graph.h"
#include <stdlib.h>
#include <stdio.h>

extern void bfs(Graph *graph, int **m);

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

    /* Create shortest paths matrix */
    int **m = (int **) malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; i++) {
        m[i] = (int *) malloc(numVertices * sizeof(int));
    }

    /* Perform DFS on the graph */
    bfs(graph, m);

    /* Print matrix */
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", m[i][j]);
        }
        putchar('\n');
    }

    /* Free memory */
    for (int i = 0; i < numVertices; i++) {
        free(m[i]);
    }
    
    free(m);
}