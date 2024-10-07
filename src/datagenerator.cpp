#include "datagenerator.h"
#include <iostream>
#include "threadshareddata.h"
#include "data.h"
#include <cstring>

Data data_example;

DataGenerator::DataGenerator(std::shared_ptr<ThreadSharedData> _new_shared_data, unsigned int tick)
    : SharedDataTaskThread(_new_shared_data),
      generation_sleep_duration(1/static_cast<double>(tick))
{
    memset(data_example.buffer, 0xFF, data_example.size);
}

DataGenerator::~DataGenerator()
{
    join();
    std::cout << "DataGenerator::~DataGenerator()" << std::endl;
}

void DataGenerator::process()
{
    while(state() == Running)
    {
        std::unique_lock<std::mutex> lk(_data->_mutex);

        if(_data->dg_flags.is_generation_started)
            _data->_cv.wait(lk, [this]{return _data->shared_flags.is_notified;});
        else
            _data->dg_flags.is_generation_started = true;

        if(_data->fw_flags.is_goal_reached)
        {
            stop();
            continue;
        }

        if(_data->_msg_queue.size() < BUFFER_SIZE)
        {
            std::cout << "posting data..." << std::endl;

            _data->shared_flags.is_pending_data = true;

            if(!_data->fw_flags.is_working)
                _data->shared_flags.is_notified = false;

            _data->_msg_queue.push(    buffer.put(data_example)    );
        }
        else
        {
            std::cerr << "DataGenerator::process() - failed to post data, queue is full" << std::endl;
            abort();
        }

        std::cout << "posting data complete" << std::endl;

        lk.unlock();
        _data->_cv.notify_one();

        std::this_thread::sleep_for(std::chrono::duration<double, std::ratio<1, 1>>(generation_sleep_duration));
    }
}
