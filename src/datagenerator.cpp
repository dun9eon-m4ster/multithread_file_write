#include "datagenerator.h"
#include <iostream>
#include "threadshareddata.h"
#include "data.h"
#include <cstring>
#include <iomanip>
#include "progressbar.h"

Data data_example;
double percentage = 0;
ProgressBar bar(20);
bool is_generation_started = false;


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

        if(is_generation_started)
            _data->_cv.wait(lk, [this]{return _data->shared_flags.is_notified;});
        else
            is_generation_started = true;

        if(_data->fw_data.is_goal_reached)
        {
            stop();
            continue;
        }

        if(_data->_msg_queue.size() < BUFFER_SIZE)
        {

            _data->shared_flags.is_pending_data = true;

            if(!_data->fw_data.is_working.load(std::memory_order_relaxed))
                _data->shared_flags.is_notified = false;

            _data->_msg_queue.push(    buffer.put(data_example)    );


            percentage = _data->_msg_queue.size() / static_cast<double>(BUFFER_SIZE) * 100;

            std::cout << "Msg queue load: " << bar.make(percentage)
                      << "         Data record goal: " << bar.make(_data->fw_data.data_record_percent.load(std::memory_order_relaxed)) << std::endl;
        }
        else
        {
            std::cerr << "DataGenerator::process() - failed to post data, queue is full" << std::endl;
            abort();
        }


        lk.unlock();
        _data->_cv.notify_one();

        std::this_thread::sleep_for(std::chrono::duration<double, std::ratio<1, 1>>(generation_sleep_duration));
    }
    is_generation_started = false;
}
