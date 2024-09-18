#include "taskthread.h"
#include <iostream>

TaskThread::TaskThread()
    : _state(Waiting)
{}

void TaskThread::start()
{
    if(_state != Waiting)
        return;

    auto thread_function = [this]()
    {
        this->_state = Running;
        this->process();
        this->_state = Waiting;
    };

    thread = std::thread(thread_function);
}

void TaskThread::process()
{
//    while( state() == Running)
//    {
        //do work
//        if(condition)
//            stop();
//    }
}

void TaskThread::stop()
{
    _state = Exiting;
}

TaskThread::State TaskThread::state() const
{
    return _state;
}

void TaskThread::join()
{
    if(thread.joinable())
        thread.join();
}
