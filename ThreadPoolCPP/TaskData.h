#ifndef PARALLELBFS_TASKDATA_H
#define PARALLELBFS_TASKDATA_H
class TaskData {

public:
    TaskData() = default;
    explicit TaskData(int data) : data(data) {};
    ~TaskData() = default;
    int getData();

private:
    int data;
};

#endif //PARALLELBFS_TASKDATA_H
