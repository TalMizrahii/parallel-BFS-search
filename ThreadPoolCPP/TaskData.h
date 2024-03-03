#ifndef PARALLELBFS_TASKDATA_H
#define PARALLELBFS_TASKDATA_H

#include <iostream>

using namespace std;
class TaskData {
public:
    TaskData() = default;
    explicit TaskData(int Data);
    ~TaskData() = default;
    int getData();

private:
    int data;
};

#endif //PARALLELBFS_TASKDATA_H
