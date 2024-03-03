#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([this] {
            while (true) {
                function<void()> task;
                {
                    unique_lock<mutex> lock(QueueMutex);
                    conditionFlag.wait(lock, [this] {
                        return !tasks->isEmpty() || stopBool;
                    });

                    if (stopBool && tasks->isEmpty()) {
                        return;
                    }

                    task = tasks->pop();
                }

                task();
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
