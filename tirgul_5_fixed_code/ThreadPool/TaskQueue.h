#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <pthread.h>

struct TaskData {
    void * (*function)(void *);
    void *args;
};

typedef struct TaskData TaskData;

struct TaskDataNode {
    TaskData data;
    struct TaskDataNode *next;
};

typedef struct TaskDataNode TaskDataNode;

struct TaskQueue {
    TaskDataNode *start;
    TaskDataNode *end;
    pthread_mutex_t mutex;
};

typedef struct TaskQueue TaskQueue;

void initQueue(TaskQueue *q);

void insert(TaskQueue *q, TaskData td);

TaskData pop(TaskQueue *q);

int isEmpty(TaskQueue *q);

#endif