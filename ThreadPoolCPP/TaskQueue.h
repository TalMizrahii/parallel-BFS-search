#ifndef PARALLELBFS_TASKQUEUE_H
#define PARALLELBFS_TASKQUEUE_H

#include "TaskData.h"
#include <queue>
#include <mutex>
#include <condition_variable>



using namespace std;
class TaskQueue {
public:
    TaskQueue() = default;

    void initQueue();
    ~TaskQueue() = default;

    void insert(TaskData td);

    TaskData pop();

    bool isEmpty() const;

private:
    queue<TaskData> queue_;
    mutable mutex queueMutex_;
    condition_variable conditionFlag_;
};


#endif //PARALLELBFS_TASKQUEUE_H
