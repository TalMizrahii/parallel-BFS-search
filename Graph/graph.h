#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef int vertex;

struct node {
    vertex v;
    struct node *next;
};

typedef struct node node;

struct Graph {
    unsigned numVertices;
    node **adjacencyLists;
    int *num_visits; // Number of times a vertex has been visited
};

typedef struct Graph Graph;

node * createNode(vertex v);

void addEdge(Graph *graph, vertex source, vertex destination);

Graph * createGraph(int numVertices);

#endif
