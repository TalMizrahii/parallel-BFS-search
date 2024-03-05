#ifndef PARALLELBFS_THREADPOOL_H
#define PARALLELBFS_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include "TaskQueue.h"
#include "bfs.cpp"

using namespace std;

class ThreadPool {
public:
    ThreadPool();

    ~ThreadPool();

    void enqueueTask(const function<void()> &task);

private:
    bool stopBool = false;
    TaskQueue *tasks;
    condition_variable conditionFlag;
    vector<thread> threads;
    mutex queueMutex;
};

#endif //PARALLELBFS_THREADPOOL_H
