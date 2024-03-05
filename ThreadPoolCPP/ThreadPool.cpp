#include "ThreadPool.h"

ThreadPool::ThreadPool() : tasks(nullptr), stopBool(false) {
    size_t num_threads = thread::hardware_concurrency();
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    this->conditionFlag.wait(lock, [this] {
                        return tasks != nullptr || stopBool;
                    });

                    if (stopBool && (tasks == nullptr || tasks->isEmpty())) {
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
        unique_lock<mutex> lock(queueMutex);
        stopBool = true;
    }

    conditionFlag.notify_all();

    for (auto &thread : threads) {
        thread.join();
    }

}

void ThreadPool::enqueueTask(const function<void()>& task) {
    tasks->insert(task);
}
