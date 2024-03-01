#include "TaskQueue.h"
#include <stdlib.h>
#include <stdio.h>

void initQueue(TaskQueue *q) {
    /* Initialize the mutex */
    if (pthread_mutex_init(&(q->mutex), NULL) != 0) {
        perror("mutex init has failed.");
        exit(1);
    }

    /* Init start and end to NULL */
    q->end = q->start = NULL;
}

void insert(TaskQueue *q, TaskData td) {
    /* Create a new node with the given data */
    TaskDataNode *newNode = malloc(sizeof(TaskDataNode));
    newNode->next = NULL;
    newNode->data = td; 

    /* Synchronously insert the new node */
    pthread_mutex_lock(&q->mutex);

    if ((q->end == NULL && q->start != NULL) ||
        (q->end != NULL && q->start == NULL)) {
        perror("'end' and 'start' are not in sync.");
        exit(1);
    }

    if (q->end == NULL) {
        q->start = q->end = newNode;
    } else {
        q->end->next = newNode;
        q->end = q->end->next;
    }

    pthread_mutex_unlock(&q->mutex);
}

TaskData pop(TaskQueue *q) {
    /* Synchronously pop the first element */
    pthread_mutex_lock(&q->mutex);

    if ((q->end == NULL && q->start != NULL) ||
        (q->end != NULL && q->start == NULL)) {
        perror("'end' and 'start' are not in sync.");
        exit(1);
    }

    if (q->start == NULL) {
        perror("cannot pop from an empty queue.");
        exit(1);
    }

    TaskDataNode *popNode = q->start;

    if ((q->start = popNode->next) == NULL) {
        q->end = NULL;
    }

    pthread_mutex_unlock(&q->mutex);

    /* Free the popped node and return the data */
    TaskData output = popNode->data;
    free(popNode);
    return output;
}

int isEmpty(TaskQueue *q) {
    /* Synchronously check if the queue is empty */
    pthread_mutex_lock(&q->mutex);
    int isEmpty = (q->start == NULL);
    pthread_mutex_unlock(&q->mutex);

    /* Return the result */
    return isEmpty;
}
