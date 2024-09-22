#include "filewriter.h"
#include <iostream>
#include "threadshareddata.h"
#include <fstream>
#include "data.h"

FileWriter::FileWriter(std::shared_ptr<ThreadSharedData> _new_shared_data)
    : SharedDataTaskThread(_new_shared_data)
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
        std::cout << "FileWriter::process() - file is not open" << std::endl;
        abort();
    }


    std::queue<std::shared_ptr<Data>> tmp_queue;

    while(state() == Running)
    {
        std::unique_lock<std::mutex> lk(_data->_mutex);

        _data->_cv.wait(lk, [this]{return _data->shared_flags.is_pending_data;});

        std::cout << "accessing data..." << std::endl;
        while(!_data->_msg_queue.empty())
        {
            tmp_queue.push(_data->_msg_queue.front());
            _data->_msg_queue.pop();
        }

        _data->shared_flags.is_pending_data = false;
        _data->shared_flags.is_notified = true;
        _data->fw_flags.is_working = true;

        if(_data->dg_flags.is_generation_finished)
            stop();

        std::cout << "accessing data complete" << std::endl;
        lk.unlock();
        _data->_cv.notify_one();

        while(!tmp_queue.empty())
        {
            auto data = tmp_queue.front();
            tmp_queue.pop();
            file.write(reinterpret_cast<char*>(data->buffer), data->size);
        }

        _data->fw_flags.is_working = false;
    }
}
