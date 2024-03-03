#include "TaskQueue.h"

void TaskQueue::initQueue() {

}


void TaskQueue::insert(TaskData td) {
    {
        std::lock_guard<std::mutex> lock(queueMutex_);
        queue_.emplace(td);
    }
    conditionFlag_.notify_one();
}

TaskData TaskQueue::pop() {
    std::unique_lock<std::mutex> lock(queueMutex_);
    conditionFlag_.wait(lock, [this] { return !queue_.empty(); });

    TaskData data = queue_.front();
    queue_.pop();

    return data;
}

bool TaskQueue::isEmpty() const {
    std::lock_guard<std::mutex> lock(queueMutex_);
    return queue_.empty();
}

