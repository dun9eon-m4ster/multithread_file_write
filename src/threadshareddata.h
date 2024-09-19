#ifndef THREADSHAREDDATA_H
#define THREADSHAREDDATA_H

#include <queue>
#include <mutex>
#include <condition_variable>


class MsgData;


struct ThreadSharedData
{
    enum Flags
    {
        None = 0x0,
        DataIsPosting   = 0x01,
        DataIsTaking    = 0x02,
        PendingData     = 0x04,
    };

    ThreadSharedData();
    ThreadSharedData(const ThreadSharedData &other) = delete;
    ThreadSharedData& operator=(const ThreadSharedData &other) = delete;

    void setFlag(const Flags &_new_flags, bool on = true);
    bool isFlag(const Flags &_flags_to_check) const;



    Flags flags;

    std::mutex _mutex;
    std::queue<MsgData*> _msg_queue;
    std::condition_variable _cv;
};

#endif // THREADSHAREDDATA_H
