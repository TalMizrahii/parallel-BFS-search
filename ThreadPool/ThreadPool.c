#include "ThreadPool.h"
#include "TaskQueue.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void runThreadPool(ThreadPool *tp) {
    /* As long as there are tasks in the queue or running threads... */
    while (!isEmpty(tp->q) || tp->runningThreads > 0) {
        /* If we are not past max number of threads */
        if (tp->runningThreads < tp->maxThreads && !isEmpty(tp->q)) {
            /* Run task */
            TaskData data = pop(tp->q);

            pthread_t thread;
            if (pthread_create(&thread, NULL, data.function, data.args)) {
                perror("pthread_create failed.");
                exit(1);
            } else {
                ++(tp->runningThreads);
            }
        }
    }
}