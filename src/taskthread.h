#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include <thread>
#include <memory>

struct ThreadSharedData;

class TaskThread
{
public:
    enum State
    {
        Waiting = 0,
        Running,
        Exiting
    };

    TaskThread();
    TaskThread(const TaskThread &other) = delete;
    TaskThread& operator=(const TaskThread &other) = delete;
    virtual ~TaskThread() = default;

    void start();
    void stop();
    State state() const;

protected:
    void join();

private:
    virtual void process();
    State _state;
    std::thread thread;
};

class SharedDataTaskThread : public TaskThread
{
public:
    SharedDataTaskThread(std::shared_ptr<ThreadSharedData> _new_shared_data);

protected:
    std::shared_ptr<ThreadSharedData> _data;
};

#endif // TASKTHREAD_H
