#include "filewriter.h"
#include <iostream>
#include "threadshareddata.h"
#include <fstream>
#include "data.h"

FileWriter::FileWriter(std::shared_ptr<ThreadSharedData> _new_shared_data, const size_t &_new_data_record_goal)
    : SharedDataTaskThread(_new_shared_data),
      data_recorded(0),
      data_record_goal(_new_data_record_goal)
{

}

FileWriter::~FileWriter()
{
    join();
    std::cout << "FileWriter::~FileWriter()" << std::endl;
}

void FileWriter::process()
{
    std::ofstream file;
    file.open("test.txt", std::ios_base::app);
    if(!file.is_open())
    {
        std::cerr << "FileWriter::process() - file is not open" << std::endl;
        abort();
    }


    std::queue<std::shared_ptr<Data>> tmp_queue;

    while(state() == Running)
    {
        std::unique_lock<std::mutex> lk(_data->_mutex);

        _data->_cv.wait(lk, [this]{return _data->shared_flags.is_pending_data;});


        std::shared_ptr<Data> _new_data(nullptr);
        if(!_data->_msg_queue.empty())
        {
            _new_data = _data->_msg_queue.front();
            _data->_msg_queue.pop();
        }


        _data->shared_flags.is_pending_data = false;
        _data->shared_flags.is_notified = true;
        _data->fw_data.is_working.store(true, std::memory_order_relaxed);


        lk.unlock();
        _data->_cv.notify_one();


        if(_new_data)
        {
            file.write(reinterpret_cast<char*>(_new_data->buffer), _new_data->size);
            data_recorded++;
            _data->fw_data.data_record_percent.store(data_recorded/static_cast<double>(data_record_goal) * 100, std::memory_order_relaxed);
            if(data_recorded == data_record_goal)
            {
                _data->fw_data.is_goal_reached = true;
                stop();
            }
        }


        if(!_data->fw_data.is_goal_reached.load(std::memory_order_relaxed))
            _data->fw_data.is_working.store(false);
    }
}
