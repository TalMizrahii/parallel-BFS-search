#ifndef PARALLELBFS_TASKQUEUE_H
#define PARALLELBFS_TASKQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "TaskData.h"



using namespace std;
class TaskQueue {
public:
    TaskQueue() = default;
    ~TaskQueue() = default;

    void insert(TaskData td);

    TaskData pop();

    bool isEmpty() const;

private:
    queue<TaskData> queue;
    mutable mutex queueMutex;
    condition_variable conditionFlag;
};


#endif //PARALLELBFS_TASKQUEUE_H
