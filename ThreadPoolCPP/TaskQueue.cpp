#include "TaskQueue.h"


TaskQueue::TaskQueue() {
    this->queue = std::queue<std::function<void()>>();
}

void TaskQueue::insert(const std::function<void()> &task) {
    std::lock_guard<std::mutex> lock(this->queueMutex);
    this->queue.push(task);
    this->conditionFlag.notify_one();
}

std::function<void()> TaskQueue::pop() {
    std::unique_lock<std::mutex> lock(this->queueMutex);
    this->conditionFlag.wait(lock, [this] { return !this->queue.empty(); });

    auto task = this->queue.front();
    this->queue.pop();
    return task;
}

bool TaskQueue::isEmpty() const {
    std::lock_guard<std::mutex> lock(this->queueMutex);
    return this->queue.empty();
}

