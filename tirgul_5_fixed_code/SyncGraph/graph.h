#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef int vertex;
typedef pthread_mutex_t mutex;

struct node {
    vertex v;
    struct node *next;
};

typedef struct node node;

struct Graph {
    unsigned int numVertices;
    node **adjacencyLists;
    int *num_visits; // Number of times a vertex has been visited
    mutex *num_visits_mutexes; // Mutex for each vertex
};

typedef struct Graph Graph;

/*
 * NOTE: these functions are not safe to use in 
 * a multithreaded environment - they don't make use of mutexes.
 * The only purpose of these functions is to create a graph.
 * Very similar implementation to the one in the regular DFS.
 */

node * createNode(vertex v);

void addEdge(Graph *graph, vertex source, vertex destination);

Graph * createGraph(int vertices);

#endif
