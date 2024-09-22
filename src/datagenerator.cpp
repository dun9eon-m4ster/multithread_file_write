#include "datagenerator.h"
#include <iostream>
#include "threadshareddata.h"
#include "data.h"
#include <cstring>

static const unsigned long long BUFFER_SIZE = 256;
static_assert (BUFFER_SIZE > 0, "Buffer cannot be zero");

DataGenerator::DataGenerator(std::shared_ptr<ThreadSharedData> _new_shared_data)
    : SharedDataTaskThread(_new_shared_data)
{
    for(unsigned long long i = 0; i < BUFFER_SIZE; i++)
    {
        buffer.push_back(std::shared_ptr<Data>(new Data));
    }

    buffer_iterator = buffer.begin();
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

        std::cout << "posting data..." << std::endl;

        _data->shared_flags.is_pending_data = true;

        if(!_data->fw_flags.is_working)
            _data->shared_flags.is_notified = false;

        memset((*buffer_iterator)->buffer, 0xFF, (*buffer_iterator)->size);
        _data->_msg_queue.push(*buffer_iterator);

        buffer_iterator++;
        if(buffer_iterator == buffer.end())
        {
            _data->dg_flags.is_generation_finished = true;
            stop();
        }

        std::cout << "posting data complete" << std::endl;

        lk.unlock();
        _data->_cv.notify_one();
    }
}
