#ifndef THREADSHAREDDATA_H
#define THREADSHAREDDATA_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>

struct Data;


struct ThreadSharedData
{

    struct SharedFlags
    {
        bool is_pending_data = false;
        bool is_notified = false;
    };

    struct FWData
    {
        std::atomic<bool> is_working{false};
        std::atomic<bool> is_goal_reached{false};
        std::atomic<double> data_record_percent{0};
    };

    ThreadSharedData() = default;
    ThreadSharedData(const ThreadSharedData &other) = delete;
    ThreadSharedData& operator=(const ThreadSharedData &other) = delete;

    SharedFlags shared_flags;
    FWData     fw_data;

    std::mutex _mutex;
    std::queue<std::shared_ptr<Data>> _msg_queue;
    std::condition_variable _cv;
};

#endif // THREADSHAREDDATA_H
