#include "ThreadPool.h"

/**
 * @file ThreadPool.cpp
 * @brief Implementation of the ThreadPool class for concurrent task execution.
 */

/**
 * @brief Constructor for the ThreadPool class.
 * @param graph A pointer to the Graph object associated with the ThreadPool.
 * @details Initializes the ThreadPool with a number of threads equal to the hardware concurrency.
 * Each thread runs a loop waiting for tasks to execute.
 * The ThreadPool is associated with a Graph object to manage concurrent operations on the graph.
 */
ThreadPool::ThreadPool(Graph* graph) : g(graph) {
    size_t num_threads = thread::hardware_concurrency();
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    unique_lock<std::mutex> lock(queueMutex);
                    // Wait for the condition to be satisfied (stopBool becomes true).
                    this->conditionFlag.wait(lock, [this] {
                        return stopBool;
                    });

                    // Check if both stopBool is true and the task queue is empty.
                    if (stopBool && (tasks.empty())) {
                        break;
                    }
                    // Get the task from the front of the queue and remove it.
                    task = move(tasks.front());
                    tasks.pop();
                }
                // Execute the retrieved task.
                task();
            }
        });
    }
}

/**
 * @brief Destructor for the ThreadPool class.
 * @details Signals all threads to stop and waits for them to join.
 * Deletes the associated Graph object.
 */
ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(queueMutex);
        // Set stopBool to true, indicating that threads should stop execution.
        stopBool = true;
    }

    // Notify all waiting threads to wake up.
    conditionFlag.notify_all();

    // Wait for all threads to join before proceeding.
    for (auto &thread : threads) {
        thread.join();
    }
    // Delete the associated Graph object.
    delete this->g;
}

/**
 * @brief Enqueues a task for execution in the ThreadPool.
 * @param task The task to be enqueued for execution.
 * @details Adds a task to the ThreadPool's task queue and notifies one waiting thread to execute the task.
 */
void ThreadPool::enqueueTask(const function<void()> &task) {
    {
        unique_lock<std::mutex> lock(queueMutex);
        // Check if the ThreadPool is not in a stopped state before enqueuing the task.
        if (!stopBool) {
            tasks.emplace(move(task));
        }
    }
    // Notify one waiting thread to execute the enqueued task.
    conditionFlag.notify_one();
}
