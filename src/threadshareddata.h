#ifndef THREADSHAREDDATA_H
#define THREADSHAREDDATA_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

struct Data;


struct ThreadSharedData
{

    struct SharedFlags
    {
        bool is_pending_data = false;
        bool is_notified = false;
    };

    struct DGFlags
    {
        bool is_generation_started = false;
        bool is_generation_finished = false;
    };

    struct FWFlags
    {
        bool is_working = false;
        bool is_goal_reached = false;
    };

    ThreadSharedData() = default;
    ThreadSharedData(const ThreadSharedData &other) = delete;
    ThreadSharedData& operator=(const ThreadSharedData &other) = delete;


    SharedFlags shared_flags;
    DGFlags     dg_flags;
    FWFlags     fw_flags;

    std::mutex _mutex;
    std::queue<std::shared_ptr<Data>> _msg_queue;
    std::condition_variable _cv;
};

#endif // THREADSHAREDDATA_H
