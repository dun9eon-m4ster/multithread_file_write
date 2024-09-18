#ifndef THREAD_SHARED_DATA_H
#define THREAD_SHARED_DATA_H

#include <queue>
#include <mutex>
#include <condition_variable>

class MsgData;


std::mutex shared_data_mutex;
std::queue<MsgData*> msg_queue;
bool is_pending_data = false;
std::condition_variable cv;



#endif // THREAD_SHARED_DATA_H
