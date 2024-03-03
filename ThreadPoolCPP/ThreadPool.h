#ifndef PARALLELBFS_THREADPOOL_H
#define PARALLELBFS_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include "TaskQueue.h"

using namespace std;

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads = thread::hardware_concurrency());
    ~ThreadPool();

    void setTaskQueue(TaskQueue* queue);

private:
    bool stopBool = false;
    TaskQueue* tasks;
    condition_variable conditionFlag;
    vector<thread> threads;
    mutex QueueMutex;
};

#endif //PARALLELBFS_THREADPOOL_H
