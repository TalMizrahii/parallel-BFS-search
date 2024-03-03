#include "TaskQueue.h"

void TaskQueue::insert(TaskData td) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        queue.emplace(td);
    }
    conditionFlag.notify_one();
}

TaskData TaskQueue::pop() {
    std::unique_lock<std::mutex> lock(queueMutex);
    conditionFlag.wait(lock, [this] { return !queue.empty(); });

    TaskData data = queue.front();
    queue.pop();

    return data;
}

bool TaskQueue::isEmpty() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    return queue.empty();
}

