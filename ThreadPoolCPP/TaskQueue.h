#ifndef PARALLELBFS_TASKQUEUE_H
#define PARALLELBFS_TASKQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class TaskQueue {
public:
    TaskQueue();

    ~TaskQueue() = default;

    void insert(const std::function<void()> &task);

    std::function<void()> pop();

    bool isEmpty() const;

private:
    queue<std::function<void()>> queue;
    mutable std::mutex queueMutex;
    condition_variable conditionFlag;
};

#endif //PARALLELBFS_TASKQUEUE_H
