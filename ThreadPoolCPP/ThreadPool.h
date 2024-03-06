/**
 * @file ThreadPool.h
 * @brief Declaration of the ThreadPool class for concurrent task execution.
 */

#ifndef PARALLELBFS_THREADPOOL_H
#define PARALLELBFS_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include "../bfs/bfs.h"

using namespace std;

/**
 * @class ThreadPool
 * @brief Manages a pool of threads for concurrent task execution.
 */
class ThreadPool {
public:
    /**
     * @brief Constructor for the ThreadPool class.
     * @param g A pointer to the Graph object associated with the ThreadPool.
     */
    ThreadPool(Graph * g);

    /**
     * @brief Destructor for the ThreadPool class.
     * @details Signals all threads to stop and waits for them to join.
     */
    ~ThreadPool();

    /**
     * @brief Enqueues a task for execution in the ThreadPool.
     * @param task The task to be enqueued for execution.
     */
    void enqueueTask(const function<void()> &task);

private:
    bool stopBool = false; /**< A boolean flag indicating whether the ThreadPool should stop execution. */
    queue<function<void()> > tasks; /**< A queue to store tasks for execution by the ThreadPool. */
    condition_variable conditionFlag; /**< A condition variable for signaling and synchronization. */
    vector<thread> threads; /**< A vector to store thread objects in the ThreadPool. */
    mutex queueMutex; /**< A mutex for ensuring thread-safe access to the task queue. */
    Graph *g; /**< A pointer to the Graph object associated with the ThreadPool. */
};

#endif //PARALLELBFS_THREADPOOL_H
