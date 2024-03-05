#include "ThreadPool.h"
#include "bfs.cpp"

ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([this] {
            while (true) {
                TaskData td;
                {
                    unique_lock<mutex> lock(QueueMutex);
                    conditionFlag.wait(lock, [this] {
                        return !tasks->isEmpty() || stopBool;
                    });

                    if (stopBool && tasks->isEmpty()) {
                        return;
                    }

                    // Get the next task from the queue
                    TaskData td = tasks->pop();

                }
                bfs_visit(td);
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(QueueMutex);
        stopBool = true;
    }

    conditionFlag.notify_all();

    for (auto &thread : threads) {
        thread.join();
    }
}

void ThreadPool::setTaskQueue(TaskQueue *queue) {
    this->tasks = queue;
}
